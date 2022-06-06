#pragma once

#include <cpctelera.h>
#include <man/animation.h>

#define MAX_ENTITIES    12   // Número máximo de entidades

// Tipos de entidad
#define e_type_invalid     0x00         // Entidad inválida
#define e_type_player      0x01         // Entidad Jugador
#define e_type_enemy       0x02         // Entidad Enemigo
#define e_type_mothership  0x04         // Entidad Nave nodriza
#define e_type_shot        0x08         // Entidad Disparo
#define e_type_dead        0x80         // Entidad marcada para morir
#define e_type_default     e_type_enemy // Entidad por defecto

// Componentes de las entidades
#define e_cmp_render   0x01 // Entidad renderizable
#define e_cmp_movable  0x02 // Entidad movible
#define e_cmp_input    0x04 // Entidad controlable
#define e_cmp_ai       0x08 // Entidad con IA        
#define e_cmp_animated 0x10 // Entidad con animación           
#define e_cmp_default  0x00 // Entidad sin ningún componente

//----------------------------------------------------------------------------------
// Estructura de una entidad
//    -type          -> tipo de entidad
//    -x, y          -> coordenadas x, y
//    -w, h          -> ancho y alto (en bytes)
//    -vx, vy        -> velocidad x, y
//    -sprite        -> puntero al sprite
//    -ai_behaviour  -> puntero a función de comportamiento
//
// Para poder utilizar cómodamente el tipo Entity_t dentro de la propia definición
// de la estructura, declaramos previamente el tipo, sin definirlo (forward declaration)
typedef struct Ent_t Entity_t;
//
// Alias de un puntero a función. Al contrario que en el uso "normal" de typedef, donde
// primero se pone el tipo y después el alias, en un alias de puntero a función se esribe
// de la misma forma que cuando declaramos dicho puntero, situando el alias en el mismo
// orden y no después, como la lógica podría decirnos.
//
typedef void (*BehaviourFunc_t)(Entity_t*);
typedef void (*UpdateFunc_t)(Entity_t*);
//
// A continuación, definimos la estructura y así podemos utilizar el tipo Entity_t
// en la declaración del puntero a comportamiento.
struct Ent_t{
   u8                   type;
   u8                   cmps;
   u8                   x, y; 
   u8                   w, h;
   i8                   vx, vy;
   u8 const*            sprite;
   BehaviourFunc_t      ai_vehaviour;
   u8                   ai_counter;
   AnimFrame_t const*   anim;
   u8                   anim_counter;
};

void      man_entity_init            (void);
Entity_t* man_entity_create          (void);
void      man_entity_destroy         (Entity_t*);
void      man_entity_forall          (UpdateFunc_t updFunc);
void      man_entity_forall_matching (UpdateFunc_t updFunc, u8 signature);
void      man_entity_set4destruction (Entity_t*); 
void      man_entity_update          (void);
u8        man_entity_freeSpace       ();
Entity_t* man_entity_clone           (Entity_t* e);

