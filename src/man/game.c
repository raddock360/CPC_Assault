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
static u8 m_enemy_on_lane;

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

    m_enemy_on_lane = 0;
    
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
        sys_animation_update(); // Actualiza las animaciones
        sys_render_update();    // Renderiza la escena
      
        man_entity_update();    // Actualiza las entidades en memoria. Destruyendo las muertas
        cpct_waitVSYNC();       // Esperamos al refresco de pantalla
    }
}

void man_game_create_enemy(Entity_t *e_mother) {
    // Si ya hay un enemigo en el carril de arriba, no generamos otro.
    if(m_enemy_on_lane) return;

    // Creamos enemigo
    {
        Entity_t *e = man_game_create_template_entity(&enemy1_templ);
        e->x  = e_mother->x;
        e->vx = e_mother->vx;
    }
    // Marcamos que hay un enemigo
    m_enemy_on_lane = 1;
}