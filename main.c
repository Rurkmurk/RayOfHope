#include <evo.h>
#include "resources.h"
//#include <additions.h>
#include "init_define.h"
#include "output_string.h"
#include "load_level.h"
#include "init_screen.h"
#include "player.h"
#include "shot.h"
#include "update_screen.h"



void main(void)
{
	u8 name[6];
	
	p.deadly_height=-10;
	p.healt=100;
	p.speed=2;
	p.v_speed=0;
	p.jump_impulse=7;
	p.h_step=1;
	
	s.n=0;
	s.frame=SPRITE_END;
	
	pal_select(PAL_PALETTE0);
	clear_screen(0);
	select_image(IMG_TILE);
	
	load_level();
	
	sprites_start();
	
	draw_screen();

	init_screen();
	
	for (;;) {
				
		control_player();
		
		if (t_player+p.speed<time()) {
			player_logic();
			animation_player();
			t_player=time();
		}

		shot_logic();
		
		//update_terrain();

		update_sprite();
		swap_screen();
		
		

		output_string(1, 1, "     ");
		itoa(shot_collision(), name);
		output_string(1, 1, name);
		
	}
	
}