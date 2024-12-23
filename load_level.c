#ifndef _LOAD_LEVEL
#define _LOAD_LEVEL

#define dospage		63
#define _MEMSLOT2	0x0000FF52
#define _DOS_3D13	0x0000E0A1

void put_mem(u8 pg, u16 addr, u8 data) __naked
{
//addr=32768+nn
__asm
	push	ix
	ld	ix,#0
	add	ix,sp
//pg
ld a,4 (ix)
xor #0x7f
ld bc,#0xbff7
ld (_MEMSLOT2),a
out (c),a
//addr
ld l,5 (ix)
ld h,6 (ix)
//data
ld a,7 (ix)
ld (hl),a
ld a,#0x71
out (c),a
	pop ix
	ret
__endasm;
}


u8 get_mem(u8 pg, u16 addr) __naked
{
//addr=32768+nn
__asm
	push	ix
	ld	ix,#0
	add	ix,sp
//pg
ld a,4 (ix)
xor #0x7f
ld bc,#0xbff7
ld (_MEMSLOT2),a
out (c),a
//addr
ld l,5 (ix)
ld h,6 (ix)
//data
ld l,(hl)
ld a,#0x71
out (c),a
	pop ix
	ret
__endasm;
}

u16 strlen (u8 * str)
{
	static u8 a,i;
	a=0;
	while(1)
	{
		i=*str++;
		if(!i) break;
		if(i=='\0') break;
		if(i=='^') break;
		a++;
	}
	return a;
}

i8 strcmp(u8 *str1, u8 *str2)
{	
	static u8 a,l1,l2;
	l1=strlen(str1);
	l2=strlen(str2);
	if(l1>l2) return -1;
	else if(l1<l2) return 1;
	else
	{
		for(a=0;a<l1;a++)
		{
			if(*(str1+a)<*(str2+a)) return 1;
			if(*(str1+a)>*(str2+a)) return -1;
		}
	}
	return 0;
}

void DOS(u8 pg, u8 operation,u8 blocks, u8 sector, u8 track, u16 begin_page)  __naked
	{
			__asm
			push ix
			ld	ix,#0
			add	ix,sp
			
			ld a,4 (ix)
			ex af,af
			
			ld c,5 (ix)
			ld b,6 (ix)
			ld e,7 (ix)
			ld d,8 (ix)
			ld l,9 (ix)
			ld h,10 (ix)
			call #_DOS_3D13
			
			pop ix
			ret
			__endasm;
	}

void load_file(u8 *filename,u8 page,u8 saveload)
	{
		static u8 buf[16];
		static u8 a;
		static u16 c;
		vsync();
		DOS(#0x7f-dospage,5,7,0,0,32768);//прочтем нулевую дорожку
		vsync();
		buf[8]='^';
		c=0;

		while(strcmp(buf,filename)!=0 && c<1792)
		{
			for(a=0;a<16;a++)
			{
				buf[a]=get_mem(dospage,32768+a+c);
			}
			buf[8]='^';
			c+=16;
		}
		vsync();
		if(saveload==1)
		{
			DOS(#0x7f-page,5,buf[13],buf[14],buf[15],32768);
		}
		else
		{
			DOS(#0x7f-page,6,1,buf[14],buf[15],32768);
		}
		vsync();
	}


void load_level()
{
	switch (level) {
		case 0:
			load_file("lev1_gfx", PAGE_GFX, 1);
			load_file("lev1_map", PAGE_MAP, 1);
			load_file("lev1_gfx", PAGE_GFX_TMP, 1);
			load_file("lev1_map", PAGE_MAP_TMP, 1);
			level_back=IMG_BACK_SNOW;
			level_tile=IMG_TILE_SNOW;
			level_size=18;
			
			screen=0;
			player.x=8;//8
			player.y=120;//120
			player.health=5;
			player.life=3;
			player.ammo=0;
			player.frame=25;
			player.enemy_collision=0;
			player.v_speed=0;
			
			level_palett_default=0;
			level_music_default=1;
		break;
		case 1:
			load_file("lev2_gfx", PAGE_GFX, 1);
			load_file("lev2_map", PAGE_MAP, 1);
			load_file("lev2_gfx", PAGE_GFX_TMP, 1);
			load_file("lev2_map", PAGE_MAP_TMP, 1);
			level_back=IMG_BACK_MINE;
			level_tile=IMG_TILE_MINE;
			level_size=18;
			
			screen=0;
			player.x=8;//8
			player.y=112;//112
			// player.health=5;
			// player.life=3;
			// player.ammo=5;
			player.frame=25;
			player.enemy_collision=0;
			player.v_speed=0;
			
			level_palett_default=1;
			level_music_default=2;
			
		break;
		case 2:
			load_file("lev3_gfx", PAGE_GFX, 1);
			load_file("lev3_map", PAGE_MAP, 1);
			load_file("lev3_gfx", PAGE_GFX_TMP, 1);
			load_file("lev3_map", PAGE_MAP_TMP, 1);
			level_back=IMG_BACK_LAB;
			level_tile=IMG_TILE_LAB;
			level_size=18;
			
			screen=2;
			player.x=130;
			player.y=63;
			// player.health=5;
			// player.life=3;
			// player.ammo=5;
			player.frame=25;
			player.enemy_collision=0;
			player.v_speed=0;
			
			level_palett_default=2;
			level_music_default=3;
		break;
	}
}

void reload_level()
{
	u16 i, j;
	u16 addr;
	u8 data;
	
	switch (tmp_save.screen){
		case 6:
		addr=32768+(40*6);
		break;
		case 12:
		addr=32768+(40*12);
		break;
		default:
		addr=32768;
		break;
	}

	for (j=0;j<22;j++){
		for (i=0;i<240;i++){
			data=get_mem(PAGE_MAP_TMP,addr);
			put_mem(PAGE_MAP,addr,data);
			data=get_mem(PAGE_GFX_TMP,addr);
			put_mem(PAGE_GFX,addr,data);
			addr++;
		}
		addr+=480;
	}
	
		
}

#endif
