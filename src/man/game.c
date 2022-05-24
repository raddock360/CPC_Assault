#include <man/game.h>
#include <man/entity.h>
#include <sys/physics.h>
#include <sys/render.h>
#include <sprites/Nodriza.h>
#include <sprites/Jugador.h>

//*******************************************************************
// DATOS PRIVADOS
//*******************************************************************

const Entity_t mothership_templ = {
    e_type_movable | e_type_render,  // Tipo
    38, 10,                          // x, y
    SPR_NODRIZA_W,                   // w
    SPR_NODRIZA_H,                   // h
    -1,  0,                          // vx, vy
    spr_nodriza                      // sprite
};

const Entity_t playership_templ = {
    e_type_render,   // Tipo
    0, 192,          // x, y
    SPR_JUGADOR_1_W, // w
    SPR_JUGADOR_1_H, // h
    0,  0,           // vx, vy
    spr_jugador_1    // sprite
};


//*******************************************************************
// FUNCIONES PRIVADAS
//*******************************************************************
void wait (u8 n) {
   do {
      cpct_waitHalts(2);
      cpct_waitVSYNC();
   } while(--n);
}

Entity_t* man_game_create_template_entity(const Entity_t *templ_e) {
    Entity_t *e = man_entity_create();
    cpct_memcpy(e, templ_e, sizeof(Entity_t));
    return e;
}

//*******************************************************************
// INICIO DEL JUEGO
//
void man_game_init() {
    u8 x = 30;          // Contador para el bucle de creación de entidad playership
    man_entity_init();
    sys_render_init();

    man_game_create_template_entity(&mothership_templ);

    do {
        Entity_t *e;
        e = man_game_create_template_entity(&playership_templ);
        e->x = x;
        x -= 10;
    } while (x != 0);    
}


void man_game_play() {
    while(1) {
        sys_physics_update();
        sys_render_update();
      
        man_entity_update();
        cpct_waitVSYNC();
    }
}