#include <sys/generator.h>
#include <sys/physics.h>
#include <man/entity.h>

//================================================================================
//================================================================================
//  FUNCIONES PRIVADAS
//================================================================================
//================================================================================

// Entidad por defecto. Se utiliza para inicializar las entidades creadas.
const Entity_t init_e = {
   e_type_star,   // tipo
   79, 1,         // x, y
   -1,            // vx
   0x80,          // color
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
   Entity_t* e = man_entity_create();           // Puntero a la entidad reservada en el array
   cpct_memcpy(e, &init_e, sizeof(Entity_t));   // Inicializamos la entidad con los valores standar
   e->y  = cpct_rand() % 200;                   // Asignamos una posición y aleatoria (0 a 200)
   e->vx = -1-(cpct_rand() & 0x03);             // Asignamos una velocidad x aleatoria (-1 a -3 )

   // Asignamos un color en función de la velocidad de la estrella generada
   switch ( e->vx ) {
   case -1:
      e->color = 0x88;
      break;
   case -2:
      e->color = 0x08;
      break;
   case -3:
      e->color = 0x80;
   }
}

//================================================================================
//================================================================================
//  FUNCIONES PÚBLICAS
//================================================================================
//================================================================================

/////////////////////////////////////////////////////////////////////////////////
//  ACTUALIZA EL GENERADOR
//  Actualiza el generador de estrellas para crear nuevas entidades. Primero
//  comprueba que haya espacio libre en el array de entidades. Si hay espacio, genera una nueva estrella.
//
void sys_generator_update() {
   u8 free = man_entity_freeSpace();
   if( free > 2 ) free = 2;
   while( free ) {
      generateNewStar();   
      --free;
   } 
      
}


