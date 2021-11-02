#include "entity.h"

Entity_t  m_entities[10];     // ARRAY DE ENTIDADES
Entity_t* m_next_free_entity; // PUNTERO A LA SIGUIENTE ENTIDAD LIBRE

///////////////////////////////////////////////////////////////////////////////////
// INICIALIZA EL ARRAY DE ENTIDADES RELLENÁNDOLO CON CEROS
// RECIBE:     NADA
// DEVUELVE:   NADA
//
void man_entity_init (void) {
   cpct_memset (m_entities, 0, sizeof(m_entities));
   m_next_free_entity = m_entities;
}

///////////////////////////////////////////////////////////////////////////////////
// CREA UNA ENTIDAD EN EL ARRAY DE ENTIDADES Y LA MARCA COMO TIPO DEFAULT. 
// LUEGO AUMENTA EL PUNTERO A LA SIGUIENTE ENTIDAD LIBRE Y DEVUELVE EL PUNTERO A 
// LA ENTIDAD CREADA
// RECIBE:     NADA
// DEVUELVE:   PUNTERO A LA ENTIDAD CREADA
Entity_t* man_entity_create (void) {
   Entity_t* e = m_next_free_entity;
   m_next_free_entity = e + 1;
   e->type = e_type_default;
   return e;
}

///////////////////////////////////////////////////////////////////////////////////
// APLICA EL MÉTODO RECIBIDO COMO ARGUMENTO (MEDIANTE UN PUNTERO A FUNCIÓN) A TODAS
// LAS ENTIDADES QUE NO SEAN INVÁLIDAS
// RECIBE:     PUNTERO AL MÉTODO A UTILIZAR CON LAS ENTIDADES
// DEVUELVE:   NADA
//
void man_entity_forall (void (*ptrfunc) (Entity_t*)) {
   Entity_t* e = m_entities;
   while (e->type != e_type_invalid) {
      ptrfunc(e);
      ++e;
   }
}

///////////////////////////////////////////////////////////////////////////////////
// DESTROY
//    Destruye una entidad dada y libera la memoria asignada a esta, copiando
//    la última entidad válida del array sobre su posición.
// INPUT:
//    - dead_e: puntero a la entidad a destruir
// PRECONDICIONES:
//    - dead_e: debe ser un puntero a una entidad válida
//
void man_entity_destroy (Entity_t* dead_e) {
   Entity_t* de = dead_e;
   Entity_t* last = m_next_free_entity;
   --last;
   if (de != last) 
      cpct_memcpy(dead_e, last, sizeof(Entity_t));
   last->type = e_type_invalid;
   m_next_free_entity = last;
}

///////////////////////////////////////////////////////////////////////////////////
// SET 4 DESTRUCTION
//    MARCA UNA ENTIDAD PARA SU POSTERIOR DESTRUCCIÓN
// INPUT:
//    - dead_e: puntero a la entidad a destruir
// PRECONDICIONES:
//    - dead_e: debe ser un puntero a una entidad válida
//
void man_entity_set4destruction (Entity_t* dead_e) {
   dead_e->type |= e_type_dead;
}

///////////////////////////////////////////////////////////////////////////////////
// UPDATE
//    ACTUALIZA EL MANAGER DE ENTIDADES DESTRUYENDO TODAS LAS ENTIDADES MARCADAS
//
void man_entity_update (void) {
   Entity_t* e = m_entities;
   while(e->type != e_type_invalid) {
      if (e->type & e_type_dead) {
         man_entity_destroy(e);
      } else {
         ++e;
      }
   }
}