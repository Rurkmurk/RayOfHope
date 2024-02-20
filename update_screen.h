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
	
	//hud
	select_image(IMG_TILE_HUD);
	for (n=0;n<5;n++)
		draw_tile(4+n,23,120+(40*player.health)+n);
	for (n=0;n<5;n++)
		draw_tile(33+n,23,125+(40*player.ammo)+n);
		
}

#endif