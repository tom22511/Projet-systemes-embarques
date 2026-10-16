#ifndef ACQUISITION_H
#define ACQUISITION_H

#include "cesi_types.h"
#include <stdbool.h>

void initialiserCapteursGlobaux(void);
MesureMeteo acquerirDonneesMeteo(bool modeEco);

#endif
