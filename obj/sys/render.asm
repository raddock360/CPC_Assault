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
;src/sys/render.c:4: void sys_render_one_entity (Entity_t* e) {
;	---------------------------------
; Function sys_render_one_entity
; ---------------------------------
_sys_render_one_entity::
	push	ix
	ld	ix,#0
	add	ix,sp
	push	af
	push	af
;src/sys/render.c:5: u8* pvmem = cpct_getScreenPtr (CPCT_VMEM_START, e->x - e->vx, e->y);
	ld	e,4 (ix)
	ld	d,5 (ix)
	ld	hl, #0x0002
	add	hl,de
	ld	-2 (ix), l
	ld	-1 (ix), h
	ld	b, (hl)
	ld	hl, #0x0001
	add	hl,de
	ex	(sp), hl
	pop	hl
	push	hl
	ld	c, (hl)
	ld	l, e
	ld	h, d
	inc	hl
	inc	hl
	inc	hl
	ld	l, (hl)
	ld	a, c
	sub	a, l
	push	de
	push	bc
	inc	sp
	push	af
	inc	sp
	ld	hl, #0xc000
	push	hl
	call	_cpct_getScreenPtr
	pop	de
;src/sys/render.c:6: *pvmem = 0;
	ld	(hl), #0x00
;src/sys/render.c:7: pvmem = cpct_getScreenPtr (CPCT_VMEM_START, e->x, e->y);
	ld	l,-2 (ix)
	ld	h,-1 (ix)
	ld	a, (hl)
	pop	hl
	push	hl
	ld	b, (hl)
	push	de
	push	af
	inc	sp
	push	bc
	inc	sp
	ld	hl, #0xc000
	push	hl
	call	_cpct_getScreenPtr
	ld	c, l
	ld	b, h
	pop	iy
	ld	a, 4 (iy)
	ld	(bc), a
	ld	sp, ix
	pop	ix
	ret
;src/sys/render.c:11: void sys_render_update() {
;	---------------------------------
; Function sys_render_update
; ---------------------------------
_sys_render_update::
;src/sys/render.c:12: man_entity_forall (sys_render_one_entity);
	ld	hl, #_sys_render_one_entity
	push	hl
	call	_man_entity_forall
	pop	af
	ret
	.area _CODE
	.area _INITIALIZER
	.area _CABS (ABS)
