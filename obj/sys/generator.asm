;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.6.8 #9946 (Linux)
;--------------------------------------------------------
	.module generator
	.optsdcc -mz80
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _sys_generator_update
	.globl _generateNewStar
	.globl _man_entity_create
	.globl _cpct_getRandom_mxor_u8
	.globl _cpct_memcpy
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
;src/sys/generator.c:25: void generateNewStar() {
;	---------------------------------
; Function generateNewStar
; ---------------------------------
_generateNewStar::
;src/sys/generator.c:26: Entity_t* e = man_entity_create();
	call	_man_entity_create
	ld	c, l
	ld	b, h
;src/sys/generator.c:27: cpct_memcpy(e, &init_e, sizeof(Entity_t));
	ld	e, c
	ld	d, b
	push	bc
	ld	hl, #0x0007
	push	hl
	ld	hl, #_init_e
	push	hl
	push	de
	call	_cpct_memcpy
	pop	bc
;src/sys/generator.c:28: e->y  = cpct_rand() % 200;
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
;src/sys/generator.c:29: e->vx = -1-(cpct_rand() & 0x03);
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
	.dw #0x0000
;src/sys/generator.c:42: void sys_generator_update() {
;	---------------------------------
; Function sys_generator_update
; ---------------------------------
_sys_generator_update::
;src/sys/generator.c:44: generateNewStar();   
	jp  _generateNewStar
	.area _CODE
	.area _INITIALIZER
	.area _CABS (ABS)
