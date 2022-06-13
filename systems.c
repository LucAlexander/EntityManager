#include "systems.h"
#include "entities.h"

system_t system_init(void f(uint32_t, vec_t*), uint32_t n, ...){
	system_t sys;
	sys.mask = vu64_tInit();
	sys.filter= vu64_tInit();
	sys.magnet = vu64_tInit();
	sys.func = f;
	uint32_t i;
	va_list v;
	va_start(v,n);
	for (i = 0;i<n;++i){
		maskAddBit(&sys.mask, va_arg(v, uint32_t));
	}
	//TODO set default mask filters for entity flags
	va_end(v);
	return sys;
}

void system_add_filter(system_t* sys, uint32_t n, ...){
	uint32_t i;
	va_list v;
	va_start(v, n);
	for (i = 0;i<n;++i){
		maskAddBit(&sys->filter, va_arg(v, uint32_t));
	}
	va_end(v);
}

void system_remove_filter(system_t* sys, uint32_t n, ...){
	uint32_t i;
	va_list v;
	va_start(v, n);
	for (i = 0;i<n;++i){
		maskRemoveBit(&sys->filter, va_arg(v, uint32_t));
	}
	va_end(v);
}

void system_add_magnet(system_t* sys, uint32_t n, ...){
	uint32_t i;
	va_list v;
	va_start(v, n);
	for (i = 0;i<n;++i){
		maskAddBit(&sys->magnet, va_arg(v, uint32_t));
	}
	va_end(v);
}

void system_remove_magnet(system_t* sys, uint32_t n, ...){
	uint32_t i;
	va_list v;
	va_start(v, n);
	for (i = 0;i<n;++i){
		maskRemoveBit(&sys->magnet, va_arg(v, uint32_t));
	}
	va_end(v);
}

void system_run(system_t* sys, entity_data* medium){
	uint32_t archetype, entity;
	for (archetype = 0;archetype<medium->archetypes.size;++archetype){
		archetype_v2* arch = varch_tRefTrusted(&medium->archetypes, archetype);
		if (maskCompare(&sys->mask, &arch->mask)){
			for (entity = 0;entity<arch->data.size;++entity){
				sys->func(entity, (vec_t*)mat_tRef(&arch->data, entity));
			}
		}
	}
}

void system_free(system_t* sys){
	vu64_tFree(&sys->mask);
	vu64_tFree(&sys->filter);
	vu64_tFree(&sys->magnet);
}

