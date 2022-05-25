#include <sys/physics.h>
#include <man/entity.h>

//-------------------------------------------------------------------------------
// Comprueba el teclado para la entidad recibida.
// INPUT: *e -> puntero a la entidad.
//
void sys_physics_check_keyboard(Entity_t *e) {
    cpct_scanKeyboard_f();

    e->vx = 0;
    if      (cpct_isKeyPressed(Key_O)) e->vx = -1;    
    else if (cpct_isKeyPressed(Key_P)) e->vx =  1;
}

//-------------------------------------------------------------------------------
// Actualiza las físicas de una entidad
// INPUT: *e -> puntero a la entidad
//
void sys_physics_update_one_entity (Entity_t* e) {
    // Si la entidad tiente input, comprobamos el teclado
    if(e->type & e_type_input) 
        sys_physics_check_keyboard(e);

    e->x += e->vx;
    e->y += e->vy;
}

void sys_physics_update() {
    // for all entities
    man_entity_forall_matching(sys_physics_update_one_entity, e_type_movable);
}