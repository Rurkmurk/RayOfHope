#include <evo.h>
#include "resources.h"
#include "init_define.c"
#include "output_string.c"
#include "start_menu.c"
#include "load_level.c"
#include "update_screen.c"
#include "init_screen.c"
#include "player.c"
#include "shot.c"
#include "enemy.c"
#include "terrain.c"


void main()
{
	// u8 name[6];

	
	
/* player setup ***********************************************************/
	player.danger_height=-14;
	player.death_height=-18;
	player.skip=3;
	//player.v_speed=0;
	player.jump_impulse=7;
	player.h_step=1;

/* shot setup *************************************************************/
	shot.dist=20;
	shot.speed=2;
	shot.frame=SPRITE_END;
	
/* enemy setup ************************************************************/


/* terrain setup **********************************************************/
	level=1;
	
/**************************************************************************/

	
	sprites_start();
	start();
	// load_level();
	// chapter();
	start_level();

	for (;;) {
		
		control_player();
		
		if (t_player+3<time()) {
			player_logic();
			player_animation();
			t_player=time();
		}

		if (t_player+2==time()) {
			terrain_animation();
		}
		
		enemy_logic();
		
		shot_logic();

		update_screen();

		
		
		

		// output_string(0, 24, "     ");
		// itoa(player.y, name);
		// output_string(0, 24, name);
		
	}
	
}