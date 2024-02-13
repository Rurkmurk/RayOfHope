#ifndef _UPDATE_SCREEN
#define _UPDATE_SCREEN

void update_sprite()
{
	u8 n;
	//player
	set_sprite(0,player.x,player.y,player.frame);

	//enemy
	for (n=1;n<=enemy_summ;n++)
		set_sprite(n,enemy[n].x,enemy[n].y,enemy[n].frame);
	
	//water
	for (n=1;n<=water_summ;n++){
		set_sprite(n+enemy_summ,water[n].x,water[n].y,water[n].frame);
		set_sprite(n+enemy_summ+water_summ,waterplant[n].x,waterplant[n].y,waterplant[n].frame);
	}
	
	
	//shot
	set_sprite(enemy_summ+waterplant_summ+water_summ+1,shot.x,shot.y,shot.frame);
}


void nex_screen()
{
	screen++;
	player.x=1;
	//load_img();
	draw_screen();
	load_map();
	init_screen();
}

void prv_screen()
{
	screen--;
	player.x=152;
	//load_img();
	draw_screen();
	load_map();
	init_screen();
}

#endif