#include <man/entity.h>
#include <man/game.h>
#include <man/animation.h>
#include <sys/physics.h>
#include <sys/ai.h>
#include <sys/render.h>
#include <sys/animation.h>
#include <sprites/Nodriza.h>
#include <sprites/Jugador.h>
#include <sprites/enemigo1.h>
#include <man/entity_templates.h>

//*******************************************************************
// DATOS PRIVADOS
//*******************************************************************
// Flag de verificación de enemigo en el carril superior
u8 m_lane_status[3];
// Flag de verificación de disparo activo
u8 m_player_shoot;

//*******************************************************************
// FUNCIONES PRIVADAS
//*******************************************************************

////////////////////////////////////////////////////////////////////////////////////
// WAIT
//      Función de espera. Llama a waitVSYNC n veces.
// INPUT:
//      u8 n -> número de veces que esperamos a vsync
//
void wait (u8 n) {
   do {
      cpct_waitHalts(2);
      cpct_waitVSYNC();
   } while(--n);
}

////////////////////////////////////////////////////////////////////////////////////
// CREATE TEMPLATE ENTITY
//      Crea una entidad, llamando a man_entity_create y la inicializa
//      copiando en el espacio reservado, los valores por defecto de la
//      entidad creada.
// INPUT: 
//      - *templ_e -> puntero a una estuctura de datos constante que 
//                    contiene los datos de inicio de la entidad.
// OUTPUT: 
//        - e -> Entity_t puntero a la entidad recién creada.
//
Entity_t* man_game_create_template_entity(const Entity_t *templ_e) {
    Entity_t *e = man_entity_create();
    cpct_memcpy(e, templ_e, sizeof(Entity_t));
    return e;
}

////////////////////////////////////////////////////////////////////////////////////
// INIT
//      Inicia el juego. Primero llama al iniciador del mánager de entidades y al del 
//      sistema de render. Después crea las distintas entidades del juego y las 
//      inicializa copiando los valores por defecto.
//
void man_game_init() {
    u8 x = 30;          // Contador para el bucle de creación de entidad playership
    man_entity_init();  // Iniciamos el sistema de entidades
    sys_render_init();  // Iniciamos el sistema de render
    m_player_shoot = 0; // No hay disparos activos al empezar la partida

    cpct_memset(m_lane_status, 0, sizeof(m_lane_status));
    
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

////////////////////////////////////////////////////////////////////////////////////
// PLAY
//      Inicia una partida al juego
//
void man_game_play() {
    while(1) {
        sys_ai_update();        // Actualiza las entidades con IA
        sys_physics_update();   // Actualiza las entidades con físicas
        sys_animation_update(); // Actualiza las animaciones
        sys_render_update();    // Renderiza la escena
      
        man_entity_update();    // Actualiza las entidades en memoria. Destruyendo las muertas
        cpct_waitVSYNC();       // Esperamos al refresco de pantalla
        wait(5);
    }
}

////////////////////////////////////////////////////////////////////////////////////
// CREATE ENEMY
//      Crea un nuevo enemigo en el carril superior, si está libre.
// INPUT:
//      - Entity_t *e -> puntero a la entidad madre nodriza
//
void man_game_create_enemy(Entity_t *e_mother) {
    // Si ya hay un enemigo en el carril de arriba, no generamos otro.
    if(m_lane_status[2]) return;

    // Creamos enemigo
    {
        Entity_t *e = man_game_create_template_entity(&enemy1_templ);
        e->x  = e_mother->x;
        e->vx = e_mother->vx;
    }
    // Marcamos que hay un enemigo
    m_lane_status[2] = 1;
}

////////////////////////////////////////////////////////////////////////////////////
// ENEMY LANE DOWN
//      Baja el enemigo al carril inferior
// INPUT:
//      - Entity_t *e_enemy -> puntero a la entidad enemiga
//
void man_game_enemy_lane_down(Entity_t *e_enemy) {
    u8 lane = 2;
    // Solo podemos bajar al enemigo si lane es 1 o 2
    if      (e_enemy->y > LANE1_Y) return;
    else if (e_enemy->y > LANE2_Y) lane = 1;

    // Comprobamos el siguiente carril para comprobar si está libre
    if(m_lane_status[lane-1]) return;

    // Creamos un clon fantasma de la entidad para borrar el carril que deja libre
    {
        Entity_t* clone = man_entity_clone(e_enemy);
        clone->type = e_type_render;
        man_entity_set4destruction(clone);
    }
    
    // Bajamos
    e_enemy->y += LANE_DY;
    m_lane_status[lane]     = 0;
    m_lane_status[lane - 1] = 1;

}

////////////////////////////////////////////////////////////////////////////////////
// GAME ENTITY DESTROY
// INPUT:
//      - Entity_t *e -> puntero a la entidad 
//
void man_game_entity_destroy(Entity_t* e) {

    man_entity_destroy(e); 
}

////////////////////////////////////////////////////////////////////////////////////
// GAME PLAYER SHOOT
//      Crea un disparo del jugador
// INPUT:
//      - Entity_t *e_player -> puntero a la entidad 
//
void man_game_player_shoot(Entity_t* e_player){
    // Comprobamos si existe ya algún disparo
    if(m_player_shoot) return;
    
    // Disparo
    {
        Entity_t* e = man_game_create_template_entity(&vshoot_templ);
        e->x = e_player->x + 2;
    }

    // Activamos el flag de disparo (sólo puede haber un disparo en pantalla)
    m_player_shoot = 1;
}