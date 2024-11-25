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
	

/* player setup ***********************************************************/
	player.danger_height=-16;
	//player.death_height=-18;
	player.skip=3;
	//player.v_speed=0;
	player.jump_impulse=7;
	player.h_step=1;

/* shot setup *************************************************************/
	shot.dist=22;
	shot.speed=1;
	shot.frame=SPRITE_END;
/* enemy setup ************************************************************/

/* terrain setup **********************************************************/
	
// /**************************************************************************/

	sprites_start();
	
	start_image();
	
	menu_main();
}