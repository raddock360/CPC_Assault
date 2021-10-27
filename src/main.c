#include <cpctelera.h>
#include "man/entity.h"
#include "sys/physics.h"
#include "sys/render.h"

const Entity_t init_e = {
   e_type_star,   // tipo
   79, 1,         // x, y
   -1,            // vx
   0xff           // color
};

void  createEntity() {
   Entity_t* e = man_entity_create();
   cpct_memcpy(e, &init_e, sizeof(Entity_t));
   e->y  = cpct_rand() % 200;
   e->vx = -1-(cpct_rand() & 0x03);
}

void wait(u8 n) {
   do {
      cpct_waitHalts(2);
      cpct_waitVSYNC();
   } while(--n);
}

void main(void) {
   cpct_disableFirmware();
   cpct_setVideoMode(0);
   cpct_setBorder(HW_BLACK);
   cpct_setPALColour(0, HW_BLACK);
   
   man_entity_init();
   for(u8 i = 5; i > 0; --i)
      createEntity();
   
   while(1) {
      sys_physics_update();
      sys_render_update();
      wait(10);
   }
}