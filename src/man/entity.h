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
#define e_cmp_collider 0x20 // Entidad con colisiones  
#define e_cmp_default  0x00 // Entidad sin ningún componente 

// Macros
// Comprueba si el tipo de la entidad recibida es distinta de inválida
#define IsValid(E) ((E)->type != e_type_invalid)
// Comprueba si el componente de la entidad coincide con el especificado
#define SignatureMatches(E, S) (((E)->cmps & (S)) == (S))
// Comprueba si la entidad está muerta
#define IsDead(E) ((e)->type & e_type_dead)

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
typedef void (*UpdateFunc2E_t)(Entity_t*, Entity_t*);
//
// A continuación, definimos la estructura y así podemos utilizar el tipo Entity_t
// en la declaración del puntero a comportamiento.
struct Ent_t{
   u8                   type;            // Tipo de entidad
   u8                   cmps;            // Componentes de la entidad
   u8                   x, y;            // Posición X e Y
   u8                   w, h;            // Ancho y alto
   i8                   vx, vy;          // Velocidad X e Y
   u8 const*            sprite;          // Puntero al sprite 
   BehaviourFunc_t      ai_vehaviour;    // Puntero al comportamiento
   u8                   ai_counter;      // Contador para la IA
   AnimFrame_t const*   anim;            // Puntero a la estructura fotograma
   u8                   anim_counter;    // Contador para la animación
   u8                   collide_against; // ¿Contra qué colisiona la entidad?
};

//**********************************************************************************
// Funciones públicas
//**********************************************************************************
void      man_entity_init                  (void);
Entity_t* man_entity_create                (void);
void      man_entity_destroy               (Entity_t*);
void      man_entity_forall                (UpdateFunc_t updFunc);
void      man_entity_forall_matching       (UpdateFunc_t updFunc, u8 signature);
void      man_entity_set4destruction       (Entity_t*); 
void      man_entity_update                (void);
u8        man_entity_freeSpace             ();
Entity_t* man_entity_clone                 (Entity_t* e);
void      man_entity_forall_pairs_matching (UpdateFunc2E_t updfunc, u8 signature);

