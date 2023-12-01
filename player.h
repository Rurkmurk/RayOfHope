#ifndef _PLAYER
#define _PLAYER

void control_player()
{
	u8 key;
	u8 dx=0, dy=0, fire=0;
	key=joystick();
	if(key&JOY_UP)
	{
		dy=JOY_UP;
	}
	if(key&JOY_RIGHT)
	{
		dx=JOY_RIGHT;
	}
	if(key&JOY_LEFT)
	{
		dx=JOY_LEFT;
	}
	if(key&JOY_DOWN)
	{
		dy=JOY_DOWN;
	}
	if(key&JOY_FIRE)
	{
		fire=JOY_FIRE;
	}
	if(key!=FALSE) t_idle=time();
	p.direct=dx+dy+fire;
}


u16 player_collision()
{
	static u16 collision;
	
	u8 pxl, pxc, pxr, pyu, pyc, pyd, py_ground, py_stairs;
	
	collision=0;
	
	pxl=(p.x+2)/4;
	pxc=(p.x+3)/4;
	pxr=(p.x+5)/4;
	
	pyu=(p.y)/8;
	pyc=(p.y+7)/8;
	pyd=(p.y+15)/8;
	
	py_stairs=(p.y+10)/8;
	py_ground=(p.y+16)/8;

	//up
	if ((map[pyu][pxl]>31)||(map[pyu][pxc]>31||(map[pyu][pxr]>31))) collision^=UP;
	//down
	if ((map[py_ground][pxl]>47)||(map[py_ground][pxc]>47)||(map[py_ground][pxr]>47)) collision^=DOWN;
	//right
	if (map[pyu][pxr]>47||map[pyc][pxr]>47||map[pyd][pxr]>47) collision^=RIGHT;
	//left
	if (map[pyu][pxl]>47||map[pyc][pxl]>47||map[pyd][pxl]>47) collision^=LEFT;
	//ground
	if ((map[py_ground][pxl]>95)&&(map[py_ground][pxl]<239)||(map[py_ground][pxr]>95)&&(map[py_ground][pxr]<239)) collision^=GROUND;
	//stairs
	if ((map[py_stairs][pxc]>31)&&(map[py_stairs][pxc]<48)) collision^=STAIRS;
	//lava
	if (map[py_ground][pxc]==LAVA) collision^=#0x80;
	//water_wave
	if ((map[py_ground][pxl]==WATER_WAVE)&&(map[py_ground][pxr]==WATER_WAVE)) collision^=DOWN;
	//water
	if (map[py_ground][pxc]==WATER) collision^=#0x100;
	//water plant
	if (map[py_ground][pxc]==WATER_PLANTS) collision^=#0x200;
	
	return (collision);
}



void player_logic()
{
	i8 j;
	
	u16 p_collision;
	
	if (!p.healt) return;
	
	p_collision=player_collision();
	
	//idle
	if (!p.direct&&p.new_status!=JUMP&&p.old_status!=STAIRS)
		p.new_status=IDLE;
	
	//stairs stand
	if (!p.direct&&(p_collision&STAIRS)==STAIRS)
		p.new_status=STAIRS_STAND;
	
	//water 
	if ((p_collision&#0x100)==#0x100)
	{
		p.y++;
		p.new_status=WATER;
		return;
	}
	if ((p_collision&#0x200)==#0x200)
	{
		p.y+4;
		p.healt=0;
		return;
	}

	//lava
	if ((p_collision&#0x80)==#0x80)
	{
		p.y+=7;
		p.new_status=LAVA;
		p.healt=0;
		return;
	}
	
	//up
	if ((p.direct&JOY_UP)==JOY_UP)
	{
		
		if ((p_collision&STAIRS)==STAIRS)
		{
				p.y-=2;
				p.new_status=STAIRS;
		}
		
		if ((p_collision&GROUND)==GROUND)
		{
			p.v_speed=p.jump_impulse-GRAVITY;
			p.new_status=JUMP;
		}
	}
	
	if (p.v_speed)
	{
		p.v_speed--;
		for (j=0;j<=p.v_speed;j++)
		{
			if ((player_collision()&UP)!=UP) p.y--;
			else
			{
				p.v_speed=0;
				break;
			}
		}
	}
	
	// right 
	if ((p.direct&JOY_RIGHT)==JOY_RIGHT&&(p_collision&RIGHT)!=RIGHT)
	{
		p.x+=p.h_speed;
		p.new_status=RIGHT;
	}
	if ((p_collision&RIGHT)==RIGHT) p.x-=p.h_speed;
	
	//left
	if ((p.direct&JOY_LEFT)==JOY_LEFT&&(p_collision&LEFT)!=LEFT)
	{
		p.x-=p.h_speed;
		p.new_status=LEFT;
	}
	if ((p_collision&LEFT)==LEFT) p.x+=p.h_speed;
	
	//left jump
	if (p.direct==JOY_LEFT+JOY_UP) p.new_status=JUMP_LEFT;
	
	//right jump
	if (p.direct==JOY_RIGHT+JOY_UP) p.new_status=JUMP_RIGHT;
	
	//down stairs
	if ((p.direct&JOY_DOWN)==JOY_DOWN)
	{
		for (j=0;j<2;j++)
		{
			if ((p_collision&STAIRS)==STAIRS&&(player_collision()&GROUND)!=GROUND)
			{
				p.y+=1;
				p.new_status=STAIRS;
			}
			else break;
		}
	}
	
	// drop down
	if ((p_collision&DOWN)!=DOWN&&!p.v_speed)
	{
		for (j=0;j<=GRAVITY;j++)
		{
			if ((player_collision()&DOWN)!=DOWN&&(p_collision&STAIRS)!=STAIRS)
			{
				p.new_status=DOWN;
				p.y++;
			}
			else break;
		}
	}
	
	// fire
	
	if ((p.direct&JOY_FIRE)==JOY_FIRE)
	{
		if (p.old_status==LEFT) p.new_status=FIRE_LEFT;
		else p.new_status=FIRE_RIGHT;
	}	

}

void animation_player()
{
	switch (p.new_status)
	{
		case WATER:
			p.frame=28;
			break;
			
		case LAVA:
			p.frame=31;
			break;
		
		case RIGHT:
			if ((p.old_status)!=RIGHT)
			{
				p.old_status=RIGHT;
				p.frame=0;
			}
			else
			{
				p.frame=p.frame<7?++p.frame:0;
			}
			break;
		
		case LEFT:
			if ((p.old_status)!=LEFT)
			{
				p.old_status=LEFT;
				p.frame=8;
			}
			else
			{
				p.frame=p.frame<15?++p.frame:8;
			}
			break;
			
		case JUMP:
			p.frame=22;
			break;
			
		case JUMP_LEFT:
			p.frame=19;
			break;
			
		case JUMP_RIGHT:
			p.frame=18;
			break;
			
		case STAIRS:
			if ((p.old_status)!=STAIRS)
			{
				p.old_status=STAIRS;
				p.frame=23;
			}
			else
			{
				p.frame=p.frame<26?++p.frame:23;
			}
			break;
			
		case STAIRS_STAND:
			p.frame=23;
			break;
			
		case FIRE_LEFT:
			p.frame=17;
			border (3);
			break;
		
		case FIRE_RIGHT:
			p.frame=16;
			border (2);
			break;
			
			
		default:
			if (p.new_status==IDLE&&(player_collision()&STAIRS)!=STAIRS&&(p.healt!=0))
			{
				if (t_idle+200>time()) p.frame=20;
				else if (t_idle+210>time()) p.frame=22;
				else if (t_idle+230>time()) p.frame=21;
				else if (t_idle+240>time()) p.frame=22;
				else if (t_idle+260>time()) p.frame=21;
				else t_idle=time();	
			}
	}
}

#endif