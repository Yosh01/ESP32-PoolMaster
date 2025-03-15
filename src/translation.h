#pragma once

// Define language codes here and add to languages[] in system.cpp
#define POOLMASTER_LOCALE_EN "English"
#define POOLMASTER_LOCALE_FR "Français"

// IMPORTANT! translations are in the order: en, fr
//
// if there is no translation, it will default to en
//
const char * const languages[] = {POOLMASTER_LOCALE_EN,
                                  POOLMASTER_LOCALE_FR};

static constexpr uint8_t NUM_LANGUAGES = sizeof(languages) / sizeof(const char *);


// STRINGS USED IN NEXTION SCREENS (value passed in Nextion main loop when page changed)
MAKE_WORD_TRANSLATION(NXT_ADD, "Add", "Ajout", "", "")
MAKE_WORD_TRANSLATION(NXT_APPLY, "Apply", "Valider", "", "")
MAKE_WORD_TRANSLATION(NXT_OK, "Ok", "Ok", "", "")
MAKE_WORD_TRANSLATION(NXT_CONNECT, "Connect", "Connexion", "", "")
MAKE_WORD_TRANSLATION(NXT_MODE_TITLE, "Modes", "Modes", "", "")
MAKE_WORD_TRANSLATION(NXT_CALIB_TITLE, "Probes Calibration", "Calibration des Sondes", "", "")
MAKE_WORD_TRANSLATION(NXT_CALIB_REFERENCE, "Reference", "Solution", "", "")
MAKE_WORD_TRANSLATION(NXT_CALIB_MEASURED, "Measured", "Mesuré", "", "")
MAKE_WORD_TRANSLATION(NXT_CALIB_PHPROBE, "pH Probe", "Sonde pH", "", "")
MAKE_WORD_TRANSLATION(NXT_CALIB_ORPPROBE, "Orp Probe", "Sonde Orp", "", "")
MAKE_WORD_TRANSLATION(NXT_NEWTANK_TITLE, "New Tank", "Remplissage Bidon", "", "")
MAKE_WORD_TRANSLATION(NXT_NEWTANK_VOL, "Tank Vol. \\r  (Liters)", "Vol. bidon \\r (en litres)", "", "")
MAKE_WORD_TRANSLATION(NXT_NEWTANK_FILL, "Tank Fill (%)", "Remplissage \\r     (en %)", "", "")
MAKE_WORD_TRANSLATION(NXT_ELECTRO_TITLE, "SWG Configuration", "Configuration Electrolyseur", "", "")
MAKE_WORD_TRANSLATION(NXT_ELECTRO_TEMP, "Minimum\\rTemperature", "Température\\rMinimum", "", "")
MAKE_WORD_TRANSLATION(NXT_ELECTRO_DELAY, "Delay Before\\rStart", "Délai Avant\\rDémarrage (min)", "", "")
MAKE_WORD_TRANSLATION(NXT_INFO_TITLE, "System Information", "Information Système", "", "")
MAKE_WORD_TRANSLATION(NXT_INFO_ALARMS, "Alarms", "Alarmes", "", "")
MAKE_WORD_TRANSLATION(NXT_DATE_TITLE, "Set Date/Time", "Réglage Horloge", "", "")

MAKE_WORD_TRANSLATION(NXT_WIFI_TITLE, "Wifi Settings", "Réglages Wifi", "", "")
MAKE_WORD_TRANSLATION(NXT_WIFI_NETWORK, "Network:", "Réseau:", "", "")
MAKE_WORD_TRANSLATION(NXT_WIFI_PASSWORD, "Password:", "Mot de Passe:", "", "")
MAKE_WORD_TRANSLATION(NXT_WIFI_WIFI, "Wifi:", "Wifi:", "", "")
MAKE_WORD_TRANSLATION(NXT_WIFI_IP, "IP:", "IP:", "", "")
MAKE_WORD_TRANSLATION(NXT_WIFI_NOTCONNECTED, "Not Connected", "Non Connecté", "", "")
MAKE_WORD_TRANSLATION(NXT_WIFI_NONETWORKFOUND, "No Network Found", "Aucune Réseau Trouvé", "", "")

MAKE_WORD_TRANSLATION(NXT_MQTT_TITLE, "MQTT Settings", "Configuration MQTT", "", "")
MAKE_WORD_TRANSLATION(NXT_MQTT_SERVER, "Server:", "Serveur:", "", "")
MAKE_WORD_TRANSLATION(NXT_MQTT_LOGIN, "Login:", "Utilisateur:", "", "")
MAKE_WORD_TRANSLATION(NXT_MQTT_PASSWORD, "Password:", "Mot de Passe:", "", "")
MAKE_WORD_TRANSLATION(NXT_MQTT_ID, "ID:", "ID:", "", "")
MAKE_WORD_TRANSLATION(NXT_MQTT_TOPIC, "Topic:", "Topic:", "", "")
MAKE_WORD_TRANSLATION(NXT_MQTT_AUTHENT, "Authentication:", "Authentification:", "", "")
MAKE_WORD_TRANSLATION(NXT_MQTT_STATUS, "Status:", "Etat:", "", "")

MAKE_WORD_TRANSLATION(NXT_LANG_TITLE, "Language Selection", "Sélection de la langue", "", "")

MAKE_WORD_TRANSLATION(NXT_GRAPH_TITLE, "History Graph", "Graphique Historique", "", "")

MAKE_WORD_TRANSLATION(NXT_PHORPTANKS_TITLE, "pH & Chlorine Tanks", "Bidons pH & Chlorine", "", "")
MAKE_WORD_TRANSLATION(NXT_PHORPTANKS_FILLCHL, "Fill Chl", "Remplir Chl", "", "")
MAKE_WORD_TRANSLATION(NXT_PHORPTANKS_FILLPH, "Fill pH", "Remplir pH", "", "")

// HELP MESSAGE
MAKE_WORD_TRANSLATION(NXT_HELP_1_TITLE, "Probe Calibration", "Calibration des Sondes","","")
MAKE_WORD_TRANSLATION(NXT_HELP_1_CONTENT, "Step1: place probe in the reference solutionStep2: enter reference solution nominal value in the field below\\rStep3: wait for the probe reading to stabilize then press OK\\rStep4: if available, press ADD button to add a measurement from another\\rref. solution and repeat steps 1-3 (up to 3 points)\\rStep5: press APPLY to complete calibration", "Etape1: Placer la sonde dans la solution de référence\\rEtape2: Entrer ci-dessous la valeur nominale de la solution de référence\\rEtape3: Attendre que la lecture de la sonde se stabilise et appuyer sur OK\\rEtape4: Si une autre solution de référence est disponible, appuyer sur\\rAJOUTER et répéter les étapes 1-3 (3 solutions max.)\\rEtape5: Appuyer sur VALIDER pour terminer la procédure", "Step1: place probe in the reference solution\\rStep2: enter reference solution nominal value in the field below\\rStep3: wait for the probe reading to stabilize then press OK\\rStep4: if available, press ADD button to add a measurement from another\\rref. solution and repeat steps 1-3 (up to 3 points)\\rStep5: press APPLY to complete calibration|Etape1: Placer la sonde dans la solution de référence\\rEtape2: Entrer ci-dessous la valeur nominale de la solution de référence\\rEtape3: Attendre que la lecture de la sonde se stabilise et appuyer sur OK\\rEtape4: Si une autre solution de référence est disponible, appuyer sur\\rAJOUTER et répéter les étapes 1-3 (3 solutions max.)\\rEtape5: Appuyer sur VALIDER pour terminer la procédure", "","")

// Menus, as displayed on the Nextion screen
MAKE_WORD_TRANSLATION(NXT_MENU_LEFT1,  "  Modes", "  Modes", "  ", "  ")
MAKE_WORD_TRANSLATION(NXT_MENU_LEFT2,  "  pH/Orp", "  pH/Orp", "  ", "  ")
MAKE_WORD_TRANSLATION(NXT_MENU_LEFT3,  "  SWG", "  Electrolyse", "  ", "  ")
MAKE_WORD_TRANSLATION(NXT_MENU_LEFT4,  "  System", "  Système", "  ", "  ")
MAKE_WORD_TRANSLATION(NXT_MENU_LEFT5,  "  ", "  ", "  ", "  ")
MAKE_WORD_TRANSLATION(NXT_MENU_LEFT6,  "  ", "  ", "  ", "  ")
MAKE_WORD_TRANSLATION(NXT_MENU_LEFT7,  "  ", "  ", "  ", "  ")
MAKE_WORD_TRANSLATION(NXT_MENU_LEFT8,  "  ", "  ", "  ", "  ")
MAKE_WORD_TRANSLATION(NXT_MENU_LEFT9,  "  ", "  ", "  ", "  ")
MAKE_WORD_TRANSLATION(NXT_MENU_LEFT10, "  ", "  ", "  ", "  ")
MAKE_WORD_TRANSLATION(NXT_MENU_LEFT11, "  ", "  ", "  ", "  ")
MAKE_WORD_TRANSLATION(NXT_MENU_LEFT12, "  ", "  ", "  ", "  ")


MAKE_WORD_TRANSLATION(NXT_SUBMENU1,  "Auto Filtering Mode", "Mode Filtration Automatique", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU2,  "Winter Mode", "Hivernage", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU3,  "pH Auto Regulation", "Régulation Auto pH", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU4,  "Orp Auto Régulation", "Régulation Auto Orp", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU5,  "", "", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU6,  "", "", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU7,  "", "", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU8,  "Calibrate Probes", "Calibration des Sondes", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU9,  "Tank Status", "Etat des Bidons", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU10, "", "", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU11, "", "", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU12, "", "", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU13, "", "", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU14, "", "", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU15, "Salt Water Generator Mode", "Mode Electrolyse", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU16, "SWG Configuration", "Configuration Electrolyse", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU17, "", "", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU18, "", "", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU19, "", "", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU20, "", "", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU21, "", "", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU22, "Language", "Langue", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU23, "Clear Current Alarm(s)", "Effacer les Alarmes", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU24, "System Info", "Info Système", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU25, "Set Date/Time", "Réglage Horloge", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU26, "Wifi Settings", "Réglages Wifi", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU27, "MQTT Settings", "Réglages MQTT", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU28, "", "", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU29, "", "", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU30, "", "", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU31, "", "", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU32, "", "", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU33, "", "", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU34, "", "", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU35, "", "", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU36, "", "", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU37, "", "", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU38, "", "", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU39, "", "", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU40, "", "", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU41, "", "", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU42, "", "", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU43, "", "", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU44, "", "", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU45, "", "", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU46, "", "", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU47, "", "", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU48, "", "", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU49, "", "", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU50, "", "", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU51, "", "", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU52, "", "", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU53, "", "", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU54, "", "", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU55, "", "", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU56, "", "", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU57, "", "", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU58, "", "", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU59, "", "", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU60, "", "", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU61, "", "", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU62, "", "", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU63, "", "", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU64, "", "", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU65, "", "", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU66, "", "", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU67, "", "", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU68, "", "", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU69, "", "", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU70, "", "", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU71, "", "", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU72, "", "", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU73, "", "", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU74, "", "", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU75, "", "", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU76, "", "", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU77, "", "", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU78, "", "", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU79, "", "", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU80, "", "", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU81, "", "", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU82, "", "", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU83, "", "", "", "")
MAKE_WORD_TRANSLATION(NXT_SUBMENU84, "", "", "", "")

