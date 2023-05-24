#include <evo.h>
#include "resources.h"
#include <additions.h>

#define	HIGH_LEVEL	25
#define	WIDTH_LEVEL	40
#define RIGHT 1
#define LEFT 0

#define EMPTY 51

u32 t=0;

struct
{
	u8 x;	
	u8 y;
	u8 healt;
	u8 last_direct;
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
			if (map[x][y]==240)
			{
				player.x=4*x;
				player.y=8*(y-1);
				map[x][y]=0;
				break;
			}

	
	set_sprite(0,player.x,player.y,12);
			
	swap_screen();
}

u8 control_player()
{
	u8 key;
	u8 dx=0, dy=0, fire=0;
	u8 direct=0;
	
	vsync();
	key=joystick();
	vsync();
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
	if(key!=FALSE) t=time();
	direct=dx+dy+fire;
	return (direct);
}
		
void player_collision(u8 map[WIDTH_LEVEL][HIGH_LEVEL])
{
	if (map[(player.x)/4][player.y/8+2]==EMPTY&&map[(player.x+6)/4][player.y/8+2]==EMPTY)
	{
		player.y+=2;
		set_sprite(0,player.x,player.y,20);
		swap_screen();
		player_collision(map);
	}
	
}

void idle()
{
	if (t+250>time())
	{
		set_sprite(0,player.x,player.y,20);
		swap_screen();
	}
	else if (t+300>time())
	{
		set_sprite(0,player.x,player.y,21);
		swap_screen();
	}
	else
	{
		t=time();
	}
}


void player_move (u8 direct, u8 map[WIDTH_LEVEL][HIGH_LEVEL])
{
	u8 i;
	
	if (direct==#0x0) idle();
	
	//move right
	if (direct==#0x4)
	{
		i=0;
		while (control_player()==#0x4)
		{
			if (map[(player.x)/4+2][(player.y)/8+0]==EMPTY
				&&map[(player.x)/4+2][(player.y)/8+1]==EMPTY)
			{
				player.x+=1;
				set_sprite(0,player.x,player.y,i);
				swap_screen();
				//delay (2);
				player_collision(map);
				i++;
				if (i>7) i=0;
			}
			else
			{
				set_sprite(0,player.x,player.y,0);
				swap_screen();
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
			if (map[(player.x)/4][(player.y)/8]==EMPTY
				&&map[(player.x)/4][(player.y)/8+1]==EMPTY)
			{
				player.x-=1;
				set_sprite(0,player.x,player.y,i);
				swap_screen();
				//delay (2);
				player_collision(map);
				i++;
				if (i>15) i=8;
			}
			else
			{
				set_sprite(0,player.x,player.y,8);
				swap_screen();
			}
		}
		player.last_direct=LEFT;
	}
	
	//jump up
	if (direct==#0x1)
	{
		for (i=0;i<4;i++)
		{
			player.y-=2;
			set_sprite(0,player.x,player.y,21);
			swap_screen();
			delay (i/2);
		}
		if (map[player.x/4][player.y/8+2]==EMPTY)
		{
			player.y+=2;
			set_sprite(0,player.x,player.y,20);
			swap_screen();
		}
	}
	//jump right
	if (direct==#0x5)
	{
		for (i=0;i<5;i++)
		{
			if (map[(player.x)/4+2][(player.y)/8+1]==EMPTY
				&&map[(player.x)/4+2][(player.y)/8+2]==EMPTY) player.x+=2;
			player.y-=2;
			set_sprite(0,player.x,player.y,18);
			swap_screen();
			delay (i);
		}
		if (map[player.x/4][player.y/8+2]==EMPTY)
		{
			if (map[(player.x)/4+2][(player.y)/8+1]==EMPTY
				&&map[(player.x)/4+2][(player.y)/8+2]==EMPTY) player.x+=2;
			player.y+=2;
			set_sprite(0,player.x,player.y,18);
			swap_screen();
			
		}
		player.last_direct=RIGHT;
	}
	//jump left
	if (direct==#0x9)
	{
		for (i=0;i<5;i++)
		{
			if (map[(player.x)/4][(player.y)/8+1]==EMPTY
				&&map[(player.x)/4][(player.y)/8+2]==EMPTY) player.x-=2;
			player.y-=2;
			set_sprite(0,player.x,player.y,19);
			swap_screen();
			delay (i);
		}
		if (map[player.x/4][player.y/8+2]==EMPTY)
		{
			if (map[(player.x)/4][(player.y)/8+1]==EMPTY
				&&map[(player.x)/4][(player.y)/8+2]==EMPTY) player.x-=2;
			player.y+=2;
			set_sprite(0,player.x,player.y,19);
			swap_screen();
			
		}
		player.last_direct=LEFT;
	}
	
	//fire left
	if (direct==#0xA)
	{
			set_sprite(0,player.x,player.y,17);
			swap_screen();
			player.last_direct=LEFT;
	}
	//fire right
	if (direct==#0x6)
	{
			set_sprite(0,player.x,player.y,16);
			swap_screen();
			player.last_direct=RIGHT;
	}
	//down
	if (direct==#0x2)
	{
			if (player.last_direct==RIGHT)
				set_sprite(0,player.x,player.y,16);
			else
				set_sprite(0,player.x,player.y,17);
			swap_screen();
	}
}


void main(void)
{
	u8 map[WIDTH_LEVEL][HIGH_LEVEL];
	
	pal_select(PAL_PLAYER);
	clear_screen(0);
	select_image(IMG_TILE);
	
	sprites_start();
	
	load_level(map);
	
	draw_level(map);
	
	draw_player(map);

	
	while (1)
	{
		player_move(control_player(),map);
		player_collision(map);
	}
	
}