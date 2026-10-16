#ifndef ACQUISITION_H
#define ACQUISITION_H

#include <stdbool.h>
#include <stdint.h>
#include "cesi_types.h"

typedef struct {
    uint32_t timestamp;
    Env_Data env;
    GPS_Data gps;
    float luminosite;
    bool capteurValide;
} MesureMeteo;

void initialiserCapteursGlobaux(void);
MesureMeteo acquerirDonneesMeteo(bool modeEco);

#endif
