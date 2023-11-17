#include <evo.h>
#include "resources.h"
#include <additions.h>
#include "init_define.h"
#include "output_string.h"
#include "load_level.h"
#include "init_screen.h"
#include "player.h"
#include "update_screen.h"



void main(void)
{
	u8 name[6];
	
	p.healt=100;
	p.old_direct=0;
	p.v_speed=0;
	p.jump_impulse=7;
	p.h_speed=1;
	
	pal_select(PAL_PALETTE0);
	clear_screen(0);
	select_image(IMG_TILE);
	
	load_level();
	
	sprites_start();
	
	draw_screen();

	init_screen();
	
	while (1)
	{
		control_player();

		if (t_player+4<time())
		{
			player_logic();
			t_player=time();
		}	
	
		

		
		update_player();
		
		border (2);
		update_terrain();
		border (0);
		
		swap_screen();

		output_string(1, 1, "      ");
		itoa(p.v_speed, name);
		output_string(1, 1, name);
		
	}
	
}