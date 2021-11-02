#pragma once
#include <cpctelera.h>

#define e_type_invalid  0x00 //
#define e_type_star     0x01 // El bit mas bajo indica estrella válida
#define e_type_dead     0x80 // El bit mas alto indica estrella muerta
#define e_type_default  0x7f // Entidad por defecto (todos los bits a 1 excepto al mas alto)

typedef struct {
   u8    type;
   u8    x, y;
   i8    vx;
   u8    color;
   u8*   prevptr;
} Entity_t;

void      man_entity_init (void);
Entity_t* man_entity_create (void);
void      man_entity_destroy (Entity_t*);
void      man_entity_forall (void (*ptrfunc) (Entity_t*));
void      man_entity_set4destruction (Entity_t*); 
void      man_entity_update (void);

