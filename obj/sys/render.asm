;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.6.8 #9946 (Linux)
;--------------------------------------------------------
	.module render
	.optsdcc -mz80
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _sys_render_one_entity
	.globl _man_entity_forall
	.globl _cpct_getScreenPtr
	.globl _cpct_setPALColour
	.globl _cpct_setPalette
	.globl _cpct_setVideoMode
	.globl _palette
	.globl _sys_render_init
	.globl _sys_render_update
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _DATA
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _INITIALIZED
;--------------------------------------------------------
; absolute external ram data
;--------------------------------------------------------
	.area _DABS (ABS)
;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
	.area _HOME
	.area _GSINIT
	.area _GSFINAL
	.area _GSINIT
;--------------------------------------------------------
; Home
;--------------------------------------------------------
	.area _HOME
	.area _HOME
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area _CODE
;src/sys/render.c:14: void sys_render_one_entity (Entity_t* e) {
;	---------------------------------
; Function sys_render_one_entity
; ---------------------------------
_sys_render_one_entity::
	push	ix
	ld	ix,#0
	add	ix,sp
	push	af
	dec	sp
;src/sys/render.c:21: if (e->prevptr != 0) 	
	ld	c,4 (ix)
	ld	b,5 (ix)
	ld	hl, #0x0005
	add	hl,bc
	ex	(sp), hl
	pop	hl
	push	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a, d
	or	a,e
	jr	Z,00102$
;src/sys/render.c:22: *(e->prevptr) = 0;
	xor	a, a
	ld	(de), a
00102$:
;src/sys/render.c:26: if (!(e->type & e_type_dead)) {
	ld	a, (bc)
	rlca
	jr	C,00108$
;src/sys/render.c:27: xPixelCoord = e->x;
	ld	l, c
	ld	h, b
	inc	hl
	ld	d, (hl)
;src/sys/render.c:28: xByteCoord = (xPixelCoord / 2) + (xPixelCoord % 2);
	ld	e, d
	srl	e
	ld	a, d
	and	a, #0x01
	ld	-1 (ix), a
	ld	a, e
	add	a, -1 (ix)
;src/sys/render.c:29: pvmem = cpct_getScreenPtr (CPCT_VMEM_START, xByteCoord, e->y);
	ld	l, c
	ld	h, b
	inc	hl
	inc	hl
	ld	d, (hl)
	push	bc
	ld	e, a
	push	de
	ld	hl, #0xc000
	push	hl
	call	_cpct_getScreenPtr
	ex	de,hl
	pop	iy
	ld	c, 4 (iy)
;src/sys/render.c:30: if( ( xPixelCoord % 2) == 0 ) {
	ld	a, -1 (ix)
	or	a, a
	jr	NZ,00104$
;src/sys/render.c:31: *pvmem = e->color >> 1;	
	ld	a,c
	srl	a
	ld	(de), a
	jr	00105$
00104$:
;src/sys/render.c:33: *pvmem = e->color;
	ld	a, c
	ld	(de), a
00105$:
;src/sys/render.c:35: e->prevptr = pvmem;
	pop	hl
	push	hl
	ld	(hl), e
	inc	hl
	ld	(hl), d
00108$:
	ld	sp, ix
	pop	ix
	ret
;src/sys/render.c:56: void sys_render_init() {
;	---------------------------------
; Function sys_render_init
; ---------------------------------
_sys_render_init::
;src/sys/render.c:57: cpct_setVideoMode(0);
	ld	l, #0x00
	call	_cpct_setVideoMode
;src/sys/render.c:58: cpct_setBorder(HW_BLACK);
	ld	hl, #0x1410
	push	hl
	call	_cpct_setPALColour
;src/sys/render.c:59: cpct_setPalette(palette, 16);
	ld	hl, #0x0010
	push	hl
	ld	hl, #_palette
	push	hl
	call	_cpct_setPalette
	ret
_palette:
	.db #0x14	; 20
	.db #0x0b	; 11
	.db #0x0a	; 10
	.db #0x1e	; 30
	.db #0x0b	; 11
	.db #0x0b	; 11
	.db #0x0b	; 11
	.db #0x0b	; 11
	.db #0x0b	; 11
	.db #0x0b	; 11
	.db #0x0b	; 11
	.db #0x0b	; 11
	.db #0x0b	; 11
	.db #0x0b	; 11
	.db #0x0b	; 11
	.db #0x0b	; 11
;src/sys/render.c:68: void sys_render_update() {
;	---------------------------------
; Function sys_render_update
; ---------------------------------
_sys_render_update::
;src/sys/render.c:69: man_entity_forall (sys_render_one_entity);
	ld	hl, #_sys_render_one_entity
	push	hl
	call	_man_entity_forall
	pop	af
	ret
	.area _CODE
	.area _INITIALIZER
	.area _CABS (ABS)
