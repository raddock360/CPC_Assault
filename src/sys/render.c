#include <sys/render.h>
#include <man/entity.h>
#include <sprites/main_palette.h>

u8* g_screen;
u8* g_backBuffer;

//================================================================================
//================================================================================
// FUNCIONES PRIVADAS
//================================================================================
//================================================================================

/////////////////////////////////////////////////////////////////////////////////
// RENDERIZA UNA ENTIDAD
// - Pinta una entidad en pantalla.
//
void sys_render_one_entity (Entity_t* e) {
	u8* pvmem =	cpct_getScreenPtr(g_backBuffer, e->x, e->y);
	
	if(e->type & e_type_dead) {
		cpct_drawSolidBox(e->pos_ptr[2], 0, e->w, e->h);
		cpct_drawSolidBox(e->pos_ptr[1], 0, e->w, e->h);

	} else {
		cpct_drawSolidBox(e->pos_ptr[2], 0, e->w, e->h);
		cpct_drawSprite(e->sprite, pvmem, e->w, e->h);
	}

	e->pos_ptr[0] = pvmem;
	e->pos_ptr[2] = e->pos_ptr[1];
	e->pos_ptr[1] = e->pos_ptr[0];
	

	// Si la entidad está muerta, dibujamos borramos su sprite con una caja negra
	// Si está viva, la renderizamos en la nueva posición	
	//if (e->type & e_type_dead) {
	//	cpct_drawSolidBox(pvmem, 0, e->w, e->h);
	//} else if (!(e->type & e_type_dead)) {
	//	cpct_drawSprite(e->sprite, pvmem, e->w, e->h);
	//} 
}

//================================================================================
//================================================================================
// FUNCIONES PÚBLICAS
//================================================================================
//================================================================================

/////////////////////////////////////////////////////////////////////////////////
// INICIALIZA LA PANTALLA DE JUEGO
// - Inicializa el modo de vídeo y establece los colores
//
void sys_render_init() {
	cpct_setVideoMode(0);
	cpct_setBorder(HW_BLACK);
	cpct_setPalette(main_palette, 16);
	g_screen = (u8*)0xC000;
	g_backBuffer = (u8*)0x8000;
	cpct_memset(g_screen, 0, 0x4000);
	cpct_memset(g_backBuffer, 0, 0x4000);
}

/////////////////////////////////////////////////////////////////////////////////
// INICIALIZA LA PANTALLA DE JUEGO
// - Inicializa el modo de vídeo y establece los colores
//
void sys_render_switch_video_buffers() {
	u8* temp = g_screen;
	g_screen = g_backBuffer;
	g_backBuffer = temp;
	cpct_setVideoMemoryPage((u16)g_screen >> 10);
}

/////////////////////////////////////////////////////////////////////////////////
// ACTUALIZA EL MOTOR DE RENDER
// - Pinta todas las entidades de la pantalla. Para ello, llama al mánager 
// de entidades pasándole el puntero a la función de renderizado. El mánager se 
// encarga de aplicar la función a cada una de las entidades.
//
void sys_render_update() {
	man_entity_forall_matching(sys_render_one_entity, e_cmp_render);
}
