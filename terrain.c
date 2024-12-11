#ifndef _TERRAIN
#define _TERRAIN

void terrain_animation()
{
	static u8 n;
	for (n=1;n<=water_summ;n++){
		if (water[n].frame<water[n].n_spr+36){
			water[n].frame+=4;
			waterplant[n].frame+=4;
		}
		else {
			water[n].frame-=36;
			waterplant[n].frame-=36;
		}
	}
	
	for (n=1;n<=light_summ;n++){
		if (light[n].frame<light[n].n_spr+11){
			light[n].frame++;
		}
		else {
			light[n].frame=light[n].n_spr;
		}
	}
	
	for (n=1;n<=fan_summ;n++){
		if (fan[n].frame<fan[n].n_spr+7){
			fan[n].frame++;
		}
		else {
			fan[n].frame=fan[n].n_spr;
		}
	}
}

#endif