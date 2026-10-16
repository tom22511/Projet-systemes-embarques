#include "gestion_modes.h"
#include "lib/cesi_grove/include/grove_button.h"
#include "lib/cesi_grove/include/grove_rgb.h"

void initialiserModes(void) {
    // Initialisation des boutons et des LED RGB d'état
}

EtatSysteme executerMachineAEDats(EtatSysteme etatActuel, bool *modeEcoActif) {
    // Gestion des transitions par appuis longs (5s) sur les boutons
    // et pilotage des couleurs de la LED (Vert, Bleu, Orange, Jaune)
    return etatActuel;
}
