#include <sys/generator.h>
#include <sys/physics.h>
#include <man/entity.h>

//================================================================================
//================================================================================
//  FUNCIONES PRIVADAS
//================================================================================
//================================================================================

const Entity_t init_e = {
   e_type_star,   // tipo
   79, 1,         // x, y
   -1,            // vx
   0xff,          // color
   0x0000         // prev pointer
};

/////////////////////////////////////////////////////////////////////////////////
//  GENERA UNA NUEVA ESTRELLA
//      Crea e inicializa una nueva entidad estrella
//
//  PRECONDICIÓN:
//      - Tiene que haber memoria libre para nuevas entidades
//
void generateNewStar() {
   Entity_t* e = man_entity_create();
   cpct_memcpy(e, &init_e, sizeof(Entity_t));
   e->y  = cpct_rand() % 200;
   e->vx = -1-(cpct_rand() & 0x03);
}

//================================================================================
//================================================================================
//  FUNCIONES PÚBLICAS
//================================================================================
//================================================================================

/////////////////////////////////////////////////////////////////////////////////
//  ACTUALIZA EL GENERADOR
//      Actualiza el generador de estrellas para crear nuevas entidades
//
void sys_generator_update() {
    u8 free = man_entity_freeSpace();
    if (free) 
      generateNewStar();   
}


