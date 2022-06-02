#include <man/entity.h>

#define LANE_DY     30
#define LANE2_Y     40
#define LANE1_Y     (LANE2_Y + LANE_DY)
#define LANE0_Y     (LANE2_Y + 2*(LANE_DY)) 

#define PLAYER_X    38
#define PLAYER_Y    180
#define PLAYERSHOT_Y (PLAYER_Y - 8)

extern const Entity_t mothership_templ;
extern const Entity_t playership_templ;
extern const Entity_t player_templ;
extern const Entity_t enemy1_templ;
extern const Entity_t vshoot_templ;