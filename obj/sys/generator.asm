;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.6.8 #9946 (Linux)
;--------------------------------------------------------
	.module generator
	.optsdcc -mz80
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _generateNewStar
	.globl _man_entity_freeSpace
	.globl _man_entity_create
	.globl _cpct_getRandom_mxor_u8
	.globl _cpct_memcpy
	.globl _init_e
	.globl _sys_generator_update
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
;src/sys/generator.c:27: void generateNewStar() {
;	---------------------------------
; Function generateNewStar
; ---------------------------------
_generateNewStar::
;src/sys/generator.c:28: Entity_t* e = man_entity_create();           // Puntero a la entidad reservada en el array
	call	_man_entity_create
	ex	de,hl
;src/sys/generator.c:29: cpct_memcpy(e, &init_e, sizeof(Entity_t));   // Inicializamos la entidad con los valores standar
	ld	c, e
	ld	b, d
	push	de
	ld	hl, #0x0007
	push	hl
	ld	hl, #_init_e
	push	hl
	push	bc
	call	_cpct_memcpy
	pop	de
;src/sys/generator.c:30: e->y  = cpct_rand() % 200;                   // Asignamos una posición y aleatoria (0 a 200)
	ld	c, e
	ld	b, d
	inc	bc
	inc	bc
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
	ld	(bc), a
;src/sys/generator.c:31: e->vx = -1-(cpct_rand() & 0x03);             // Asignamos una velocidad x aleatoria (-1 a -3 )
	ld	l, e
	ld	h, d
	inc	hl
	inc	hl
	inc	hl
	push	hl
	push	de
	call	_cpct_getRandom_mxor_u8
	ld	a, l
	pop	de
	pop	hl
	and	a, #0x03
	ld	c, a
	ld	a, #0xff
	sub	a, c
	ld	b, a
	ld	(hl), b
;src/sys/generator.c:34: switch ( e->vx ) {
	ld	c, (hl)
;src/sys/generator.c:36: e->color = 0x88;
	ld	hl, #0x0004
	add	hl, de
;src/sys/generator.c:34: switch ( e->vx ) {
	ld	a, b
	sub	a, #0xfd
	jr	Z,00103$
	ld	a, c
	sub	a, #0xfe
	jr	Z,00102$
	inc	c
	ret	NZ
;src/sys/generator.c:36: e->color = 0x88;
	ld	(hl), #0x88
;src/sys/generator.c:37: break;
	ret
;src/sys/generator.c:38: case -2:
00102$:
;src/sys/generator.c:39: e->color = 0x08;
	ld	(hl), #0x08
;src/sys/generator.c:40: break;
	ret
;src/sys/generator.c:41: case -3:
00103$:
;src/sys/generator.c:42: e->color = 0x80;
	ld	(hl), #0x80
;src/sys/generator.c:43: }
	ret
_init_e:
	.db #0x01	; 1
	.db #0x4f	; 79	'O'
	.db #0x01	; 1
	.db #0xff	; -1
	.db #0x80	; 128
	.dw #0x0000
;src/sys/generator.c:57: void sys_generator_update() {
;	---------------------------------
; Function sys_generator_update
; ---------------------------------
_sys_generator_update::
;src/sys/generator.c:58: u8 free = man_entity_freeSpace();
	call	_man_entity_freeSpace
	ld	c, l
;src/sys/generator.c:59: if( free > 2 ) free = 2;
	ld	a, #0x02
	sub	a, c
	jr	NC,00110$
	ld	c, #0x02
;src/sys/generator.c:60: while( free ) {
00110$:
00103$:
	ld	a, c
	or	a, a
	ret	Z
;src/sys/generator.c:61: generateNewStar();   
	push	bc
	call	_generateNewStar
	pop	bc
;src/sys/generator.c:62: --free;
	dec	c
	jr	00103$
	.area _CODE
	.area _INITIALIZER
	.area _CABS (ABS)
