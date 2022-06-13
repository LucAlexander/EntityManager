#ifndef SYSTEMS_H
#define SYSTEMS_H

#include "bitmasks.h"
#include <stdarg.h>

struct entity_data;
struct vec_t;

typedef struct system_t{
	vu64_t mask;
	vu64_t filter;
	vu64_t magnet;
	void (*func)(uint32_t, struct vec_t*);
}system_t;

system_t system_init(void f(uint32_t, struct vec_t*), uint32_t n, ...);
void system_add_filter(system_t* sys, uint32_t n, ...);
void system_remove_filter(system_t* sys, uint32_t n, ...);
void system_add_magnet(system_t* sys, uint32_t n, ...);
void system_remove_magnet(system_t* sys, uint32_t n, ...);
void system_run(system_t* sys, struct entity_data* medium);
void system_free(system_t* sys);

#endif
