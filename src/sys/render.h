#pragma once

#include <cpctelera.h>

extern u8* g_screen;
extern u8* g_backBuffer;

void sys_render_update();
void sys_render_init();
void sys_render_switch_video_buffers();