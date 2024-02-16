#ifndef _LOAD_LEVEL
#define _LOAD_LEVEL

#define dospage			63
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
	u8 j=0;
	u16 i=0;
	u16 addr_get=32768;
	u16 addr_put=32768;
	u8 buf[3];
	u8 nn;
	
	switch (level) {
		case 0:
			load_file("map0_img", 60, 1);
			load_file("map0_cod", 62, 1);
		break;
		case 1:
			load_file("map1_img", 60, 1);
			load_file("map1_cod", 62, 1);
		break;
		case 2:
			load_file("map2_img", 60, 1);
			load_file("map2_cod", 62, 1);
		break;
	}
	
		for(;;){
			do {
				buf[j]=get_mem(60,addr_get+i)-48; // 48 is 30 in HEX
				j++;
				i++;
			}
			while (get_mem(60,addr_get+i)!=#0x2C&&get_mem(60,addr_get+i)!=#0x3B);
			
			if (j==3) nn=100*buf[0]+10*buf[1]+buf[2];
			else if (j==2) nn=10*buf[0]+buf[1];
			else nn=buf[0];
			
			put_mem(61,addr_put++,nn);
			
			if (get_mem(60,addr_get+i)==#0x3B)
				break;
			i++;
			j=0;
		}
		
		j=0;
		i=0;
		addr_get=32768;
		addr_put=32768;
		
		for(;;){
			do {
				buf[j]=get_mem(62,addr_get+i)-48; // 48 is 30 in HEX
				j++;
				i++;
			}
			while (get_mem(62,addr_get+i)!=#0x2C&&get_mem(62,addr_get+i)!=#0x3B);
			
			if (j==3) nn=100*buf[0]+10*buf[1]+buf[2];
			else if (j==2) nn=10*buf[0]+buf[1];
			else nn=buf[0];
			
			put_mem(63,addr_put++,nn);
			
			if (get_mem(62,addr_get+i)==#0x3B)
				break;
			i++;
			j=0;
		}

}

// void load_img()
// {
	// u8 x, y;
	// u16 i=0;
	// u16 addr=0;
	
	// addr=32768+40*screen;
	
	// for (y=0;y<HIGH_LEVEL;y++){
		// for (x=0;x<WIDTH_LEVEL;x++)
		// {
			// map[y][x]=get_mem(61,addr++);
			
		// }
		// addr+=160;
	// }
// }

// void load_map()
// {
	// u8 x, y;
	// u16 i=0;
	// u16 addr=0;
	
	// addr=32768+40*screen;
	
	// for (y=0;y<HIGH_LEVEL;y++){
		// for (x=0;x<WIDTH_LEVEL;x++)
		// {
			// map[y][x]=get_mem(63,addr++);
			
		// }
		// addr+=160;
	// }
// }






#endif


// do
			// {
				// buf[j]=get_mem(30,addr+i)-48; // 48 is 30 in HEX
				// j++;
				// i++;
			// }
			// while (get_mem(30,addr+i)!=#0x2C);
			
			// if (j==3) map[y][x]=100*buf[0]+10*buf[1]+buf[2];
			// else if (j==2) map[y][x]=10*buf[0]+buf[1];
			// else map[y][x]=buf[0];
			
			// i++;
			// j=0;









// u8 LoadLevel()
// {
	// u8 map[40][25];
	// u8 x, y;
	// u8 j=0;
	// u16 i=0;
	// u8 buf[3];
	// u8 *p;
	
	// p=(*map[25]);
	
	// load_file("level001", 30, 1);
		
	// for (y=0;y<25;y++)
		// for (x=0;x<40;x++)
		// {
			// do
			// {
				// buf[j]=get_mem(30,32768+i)-48;
				// j++;
				// i++;
			// }while (get_mem(30,32768+i)!=',');
			
			// if (j==3) map[x][y]=100*buf[0]+10*buf[1]+buf[2];
			// else if (j==2) map[x][y]=10*buf[0]+buf[1];
			// else map[x][y]=buf[0];

			// i++;
			// j=0;
		// }
	// return *p;
// }