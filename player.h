#ifndef _PLAYER
#define _PLAYER

void control_player()
{
	u8 key;
	u8 dx=0, dy=0, fire=0;
	key=joystick();
	if(key&JOY_UP) {
		dy=JOY_UP;
		}
	if(key&JOY_RIGHT) {
		dx=JOY_RIGHT;
	}
	if(key&JOY_LEFT) {
		dx=JOY_LEFT;
	}
	if(key&JOY_DOWN) {
		dy=JOY_DOWN;
	}
	if(key&JOY_FIRE) {
		fire=JOY_FIRE;
	}
	if(key!=FALSE) t_idle=time();
	player.direct=dx+dy+fire;
}


u16 player_collision()
{
	static u16 collision;
	
	u8 pxl, pxc, pxr, pyu, pyc, pyd, py_ground, py_stairs;
	
	collision=0;
	
	pxl=(player.x+2)/4;
	pxc=(player.x+3)/4;
	pxr=(player.x+5)/4;
	
	pyu=(player.y)/8;
	pyc=(player.y+7)/8;
	pyd=(player.y+15)/8;
	
	py_stairs=(player.y+10)/8;
	py_ground=(player.y+16)/8;

	//up
	if ((map[pyu][pxl]!=0)&&(map[pyu][pxr]!=0))
		collision^=COL_UP;
	//down
	if ((map[py_ground][pxl]==WALL)||(map[py_ground][pxc]==WALL)||(map[py_ground][pxr]==WALL))
		collision^=COL_DOWN;
	//right
	if (map[pyu][pxr]==WALL||map[pyc][pxr]==WALL||map[pyd][pxr]==WALL)
		collision^=COL_RIGHT;
	//left
	if ((map[pyu][pxl]==WALL)||(map[pyc][pxl]==WALL)||(map[pyd][pxl]==WALL))
		collision^=COL_LEFT;
	//ground
	if ((map[py_ground][pxl]==WALL)||(map[py_ground][pxr]==WALL))
		collision^=COL_GROUND;
	//stairs
	if (map[py_stairs][pxl]==STAIRS&&map[py_stairs][pxr]==STAIRS)
		collision^=COL_STAIRS;
	//lava
	// if (map[py_ground][pxc]==6)
		// collision^=COL_LAVA;
	//water
	if (map[pyc][pxr-1]==WATER||map[pyc][pxr]==WATER)
		collision^=COL_WATER;
		
	//danger
	if (map[pyd][pxc]==DANGER||map[pyu][pxc]==DANGER)
		collision^=COL_DANGER;
	
	//box ammo
	if (map[pyd][pxl]==AMMO){
		map[pyd][pxl]=0;
		open_box(pyd, pxl);
		player.ammo++;
	}
	if (map[pyd][pxl]==AMMO_FULL){
		map[pyd][pxl]=0;
		open_box(pyd, pxl);
		player.ammo=AMMO_MAX;
	}
	
	//box health
	if (map[pyd][pxl]==HEALTH){
		map[pyd][pxl]=0;
		open_box(pyd, pxl);
		player.health++;
	}
	if (map[pyd][pxl]==HEALTH_FULL){
		map[pyd][pxl]=0;
		open_box(pyd, pxl);
		player.health=HEALTH_MAX;
	}
	
	//screen right
	if (pxc==39)
		collision^=COL_NEX_SCR;
	
	//screen left
	if (pxc==0)
		collision^=COL_PRV_SCR;
	
	return (collision);
}



void player_logic()
{
	i8 j;
	
	static u8 trig_jump, trig_left;
	
	u16 p_collision;
	
	p_collision=player_collision();
	
	player.h_step=1;
	
	if (!player.health) {
		if (player.status==ST_DEATH)
			start_level();
		if ((player.status!=ST_WATER)&&(player.status!=ST_LAVA))
			player.status=ST_DEATH;
		return;
	}
	
	//idle
	if (!player.direct&&player.status!=ST_JUMP&&player.status!=ST_STAIRS)
		player.status=ST_IDLE;
	 
	//stairs stand
	if (!player.direct&&(p_collision&COL_STAIRS)==COL_STAIRS)
		player.status=STAIRS_STAND;
	
	//water 
	if ((p_collision&COL_WATER)==COL_WATER) {
		player.y++;
		if (player.y>142){
			player.health=0;
			player.status=ST_DEATH;
			return;
		}
		player.status=ST_WATER;
		return;
	}
	
	//danger
	if ((p_collision&COL_DANGER)==COL_DANGER)
		player.health--;
	
	//lava
	if ((p_collision&COL_LAVA)==COL_LAVA) {
		player.y+=7;
		player.status=ST_LAVA;
		player.health=0;
		return;
	}
	
	//up
	if ((player.direct&JOY_UP)==JOY_UP) {
		if ((p_collision&COL_STAIRS)==COL_STAIRS) {
			player.y-=2;
			player.status=ST_STAIRS;
		}
		if ((p_collision&COL_GROUND)==COL_GROUND&&player.status!=ST_STAIRS&&trig_jump) {
			player.v_speed=player.jump_impulse-GRAVITY;
			player.status=ST_JUMP;
			trig_jump=FALSE;
		}
	}
	
	if (player.v_speed>0) {
		player.v_speed--;
		for (j=0;j<=player.v_speed;j++) {
			if ((player_collision()&COL_UP)!=COL_UP) player.y--;
			else {
				player.v_speed=0;
				break;
			}
		}
	}
	
	// right 
	
	if (player.direct==JOY_RIGHT&&(p_collision&COL_RIGHT)!=COL_RIGHT) {
		player.status=ST_RIGHT;
		trig_left=FALSE;
		player.x+=player.h_step;
	}
	
	if (player.direct==JOY_RIGHT+JOY_UP&&(p_collision&COL_RIGHT)!=COL_RIGHT) {
		if (player.v_speed>0){
			player.status=JUMP_RIGHT;
			player.h_step=player.v_speed;
			trig_left=FALSE;
		}
		else {
			player.status=ST_RIGHT;
			player.h_step=1;
		}
		player.x+=player.h_step;
	}
	if ((player_collision()&COL_RIGHT)==COL_RIGHT)
		player.x-=player.h_step;
	if ((player_collision()&COL_NEX_SCR)==COL_NEX_SCR)
		nxt_screen();
	
	
	//left
	if (player.direct==JOY_LEFT&&(p_collision&COL_LEFT)!=COL_LEFT) {
		player.status=ST_LEFT;
		trig_left=TRUE;
		player.x-=player.h_step;
	}
	
	if (player.direct==JOY_LEFT+JOY_UP&&(p_collision&COL_LEFT)!=COL_LEFT) {
		if (player.v_speed>0){
			player.status=JUMP_LEFT;
			player.h_step=player.v_speed;
			trig_left=TRUE;
		}
		else {
			player.status=ST_LEFT;
			player.h_step=1;
		}
		player.x-=player.h_step;
	}
	if ((player_collision()&COL_LEFT)==COL_LEFT)
		player.x+=player.h_step;
	if ((player_collision()&COL_PRV_SCR)==COL_PRV_SCR)
		prv_screen();
	
	
	//down stairs
	if ((player.direct&JOY_DOWN)==JOY_DOWN) {
		for (j=0;j<2;j++) {
			if ((p_collision&COL_STAIRS)==COL_STAIRS&&(player_collision()&COL_GROUND)!=COL_GROUND) {
				player.y+=1;
				player.status=ST_STAIRS;
			}
			else break;
		}
	}
	
	// drop down
	if ((p_collision&COL_DOWN)!=COL_DOWN&&player.v_speed<=0) {
		player.v_speed-=GRAVITY;
		for (j=0;j>player.v_speed;j--) {
			if ((player_collision()&COL_DOWN)!=COL_DOWN&&(player_collision()&COL_WATER)!=COL_WATER
			&&(p_collision&COL_STAIRS)!=COL_STAIRS) {
				player.status=ST_DOWN;
				player.y++;
			}
			else {
				if (player.v_speed<player.deadly_height)
					player.health--;

				player.v_speed=0;
				break;
			}
		}
	}
	
	//enemy collision
	if (player.enemy_collision==COL_ENEMY_RIGHT){
		player.health--;
		for (j=0;j<2;j++){
			if ((player_collision()&COL_LEFT)!=COL_LEFT)
				player.x--;
			if ((player_collision()&COL_PRV_SCR)==COL_PRV_SCR){
				prv_screen();
			}
		}
		player.enemy_collision=0;
	}
	if (player.enemy_collision==COL_ENEMY_LEFT){
		player.health--;
		for (j=0;j<2;j++){
			if ((player_collision()&COL_RIGHT)!=COL_RIGHT)
				player.x++;
			if ((player_collision()&COL_NEX_SCR)==COL_NEX_SCR){
				nxt_screen();
			}
		}
		player.enemy_collision=0;
	}
	
	
	// fire
	if ((player.direct&JOY_DOWN)==JOY_DOWN&&(player_collision()&COL_GROUND)==COL_GROUND) {
		if (trig_left==TRUE)
			player.status=DOWN_LEFT;
		else
			player.status=DOWN_RIGHT;
	}	

	if (player.status==DOWN_RIGHT&&(player.direct&(JOY_LEFT+JOY_DOWN))==(JOY_LEFT+JOY_DOWN)) {
		player.status=DOWN_LEFT;
		trig_left=TRUE;
	}	
	
	if (player.status==DOWN_LEFT&&(player.direct&(JOY_RIGHT+JOY_DOWN))==(JOY_RIGHT+JOY_DOWN)) {
		player.status=DOWN_RIGHT;
		trig_left=FALSE;
	}	
	
	if (player.status==DOWN_LEFT&&(player.direct&JOY_FIRE)==JOY_FIRE&&player.ammo) {
		shot.direct=LEFT;
	}	
	
	if (player.status==DOWN_RIGHT&&(player.direct&JOY_FIRE)==JOY_FIRE&&player.ammo) {
		shot.direct=RIGHT;
	}	

	if ((player.direct&JOY_UP)!=JOY_UP)
		trig_jump=TRUE;

}

void player_animation()
{
	switch (player.status) {
		
		case ST_DEATH:
			player.frame=30;
			break;
		
		case ST_WATER:
			player.frame=33;
			break;
			
		case ST_LAVA:
			player.frame=32;
			break;
		
		case ST_RIGHT:
			if (player.frame<3||player.frame>10) {
				player.frame=3;
			}
			else {
				player.frame=player.frame<10?++player.frame:3;
			}
			break;
		
		case ST_LEFT:
			if (player.frame<14||player.frame>21) {
				player.frame=14;
			}
			else {
				player.frame=player.frame<21?++player.frame:14;
			}
			break;
			
		case ST_JUMP:
			player.frame=33;
			break;
			
		case JUMP_LEFT:
			player.frame=25;
			break;
			
		case JUMP_RIGHT:
			player.frame=24;
			break;
			
		case ST_STAIRS:
			if (player.frame<26||player.frame>29) {
				player.frame=26;
			}
			else {
				player.frame=player.frame<29?++player.frame:26;
			}
			break;
			
		case STAIRS_STAND:
			player.frame=26;
			break;
			
		case DOWN_LEFT:
			player.frame=23;
			break;
		
		case DOWN_RIGHT:
			player.frame=22;
			break;

		default:
			if (player.status==ST_IDLE&&(player_collision()&COL_STAIRS)!=COL_STAIRS&&
			(player.health!=0)) {
				if (t_idle+30>time())
					player.frame=0;
				else if (t_idle+50>time())
					player.frame=1;
				else t_idle=time();
			}
	}
}

#endif