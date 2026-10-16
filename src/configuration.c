#include "configuration.h"
#include "board_pins.h"
#include <stdio.h>
#include <string.h>

extern unsigned long millis(void);

#define TIMEOUT_CONFIG_MS 1800000UL // 30 minutes d'inactivité
static unsigned long dernierTempsActivite = 0;

void initialiserUARTConfig(void) {
    dernierTempsActivite = millis();
}

bool gererModeConfiguration(void) {
    // Sécurité : bascule automatique en mode standard après 30 minutes d'inactivité
    if (millis() - dernierTempsActivite >= TIMEOUT_CONFIG_MS) {
        return true; 
    }
    return false;
}
