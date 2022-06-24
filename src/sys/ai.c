#include <man/entity.h>
#include <sys/ai.h>
#include <man/game.h>

///////////////////////////////////////////////////////////////////////////////////
// BEHAVIOUR MOTHERSHIP
//      Define comportamiento de la nave nodriza 
// INPUT: 
//      *e -> puntero a la entidad
//
void sys_ai_behaviour_mothership(Entity_t* e) {
    if(e->x == 20) {
        man_game_create_enemy(e);
    }
    sys_ai_behaviour_left_right(e);
}

///////////////////////////////////////////////////////////////////////////////////
// BEHAVIOUR LEFT RIGTH
//      Comportamiento de movimiento izquierda derecha 
// INPUT: 
//      *e -> puntero a la entidad
//
void sys_ai_behaviour_left_right(Entity_t* e) {
    const u8 right_bound = 80 - e->w;

    if      (e->x == 0)           e->vx = 1;
    else if (e->x == right_bound) e->vx = -1;
}

///////////////////////////////////////////////////////////////////////////////////
// BEHAVIOUR ENEMY
//      Comportamiento de la nave enemiga
// INPUT: 
//      *e -> puntero a la entidad
//
void sys_ai_behaviour_enemy(Entity_t* e) {
    if(!(e->x & 7)) {
        man_game_enemy_lane_down(e);
    }
    sys_ai_behaviour_left_right(e);
    sys_ai_behaviour_enemy_shoot(e);
}

///////////////////////////////////////////////////////////////////////////////////
// BEHAVIOUR ENEMY
//      Comportamiento de la nave enemiga
// INPUT: 
//      *e -> puntero a la entidad
//
void sys_ai_behaviour_enemy_shoot(Entity_t *e) {
    man_game_enemy_shoot(e);
}

///////////////////////////////////////////////////////////////////////////////////
// BEHAVIOUR AUTODESTROY
// INPUT: 
//      *e -> puntero a la entidad
//
void sys_ai_vehaviour_autodestroy(Entity_t* e) {
    if(--(e->ai_counter) == 0)
        man_game_entity_destroy(e);
}

///////////////////////////////////////////////////////////////////////////////////
// UPDATE ONE ENTITY
//      Actualiza las físicas de una entidad, basándose en su comportamiento. 
// INPUT: 
//      *e -> puntero a la entidad
//
void sys_ai_update_one_entity (Entity_t* e) {
    e->ai_vehaviour(e);
}

void sys_ai_update() {
    // for all entities
    man_entity_forall_matching(sys_ai_update_one_entity, e_cmp_movable | e_cmp_ai);
}