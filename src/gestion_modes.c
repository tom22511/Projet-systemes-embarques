#include "gestion_modes.h"
#include "board_pins.h"
#include "grove_button.h"
#include "grove_rgb.h"

void initialiserModes(void) {
    // Initialisation des boutons et des LED RGB d'état
}

EtatSysteme executerMachineAEtats(EtatSysteme etatActuel, bool *modeEcoActif) {
    bool appuiLongVert = false;  // À lier avec grove_button
    bool appuiLongRouge = false; // À lier avec grove_button

    // Bascule Mode Standard <-> Mode Économique (Bouton vert - Appui long 5s)
    if (appuiLongVert) {
        if (etatActuel == ETAT_STANDARD) {
            *modeEcoActif = true;
            etatActuel = ETAT_ECONOMIQUE;
        } else if (etatActuel == ETAT_ECONOMIQUE) {
            *modeEcoActif = false;
            etatActuel = ETAT_STANDARD;
        }
    }

    // Bascule vers le Mode Maintenance (Bouton rouge - Appui long 5s)
    if (appuiLongRouge) {
        if (etatActuel != ETAT_MAINTENANCE) {
            etatActuel = ETAT_MAINTENANCE;
        } else {
            etatActuel = (*modeEcoActif) ? ETAT_ECONOMIQUE : ETAT_STANDARD;
        }
    }

    return etatActuel;
}
