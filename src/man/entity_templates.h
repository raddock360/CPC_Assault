#include <man/entity.h>

#define LANE_DY     30                      // Distancia entre carrilles
#define LANE2_Y     40                      // Carril mas próximo a nave nodriza
#define LANE1_Y     (LANE2_Y + LANE_DY)     // Carril intermedio
#define LANE0_Y     (LANE2_Y + 2*(LANE_DY)) // Carril mas alejado de la nave nodriza

#define PLAYER_X    38                      // Posición X inicial del jugador
#define PLAYER_Y    180                     // Posición Y inicial del jugador
#define PLAYERSHOT_Y (PLAYER_Y - 8)         // Posición Y inicial del disparo del jugador

extern const Entity_t mothership_templ;
extern const Entity_t playership_templ;
extern const Entity_t player_templ;
extern const Entity_t enemy1_templ;
extern const Entity_t vshoot_templ;
extern const Entity_t vshoot_enemy_templ;
