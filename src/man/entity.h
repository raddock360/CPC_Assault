#pragma once
#include <cpctelera.h>

#define e_type_invalid  0x00 //
#define e_type_render   0x01 // Renderable entity
#define e_type_movable  0x02 // Movable entity
#define e_type_input    0x04 // Controllable entity
#define e_type_dead     0x80 // El bit mas alto indica estrella muerta
#define e_type_default  0x7f // Entidad por defecto (todos los bits a 1 excepto al mas alto)
#define MAX_ENTITIES    12   // Número máximo de entidades

typedef struct {
   u8    type;
   u8    x, y;
   u8    w, h;
   i8    vx, vy;
   u8*   sprite;
} Entity_t;

void      man_entity_init (void);
Entity_t* man_entity_create (void);
void      man_entity_destroy (Entity_t*);
void      man_entity_forall (void (*ptrfunc) (Entity_t*));
void      man_entity_set4destruction (Entity_t*); 
void      man_entity_update (void);
u8        man_entity_freeSpace();

