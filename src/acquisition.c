#include "acquisition.h"
#include "grove_bme680.h"
#include "grove_gps_air530z.h"
#include "grove_light.h"
#include "grove_rtc_ds1307.h"
#include <stdio.h>

void initialiserCapteursGlobaux(void) {
    GroveBME680_Init();
    GroveLight_Init();
    GroveGPS_Init();
    GroveRTC_Init();
}

MesureMeteo acquerirDonneesMeteo(bool modeEco) {
    MesureMeteo mesure;
    mesure.capteurValide = true;

    // Horodatage via RTC DS1307
    RTC_DateTime dt;
    if (GroveRTC_GetDateTime(&dt)) {
        mesure.timestamp = dt.seconds + (dt.minutes * 60) + (dt.hours * 3600);
    } else {
        mesure.timestamp = 0;
    }

    // Lecture environnementale BME680
    if (!GroveBME680_ReadEnvironment(&mesure.env)) {
        mesure.env.temperature_c = 0.0f;
        mesure.env.humidity_percent = 0.0f;
        mesure.env.pressure_hpa = 0.0f;
        mesure.capteurValide = false;
    }

    // Lecture de la luminosité (capteur A0/A2)
    uint16_t rawLight = GroveLight_ReadRaw();
    if (rawLight != 0xFFFF) {
        mesure.luminosite = (float)rawLight * (3.3f / 4095.0f) * 100.0f;
    } else {
        mesure.luminosite = 0.0f;
    }

    // Lecture GPS Air530Z (omis en mode éco pour économiser l'énergie)
    if (!modeEco) {
        if (!GroveGPS_ReadGGA(&mesure.gps, 500)) {
            mesure.gps.valid = false;
            mesure.gps.latitude = 0.0;
            mesure.gps.longitude = 0.0;
        }
    } else {
        mesure.gps.valid = false;
        mesure.gps.latitude = 0.0;
        mesure.gps.longitude = 0.0;
    }

    return mesure;
}
