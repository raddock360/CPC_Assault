#include <sys/collisions.h>
#include <man/entity.h>
#include <man/game.h>


/////////////////////////////////////////////////////////////////////////////////////
// UPDATE ONE ENTITY
//      Actualiza las colisiones de dos entidades con colisiones
// INPUT:
//      - Entity_t *e1 -> puntero a la primera entidad
//      - Entity_t *e2 -> puntero a la segunda entidad
//
void sys_collisions_update_entities (Entity_t* e1, Entity_t* e2) {
    // Comprobamos si las entidades PUEDEN colisionar
    // ¿Colisiona la entidad 1 contra la entidad 2?
    // ¿Colisiona la entidad 2 contra la entidad 1?
    // Si el OR da 0 significa que ninguna de las 2 entidades  puede colisionar
    // con la otra, así que retornamos. 
    // En caso contrario, significa que alguna de las dos entidades
    // tiene la capacidad de colisionar con la otra, así que continuamos. 
    u8 e1_col_e2 = e1->collide_against & e2->type;
    u8 e2_col_e1 = e2->collide_against & e1->type;
    if((e1_col_e2 | e2_col_e1) == 0) return;

    // Las entidades PUEDEN colisionar, así que comprobamos si realmente colisionan.
    // TODO
    if(((e1->x + e1->w) > e2->x) && (e1->x < (e2->x + e2->w))) { 
        if((e1->y < (e2->y + e2->h)) && ((e1->y + e1->h) > e2->y)) {
            man_game_entity_destroy(e1);
            man_game_entity_destroy(e2);
        }
    }
}

void sys_collisions_update() {
    // for all entities
    man_entity_forall_pairs_matching(sys_collisions_update_entities, e_cmp_collider);
}