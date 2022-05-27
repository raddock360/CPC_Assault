#pragma once
#include <cpctelera.h>
#include <sprites/enemigo1.h>

struct AnimFrame_t {
    u8  time;
    const u8* sprite;
};

const struct AnimFrame_t man_anim_enemy1[2] = {
    {12, spr_enemigo1_0}, 
    {12, spr_enemigo1_1},
    {0, 0x0000}
};