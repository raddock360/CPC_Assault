#include <cpctelera.h>
#include "man/entity.h"
#include "sys/physics.h"
#include "sys/render.h"
#include "sys/generator.h"

void wait(u8 n) {
   do {
      cpct_waitHalts(2);
      cpct_waitVSYNC();
   } while(--n);
}

void main(void) {
   cpct_disableFirmware();

   man_entity_init();
   sys_render_init();
      
   while(1) {
      sys_physics_update();
      sys_generator_update();
      sys_render_update();
      
      man_entity_update();
      wait(10);
   }
}