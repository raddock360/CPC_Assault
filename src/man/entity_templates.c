#include <man/entity_templates.h>
#include <sys/ai.h>
#include <sprites/enemigo1.h>
#include <sprites/Jugador.h>
#include <sprites/Nodriza.h>
#include <man/animation.h>

// Entidad por defecto de la nave nodriza
const Entity_t mothership_templ = {
    e_type_ai | e_type_movable | e_type_render,  // Tipo
    38, 10,                         // x, y
    SPR_NODRIZA_W,                  // w
    SPR_NODRIZA_H,                  // h
    -1,  0,                         // vx, vy
    spr_nodriza,                    // sprite
    sys_ai_behaviour_mothership,    // comportamiento de la entidad
    0x0000,                         // Animación (no tiene)
    0x00                            // Contador de animación
};

// Entidad por defecto de las naves del marcador de vidas
const Entity_t playership_templ = {
    e_type_render,                  // Tipo
     0, 192,                        // x, y
    SPR_JUGADOR_1_W,                // w
    SPR_JUGADOR_1_H,                // h
     0,   0,                        // vx, vy
    spr_jugador_1,                  // sprite
    0x0000,                         // entidad sin IA (puntero NULL)
    0x0000,                         // Animación (no tiene)
    0x00                            // Contador de animación 
};

// Entidad por defecto de la nave del jugador
const Entity_t player_templ = {
    e_type_movable | e_type_input | e_type_render,   // Tipo
    38, 180,                        // x, y
    SPR_JUGADOR_0_W,                // w
    SPR_JUGADOR_0_H,                // h
     0,   0,                        // vx, vy
    spr_jugador_0,                  // sprite
    0x0000,                         // entidad sin IA (puntero NULL)
    0x0000,                         // Sin animación
    0x00                            // Contador de animación
};

// Entidad por defecto de la nave enemiga 1
const Entity_t enemy1_templ = {
    e_type_movable | e_type_ai | e_type_render | e_type_animated, // Tipo
     0, LANE2_Y,                    // x, y
    SPR_ENEMIGO1_0_W,               // w
    SPR_ENEMIGO1_0_H,               // h
     0,  0,                         // vx, vy
    spr_enemigo1_0,                 // sprite
    sys_ai_behaviour_enemy,         // entidad sin IA (puntero NULL)
    man_anim_enemy1,                // Animación
    man_anim_enemy1_time            // Contador de animación
};

