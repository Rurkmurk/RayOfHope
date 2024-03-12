#ifndef _TERRAIN
#define _TERRAIN

void terrain_animation()
{
	static u8 n;
	for (n=1;n<=water_summ;n++){
		if (water[n].frame<SPR_WATER+36){
			water[n].frame+=4;
			waterplant[n].frame+=4;
		}
		else {
			water[n].frame-=36;
			waterplant[n].frame-=36;
		}
	}
}

#endif