#include <evo.h>
#include "resources.h"
#include "init_define.c"
#include "output_string.c"
#include "load_level.c"
#include "start_menu.c"
#include "update_screen.c"
#include "init_screen.c"
#include "player.c"
#include "shot.c"
#include "enemy.c"
#include "terrain.c"
#include "game_loop.c"


void main()
{
	
	model=EVO;

/* player setup ***********************************************************/
	player.danger_height=-16;
	player.jump_impulse=7;
	player.h_step=1;

/* shot setup *************************************************************/
	shot.dist=22;
	shot.speed=1;
	shot.direct=FALSE;
	shot.status=FALSE;
	shot.frame=SPRITE_END;
/* enemy setup ************************************************************/
	stalact_speed=1;
/* terrain setup **********************************************************/
	
// /**************************************************************************/

	speed_meter();
	
	sprites_start();
	
	start_image();
	
	menu_main();
}