#include "physics.h"
#include "man/entity.h"

void sys_physics_update_one_entity( Entity_t* e ) {
    u8 newx = e->x + e->vx;
    if(newx > e->x) 
        man_entity_destroy( e );
        //man_entity_set4destruction( e );
    else
        e->x = newx;
}

void sys_physics_update() {
    // for all entities
    man_entity_forall( sys_physics_update_one_entity );
}