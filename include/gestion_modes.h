#ifndef GESTION_MODES_H
#define GESTION_MODES_H

#include "cesi_types.h"
#include <stdbool.h>

void initialiserModes(void);
EtatSysteme executerMachineAEtats(EtatSysteme etatActuel, bool *modeEcoActif);

#endif
