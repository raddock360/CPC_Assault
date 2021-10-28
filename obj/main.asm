;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.6.8 #9946 (Linux)
;--------------------------------------------------------
	.module main
	.optsdcc -mz80
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _main
	.globl _wait
	.globl _createEntity
	.globl _sys_render_update
	.globl _sys_physics_update
	.globl _man_entity_create
	.globl _man_entity_init
	.globl _cpct_getRandom_mxor_u8
	.globl _cpct_setPALColour
	.globl _cpct_waitVSYNC
	.globl _cpct_setVideoMode
	.globl _cpct_waitHalts
	.globl _cpct_memcpy
	.globl _cpct_disableFirmware
	.globl _init_e
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
;src/main.c:13: void  createEntity() {
;	---------------------------------
; Function createEntity
; ---------------------------------
_createEntity::
;src/main.c:14: Entity_t* e = man_entity_create();
	call	_man_entity_create
	ld	c, l
	ld	b, h
;src/main.c:15: cpct_memcpy(e, &init_e, sizeof(Entity_t));
	ld	e, c
	ld	d, b
	push	bc
	ld	hl, #0x0005
	push	hl
	ld	hl, #_init_e
	push	hl
	push	de
	call	_cpct_memcpy
	pop	bc
;src/main.c:16: e->y  = cpct_rand() % 200;
	ld	e, c
	ld	d, b
	inc	de
	inc	de
	push	bc
	push	de
	call	_cpct_getRandom_mxor_u8
	ld	h, l
	ld	a, #0xc8
	push	af
	inc	sp
	push	hl
	inc	sp
	call	__moduchar
	pop	af
	ld	a, l
	pop	de
	pop	bc
	ld	(de), a
;src/main.c:17: e->vx = -1-(cpct_rand() & 0x03);
	inc	bc
	inc	bc
	inc	bc
	push	bc
	call	_cpct_getRandom_mxor_u8
	pop	bc
	ld	a, l
	and	a, #0x03
	ld	e, a
	ld	a, #0xff
	sub	a, e
	ld	(bc), a
	ret
_init_e:
	.db #0x01	; 1
	.db #0x4f	; 79	'O'
	.db #0x01	; 1
	.db #0xff	; -1
	.db #0xff	; 255
;src/main.c:20: void wait(u8 n) {
;	---------------------------------
; Function wait
; ---------------------------------
_wait::
;src/main.c:21: do {
	ld	hl, #2+0
	add	hl, sp
	ld	c, (hl)
00101$:
;src/main.c:22: cpct_waitHalts(2);
	push	bc
	ld	l, #0x02
	call	_cpct_waitHalts
	call	_cpct_waitVSYNC
	pop	bc
;src/main.c:24: } while(--n);
	dec c
	jr	NZ,00101$
	ret
;src/main.c:27: void main(void) {
;	---------------------------------
; Function main
; ---------------------------------
_main::
;src/main.c:28: cpct_disableFirmware();
	call	_cpct_disableFirmware
;src/main.c:29: cpct_setVideoMode(0);
	ld	l, #0x00
	call	_cpct_setVideoMode
;src/main.c:30: cpct_setBorder(HW_BLACK);
	ld	hl, #0x1410
	push	hl
	call	_cpct_setPALColour
;src/main.c:31: cpct_setPALColour(0, HW_BLACK);
	ld	hl, #0x1400
	push	hl
	call	_cpct_setPALColour
;src/main.c:33: man_entity_init();
	call	_man_entity_init
;src/main.c:34: for(u8 i = 5; i > 0; --i)
	ld	c, #0x05
00106$:
	ld	a, c
	or	a, a
	jr	Z,00103$
;src/main.c:35: createEntity();
	push	bc
	call	_createEntity
	pop	bc
;src/main.c:34: for(u8 i = 5; i > 0; --i)
	dec	c
	jr	00106$
;src/main.c:37: while(1) {
00103$:
;src/main.c:38: sys_physics_update();
	call	_sys_physics_update
;src/main.c:39: sys_render_update();
	call	_sys_render_update
;src/main.c:40: wait(10);
	ld	a, #0x0a
	push	af
	inc	sp
	call	_wait
	inc	sp
	jr	00103$
	.area _CODE
	.area _INITIALIZER
	.area _CABS (ABS)
