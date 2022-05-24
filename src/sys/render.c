#include <sys/render.h>
#include <man/entity.h>
#include <sprites/main_palette.h>

//================================================================================
//================================================================================
// FUNCIONES PRIVADAS
//================================================================================
//================================================================================

/////////////////////////////////////////////////////////////////////////////////
// RENDERIZA UNA ENTIDAD
// - Pinta una estrella en pantalla
//
void sys_render_one_entity (Entity_t* e) {
	if (!(e->type & e_type_dead)) {
		u8 *pvmem = cpct_getScreenPtr (CPCT_VMEM_START, e->x, e->y);
		cpct_drawSprite(e->sprite, pvmem, e->w, e->h);
	} 
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
}

/////////////////////////////////////////////////////////////////////////////////
// ACTUALIZA EL MOTOR DE RENDER
// - Pinta todas las entidades de la pantalla. Para ello, llama al mánager 
// de entidades pasándole el puntero a la función de renderizado. El mánager se 
// encarga de aplicar la función a cada una de las entidades.
//
void sys_render_update() {
    man_entity_forall (sys_render_one_entity);
}
