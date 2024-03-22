#include <evo.h>
#include "resources.h"
#include "init_define.h"
#include "output_string.h"
#include "load_level.h"
#include "update_screen.h"
#include "init_screen.h"
#include "player.h"
#include "shot.h"
#include "enemy.h"
#include "terrain.h"


void main()
{
	//u8 name[6];

	
	
/* player setup ***********************************************************/
	player.danger_height=-14;
	player.death_height=-18;
	player.skip=3;
	player.v_speed=0;
	player.jump_impulse=7;
	player.h_step=1;

/* shot setup *************************************************************/
	shot.dist=20;
	shot.speed=2;
	shot.frame=SPRITE_END;
	
/* enemy setup ************************************************************/


/* terrain setup **********************************************************/

	
/**************************************************************************/
	
	pal_select(0);
	clear_screen(0);
	
	sprites_start();
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
		// itoa(time(), name);
		// output_string(0, 24, name);
		
	}
	
}