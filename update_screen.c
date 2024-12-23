#ifndef _UPDATE_SCREEN
#define _UPDATE_SCREEN

void update_screen()
{
	static u8 n, summ;

	//player
	set_sprite(0,player.x,player.y,player.frame);

	//enemy
	for (n=1;n<=enemy_summ;n++)
		set_sprite(n,enemy[n].x,enemy[n].y,enemy[n].frame);
	
	//water
	summ=enemy_summ;
	for (n=1;n<=water_summ;n++){
		set_sprite(n+summ,water[n].x,water[n].y,water[n].frame);
	}
	
	//waterplant
	summ+=water_summ;
	for (n=1;n<=waterplant_summ;n++){
		set_sprite(n+summ,waterplant[n].x,waterplant[n].y,waterplant[n].frame);
	}
	
	//light
	summ+=waterplant_summ;
	for (n=1;n<=light_summ;n++)
		set_sprite(n+summ,light[n].x,light[n].y,light[n].frame);
	
	//fan
	summ+=light_summ;
	for (n=1;n<=fan_summ;n++)
		set_sprite(n+summ,fan[n].x,fan[n].y,fan[n].frame);
	
	//shot
	summ+=fan_summ;
	set_sprite(summ+1,shot.x,shot.y,shot.frame);
	
	//end
	set_sprite(summ+2,0,0,SPRITE_END);

	swap_screen();
}

void update_hud()
{
	static u8 n;
	
	select_image(IMG_TILE_HUD);
	for (n=0;n<10;n++)
		draw_tile(5+n,23,(20*player.health)+n);
	for (n=0;n<10;n++)
		draw_tile(27+n,23,(20*player.ammo)+n+10);
	for (n=0;n<6;n++)
		draw_tile(17+n,23,214+n+(player.life*6));
}


void open_box (u8 y, u8 x)
{
	static u16 addr;
	
	select_image(level_tile);
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
