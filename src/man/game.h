#pragma once
#include <man/entity.h>

//**************************************************************
// FUNCIONES PÚBLICAS
//**************************************************************
void man_game_init              ();
void man_game_play              ();
void man_game_create_enemy      (Entity_t *e_mother);
void man_game_enemy_lane_down   (Entity_t* e_enemy);
