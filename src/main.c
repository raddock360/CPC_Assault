#include <cpctelera.h>
#include <man/game.h>

//--------------------------------------------------------------------------------
// Función principal. Aquí empieza la magia.
//
void main(void) {
   cpct_setStackLocation((void*)0x8000);
   cpct_disableFirmware(); // Deshabilitamos el firmware del Amstrad

   man_game_init();        // Llamamos al inicializador del juego
   man_game_play();        // Jugamos una partida
}