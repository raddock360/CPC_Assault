#include <cpctelera.h>
#include "man/entity.h"
#include "sys/physics.h"

const Entity_t init_e = {
   e_type_star,   // tipo
   79, 1,         // x, y
   -1,            // vx
   0xff           // color
};

void  createEntity() {
   Entity_t* e = man_entity_create();
   cpct_memcpy(e, &init_e, sizeof(Entity_t));

}

void main(void) {
   man_entity_init();
   for(u8 i = 5; i > 0; --i)
      createEntity();
   sys_physics_update();
   
   while(1);
}

