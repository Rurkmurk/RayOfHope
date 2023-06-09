#include <evo.h>
#include "resources.h"
#include <additions.h>

#define	HIGH_LEVEL	25
#define	WIDTH_LEVEL	40
#define RIGHT 1
#define LEFT 0


u32 t=0;
static u8 map[WIDTH_LEVEL][HIGH_LEVEL];

struct
{
	u8 x;	
	u8 y;
	u8 healt;
	u8 frame;
	u8 last_direct;
}player;


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
	
	for (y=0; y<HIGH_LEVEL; y++)
		for (x=0; x<WIDTH_LEVEL; x++)
			draw_tile(x,y,map[x][y]);

	swap_screen();
}


void draw_player()
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

	
	set_sprite(0,player.x,player.y,20);
			
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


u8 player_collision()
{
	static u8 collision;
	
	collision=0;
	//up
	if ((map[(player.x+2)/4][(player.y+6)/8-1]<32)&&(map[(player.x+5)/4][(player.y+6)/8-1]<32)) collision+=#0x1;
	//down
	if ((map[(player.x+2)/4][player.y/8+2]<16)&&(map[(player.x+5)/4][player.y/8+2]<16)) collision+=#0x2;
	//right
	if (map[(player.x+7)/4][(player.y)/8]<32&&map[(player.x+7)/4][(player.y+15)/8]<32) collision+=#0x4;
	//left
	if (map[player.x/4][player.y/8]<32&&map[player.x/4][(player.y+15)/8]<32) collision+=#0x8;
	//stairs
	if ((map[(player.x+3)/4][(player.y+15)/8]>=16)&&(map[(player.x+3)/4][(player.y+15)/8]<32)) collision+=#0x20;
	//lava
	if ((map[(player.x+2)/4][(player.y+17)/8]>=32)&&(map[(player.x+5)/4][(player.y+17)/8]>=32)&&(map[(player.x+2)/4][(player.y+17)/8]<48)&&(map[(player.x+5)/4][(player.y+17)/8]<48)) collision+=#0x40;
	//water
	if ((map[(player.x+2)/4][(player.y+17)/8]>=48)&&(map[(player.x+5)/4][(player.y+17)/8]>=48)&&(map[(player.x+2)/4][(player.y+17)/8]<64)&&(map[(player.x+5)/4][(player.y+17)/8]<64)) collision+=#0x80;
	
	
	return (collision);
}


void idle()
{
	if ((player_collision()&#0x20)==#0x20)
	{
		set_sprite(0,player.x,player.y,24);
		swap_screen();
	}
	else
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
	
}


void player_move (u8 direct)
{
	u8 i,j;
	
	if (direct==#0x0) idle();
	
	//move right
	if (direct==#0x4)
	{
		i=0;
		while (control_player()==#0x4)
		{
			if ((player_collision()&#0x4)==#0x4)
			{
				player.x+=1;
				set_sprite(0,player.x,player.y,i);
				swap_screen();
				i++;
				if (i>7) i=0;
				if ((player_collision()&#0x2)==#0x2) player.x+=1;
				while ((player_collision()&#0x2)==#0x2)
				{
					player.y+=2;
					set_sprite(0,player.x,player.y,21);
					swap_screen();
				}
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
			if ((player_collision()&#0x8)==#0x8)
			{
				player.x-=1;
				set_sprite(0,player.x,player.y,i);
				swap_screen();
				i++;
				if (i>15) i=8;
				if ((player_collision()&#0x2)==#0x2) player.x-=1;
				while ((player_collision()&#0x2)==#0x2)
				{
					player.y+=2;
					set_sprite(0,player.x,player.y,21);
					swap_screen();
				}
			}
			else
			{
				set_sprite(0,player.x-1,player.y,8);
				swap_screen();
			}
		}
		player.last_direct=LEFT;
	}
	
	// stairs up
	if (direct==#0x1&&(player_collision()&#0x21)==#0x21)
	{
		if (map[player.x/4][(player.y+15)/8]>15&&map[player.x/4][(player.y+15)/8]<32) player.x=player.x-(player.x%4);
		else player.x=player.x-(player.x%4)+4;
				
		while (control_player()==#0x1)
		{
			if ((player_collision()&#0x20)==#0x20)
			{
				player.y-=1;
				set_sprite(0,player.x,player.y,23);
				swap_screen();
				player.y-=1;
				set_sprite(0,player.x,player.y,23);
				swap_screen();
				player.y-=1;
				set_sprite(0,player.x,player.y,24);
				swap_screen();
				player.y-=1;
				set_sprite(0,player.x,player.y,24);
				swap_screen();
				player.y-=1;
				set_sprite(0,player.x,player.y,25);
				swap_screen();
				player.y-=1;
				set_sprite(0,player.x,player.y,25);
				swap_screen();
				player.y-=1;
				set_sprite(0,player.x,player.y,24);
				swap_screen();
				player.y-=1;
				set_sprite(0,player.x,player.y,24);
				swap_screen();
			}
		}
	}
	
	//jump up
	if (direct==#0x1&&(player_collision()&#0x20)!=#0x20)
	{
		set_sprite(0,player.x,player.y,22);
		swap_screen();
		set_sprite(0,player.x,player.y,22);
		swap_screen();
		set_sprite(0,player.x,player.y,20);
		swap_screen();
		set_sprite(0,player.x,player.y,21);
		swap_screen();
		for (i=0;i<5;i++)
		{
			if ((player_collision()&#0x1)==#0x1) player.y-=2;
			set_sprite(0,player.x,player.y,21);
			swap_screen();
			delay (i/2);
		}
		while ((player_collision()&#0x2)==#0x2)
		{
			player.y+=2;
			set_sprite(0,player.x,player.y,21);
			swap_screen();
		}
	}
	//jump right
	if (direct==#0x5)
	{
		for (i=0;i<5;i++)
		{
			if ((player_collision()&#0x1)==#0x1)
			{
				player.y-=2;
				//set_sprite(0,player.x,player.y,18);
				//swap_screen();
				//player.y-=1;	
			}
			
			if ((player_collision()&#0x4)==#0x4) player.x+=1;
			
			set_sprite(0,player.x,player.y,18);
			swap_screen();
		}
			
		if ((player_collision()&#0x4)==#0x4) player.x+=1;
		set_sprite(0,player.x,player.y,18);
		swap_screen();
		
		while ((player_collision()&#0x2)==#0x2)
		{
			
			player.y+=2;
			if (i>1&&(player_collision()&#0x4)==#0x4)
			{
				i-=1;
				player.x+=1;
			}

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
			if ((player_collision()&#0x1)==#0x1)
			{
				player.y-=2;
				//set_sprite(0,player.x,player.y,19);
				//swap_screen();
				//player.y-=1;
			}
			
			if ((player_collision()&#0x8)==#0x8) player.x-=1;
			
			set_sprite(0,player.x,player.y,19);
			swap_screen();
		}

		while ((player_collision()&#0x2)==#0x2)
		{
			
			player.y+=2;
			if (i>1&&(player_collision()&#0x8)==#0x8)
			{
				i--;
				player.x-=1;
			}

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
		if ((map[(player.x+3)/4][(player.y+17)/8]>=16)&&(map[(player.x+3)/4][(player.y+17)/8]<32))
		{
			if (map[player.x/4][(player.y+17)/8]>15&&map[player.x/4][(player.y+17)/8]<32) player.x=player.x-(player.x%4);
			else player.x=player.x-(player.x%4)+4;
					
			while (control_player()==#0x2)
			{
				if ((map[(player.x+3)/4][(player.y+17)/8]>=16)&&(map[(player.x+3)/4][(player.y+17)/8]<32))
				{
					player.y+=2;
					set_sprite(0,player.x,player.y,23);
					swap_screen();
					player.y+=2;
					set_sprite(0,player.x,player.y,24);
					swap_screen();
					player.y+=2;
					set_sprite(0,player.x,player.y,25);
					swap_screen();
					player.y+=2;
					set_sprite(0,player.x,player.y,24);
					swap_screen();
				}
			}
		}
		else
		{
			if (player.last_direct==RIGHT)
				set_sprite(0,player.x,player.y,16);
			else
				set_sprite(0,player.x,player.y,17);
			swap_screen();
		}
		
	//lava
	if ((player_collision()&#0x40)==#0x40)
	{
		for (i=0;i<8;i++)
		{
			player.y+=1;
			set_sprite(0,player.x,player.y,21);
			swap_screen();
		}
		set_sprite(0,player.x,player.y,26);
		swap_screen();
		set_sprite(0,player.x,player.y,28);
		swap_screen();
		set_sprite(0,player.x,player.y,29);
		swap_screen();
		set_sprite(0,player.x,player.y,30);
		swap_screen();
		set_sprite(0,player.x,player.y,SPRITE_END);
		swap_screen();
		while (1);
	}
	//water
	if ((player_collision()&#0x80)==#0x80)
	{
		for (i=0;i<3;i++)
		{
			for (j=0;j<4;j++)
			{
				player.y+=1;
				set_sprite(0,player.x,player.y,21);
				swap_screen();
			}
			for (j=0;j<4;j++)
			{
				player.y+=1;
				set_sprite(0,player.x,player.y,22);
				swap_screen();
			}
		}
		while ((player_collision()&#0x80)==#0x80)
		{
			player.y+=1;
			set_sprite(0,player.x,player.y,27);
			swap_screen();
		}
		
		while (1);
	}
}


void main(void)
{
	u8 name[3];
	
	
	
	pal_select(PAL_PLAYER);
	clear_screen(0);
	select_image(IMG_TILE);
	
	sprites_start();
	
	load_level();
	
	draw_level();
	
	draw_player();

	
	while (1)
	{
		player_move(control_player());

		output_string(1, 1, "   ");
		itoa(player_collision()&#0x20, name);
		output_string(1, 1, name);
	}
	
}