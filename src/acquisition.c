#include "acquisition.h"
#include "board_pins.h"
#include "grove_bme680.h"
#include "grove_gps_air530z.h"
#include "grove_rtc_ds1307.h"
#include "grove_light.h"

void initialiserCapteursGlobaux(void) {
    // Initialisation des drivers de capteurs
}

MesureMeteo acquerirDonneesMeteo(bool modeEco) {
    MesureMeteo mesure;
    bool capteurRepond = true; // Gestion du timeout (valeur "NA" si false)

    if (capteurRepond) {
        mesure.timestamp = 0; 
        mesure.temperature = 22.0f; 
        mesure.pression = 1013.0f;  
        mesure.humidite = 50.0f;    
        mesure.luminosite = 300.0f; 
        
        if (!modeEco) {
            mesure.latitudeGPS = 48.85f;
            mesure.longitudeGPS = 2.35f;
        } else {
            mesure.latitudeGPS = 0.0f;
            mesure.longitudeGPS = 0.0f;
        }
        mesure.capteurValide = true;
    } else {
        mesure.capteurValide = false; // Déclenchement de la valeur "NA"
    }

    return mesure;
}
