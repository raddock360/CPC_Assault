#include <man/game.h>
#include <man/entity.h>
#include <sys/physics.h>
#include <sys/ai.h>
#include <sys/render.h>
#include <sprites/Nodriza.h>
#include <sprites/Jugador.h>
#include <sprites/enemigo1.h>

//*******************************************************************
// DATOS PRIVADOS
//*******************************************************************

// Entidad por defecto de la nave nodriza
const Entity_t mothership_templ = {
    e_type_ai | e_type_movable | e_type_render,  // Tipo
    38, 10,                          // x, y
    SPR_NODRIZA_W,                   // w
    SPR_NODRIZA_H,                   // h
    -1,  0,                          // vx, vy
    spr_nodriza,                     // sprite
    sys_ai_behaviour_mothership      // comportamiento de la entidad
};

// Entidad por defecto de las naves del marcador de vidas
const Entity_t playership_templ = {
    e_type_render,   // Tipo
    0, 192,          // x, y
    SPR_JUGADOR_1_W, // w
    SPR_JUGADOR_1_H, // h
    0,  0,           // vx, vy
    spr_jugador_1,   // sprite
    0x0000           // entidad sin IA (puntero NULL)
};

// Entidad por defecto de la nave del jugador
const Entity_t player_templ = {
    e_type_movable | e_type_input | e_type_render,   // Tipo
    38, 180,         // x, y
    SPR_JUGADOR_0_W, // w
    SPR_JUGADOR_0_H, // h
    0,  0,           // vx, vy
    spr_jugador_0,   // sprite
    0x0000           // entidad sin IA (puntero NULL)
};

// Entidad por defecto de la nave enemiga 1
const Entity_t enemy1_templ = {
    e_type_movable | e_type_ai | e_type_render,   // Tipo
    0, 40,            // x, y
    SPR_ENEMIGO1_0_W, // w
    SPR_ENEMIGO1_0_H, // h
    0,  0,            // vx, vy
    spr_enemigo1_0,   // sprite
    sys_ai_behaviour_left_right // entidad sin IA (puntero NULL)
};


//*******************************************************************
// FUNCIONES PRIVADAS
//*******************************************************************

//-------------------------------------------------------------------
// Función de espera. Llama a waitVSYNC n veces.
//
void wait (u8 n) {
   do {
      cpct_waitHalts(2);
      cpct_waitVSYNC();
   } while(--n);
}

//-------------------------------------------------------------------
// Crea una entidad, llamando a man_entity_create y la inicializa
// copiando en el espacio reservado, los valores por defecto de la
// entidad creada.
// INPUT: *templ_e -> puntero a una estuctura de datos constante que 
//        contiene los datos de inicio de la entidad.
// OUTPUT: e -> Entity_t puntero a la entidad recién creada.
//
Entity_t* man_game_create_template_entity(const Entity_t *templ_e) {
    Entity_t *e = man_entity_create();
    cpct_memcpy(e, templ_e, sizeof(Entity_t));
    return e;
}

//-------------------------------------------------------------------------------------
// Inicia el juego. Primero llama al iniciador del mánager de entidades y al del 
// sistema de render. Después crea las distintas entidades del juego y las inicializa
// copiando los valores por defecto.
//
void man_game_init() {
    u8 x = 30;          // Contador para el bucle de creación de entidad playership
    man_entity_init();  // Iniciamos el sistema de entidades
    sys_render_init();  // Iniciamos el sistema de render

    // Crea la entidad nave dodriza y la inicializa
    man_game_create_template_entity(&mothership_templ);

    // Crea las tres entidades del marcador de vidas y las inicializa
    do {
        Entity_t *e;
        x -= 10;
        e = man_game_create_template_entity(&playership_templ);
        e->x = x;
    } while (x != 0);     

    // Crea la entidad del jugador y la inicializa
    man_game_create_template_entity(&player_templ);

    /*Crea una entidad enemigo 1
    {
        Entity_t *e = man_game_create_template_entity(&enemy1_templ);
        e->x = 38;
        e->vx = 1;
    }
    */
}

//-------------------------------------------------------------------------------------
// Inicia una partida al juego
//
void man_game_play() {
    while(1) {
        sys_ai_update();        // Actualiza las entidades con IA
        sys_physics_update();   // Actualiza las entidades con físicas
        sys_render_update();    // Renderiza la escena
      
        man_entity_update();    // Actualiza las entidades en memoria. Destruyendo las muertas
        cpct_waitVSYNC();       // Esperamos al refresco de pantalla
    }
}