#include <cpctelera.h>
#include <sys/animation.h>
#include <man/entity.h>


/////////////////////////////////////////////////////////////////////////////////////
// UPDATE ONE ENTITY
//      Actualiza la animación de una entidad
// INPUT:
//      - Entity_t *e -> puntero a la entidad
//
void sys_animation_update_one_entity (Entity_t* e) {
    // Cambia el sprite cuando el contador e_anim_counter es 0
    if(--(e->anim_counter) == 0) {
        ++ e->anim;
        // Si se terminan los sprites, volvemos al principio 
        if(e->anim->time == 0){
            e->anim = e->anim->val.next;
        }
        // Carga el siguiente sprite de la animación
        e->sprite = e->anim->val.sprite;
        e->anim_counter = e->anim->time;
    }
}

void sys_animation_update() {
    // for all entities
    man_entity_forall_matching(sys_animation_update_one_entity, e_type_animated);
}