#pragma once
#include <man/entity.h>

typedef union  SpNx_t SpriteOrNextFrame_t;
typedef struct AnFr_t AnimFrame_t;

union SpNx_t {
    u8* const           sprite;
    AnimFrame_t* const  next;
};

struct AnFr_t {
    u8 const            time;
    SpriteOrNextFrame_t val;
};

//**********************************************************************************
// CONSTANTES PÚBLICAS
//**********************************************************************************

////////////////////////////////////////////////////////////////////////////////////
// Animaciones
#define man_anim_enemy1_time 12
extern const AnimFrame_t man_anim_enemy1[];