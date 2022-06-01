#include <man/entity.h>

Entity_t  m_entities[MAX_ENTITIES];     // ARRAY DE ENTIDADES
u8 m_zero_type_at_the_end;              // Byte a 0 para indicar el final del array de entidades
Entity_t* m_next_free_entity;           // PUNTERO A LA SIGUIENTE ENTIDAD LIBRE
u8 m_num_entities;                      // Número de entidades ya reservadas

///////////////////////////////////////////////////////////////////////////////////
// INICIALIZA EL ARRAY DE ENTIDADES RELLENÁNDOLO CON CEROS
// RECIBE:     NADA
// DEVUELVE:   NADA
//
void man_entity_init (void) {
   cpct_memset (m_entities, 0, sizeof(m_entities));
   m_next_free_entity = m_entities;
   m_num_entities = 0;
   m_zero_type_at_the_end = e_type_invalid;
}

///////////////////////////////////////////////////////////////////////////////////
// CREA UNA ENTIDAD EN EL ARRAY DE ENTIDADES Y LA MARCA COMO TIPO DEFAULT. 
// LUEGO AUMENTA EL PUNTERO A LA SIGUIENTE ENTIDAD LIBRE Y DEVUELVE EL PUNTERO A 
// LA ENTIDAD CREADA
// RECIBE:     NADA
// DEVUELVE:   PUNTERO A LA ENTIDAD CREADA
//
Entity_t* man_entity_create (void) {
   Entity_t* e = m_next_free_entity;
   m_next_free_entity = e + 1;
   e->type = e_type_default;
   ++m_num_entities;
   return e;
}

///////////////////////////////////////////////////////////////////////////////////
// CLONE
//    TODO
// Precondiciones:
//    Debe haber espacio para, al menos, pode crear una entidad  
//
Entity_t* man_entity_clone(Entity_t* e) {
   Entity_t* clone = man_entity_create();
   cpct_memcpy(clone, e, sizeof(Entity_t));
   return clone;
}

///////////////////////////////////////////////////////////////////////////////////
// APLICA EL MÉTODO RECIBIDO COMO ARGUMENTO (MEDIANTE UN PUNTERO A FUNCIÓN) A TODAS
// LAS ENTIDADES QUE NO SEAN INVÁLIDAS. LA FUNCIÓN RECORRE EL ARRAY DE ENTIDADES
// HASTA ENCONTRAR UNA ENTIDAD INVÁLIDA. NUESTRO ARRAY SIEMPRE ESTÁ TERMINADO CON
// UN BYTE A 0 QUE SIMULA SER UNA ENTIDAD INVÁLIDA PARA QUE EL BUCLE NO SE SALGA 
// DEL ARRAY CUANDO TODAS LAS ENTIDADES POSIBLES SON VÁLIDAS.
// RECIBE:     
//    PUNTERO AL MÉTODO A UTILIZAR CON LAS ENTIDADES
// DEVUELVE:   
//    NADA
//
void man_entity_forall (UpdateFunc_t updFunc) {
   Entity_t* e = m_entities;
   
   while (e->type != e_type_invalid) {
      updFunc(e);
      ++e;
   }
}

///////////////////////////////////////////////////////////////////////////////////
// APLICA EL MÉTODO RECIBIDO COMO ARGUMENTO (MEDIANTE UN PUNTERO A FUNCIÓN) A TODAS
// LAS ENTIDADES QUE CUMPLAN CON EL BYTE DE FIRMA RECIBIDO. LA FUNCIÓN RECORRE EL 
// ARRAY DE ENTIDADES HASTA ENCONTRAR UNA ENTIDAD INVÁLIDA. NUESTRO ARRAY SIEMPRE ESTÁ TERMINADO CON
// UN BYTE A 0 QUE SIMULA SER UNA ENTIDAD INVÁLIDA PARA QUE EL BUCLE NO SE SALGA 
// DEL ARRAY CUANDO TODAS LAS ENTIDADES POSIBLES SON VÁLIDAS.
// RECIBE:     
//    PUNTERO AL MÉTODO A UTILIZAR CON LAS ENTIDADES
//    BYTE DE FIRMA
// DEVUELVE:   
//    NADA
//
void man_entity_forall_matching (UpdateFunc_t updfunc, u8 signature) {
   Entity_t* e = m_entities;
   
   while (e->type != e_type_invalid) {
      if((e->type & signature) == signature)
         updfunc(e);
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
   --m_num_entities;
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

///////////////////////////////////////////////////////////////////////////////////
// FREE SPACE
//    Retorna el número de entidades vacías disponibles
// Devuelve:
//    u8:   Número de entidades libres
//
u8 man_entity_freeSpace() {
   return MAX_ENTITIES - m_num_entities;
}