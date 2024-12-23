#ifndef _GAME_LOOP
#define _GAME_LOOP

void game_loop()
{
	t_player=time();
	
	switch (model){
		case EVO:
			while (TRUE) {
				
				control_player();
				
				if (t_player+4<=time()) {
					player_logic();
					player_animation();
					t_player=time();
				}

				if (t_player+3<=time()) {
					terrain_animation();
				}

				enemy_logic();

				shot_logic();

				update_screen();
			}
		break;
		case ATM:
			while (TRUE) {
				
				if (t_player==time()) vsync();
				t_player=time();
				shot_logic();
				enemy_logic();
				
				if (t_player==time()) vsync();
				t_player=time();
				control_player();
				player_logic();
				player_animation();
				shot_logic();
				
				if (t_player==time()) vsync();
				shot_logic();
				enemy_logic();
				//t_player=time();
				update_screen();
				
				t_player=time();
				terrain_animation();
				enemy_logic();
				shot_logic();
				
			}
		break;
	}
	
	
}

#endif