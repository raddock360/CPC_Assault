#include <sys/render.h>
#include <man/entity.h>

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
	u8 xPixelCoord, xByteCoord;
	u8* pvmem;

	// Comprobamos si ya hemos pintado la estrella anteriormente. Para ello miramos si 
	// teníamos guardado el puntero a la anterior posición de memoria. En caso afirmativo
	// borramos la estrella.
	if (e->prevptr != 0) 	
		*(e->prevptr) = 0;
	
	// Si la estrella no está muerta la pintamos y almacenamos la dirección de memoria
	// en la variable [prevptr] para borrarla en el siguiente fotograma.
	if (!(e->type & e_type_dead)) {
		xPixelCoord = e->x;
		xByteCoord = (xPixelCoord / 2) + (xPixelCoord % 2);
		pvmem = cpct_getScreenPtr (CPCT_VMEM_START, xByteCoord, e->y);
		if( ( xPixelCoord % 2) == 0 ) {
			*pvmem = e->color >> 1;	
		} else {
			*pvmem = e->color;
		}
		e->prevptr = pvmem;
	} 
}

//================================================================================
//================================================================================
// FUNCIONES PÚBLICAS
//================================================================================
//================================================================================

const u8 palette[] = {
	HW_BLACK, HW_BRIGHT_WHITE, HW_BRIGHT_YELLOW, HW_YELLOW, 
	HW_BRIGHT_WHITE, HW_BRIGHT_WHITE, HW_BRIGHT_WHITE, HW_BRIGHT_WHITE,
	HW_BRIGHT_WHITE, HW_BRIGHT_WHITE, HW_BRIGHT_WHITE, HW_BRIGHT_WHITE,
	HW_BRIGHT_WHITE, HW_BRIGHT_WHITE, HW_BRIGHT_WHITE, HW_BRIGHT_WHITE
};

/////////////////////////////////////////////////////////////////////////////////
// INICIALIZA LA PANTALLA DE JUEGO
// - Inicializa el modo de vídeo y establece los colores
//
void sys_render_init() {
	cpct_setVideoMode(0);
	cpct_setBorder(HW_BLACK);
	cpct_setPalette(palette, 16);
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
