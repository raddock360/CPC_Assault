#include <cpctelera.h>
#include <man/game.h>

void main(void) {
   cpct_disableFirmware();

   man_game_init();
   man_game_play();
}