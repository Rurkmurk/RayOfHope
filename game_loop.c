#ifndef _GAME_LOOP
#define _GAME_LOOP

void game_loop()
{
	t_player=time();
	
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
}

#endif