#ifndef _PLAYER
#define _PLAYER

void control_player()
{
	static u8 key;
	static u8 dx, dy, fire;
	dx=0;
	dy=0;
	fire=0;
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
	static u8 pxl, pxc, pxr, pyu, pyc, pyd, py_ground, py_stairs;
	
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
	if ((map[pyu][pxl]==1)&&(map[pyu][pxr]==1))
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
		if (player.ammo<AMMO_MAX){
			map[pyd][pxl]=0;
			player.ammo++;
			sfx_play(SFX_LOAD,8);
			open_box(pyd, pxl);
		}
	}
	if (map[pyd][pxl]==AMMO_FULL){
		if (player.ammo<AMMO_MAX){
		map[pyd][pxl]=0;
		if (player.ammo>7)
			player.ammo=AMMO_MAX;
		else player.ammo+=3;
		sfx_play(SFX_LOAD_FULL,8);
		open_box(pyd, pxl);
		}
	}
	
	//box health
	if (map[pyd][pxl]==HEALTH){
		if (player.health<HEALTH_MAX){
			map[pyd][pxl]=0;
			player.health++;
			sfx_play(SFX_HEALTH,8);
			open_box(pyd, pxl);
		}
	}
	if (map[pyd][pxl]==HEALTH_FULL){
		if (player.health<HEALTH_MAX){
			map[pyd][pxl]=0;
			if (player.health>7)
				player.health=HEALTH_MAX;
			else player.health+=3;
			sfx_play(SFX_HEALTH_FULL,8);
			open_box(pyd, pxl);
		}
	}
	
	//screen right
	if (pxc==39)
		collision^=COL_NXT_SCR;
	
	//screen left
	if (pxc==0)
		collision^=COL_PRV_SCR;
	
	//screen down
	if (pyc==21)
		collision^=COL_DOWN_SCR;
	
	// screen up
	if (pyc==0)
		collision^=COL_UP_SCR;
	
	//next level
	// if (map[pyd][pxc]==EXIT){
		// pal_select(2);
		// clear_screen(0);
		// draw_image(0,0,IMG_RC);
		// set_sprite(0,0,0,SPRITE_END);
		// swap_screen();
		// press_key();
		// start_level();
	// }
	
	return (collision);
}



void player_logic()
{
	static i8 j;
	
	static u8 trig_jump, trig_left;
	
	static u16 p_collision;
	
	p_collision=player_collision();
	
	player.h_step=1;
	
	if (!player.health) {
		if (player.status==ST_DEATH&&t_death+100<time()){
			player.status=ST_IDLE;
			if (!player.life){
				player.life=3;
				start_level();
			}
			else
				restart_level();
				
		}
			
		//else if (player.status!=ST_WATER&&player.status!=ST_LAVA){
		else if (player.status!=ST_DEATH){
		
			if ((p_collision&COL_DOWN)!=COL_DOWN){
				player.v_speed-=GRAVITY;
				//player.status=ST_DOWN;
				for (j=0;j>player.v_speed;j--){
					p_collision=player_collision();
					if ((p_collision&COL_DOWN)!=COL_DOWN&&(p_collision&COL_WATER)!=COL_WATER){
						player.y++;
						if ((player_collision()&COL_DOWN_SCR)==COL_DOWN_SCR)
							down_screen();
					}
					else {
						player.status=ST_DEATH;
						sfx_play(SFX_DEATH,8);
					}
				}
			}
			else {
				player.status=ST_DEATH;
				sfx_play(SFX_DEATH,8);
				player.life--;
				t_death=time();
			}
		}
		return;
	}
	
	//idle
	if (!player.direct&&player.status!=ST_JUMP&&player.status!=ST_STAIRS)
		player.status=ST_IDLE;
	if ((player.direct&JOY_UP)==JOY_UP&&trig_jump==FALSE)
		player.status=ST_IDLE;
	 
	//stairs stand
	if (!player.direct&&(p_collision&COL_STAIRS)==COL_STAIRS)
		player.status=STAIRS_STAND;
	
	//water 
	if ((p_collision&COL_WATER)==COL_WATER) {
		player.y++;
		if (player.y>142){
			player.health=0;
			update_hud();
			player.status=ST_DEATH;
			sfx_play(SFX_DEATH,8);
			return;
		}
		player.status=ST_WATER;
		return;
	}
	
	//danger
	if ((p_collision&COL_DANGER)==COL_DANGER){
		player.health--;
		sfx_play(SFX_DAMAGE,8);
		update_hud();
	}
	
	//lava
	// if ((p_collision&COL_LAVA)==COL_LAVA) {
		// player.y+=7;
		// player.status=ST_LAVA;
		// player.health=0;
		// update_hud();
		// return;
	// }
	
	//up
	if ((player.direct&JOY_UP)==JOY_UP) {
		if ((p_collision&COL_STAIRS)==COL_STAIRS) {
			player.y-=2;
			if ((player_collision()&COL_UP_SCR)==COL_UP_SCR)
				up_screen();
			player.status=ST_STAIRS;
		}
		if ((p_collision&COL_GROUND)==COL_GROUND&&player.status!=ST_STAIRS&&trig_jump) {
			player.v_speed=player.jump_impulse-GRAVITY;
			player.status=ST_JUMP;
			sfx_play(SFX_JUMP_UP,8);
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
	
	if (player.direct==JOY_RIGHT&&(p_collision&COL_RIGHT)!=COL_RIGHT){
		if (player.status==STAIRS_STAND){
			player.x+=player.h_step;
			player.status=ST_STAIRS;
		}
		else {
			player.status=ST_RIGHT;
			trig_left=FALSE;
			player.x+=player.h_step;
			if ((player_collision()&COL_NXT_SCR)==COL_NXT_SCR)
				nxt_screen();
		}
		
	}
	
	if (player.direct==JOY_RIGHT+JOY_UP&&(p_collision&COL_RIGHT)!=COL_RIGHT) {
		if (player.v_speed>0){
			player.status=JUMP_RIGHT;
			//sfx_play(SFX_JUMP_UP,8);
			player.h_step=player.v_speed;
			trig_left=FALSE;
		}
		else {
			player.status=ST_RIGHT;
			player.h_step=1;
		}
		//player.x+=player.h_step;
		for (j=0;j<player.h_step;j++){
			player.x++;
			if ((player_collision()&COL_NXT_SCR)==COL_NXT_SCR){
				update_screen();
				nxt_screen();
			}
		}
	}
	if ((player_collision()&COL_RIGHT)==COL_RIGHT)
		player.x-=player.h_step;
	
	
	
	//left
	if (player.direct==JOY_LEFT&&(p_collision&COL_LEFT)!=COL_LEFT) {
		if (player.status==STAIRS_STAND){
			player.x-=player.h_step;
			player.status=ST_STAIRS;
		}
		else {
			player.status=ST_LEFT;
			trig_left=TRUE;
			player.x-=player.h_step;
			if ((player_collision()&COL_PRV_SCR)==COL_PRV_SCR)
				prv_screen();
		}
	}
	
	if (player.direct==JOY_LEFT+JOY_UP&&(p_collision&COL_LEFT)!=COL_LEFT) {
		if (player.v_speed>0){
			player.status=JUMP_LEFT;
			//sfx_play(SFX_JUMP_UP,8);
			player.h_step=player.v_speed;
			trig_left=TRUE;
		}
		else {
			player.status=ST_LEFT;
			player.h_step=1;
		}
		//player.x-=player.h_step;
		for (j=0;j<player.h_step;j++){
			player.x--;
			if ((player_collision()&COL_PRV_SCR)==COL_PRV_SCR){
				update_screen();
				prv_screen();
			}
		}	
	}
	if ((player_collision()&COL_LEFT)==COL_LEFT)
		player.x+=player.h_step;
	
	
	
	//down stairs
	if ((player.direct&JOY_DOWN)==JOY_DOWN) {
		for (j=0;j<2;j++) {
			if ((p_collision&COL_STAIRS)==COL_STAIRS&&(player_collision()&COL_GROUND)!=COL_GROUND) {
				player.y++;
				if ((player_collision()&COL_DOWN_SCR)==COL_DOWN_SCR)
					down_screen();
				player.status=ST_STAIRS;
				
			}
			else break;
		}
	}
	
	// drop down
	if ((p_collision&COL_DOWN)!=COL_DOWN&&(p_collision&COL_STAIRS)!=COL_STAIRS&&player.v_speed<=0){
		player.v_speed-=GRAVITY;
		//player.status=ST_DOWN_PUSH;
		for (j=0;j>player.v_speed;j--){
			
			if ((p_collision&COL_DOWN)!=COL_DOWN&&(p_collision&COL_WATER)!=COL_WATER&&(p_collision&COL_STAIRS)!=COL_STAIRS){
				player.y++;
				if ((player_collision()&COL_DOWN_SCR)==COL_DOWN_SCR)
					down_screen();
			}
			else if ((p_collision&COL_WATER)!=COL_WATER){
				
				sfx_play(SFX_JUMP_DOWN,8);
				
				if (player.v_speed<=player.death_height){
					if (player.health<=5)
						player.health=0;
					else {
						player.health-=5;
						sfx_play(SFX_DAMAGE,8);
					}
				}
				
				else if (player.v_speed<=player.danger_height){
					if (player.health)
						player.health--;
					sfx_play(SFX_DAMAGE,8);
				}
				player.v_speed=0;
				player.status=ST_DOWN_PUSH;
				update_hud();
				break;
			}
			p_collision=player_collision();
		}
		if ((p_collision&COL_DOWN)==COL_DOWN){
			player.v_speed=0;
			player.status=ST_DOWN_PUSH;
			sfx_play(SFX_JUMP_DOWN,8);
		}
	}

	
	//enemy collision
	if (player.enemy_collision){
		switch (player.enemy_collision){
			case COL_ENEMY_RIGHT:
				if (player.health)
					player.health--;
				sfx_play(SFX_DAMAGE,8);
				update_hud();
				for (j=0;j<2;j++){
					if ((player_collision()&COL_LEFT)!=COL_LEFT)
						player.x--;
					if ((player_collision()&COL_PRV_SCR)==COL_PRV_SCR)
						prv_screen();
				}
				player.enemy_collision=0;
			break;
			case COL_ENEMY_LEFT:
				if (player.health)
					player.health--;
				sfx_play(SFX_DAMAGE,8);
				update_hud();
				for (j=0;j<2;j++){
					if ((player_collision()&COL_RIGHT)!=COL_RIGHT)
						player.x++;
					if ((player_collision()&COL_NXT_SCR)==COL_NXT_SCR)
						nxt_screen();
				}
				player.enemy_collision=0;
			break;
			case COL_ENEMY_CENTR:
				if (player.health)
					player.health--;
				sfx_play(SFX_DAMAGE,8);
				update_hud();
				player.enemy_collision=0;
			break;
			case COL_ENEMY_RIGHT+COL_ENEMY_CENTR:
				player.x++;
				player.enemy_collision=0;
			break;
			case COL_ENEMY_LEFT+COL_ENEMY_CENTR:
				player.x--;
				player.enemy_collision=0;
			break;
			default:
				player.enemy_collision=0;
			break;
				
		}
	}

	
	// fire
	if ((player.direct&JOY_DOWN)==JOY_DOWN&&(player_collision()&COL_GROUND)==COL_GROUND) {
		if (trig_left==TRUE){
			if (player.ammo)
				player.status=DOWN_LEFT;
			else
				player.status=ST_IDLE;
		}
		else{
			if (player.ammo)
				player.status=DOWN_RIGHT;
			else
				player.status=ST_IDLE;
		}
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
			player.frame=27;
			break;
		
		case ST_WATER:
			player.frame=26;
			break;
			
		case ST_LAVA:
			player.frame=28;
			break;
		
		case ST_RIGHT:
			if (player.frame>7) {
				player.frame=0;
			}
			else {
				player.frame=player.frame<7?++player.frame:0;
				if (player.frame==2||player.frame==6)
					sfx_play(SFX_STEP,8);
			}
			break;
		
		case ST_LEFT:
			if (player.frame<8||player.frame>15) {
				player.frame=8;
			}
			else {
				player.frame=player.frame<15?++player.frame:8;
				if (player.frame==10||player.frame==14)
					sfx_play(SFX_STEP,8); 
			}
			break;
			
		case ST_JUMP:
			player.frame=26;
			break;
			
		case JUMP_LEFT:
			player.frame=19;
			break;
			
		case JUMP_RIGHT:
			player.frame=18;
			break;
			
		case ST_STAIRS:
			if (player.frame<20||player.frame>23) {
				player.frame=20;
			}
			else {
				player.frame=player.frame<23?++player.frame:20;
			}
			break;
			
		case STAIRS_STAND:
			player.frame=20;
			break;
			
		case DOWN_LEFT:
			player.frame=17;
			break;
		
		case DOWN_RIGHT:
			player.frame=16;
			break;

		default:
			if (player.status==ST_IDLE&&(player_collision()&COL_STAIRS)!=COL_STAIRS&&
			player.health) {
				if (t_idle+30>time())
					player.frame=24;
				else if (t_idle+50>time())
					player.frame=25;
				else t_idle=time();
			}
	}
}

#endif