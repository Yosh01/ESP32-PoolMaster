// Supervisory task

#include <Arduino.h>                // Arduino framework
#include "Config.h"
#include "PoolMaster.h"
#ifdef SMTP
#include <ESP_Mail_Client.h>
#endif
#ifdef ELEGANT_OTA
static WiFiClient wificlient;
AsyncWebServer server(80);
#endif

#ifdef SMTP
SMTPSession smtp;
Session_Config config;
SMTP_Message message;
#endif
// Functions prototypes

void readLocalTime(void);
bool saveParam(const char*,uint8_t );
bool saveParam(const char*,bool );
bool saveParam(const char*,unsigned long );
bool saveParam(const char*,double );
void SetPhPID(bool);
void SetOrpPID(bool);
void mqttErrorPublish(const char*);
void PublishSettings(void);
void UpdateTFT(void);
void SetFullyLoaded(void);
void stack_mon(UBaseType_t&);
#ifdef SMTP
void smtpCallback(SMTP_Status);
bool SMTP_Connect(void);
void Send_Email(void);
#endif

void PoolMaster(void *pvParameters)
{
  bool DoneForTheDay = false;                     // Reset actions done once per day
  bool d_calc = false;                            // Filtration duration computed

  static UBaseType_t hwm=0;                       // free stack size
  #ifdef SMTP
  MailClient.networkReconnect(true);
  #ifndef SILENT_MODE
    smtp.debug(1);
  #endif
  smtp.callback(smtpCallback);
  config.server.host_name = SMTP_HOST;
  config.server.port = SMTP_PORT;
  config.login.email = AUTHOR_LOGIN;
  config.login.password = AUTHOR_PASSWORD;
  config.login.user_domain = "127.0.0.1";

  message.sender.name = F("PoolMaster");
  message.sender.email = AUTHOR_EMAIL;
  message.subject = F("PoolMaster Event");
  message.addRecipient(F("Home"), RECIPIENT_EMAIL);
  message.text.charSet = "us-ascii";
  message.text.transfer_encoding = Content_Transfer_Encoding::enc_7bit;
  message.priority = esp_mail_smtp_priority_low;
  message.response.notify = esp_mail_smtp_notify_success | esp_mail_smtp_notify_failure | esp_mail_smtp_notify_delay;
  #endif
  while(!startTasks);
  vTaskDelay(DT3);                                // Scheduling offset 

  esp_task_wdt_add(nullptr);
  TickType_t period = PT3;  
  TickType_t ticktime = xTaskGetTickCount(); 

  #ifdef CHRONO
  unsigned long td;
  int t_act=0,t_min=999,t_max=0;
  float t_mean=0.;
  int n=1;
  #endif

  for(;;)
  {  
    // reset watchdog
    esp_task_wdt_reset();

    #ifdef CHRONO
    td = millis();
    #endif    

    // Handle OTA update
    ArduinoOTA.handle();

#ifdef ELEGANT_OTA
    //server.handleClient();
    ElegantOTA.loop();
#endif

    //update pumps & relays
    FiltrationPump.loop();
    PhPump.loop();
    ChlPump.loop();
    RobotPump.loop(); 
    SWG.loop();

    //reset time counters at midnight and send sync request to time server
    if (hour() == 0 && !DoneForTheDay)
    {
        //First store current Chl and Acid consumptions of the day in Eeprom
        storage.AcidFill = PhPump.GetTankFill();
        storage.ChlFill = ChlPump.GetTankFill();
        saveParam("AcidFill", storage.AcidFill);
        saveParam("ChlFill", storage.ChlFill);

        FiltrationPump.ResetUpTime();
        PhPump.ResetUpTime();
        PhPump.SetTankFill(storage.AcidFill);
        ChlPump.ResetUpTime();
        ChlPump.SetTankFill(storage.ChlFill);
        RobotPump.ResetUpTime();
        SWG.ResetUpTime();

        //EmergencyStopFiltPump = false;
        d_calc = false;
        DoneForTheDay = true;
        cleaning_done = false;

        readLocalTime();
        setTime(timeinfo.tm_hour,timeinfo.tm_min,timeinfo.tm_sec,timeinfo.tm_mday,timeinfo.tm_mon+1,timeinfo.tm_year-100);

    }
    else if(hour() == 1)
    {
        DoneForTheDay = false;
    }

    // Compute next Filtering duration and start/stop hours at 15:00 (to filter during the hotest period of the day)
    // Wait at least 5mn after filtration start in order to let the temperature stabilizes in pipes, and to avoid
    // taking into account not yet measured temperature if the system starts at 15:xx. 
    // Depending on water temperature, the filtration duration is either 2 hours, temp/3 or temp/2 hours.
    #ifdef DEBUG
    if (second() == 0 && (millis() - FiltrationPump.LastStartTime) > 300000 && !d_calc)
    #else
    if (hour() == 15 && (millis() - FiltrationPump.LastStartTime) > 300000 && !d_calc)
    #endif
    {
        if (storage.WaterTemp < storage.WaterTempLowThreshold){
            storage.FiltrationDuration = 2;}
        else if (storage.WaterTemp >= storage.WaterTempLowThreshold && storage.WaterTemp < storage.WaterTemp_SetPoint){
            storage.FiltrationDuration = round(storage.WaterTemp / 3.);}
        else if (storage.WaterTemp >= storage.WaterTemp_SetPoint){
            storage.FiltrationDuration = round(storage.WaterTemp / 2.);}
    
        storage.FiltrationStart = 15 - (int)round(storage.FiltrationDuration / 2.);
        if (storage.FiltrationStart < storage.FiltrationStartMin)
        storage.FiltrationStart = storage.FiltrationStartMin;    
        storage.FiltrationStop = storage.FiltrationStart + storage.FiltrationDuration;
        if (storage.FiltrationStop > storage.FiltrationStopMax)
        storage.FiltrationStop = storage.FiltrationStopMax;

        saveParam("FiltrStart",storage.FiltrationStart);  
        saveParam("FiltrStop",storage.FiltrationStop);  

        Debug.print(DBG_INFO,"Filtration duration: %dh",storage.FiltrationDuration);
        Debug.print(DBG_INFO,"Start: %dh - Stop: %dh",storage.FiltrationStart,storage.FiltrationStop);

        PublishSettings();

        d_calc = true;
    }
    #ifdef DEBUG
    if(second() == 30 && d_calc) d_calc = false;
    #endif


/* ******************************************* 
    START OF MAIN POOLMASTER AUTOMATION LOGIC
   ******************************************* */
  if (!FiltrationPump.IsRunning())  //Filtration Pump NOT Running
  {
    // Filtration pump is not running, check conditions to start
    if ((storage.AutoMode && hour() >= storage.FiltrationStart && hour() < storage.FiltrationStop && !PSIError ) ||
        (storage.WinterMode && storage.AirTemp < -2.0 && !PSIError))
      FiltrationPump.Start();
  } else {  //Filtration Pump Running

    // Check over and under pressure alarms
    if ((((millis() - FiltrationPump.LastStartTime) > 180000) && (storage.PSIValue < storage.PSI_MedThreshold)) ||
        (storage.PSIValue > storage.PSI_HighThreshold))
    {
      PSIError = true;
      mqttErrorPublish("{\"PSI Error\":1}");
    }

    // Check outside Winter Mode tasks
    if (!storage.WinterMode) // NOT Winter Mode
    {
      //start cleaning robot for ROBOT_DURATION minutes, ROBOT_DELAY minutes after filtration start
      if (storage.AutoMode && !RobotPump.IsRunning() &&
          ((millis() - FiltrationPump.LastStartTime) / 1000 / 60) >= ROBOT_DELAY &&
          !cleaning_done)
      {
          RobotPump.Start();
          Debug.print(DBG_INFO,"Robot Start %d mn after Filtration",0);   
      }
      if(RobotPump.IsRunning() && storage.AutoMode && ((millis() - RobotPump.LastStartTime) / 1000 / 60) >= ROBOT_DURATION)
      {
          RobotPump.Stop();
          cleaning_done = true;
          Debug.print(DBG_INFO,"Robot Stop after: %d mn",(int)(millis()-RobotPump.LastStartTime)/1000/60);
      }

      // pH Regulation tasks
      if (storage.pHAutoMode)
      {
        if (!PhPID.GetMode() && ((millis() - FiltrationPump.LastStartTime) / 1000 / 60 >= storage.DelayPIDs)) 
            SetPhPID(true);
      }

      // Orp Regulation tasks
      if (storage.OrpAutoMode)
      {
        // Standard Orp Injection
        if (!OrpPID.GetMode() && ((millis() - FiltrationPump.LastStartTime) / 1000 / 60 >= storage.DelayPIDs))
          SetOrpPID(true);

        // Electyrolyse is activated
        if (storage.ElectrolyseMode)
          if (!SWG.IsRunning()) //SWG NOT Running
            if ((storage.OrpValue <= storage.Orp_SetPoint*0.9) && 
                (storage.WaterTemp >= (double)storage.SecureElectro) && 
                (millis() - FiltrationPump.LastStartTime)/ 1000 / 60 >= (unsigned long)storage.DelayElectro)
              SWG.Start();
          else  //SWG Running
            if (storage.OrpValue >= storage.Orp_SetPoint*1.05)
              SWG.Stop();

      }
    } else {// Winter Mode (nothing to do)
    }

    // Conditions to stop filtration pump
    if (storage.AirTemp > 2.0)   // Do not stop if temp is below +2°C
      if ((storage.AutoMode && (hour() >= storage.FiltrationStop || hour() < storage.FiltrationStart)) ||
          (PSIError))
        FiltrationPump.Stop();
  } // End of Filtration Pimp IS Running

/* ******************************************* 
    END OF MAIN POOLMASTER AUTOMATION LOGIC
   ******************************************* */

    //UPdate Nextion TFT
    UpdateTFT();

    #ifdef SMTP
    //Send email if alarm(s) occured
    Send_Email();
    #endif

    #ifdef CHRONO
    t_act = millis() - td;
    if(t_act > t_max) t_max = t_act;
    if(t_act < t_min) t_min = t_act;
    t_mean += (t_act - t_mean)/n;
    ++n;
    Debug.print(DBG_INFO,"[PoolMaster] td: %d t_act: %d t_min: %d t_max: %d t_mean: %4.1f",td,t_act,t_min,t_max,t_mean);
    #endif 

    stack_mon(hwm);
    vTaskDelayUntil(&ticktime,period);
    SetFullyLoaded();
  }
}

//Enable/Disable pH PID
void SetPhPID(bool Enable)
{
  if (Enable)
  {
    //Start PhPID
    PhPump.ClearErrors();
    storage.PhPIDOutput = 0.0;
    storage.PhPIDwindowStartTime = millis();
    PhPID.SetMode(AUTOMATIC);
    storage.Ph_RegulationOnOff = 1;
  }
  else
  {
    //Stop PhPID
    PhPID.SetMode(MANUAL);
    storage.Ph_RegulationOnOff = 0;
    storage.PhPIDOutput = 0.0;
    PhPump.Stop();
  }
}

//Enable/Disable Orp PID
void SetOrpPID(bool Enable)
{
  if (Enable)
  {
    //Start OrpPID
    ChlPump.ClearErrors();
    storage.OrpPIDOutput = 0.0;
    storage.OrpPIDwindowStartTime = millis();
    OrpPID.SetMode(AUTOMATIC);
    storage.Orp_RegulationOnOff = 1;

  }
  else
  {
    //Stop OrpPID
    OrpPID.SetMode(MANUAL);
    storage.Orp_RegulationOnOff = 0;
    storage.OrpPIDOutput = 0.0;
    ChlPump.Stop();
  }
}

#ifdef SMTP
bool SMTP_Connect(){
  Debug.print(DBG_DEBUG,"SMTP Connection starts");
  if (!smtp.connect(&config)){
    Debug.print(DBG_ERROR,"SMTP Connection error, Status Code: %d, Error Code: %d, Reason: %s", smtp.statusCode(), smtp.errorCode(), smtp.errorReason().c_str());
    return false;
  } else Debug.print(DBG_INFO,"SMTP Connected");
  if (!smtp.isLoggedIn()) Debug.print(DBG_ERROR,"Not yet logged in.");
  else{
    if (smtp.isAuthenticated()) Debug.print(DBG_INFO,"SMTP Successfully logged in.");
    else Debug.print(DBG_ERROR,"SMTP Connected with no Auth.");
  }
  return true;
}

void Send_Email(){

    char texte[80];
    static bool notif_sent[5] = {0,0,0,0,0};

    if(PSIError)
    {
      if(!notif_sent[0])
      {
        sprintf(texte,"Water pressure alert: %4.2fbar",storage.PSIValue);
        message.text.content = texte;
        if(SMTP_Connect()){   
          if(!MailClient.sendMail(&smtp, &message))
            Debug.print(DBG_ERROR,"Error, Status Code: %d, Error Code: %d, Reason: %s", smtp.statusCode(), smtp.errorCode(), smtp.errorReason().c_str());     
          else notif_sent[0] = true;
        }
      }    
    } else notif_sent[0] = false;

    if(!ChlPump.TankLevel())
    {
      if(!notif_sent[1])
      {
        sprintf(texte,"Chlorine level LOW: %3.0f %",ChlPump.GetTankFill());
        message.text.content = texte;
        if(SMTP_Connect()){
          if(!MailClient.sendMail(&smtp, &message))
            Debug.print(DBG_ERROR,"Error, Status Code: %d, Error Code: %d, Reason: %s", smtp.statusCode(), smtp.errorCode(), smtp.errorReason().c_str());    
          else notif_sent[1] = true;
        }  
      }
    } else notif_sent[1] = false;

    if(!PhPump.TankLevel())
    {
      if(!notif_sent[2])
      {
        sprintf(texte,"Acid level LOW: %3.0f %",PhPump.GetTankFill());
        message.text.content = texte;
        if(SMTP_Connect()){ 
          if(!MailClient.sendMail(&smtp, &message))
            Debug.print(DBG_ERROR,"Error, Status Code: %d, Error Code: %d, Reason: %s", smtp.statusCode(), smtp.errorCode(), smtp.errorReason().c_str());    
          else notif_sent[2] = true;
        }  
      }

    } else notif_sent[2] = false;

    if(ChlPump.UpTimeError)
    {
      if(!notif_sent[3])
      {
        sprintf(texte,"Chlorine pump uptime: %2.0fmn",round(ChlPump.UpTime/60000.));
        message.text.content = texte; 
        if(SMTP_Connect()){       
          if(!MailClient.sendMail(&smtp, &message))
            Debug.print(DBG_ERROR,"Error, Status Code: %d, Error Code: %d, Reason: %s", smtp.statusCode(), smtp.errorCode(), smtp.errorReason().c_str());    
          else notif_sent[3] = true;
        }  
      }
    } else notif_sent[3] = false;

    if(PhPump.UpTimeError)
    {
      if(!notif_sent[4])
      {
        sprintf(texte,"Acid pump uptime: %2.0fmn",round(PhPump.UpTime/60000.));
        message.text.content = texte;
        if(SMTP_Connect()){
          if(!MailClient.sendMail(&smtp, &message))
            Debug.print(DBG_ERROR,"Error, Status Code: %d, Error Code: %d, Reason: %s", smtp.statusCode(), smtp.errorCode(), smtp.errorReason().c_str());    
          else notif_sent[4] = true;
        }  
      }
    } else notif_sent[4] = false; 
}

/* Callback function to get the Email sending status */
void smtpCallback(SMTP_Status status){
  /* Print the current status */
  Debug.print(DBG_INFO,"Email send status: %d",status.info());

  /* Print the sending result */
  if (status.success()){
    Debug.print(DBG_INFO,"Message sent success: %d", status.completedCount());
    Debug.print(DBG_INFO,"Message sent failed: %d", status.failedCount());

    for (size_t i = 0; i < smtp.sendingResult.size(); i++)
    {
      /* Get the result item */
      SMTP_Result result = smtp.sendingResult.getItem(i);

      // In case, ESP32, ESP8266 and SAMD device, the timestamp get from result.timestamp should be valid if
      // your device time was synched with NTP server.
      // Other devices may show invalid timestamp as the device time was not set i.e. it will show Jan 1, 1970.
      // You can call smtp.setSystemTime(xxx) to set device time manually. Where xxx is timestamp (seconds since Jan 1, 1970)
      
      Debug.print(DBG_INFO,"Message No: %d", i + 1);
      Debug.print(DBG_INFO,"Status: %s", result.completed ? "success" : "failed");
      Debug.print(DBG_INFO,"Date/Time: %s", MailClient.Time.getDateTimeString(result.timestamp, "%B %d, %Y %H:%M:%S").c_str());
      Debug.print(DBG_INFO,"Recipient: %s", result.recipients.c_str());
      Debug.print(DBG_INFO,"Subject: %s", result.subject.c_str());
    }

    // Clear sending result as the memory usage will grow up.
    smtp.sendingResult.clear();
  }
}
#endif