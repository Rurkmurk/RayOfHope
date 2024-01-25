#include <evo.h>
#include "resources.h"
//#include <additions.h>
#include "init_define.h"
#include "output_string.h"
#include "load_level.h"
#include "init_screen.h"
#include "player.h"
#include "shot.h"
#include "enemy.h"
#include "update_screen.h"



void main()
{
	u8 name[6];
	u8 slime_skip;
	
/* player setup ***********************************************************/
	player.deadly_height=-15;
	player.skip=3;
	player.v_speed=0;
	player.jump_impulse=7;
	player.h_step=1;

/* shot setup *************************************************************/
	shot.dist=20;
	shot.speed=2;
	shot.frame=SPRITE_END;
	
/* enemy setup ************************************************************/
	slime_skip=5;
/**************************************************************************/
	
	pal_select(PAL_PALETTE0);
	clear_screen(0);
	select_image(IMG_TILE);
	
	load_level();
	
	sprites_start();
	draw_screen();
	init_screen();
	
	for (;;) {
		
		control_player();
		
		if (t_player+player.skip<time()) {
			player_logic();
			player_animation();
			t_player=time();
		}

		shot_logic();
		
		if (t_slime+slime_skip<time()) {
			enemy_logic();
			enemy_animation();
			t_slime=time();
		}

		//update_terrain();

		update_sprite();

		swap_screen();
		
		

		// output_string(0, 24, "     ");
		// itoa(enemy[1].frame-SPR_B_SLIME, name);
		// output_string(0, 24, name);
		
	}
	
}