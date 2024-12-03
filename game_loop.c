#ifndef _GAME_LOOP
#define _GAME_LOOP

void game_loop()
{
	//static u8 name[6];
	t_player=time();
	
	while (TRUE) {

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

		/* output_string(0, 0, "   ");
		if (player.v_speed<(-12)){
		itoa((100+player.v_speed), name);
		output_string(0, 0, name);
		} */
	}
}

#endif