#include <man/entity.h>
#include <sprites/enemigo1.h>
#include <man/animation.h>

const AnimFrame_t man_anim_enemy1[] = {
    {man_anim_enemy1_time, {.sprite = spr_enemigo1_0    }}, 
    {man_anim_enemy1_time, {.sprite = spr_enemigo1_1    }}, 
    {                   0, {.next   = man_anim_enemy1   }}
};