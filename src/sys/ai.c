#include <sys/ai.h>
#include <man/entity.h>

//-------------------------------------------------------------------------------
// Actualiza las físicas de una entidad
// INPUT: *e -> puntero a la entidad
//
void sys_ai_update_one_entity (Entity_t* e) {
    const u8 right_bound = 80 - e->w;

    if      (e->x == 0)           e->vx = 1;
    else if (e->x == right_bound) e->vx = -1;
}

void sys_ai_update() {
    // for all entities
    man_entity_forall_matching(sys_ai_update_one_entity, e_type_movable | e_type_ai);
}