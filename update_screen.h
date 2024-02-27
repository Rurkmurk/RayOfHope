#ifndef _UPDATE_SCREEN
#define _UPDATE_SCREEN

void update_screen()
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
	
	//end
	set_sprite(enemy_summ+waterplant_summ+water_summ+2,0,0,SPRITE_END);
		
	swap_screen();
}

void update_hud()
{
	u8 n;
	select_image(IMG_TILE_HUD);
	for (n=0;n<5;n++)
		draw_tile(4+n,23,120+(40*player.health)+n);
	for (n=0;n<5;n++)
		draw_tile(33+n,23,125+(40*player.ammo)+n);
}


void open_box (u8 y, u8 x)
{
	u16 addr;
	
	select_image(IMG_TILE_SNOW);
	color_key(15);
	draw_tile_key(x,y-1,216);
	draw_tile_key(x+1,y-1,217);
	draw_tile_key(x,y,232);
	draw_tile_key(x+1,y,233);
	
	update_hud();
	
	addr=32768+(40*screen)+((40*level_size*(y-1))+x);
	put_mem(PAGE_GFX,addr,216);
	addr=32768+(40*screen)+((40*level_size*(y-1))+x+1);
	put_mem(PAGE_GFX,addr,217);
	addr=32768+(40*screen)+((40*level_size*y)+x);
	put_mem(PAGE_GFX,addr,232);
	addr=32768+(40*screen)+((40*level_size*y)+x+1);
	put_mem(PAGE_GFX,addr,233);
	
	addr=32768+(40*screen)+(40*level_size*y+x);
	put_mem(PAGE_MAP,addr,0);
}

#endif
