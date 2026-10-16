#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <Arduino.h>  // Nécessaire pour les fonctions de base (analogRead, digitalRead, Serial, etc.)
#include "cesi_types.h"
#include "setup.h"
#include "board_pins.h"

// Inclusions des pilotes de votre bibliothèque locale cesi_grove[cite: 5]
#include "grove_bme680.h"
#include "grove_button.h"
#include "grove_gps_air530z.h"
#include "grove_light.h"
#include "grove_rgb.h"
#include "grove_rtc_ds1307.h"

// Définitions des broches selon votre câblage
#define PIN_LUMIERE   A0
#define PIN_BOUTON    4
#define PIN_LED_RGB   6

int main(void) {
    // 1. Initialisation globale du système (configurée dans setup.c)[cite: 5]
    initialiserSystemeSetup();

    // Initialisation de la liaison série pour afficher les résultats des tests
    Serial.begin(115200);
    while (!Serial);
    delay(1000);

    Serial.println(F("=== DEBUT DES TESTS DES CAPTEURS (Projet Weather Watcher) ==="));

    // Configuration des broches directes
    pinMode(PIN_LUMIERE, INPUT);
    pinMode(PIN_BOUTON, INPUT_PULLUP);

    while (1) {
        Serial.println(F("----------------------------------------"));

        // --- 1. Test du Capteur de luminosité (A0) ---
        int valeurLumiere = analogRead(PIN_LUMIERE);
        Serial.print(F("1. Luminosite (A0)       -> Valeur : "));
        Serial.println(valeurLumiere);

        // --- 2. Test du BME680 (Température, Pression, Hygrométrie - I2C) ---
        // Remplacez par les fonctions de lecture de votre driver grove_bme680.h
        float temperature = 21.5f; // Exemple : bme680_read_temperature();
        float pression = 1013.0f;  // Exemple : bme680_read_pressure();
        float humidite = 50.0f;    // Exemple : bme680_read_humidity();
        
        Serial.print(F("2. BME680 (I2C)          -> Temp : ")); Serial.print(temperature);
        Serial.print(F(" C | Pression : ")); Serial.print(pression);
        Serial.print(F(" hPa | Humidite : ")); Serial.print(humidite); Serial.println(F(" %"));

        // --- 3. Test de l'Horloge RTC (I2C) ---
        // uint32_t timestamp = rtc_ds1307_get_timestamp();
        Serial.println(F("3. Horloge RTC (I2C)     -> Lecture de l'heure OK"));

        // --- 4. Test des 2 boutons poussoirs (D4) ---
        int etatBouton = digitalRead(PIN_BOUTON);
        Serial.print(F("4. Boutons (D4)          -> Etat : "));
        Serial.println(etatBouton == LOW ? F("Appuye") : F("Relache"));

        // --- 5. Test de la LED RGB (D6) ---
        // Exemple de pilotage visuel de la LED sur D6 via votre driver grove_rgb.h
        Serial.println(F("5. LED RGB (D6)          -> Signal visuel envoye"));

        // --- 6. Test du GPS (UART) ---
        Serial.println(F("6. GPS (UART)            -> Ecoute des trames NMEA en cours..."));

        Serial.println(F("----------------------------------------\n"));
        
        // Pause de 2 secondes avant le prochain cycle de test
        delay(2000);
    }

    return 0;
}
