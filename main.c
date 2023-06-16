#include <evo.h>
#include "resources.h"
#include <additions.h>

#define	HIGH_LEVEL	25
#define	WIDTH_LEVEL	40

#define RIGHT 1
#define LEFT 0

#define PLAYER 240
#define WATER 241
#define WATER_PLANTS 242
#define LAVA 243

u32 t=0, t_idle=0;
u8 lava_summ=0;
u8 water_summ=0;
u8 n_frame=0;

static u8 map[WIDTH_LEVEL][HIGH_LEVEL];

struct
{
	u8 x;	
	u8 y;
	u8 healt;
	u8 frame;
	u8 last_direct;
}player;

struct
{
	u8 x[4];	
	u8 y[2];
	u8 tile[8];
}lava[2];

struct
{
	u8 x[4];	
	u8 y[2];
	u8 tile[8];
}water[2];


void load_level()
{
	u8 x, y;
	u8 j=0;
	u16 i=0;
	u8 buf[3];
	
	load_file("map00001", 30, 1);
		
	for (y=0;y<HIGH_LEVEL;y++)
		for (x=0;x<WIDTH_LEVEL;x++)
		{
			
			do
			{
				buf[j]=get_mem(30,32768+i)-48; // 48 is 30 in HEX
				j++;
				i++;
			}while (get_mem(30,32768+i)!=#0x2C);
			
			
			if (j==3) map[x][y]=100*buf[0]+10*buf[1]+buf[2];
			else if (j==2) map[x][y]=10*buf[0]+buf[1];
			else map[x][y]=buf[0];
			
			i++;

			j=0;
		}
}


void draw_level()
{
	u8 x, y;
	
	select_image(IMG_TILE);
	
	for (y=0; y<HIGH_LEVEL; y++)
		for (x=0; x<WIDTH_LEVEL; x++)
			draw_tile(x,y,map[x][y]);
}


void init_terrain()
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
			if (map[x][y]==WATER)
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
		}	
}


void draw_player()
{
	u8 x, y;
	
	for (y=0; y<HIGH_LEVEL; y++)
		for (x=0; x<WIDTH_LEVEL; x++)
			if (map[x][y]==PLAYER)
			{
				player.x=4*x;
				player.y=8*(y-1);
				map[x][y]=0;
				break;
			}
	player.frame=20;
}


u8 control_player()
{
	u8 key;
	u8 dx=0, dy=0, fire=0;
	u8 direct=0;
	
	//vsync();
	key=joystick();
	//vsync();
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
	direct=dx+dy+fire;
	return (direct);
}


void output_string(u8 output_x, u8 output_y, u8* str)
{
	u8 n;
	u8 save_output_x=output_x;
	select_image(IMG_FONT);
	color_key (15);
	while(1)
	{
		n=*str++;
		if(!n) break;
		draw_tile_key(output_x,output_y,n-32);
		output_x++;
		if (output_x>=40)
		{
			output_x=save_output_x;
			output_y++;
		}
	}
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
	if ((map[(player.x+3)/4][(player.y+16)/8]>=16)&&(map[(player.x+3)/4][(player.y+16)/8]<32))collision+=#0x40;
	//lava
	if ((map[(player.x+2)/4][(player.y+16)/8]==LAVA)&&(map[(player.x+5)/4][(player.y+16)/8]==LAVA))collision+=#0x80;
	//water
	if ((map[(player.x+2)/4][(player.y+16)/8]==WATER)&&(map[(player.x+5)/4][(player.y+16)/8]==WATER))collision+=#0x100;
	
	return (collision);
}


void update()
{
	u8 n,m;
	u8 tmp;
	
	//player anim
	set_sprite(0,player.x,player.y,player.frame);
	
		
	if (t+5<time())
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
		t=time();
	}
	border (13);
	swap_screen();
	
}





void idle()
{
	if ((player_collision()&#0x20)==#0x20)
	{
		player.frame=23;
		update();
	}
	else
	{
		if (t_idle+250>time())
		{
			player.frame=20;
			update();
		}
		else if (t_idle+300>time())
		{
			player.frame=21;
			update();
		}
		else
		{
			t_idle=time();
		}
	}
	
}


void player_move (u16 direct)
{
	u8 i,j;
	
	if (direct==#0x0||direct==#0x1) idle();
	
	//move right
	if (direct==#0x4)
	{
		i=0;
		while (control_player()==#0x4)
		{
			if ((player_collision()&#0x4)==#0x4)
			{
				player.x+=1;
				player.frame=i;
				update();
				i++;
				if (i>7) i=0;
				if ((player_collision()&#0x2)==#0x2) player.x+=2;
				while ((player_collision()&#0x2)==#0x2)
				{
					player.y+=2;
					
					player.frame=21;
					update();
				}
			}
			else
			{
				player.frame=0;
				update();
			}
		}
		player.last_direct=RIGHT;
	}

	//move left
	if (direct==#0x8)
	{
		i=8;
		while (control_player()==#0x8)
		{
			if ((player_collision()&#0x8)==#0x8)
			{
				player.x-=1;
				player.frame=i;
				update();
				i++;
				if (i>15) i=8;
				if ((player_collision()&#0x2)==#0x2) player.x-=2;
				while ((player_collision()&#0x2)==#0x2)
				{
					player.y+=2;
					player.frame=21;
					update();
				}
			}
			else
			{
				player.frame=8;
				update();
			}
		}
		player.last_direct=LEFT;
	}
	
	// stairs up
	if (direct==#0x1&&(player_collision()&#0x21)==#0x21)
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
	}
	
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
	
	//jump right
	if (direct==#0x5)
	{
		player.frame=18;
		for (i=0;i<4;i++)
		{
			if ((player_collision()&#0x1)==#0x1) player.y-=2;
			if ((player_collision()&#0x4)==#0x4) player.x+=1;
			update();
		}
			
		for (j=0;j<4;j++)
		{
			if ((player_collision()&#0x4)==#0x4) player.x+=1;
			update();
		}
		
		
		while ((player_collision()&#0x2)==#0x2)
		{
			
			player.y+=2;
			// if (i>1&&(player_collision()&#0x4)==#0x4)
			// {
				// i--;
				// player.x+=1;
			// }

			update();
			
		}
		player.last_direct=RIGHT;
	}

	//jump left
	if (direct==#0x9)
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
		player.last_direct=LEFT;
	}
	
	//fire left
	if (direct==#0xA)
	{
		player.frame=17;
		update();
		player.last_direct=LEFT;
	}
	
	//fire right
	if (direct==#0x6)
	{
		player.frame=16;
		update();
		player.last_direct=RIGHT;
	}
	
	//down
	if (direct==#0x2)
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
			if (player.last_direct==RIGHT)
				player.frame=16;
			else
				player.frame=17;
			update();
		}
		
	//lava
	if ((player_collision()&#0x80)==#0x80)
	{
		for (i=0;i<16;i++)
		{
			player.y+=1;
			player.frame=21;
			update();
		}
		for (i=0;i<3;i++)
		{
			player.frame=29+i;
			update();
		}
		player.frame=27;
		update();
		while (1);
	}
	//water
	if ((player_collision()&#0x100)==#0x100)
	{
		for (i=0;i<3;i++)
		{
			for (j=0;j<4;j++)
			{
				player.y+=1;
				player.frame=21;
				update();
			}
			for (j=0;j<4;j++)
			{
				player.y+=1;
				player.frame=22;
				update();
			}
		}
		while ((map[(player.x+3)/4][(player.y+16)/8]!=WATER_PLANTS))
		{
			player.y+=1;
			player.frame=28;
			update();
		}
		for (i=0;i<8;i++)
		{
			player.y+=1;
			player.frame=28;
			update();
		}
		
		while (1);
	}
}


void main(void)
{
	u8 name[3];
	t=time();
	
	pal_select(PAL_PALETTE0);
	clear_screen(0);
	select_image(IMG_TILE);
	
	sprites_start();
	
	load_level();
	
	draw_level();
	
	draw_player();
	
	init_terrain();

	
	while (1)
	{
		border (2);
		player_move(control_player());
		

		output_string(1, 1, "   ");
		itoa(n_frame, name);
		output_string(1, 1, name);
		
	}
	
}