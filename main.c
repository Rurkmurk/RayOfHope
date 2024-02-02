#include <evo.h>
#include "resources.h"
#include "init_define.h"
#include "output_string.h"
#include "load_level.h"
#include "init_screen.h"
#include "update_screen.h"
#include "player.h"
#include "shot.h"
#include "enemy.h"




void main()
{
	u8 name[6];
	u8 enemy_skip;
	
/* player setup ***********************************************************/
	player.deadly_height=-15;
	player.skip=3;
	player.v_speed=0;
	player.jump_impulse=6;
	player.h_step=1;
	player.x=8;
	player.y=120;
	player.health=10;
	player.frame=20;

/* shot setup *************************************************************/
	shot.dist=20;
	shot.speed=2;
	shot.frame=SPRITE_END;
	
/* enemy setup ************************************************************/
	enemy_skip=5;
/***************************************************************************/
	
	pal_select(0);
	clear_screen(0);
	
	load_level();
	load_img();
	sprites_start();
	draw_screen();
	
	load_map();
	init_screen();
	
	for (;;) {
		
		control_player();
		
		if (t_player+player.skip<time()) {
			player_logic();
			player_animation();
			t_player=time();
		}

		
		
		if (t_enemy+enemy_skip<time()) {
			enemy_logic();
			enemy_animation();
			t_enemy=time();
		}
		
		shot_logic();
		//update_terrain();

		update_sprite();

		swap_screen();
		
		

		output_string(0, 24, "     ");
		itoa(player.health, name);
		output_string(0, 24, name);
		
	}
	
}