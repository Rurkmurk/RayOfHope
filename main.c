#include <evo.h>
#include "resources.h"
#include <additions.h>
#include "init.h"
#include "load_level.h"
#include "output_string.h"


void draw_screen()
{
	u8 x, y;
	
	select_image(IMG_TILE);
	
	for (y=0; y<HIGH_LEVEL; y++)
		for (x=0; x<WIDTH_LEVEL; x++)
			draw_tile(x,y,map[x][y]);
}


void init_screen()
{
	u8 x, y;
	
	u8 n=0,m=0,i=0,j=0;

	
	select_image(IMG_TILE);


	for (y=0; y<HIGH_LEVEL; y++)
		for (x=0; x<WIDTH_LEVEL; x++)
		{
			if (map[x][y]==LAVA)
			{
				lava[n].x[m]=x;
				lava[n].y[0]=y;
				lava[n].tile[m]=32+m;
				draw_tile(lava[n].x[m],lava[n].y[0],lava[n].tile[m]);
				lava[n].y[1]=y+1;
				lava[n].tile[m+4]=36+m;
				
				m++;
				if (m>3)
				{
					lava_summ++;
					m=0;
					n++;
				}
			}
			if (map[x][y]==WATER_WAVE)
			{
				water[i].x[j]=x;
				water[i].y[0]=y;
				water[i].tile[j]=48+j;
				draw_tile(water[i].x[j],water[i].y[0],water[i].tile[j]);
				
				water[i].y[1]=y+3;
				water[i].tile[j+4]=56+j;
				draw_tile(water[i].x[j],water[i].y[1],water[i].tile[j+4]);
				
				j++;
				if (j>3)
				{
					water_summ++;
					j=0;
					i++;
				}
			}
			if (map[x][y]==PLAYER)
			{
				player.x=4*x;
				player.y=8*(y-1);
				map[x][y]=0;
				break;
			}
			player.frame=20;
		}	
}


void control_player()
{
	u8 key;
	u8 dx=0, dy=0, fire=0;
	
	
	key=joystick();
	if(key&JOY_UP)
	{
		dy=#0x1;
	}
	if(key&JOY_RIGHT)
	{
		dx=#0x4;
	}
	if(key&JOY_LEFT)
	{
		dx=#0x8;
	}
	if(key&JOY_DOWN)
	{
		dy=#0x2;
	}
	if(key&JOY_FIRE)
	{
		fire=#0x10;
	}
	if(key!=FALSE) t_idle=time();
	player.new_direct=dx+dy+fire;
}



u16 player_collision()
{
	static u16 collision;
	
	collision=0;
	//up
	if ((map[(player.x+2)/4][(player.y+1)/8]<32)&&(map[(player.x+5)/4][(player.y+1)/8]<32)) collision+=#0x1;
	//down
	if ((map[(player.x+3)/4][(player.y+16)/8]<16)&&(map[(player.x+4)/4][(player.y+16)/8]<16)) collision+=#0x2;
	//right
	if (map[(player.x+7)/4][(player.y)/8]<32&&map[(player.x+7)/4][(player.y+15)/8]<32) collision+=#0x4;
	//left
	if (map[player.x/4][player.y/8]<32&&map[player.x/4][(player.y+15)/8]<32) collision+=#0x8;
	//stairs up
	if ((map[(player.x+3)/4][(player.y+15)/8]>=16)&&(map[(player.x+3)/4][(player.y+15)/8]<32)) collision+=#0x20;
	//stairs down
	if ((map[(player.x+3)/4][(player.y+16)/8]>=16)&&(map[(player.x+3)/4][(player.y+16)/8]<32)) collision+=#0x40;
	//lava
	if ((map[(player.x+2)/4][(player.y+16)/8]==LAVA)&&(map[(player.x+5)/4][(player.y+16)/8]==LAVA)) collision+=#0x80;
	//water_wave
	if ((map[(player.x+2)/4][(player.y+16)/8]==WATER_WAVE)&&(map[(player.x+5)/4][(player.y+16)/8]==WATER_WAVE)) collision+=#0x2;
	//water
	if ((map[(player.x+2)/4][(player.y+16)/8]==WATER)&&(map[(player.x+5)/4][(player.y+16)/8]==WATER)) collision+=#0x100;
	//water plant
	if ((map[(player.x+2)/4][(player.y+16)/8]==WATER_PLANTS)&&(map[(player.x+5)/4][(player.y+16)/8]==WATER_PLANTS)) collision+=#0x200;
	
	return (collision);
}


void update_player()
{
	set_sprite(0,player.x,player.y,player.frame);
	
}

void update_terrain()
{
	u8 n,m;
	u8 tmp;
		
	if (t_terrain+10<time())
	{
		//lava anim
		select_image(IMG_TILE);
		for (n=0;n<lava_summ;n++)
		{
			tmp=lava[n].tile[0];
			lava[n].tile[0]=lava[n].tile[1];
			lava[n].tile[1]=lava[n].tile[2];
			lava[n].tile[2]=lava[n].tile[3];
			lava[n].tile[3]=tmp;
			
			tmp=lava[n].tile[4];
			lava[n].tile[4]=lava[n].tile[5];
			lava[n].tile[5]=lava[n].tile[6];
			lava[n].tile[6]=lava[n].tile[7];
			lava[n].tile[7]=tmp;
			
			
			for (m=0;m<4;m++)
			{
				draw_tile(lava[n].x[m],lava[n].y[0],lava[n].tile[m]);
				draw_tile(lava[n].x[m],lava[n].y[1],lava[n].tile[m+4]);
			}
		}
		
	
	
		// water anim
		for (n=0;n<water_summ;n++)
		{
			tmp=water[n].tile[0];
			water[n].tile[0]=water[n].tile[1];
			water[n].tile[1]=water[n].tile[2];
			water[n].tile[2]=water[n].tile[3];
			water[n].tile[3]=tmp;
			
			switch (n_frame)
			{
				case 0:
				water[n].tile[4]+=4;
				water[n].tile[5]+=4;
				water[n].tile[6]+=4;
				water[n].tile[7]+=4;
				break;
				case 1:
				water[n].tile[4]-=4;
				water[n].tile[5]-=4;
				water[n].tile[6]-=4;
				water[n].tile[7]-=4;
				break;
			}
			
			for (m=0;m<4;m++)
			{
				draw_tile(water[n].x[m],water[n].y[0],water[n].tile[m]);
				draw_tile(water[n].x[m],water[n].y[1],water[n].tile[m+4]);
			}
		}	
		
		if (n_frame==0) n_frame=1;
		else n_frame=0;
		t_terrain=time();
	}
	swap_screen();
}

void player_logic()
{
	static u8 i;
	u8 j;
	
	if (!player.healt) return;
	
	if (t_player+3<time()){

	// idle
	if ((player.new_direct==#0x0)&&((player.old_direct&JUMP)!=JUMP))
	{
		if (t_idle+250>time()) player.frame=20;
		else if (t_idle+300>time()) player.frame=21;
		else t_idle=time();
	}
	
	// drop down
	if ((player_collision()&#0x2)==#0x2&&!player.gravity)
	{
		if ((player.h_velocity>0)&&(player_collision()&RIGHT)==RIGHT)
		{
			player.x+=1;
			player.h_velocity--;
			player.frame=18;
		}
		else if ((player.h_velocity<0)&&(player_collision()&LEFT)==LEFT)
		{
			player.x-=1;
			player.h_velocity++;
			player.frame=19;
		}
		else
		{
			player.frame=21;
		}
		player.y+=1;
		return;
	}		
	
	//move right
	if ((player.new_direct^RIGHT)==#0x0)
	{
		if ((player.old_direct&RIGHT)!=RIGHT)
		{
			player.frame=0;
			player.old_direct^=RIGHT;
		}
		if ((player_collision()&RIGHT)==RIGHT)
		{
			player.x+=1;
			player.frame=(player.frame<7)?++player.frame:0;
		}
		else
		{
			player.frame=0;
		}
	}

	//move left
	if ((player.new_direct^LEFT)==#0x0)
	{
		if ((player.old_direct&LEFT)!=LEFT)
		{
			player.frame=8;
			player.old_direct^=#0x8;
		}
		if ((player_collision()&LEFT)==LEFT)
		{
			player.x-=1;
			player.frame=(player.frame<15)?++player.frame:8;
		}
		else
		{
			player.frame=8;
		}
	}

	//jump
	if ((player.new_direct&JUMP)==JUMP||player.gravity)
	{
		if ((player.old_direct&JUMP)!=JUMP)
		{
			player.frame=22;
			if ((player_collision()&#0x1)==#0x1)player.gravity=GRAVITY;
			else player.gravity=0;
			player.old_direct=player.new_direct;
			return;
		}
		if ((player.old_direct&RIGHT)==RIGHT)
		{
			player.h_velocity=4;
			player.frame=18;
			player.y-=player.gravity;
			player.gravity-=1;
			if ((player_collision()&RIGHT)==RIGHT) player.x+=1;
		}
		else if ((player.old_direct&LEFT)==LEFT)
		{
			player.h_velocity=-4;
			player.frame=19;
			player.y-=player.gravity;
			player.gravity-=1;
			if ((player_collision()&LEFT)==LEFT) player.x-=1;
		}
		else
		{
			player.h_velocity=0;
			player.frame=21;
			player.y-=player.gravity;
			player.gravity-=1;
		}
		if (!player.gravity)
		{
			player.old_direct=#0x0;
		}
	}
	

	// stairs up
	/* if (direct==#0x1&&(player_collision()&#0x21)==#0x21)
	{
		player.frame=23;
		if (map[player.x/4][(player.y+15)/8]>15&&map[player.x/4][(player.y+15)/8]<32) player.x=player.x-(player.x%4);
		else player.x=player.x-(player.x%4)+4;
				
		while (control_player()==#0x1)
			{
				if ((player_collision()&#0x20)==#0x20)
				{
					player.y-=2;
					update();
				}
				player.frame++;
				if (player.frame>26) player.frame=23;
			}
	} */
	
	//jump up
	// if (direct==#0x1&&(player_collision()&#0x20)!=#0x20)
	// {
		// set_sprite(0,player.x,player.y,22);
		// swap_screen();
		// set_sprite(0,player.x,player.y,22);
		// swap_screen();
		// set_sprite(0,player.x,player.y,20);
		// swap_screen();
		// set_sprite(0,player.x,player.y,21);
		// swap_screen();
		// for (i=0;i<5;i++)
		// {
			// if ((player_collision()&#0x1)==#0x1) player.y-=2;
			// set_sprite(0,player.x,player.y,21);
			// swap_screen();
			// delay (i/2);
		// }
		// while ((player_collision()&#0x2)==#0x2)
		// {
			// player.y+=2;
			// set_sprite(0,player.x,player.y,21);
			// swap_screen();
		// }
	// }
	
	

	//jump left
	/* if (direct==#0x9)
	{
		player.frame=19;
		for (i=0;i<4;i++)
		{
			if ((player_collision()&#0x1)==#0x1) player.y-=2;
			if ((player_collision()&#0x8)==#0x8) player.x-=1;
			update();
		}
		
		for (j=0;j<4;j++)
		{
			if ((player_collision()&#0x8)==#0x8) player.x-=1;
			update();
		}
		
		while ((player_collision()&#0x2)==#0x2)
		{
			
			player.y+=2;
			// if (i>1&&(player_collision()&#0x8)==#0x8)
			// {
				// i--;
				// player.x-=1;
			// }

			update();
			
		}
		player.old_direct=LEFT;
	} */
	
	//fire left
	/* if (direct==#0xA)
	{
		player.frame=17;
		update();
		player.old_direct=LEFT;
	} */
	
	//fire right
	/* if (direct==#0x6)
	{
		player.frame=16;
		update();
		player.old_direct=RIGHT;
	} */
	
	//down
	/* if (direct==#0x2)
		if ((player_collision()&#0x40)==#0x40)
		{
			player.frame=23;
			if (map[player.x/4][(player.y+16)/8]>15&&map[player.x/4][(player.y+16)/8]<32) player.x=player.x-(player.x%4);
			else player.x=player.x-(player.x%4)+4;
					
			while (control_player()==#0x2)
			{
				if ((player_collision()&#0x40)==#0x40)
				{
					player.y+=2;
					update();
				}
				player.frame++;
				if (player.frame>26) player.frame=23;
			}
		}
		else
		{
			if (player.old_direct==RIGHT)
				player.frame=16;
			else
				player.frame=17;
			update();
		} */
		
	//lava
	if ((player_collision()&#0x80)==#0x80)
	{
		for (i=0;i<16;i++)
		{
			player.y+=1;
			player.frame=21;
		//	update();
		}
		for (i=0;i<3;i++)
		{
			player.frame=29+i;
		//	update();
		}
		player.frame=27;
		//update();
		while (1);
	}
	//water
	if ((player_collision()&#0x100)==#0x100)
	{
		player.y+=1;
		player.frame=28;
	}
	
	//water plants
	if ((player_collision()&#0x200)==#0x200)
	{
		player.y+=8;
		player.frame=28;
		player.healt=0;
	}
	t_player=time();}
}


void main(void)
{
	u8 name[3];
	//t_terrain=time();
	player.healt=100;
	player.old_direct=0;
	player.h_velocity=0;
	
	pal_select(PAL_PALETTE0);
	clear_screen(0);
	select_image(IMG_TILE);
	
	sprites_start();
	
	load_level();
	
	draw_screen();
	
	init_screen();

	
	while (1)
	{
		control_player();
		player_logic();
		update_player();
		update_terrain();


		output_string(1, 1, "   ");
		itoa((player_collision()&#0x2), name);
		output_string(1, 1, name);
		
	}
	
}