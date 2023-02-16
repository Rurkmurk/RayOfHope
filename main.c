#include <evo.h>
#include "resources.h"
#include <additions.h>

#define	HIGH_LEVEL	25
#define	WIDTH_LEVEL	40

u32 t=0;

struct
{
	u8 x;	
	u8 y;
	u8 healt;
}player;


void load_level(u8 map[WIDTH_LEVEL][HIGH_LEVEL])
{
	u8 x, y;
	u8 j=0;
	u16 i=0;
	u8 buf[3];
	
	load_file("level001", 30, 1);
		
	for (y=0;y<HIGH_LEVEL;y++)
		for (x=0;x<WIDTH_LEVEL;x++)
		{
			do
			{
				buf[j]=get_mem(30,32768+i)-48; // 48 is 30 in HEX
				j++;
				i++;
			}while (get_mem(30,32768+i)!=',');
			
			if (j==3) map[x][y]=100*buf[0]+10*buf[1]+buf[2];
			else if (j==2) map[x][y]=10*buf[0]+buf[1];
			else map[x][y]=buf[0];

			i++;
			j=0;
		}
}


void draw_level(u8 map[WIDTH_LEVEL][HIGH_LEVEL])
{
	u8 x, y;
	
	for (y=0; y<HIGH_LEVEL; y++)
		for (x=0; x<WIDTH_LEVEL; x++)
			draw_tile(x,y,map[x][y]);

	swap_screen();
}


void draw_player(u8 map[WIDTH_LEVEL][HIGH_LEVEL])
{
	u8 x, y;
	
	for (y=0; y<HIGH_LEVEL; y++)
		for (x=0; x<WIDTH_LEVEL; x++)
			if (map[x][y]==160)
			{
				player.x=4*x;
				player.y=8*(y-1);
				break;
			}

	
	set_sprite(0,player.x,player.y,10);
			
	swap_screen();
}


void idle()
{
	if (t+250>time())
	{
		set_sprite(0,player.x,player.y,10);
		swap_screen();
	}
	else if (t+300>time())
	{
		set_sprite(0,player.x,player.y,11);
		swap_screen();
	}
	else
	{
		t=time();
	}
}


void player_move (i8 dx, i8 dy)
{
	player.x+=dx;
	player.y-=dy;
	set_sprite(0,player.x,player.y,10);
	swap_screen();
}


void main(void)
{
	u8 map[WIDTH_LEVEL][HIGH_LEVEL];
	u8 key;
	i8 dx=0, dy=0;
	
	pal_select(PAL_PLAYER);
	clear_screen(0);
	select_image(IMG_TILE);
	
	sprites_start();
	
	load_level(map);
	
	draw_level(map);
	
	draw_player(map);
	
	
	while (1)
	{
		idle();
		vsync();
		key=joystick();
		if(key&JOY_UP)
		{
			dy=1;
		}
		if(key&JOY_RIGHT)
		{
			dx=1;
		}
		if(key&JOY_LEFT)
		{
			dx=-1;
		}
		if(key&JOY_DOWN)
		{
			dy=-1;
		}
		if(key&JOY_FIRE)
		{
			
		}
		if (key!=FALSE)
		{
			player_move(dx,dy);
			dx=0;
			dy=0;
			t=time();
		}
			

	}
	
}