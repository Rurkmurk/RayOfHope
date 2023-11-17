#ifndef _PLAYER
#define _PLAYER

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
	p.new_direct=dx+dy+fire;
}


u16 player_collision()
{
	static u16 collision;
	
	u8 pxl, pxc, pxr, pyu, pyc, pyd, pyds;
	
	collision=0;
	
	pxl=(p.x+1)/4;
	pxc=(p.x+3)/4;
	pxr=(p.x+6)/4;
	
	pyu=(p.y-1)/8;
	pyc=(p.y+3)/8; 
	pyd=(p.y+15)/8;
	
	pyds=(p.y+16)/8; //for stairs and water

	//up
	if ((map[pyu][pxl]<16)&&(map[pyu][pxc]<16&&(map[pyu][pxr]<16))) collision+=#0x1;
	//down
	if ((map[pyd][pxl]<16)&&(map[pyd][pxc]<16)&&(map[pyd][pxr]<16)) collision+=#0x2;
	//right
	if (map[pyu+1][pxr]<32&&map[pyc][pxr]<32&&map[pyd][pxr]<32) collision+=#0x4;
	//left
	if (map[pyu+1][pxl]<32&&map[pyc][pxl]<32&&map[pyd][pxl]<32) collision+=#0x8;
	//ground
	if ((map[pyds][pxl]>79)&&(map[pyds][pxl]<240)||(map[pyds][pxr]>79)&&(map[pyds][pxr]<240)) collision+=#0x10;
	//stairs up
	if (((map[pyu][pxl]>=16)&&(map[pyu][pxl]<32))&&((map[pyu][pxr]>=16)&&(map[pyu][pxr]<32))) collision+=#0x20;
	//stairs down
	if (((map[pyd+1][pxl]>=16)&&(map[pyd+1][pxl]<32))&&((map[pyd+1][pxr]>=16)&&(map[pyd+1][pxr]<32))) collision+=#0x40;
	//lava
	if (map[pyds][pxc]==LAVA) collision+=#0x80;
	//water_wave
	if ((map[pyd][pxl]==WATER_WAVE)&&(map[pyd][pxr]==WATER_WAVE)) collision+=#0x2;
	//water
	if ((map[pyds][pxl+1]==WATER)&&(map[pyds][pxr-1]==WATER)) collision+=#0x100;
	//water plant
	if ((map[pyds][pxl+1]==WATER_PLANTS)&&(map[pyds][pxr-1]==WATER_PLANTS)) collision+=#0x200;
	
	return (collision);
}



void player_logic()
{
	static u8 i;
	i8 j;
	
	if (!p.healt) return;
	
	// idle
	if ((p.new_direct==#0x0)&&((p.old_direct&UP)!=UP))
	{
		if (t_idle+250>time()) p.frame=20;
		else if (t_idle+300>time()) p.frame=21;
		else t_idle=time();
	}
	
	//water
	if ((player_collision()&#0x100)==#0x100)
	{
		p.y++;
		p.frame=28;
		if ((player_collision()&#0x200)==#0x200)
		{
			p.y+=4;
			p.healt=0;
		}
		return;
	}
	
	//lava
	if ((player_collision()&#0x80)==#0x80)
	{
		p.y+=8;
		p.frame=31;
		p.healt=0;
	}
	
	// drop down
	if ((player_collision()&DOWN)==DOWN&&!p.v_speed)
	{
		//p.v_speed+=GRAVITY;
		for (j=0;j<=GRAVITY;j++)
		{
			p.y++;
			if ((player_collision()&DOWN)!=DOWN)
			{
				p.y--;
				//p.v_speed=0;
				break;
			}
		}
	}
	
	//jump
	if (((p.new_direct&UP)==UP)&&((player_collision()&GROUND)==GROUND))
	{
		p.v_speed=p.jump_impulse-GRAVITY;
	}
	
	if (p.v_speed>0)
	{
		p.v_speed--;
		for (j=0;j<=p.v_speed;j++)
		{
			if ((player_collision()&UP)==UP) p.y--;
			else
			{
				p.v_speed=0;
				break;
			}
		}
	}
	
	// right 
	if ((p.new_direct&RIGHT)==RIGHT)
	{
		//if ((p.old_direct&RIGHT)!=RIGHT) p.old_direct^=RIGHT;
		p.x+=p.h_speed;
		if ((player_collision()&RIGHT)!=RIGHT) p.x-=p.h_speed;
	}
	
	//left
	if (((p.new_direct&LEFT)==LEFT)&&((player_collision()&LEFT)==LEFT))
	{
		//if ((p.old_direct&LEFT)!=LEFT) p.old_direct^=LEFT;
		p.x-=p.h_speed;
		if ((player_collision()&LEFT)!=LEFT) p.x+=p.h_speed;
	}
	
	// stairs up
	if ((p.new_direct&UP)==UP)
	{
		if ((player_collision()&STAIRS_DOWN)==STAIRS_DOWN||(player_collision()&STAIRS_UP)==STAIRS_UP)
		p.y-=2;
		//if ((p.old_direct&LEFT)!=LEFT) p.old_direct^=LEFT;
	}
	
	// stairs down
	if ((p.new_direct&DOWN)==DOWN)
	{
		if ((player_collision()&GROUND)!=GROUND)
			if ((player_collision()&STAIRS_DOWN)==STAIRS_DOWN||(player_collision()&STAIRS_UP)==STAIRS_UP)
			p.y+=2;
		//if ((p.old_direct&LEFT)!=LEFT) p.old_direct^=LEFT;
	}
}

#endif