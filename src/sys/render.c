#include <sys/render.h>
#include <man/entity.h>
#include <sprites/main_palette.h>

//================================================================================
//================================================================================
// FUNCIONES PRIVADAS
//================================================================================
//================================================================================

/////////////////////////////////////////////////////////////////////////////////
// PRE RENDER ONE ENTITY
// - Calcula el puntero a la memoria de vídeo de una entidad y lo almacena en su
// 	 estructura.
//
void sys_pre_render_one_entity (Entity_t* e) {
	u8* pvmem = cpct_getScreenPtr(CPCT_VMEM_START, e->x, e->y);
	u8* prev  = e->prev_pos;

	if(prev != pvmem) {
		e->prev_pos = e->next_pos;
		e->next_pos = pvmem;
		e->move = entity_move;
	}
}

/////////////////////////////////////////////////////////////////////////////////
// RENDERIZA UNA ENTIDAD
// - Pinta una entidad en pantalla.
//
void sys_render_one_entity (Entity_t* e) {
	if(e->type & e_type_dead) {
			cpct_drawSolidBox(e->prev_pos, 0, e->w, e->h);
	} else if(e->move){
		cpct_drawSolidBox(e->prev_pos, 0, e->w, e->h);
		cpct_drawSprite(e->sprite, e->next_pos, e->w, e->h);
		e->move = entity_not_move;
	}
	
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
}

/////////////////////////////////////////////////////////////////////////////////
// PRE RENDER
// - Pre cachea los punteros a la memoria de vídeo de cada entidad. Al tenerlas 
// calculadas de antemano reducimos el tiempo del renderizado propiamente dicho
//
void sys_pre_render_update() {
    man_entity_forall_matching(sys_pre_render_one_entity, e_cmp_render);
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
