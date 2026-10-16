#include "acquisition.h"
#include "lib/cesi_grove/include/grove_bme680.h"
#include "lib/cesi_grove/include/grove_gps_air530z.h"
#include "lib/cesi_grove/include/grove_rtc_ds1307.h"
#include "lib/cesi_grove/include/grove_light.h"

void initialiserCapteursGlobaux(void) {
    // Initialisation des différents capteurs Grove
}

MesureMeteo acquerirDonneesMeteo(bool modeEco) {
    MesureMeteo mesure;
    
    // Test de réponse avec gestion du timeout (valeur "NA" si échec)
    bool capteurRepond = true; // Remplacer par la lecture réelle du driver

    if (capteurRepond) {
        mesure.temperature = 21.0f; // Valeur lue via grove_bme680
        mesure.pression = 1013.0f;
        mesure.humidite = 50.0f;
        mesure.luminosite = 300.0f;
        mesure.capteurValide = true;
    } else {
        mesure.capteurValide = false; // Déclenche la valeur "NA"
    }

    return mesure;
}
