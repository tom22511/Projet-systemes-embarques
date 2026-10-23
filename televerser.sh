#!/usr/bin/env bash

# Il faut faire ./televerser.sh dans le terminal bash pour le lancer 
# et après il faut apputer sur entrer, mode de base 

cd "$(dirname "$0")" || exit 1

# Gestion propre des erreurs avec pause
fin_erreur() {
    echo
    echo "❌ ERREUR : $1"
    read -r -p "Appuyer sur Entree pour fermer..."
    exit 1
}

# 1. Recherche de PlatformIO (adapté pour Linux et l'environnement virtuel)
if command -v pio >/dev/null 2>&1; then
    PIO="pio"
elif [ -x "$HOME/.platformio/penv/bin/pio" ]; then
    PIO="$HOME/.platformio/penv/bin/pio"
else
    fin_erreur "PlatformIO introuvable. Verifiez son installation dans ~/.platformio/penv/bin/pio"
fi

# 2. Mode de compilation : release (mise en service) ou debug (débogage)
MODE="$1"
if [ -z "$MODE" ]; then
    read -r -p "Mode de compilation : [r]elease ou [d]ebug ? (r par defaut) " choix
    case "$choix" in
        d|D|debug) MODE="debug" ;;
        *)         MODE="release" ;;
    esac
fi
case "$MODE" in
    release) ENV="nucleo_l476rg" ;;
    debug)   ENV="nucleo_l476rg_debug" ;;
    *)       fin_erreur "mode inconnu : $MODE (release ou debug)" ;;
esac

# 3. Numéro de build : lu dans include/build_number.h puis incrémenté
FICHIER_BUILD="include/build_number.h"
BUILD=0
mkdir -p include
if [ -f "$FICHIER_BUILD" ]; then
    BUILD=$(sed -n 's/^#define BUILD_NUMBER \([0-9]*\).*/\1/p' "$FICHIER_BUILD")
    BUILD=${BUILD:-0}
fi
BUILD_PRECEDENT=$BUILD
BUILD=$((BUILD + 1))

ecrire_build() {
    echo "// Généré par televerser.sh : ne pas modifier à la main" > "$FICHIER_BUILD"
    echo "#define BUILD_NUMBER $1" >> "$FICHIER_BUILD"
}

echo "=============================================="
echo "   STATION METEO 3W - COMPILATION ET ENVOI"
echo "   mode $MODE - build $BUILD"
echo "=============================================="

# 4. La carte doit être branchée en USB (port série du ST-Link)
echo
echo "[1/4] Recherche de la carte..."
if ! "$PIO" device list | grep -q "VID:PID=0483:374B"; then
    fin_erreur "Carte NUCLEO non detectee. Branchez le cable USB et verifiez le partage USB VirtualBox."
fi
echo "Carte detectee."

# 5. Compilation (le numéro de build n'est gardé que si elle réussit)
echo
echo "[2/4] Compilation..."
ecrire_build "$BUILD"
if ! "$PIO" run -e "$ENV"; then
    ecrire_build "$BUILD_PRECEDENT"
    fin_erreur "La compilation a echoue (voir les messages ci-dessus)."
fi

# 6. Téléversement par le ST-Link
echo
echo "[3/4] Televersement sur la carte..."
"$PIO" run -e "$ENV" --target upload || fin_erreur "Le televersement a echoue. Fermer les logiciels concurrents."

# 7. Moniteur série (115200 bauds, réglé dans platformio.ini)
echo
echo "[4/4] Ouverture du moniteur serie (Ctrl+C pour quitter)..."
echo
"$PIO" device monitor -e "$ENV" || fin_erreur "Moniteur serie inaccessible."
