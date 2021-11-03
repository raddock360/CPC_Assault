#include <sys/render.h>
#include <man/entity.h>

//================================================================================
//================================================================================
//  FUNCIONES PRIVADAS
//================================================================================
//================================================================================

/////////////////////////////////////////////////////////////////////////////////
//  RENDERIZA UNA ENTIDAD
//      - Pinta una estrella en pantalla
//
void sys_render_one_entity (Entity_t* e) {
	if (e->prevptr != 0) 
		*(e->prevptr) = 0;
	
	if (!(e->type & e_type_dead)) {
		u8* pvmem = cpct_getScreenPtr (CPCT_VMEM_START, e->x, e->y);
		*pvmem = e->color;
		e->prevptr = pvmem;
	} 
}

//================================================================================
//================================================================================
//  FUNCIONES PÚBLICAS
//================================================================================
//================================================================================

/////////////////////////////////////////////////////////////////////////////////
//  INICIALIZA LA PANTALLA DE JUEGO
//		- Inicializa el modo de vídeo y establece los colores
//
void sys_render_init() {
	cpct_setVideoMode(0);
	cpct_setBorder(HW_BLACK);
   	cpct_setPALColour(0, HW_BLACK);
}

/////////////////////////////////////////////////////////////////////////////////
//  ACTUALIZA EL MOTOR DE RENDER
//      - Pinta todas las entidades de la pantalla, llamando al mánager de 
//		  entidades mediante la inversión de control
//
void sys_render_update() {
    man_entity_forall (sys_render_one_entity);
}
