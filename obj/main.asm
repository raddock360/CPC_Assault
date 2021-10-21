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
	.globl _createEntity
	.globl _sys_physics_update
	.globl _man_entity_create
	.globl _man_entity_init
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
;src/main.c:12: void  createEntity() {
;	---------------------------------
; Function createEntity
; ---------------------------------
_createEntity::
;src/main.c:13: Entity_t* e = man_entity_create();
	call	_man_entity_create
;src/main.c:14: cpct_memcpy(e, &init_e, sizeof(Entity_t));
	ld	bc, #_init_e+0
	ld	de, #0x0005
	push	de
	push	bc
	push	hl
	call	_cpct_memcpy
	ret
_init_e:
	.db #0x01	; 1
	.db #0x4f	; 79	'O'
	.db #0x01	; 1
	.db #0xff	; -1
	.db #0xff	; 255
;src/main.c:18: void main(void) {
;	---------------------------------
; Function main
; ---------------------------------
_main::
;src/main.c:19: man_entity_init();
	call	_man_entity_init
;src/main.c:20: for(u8 i = 5; i > 0; --i)
	ld	c, #0x05
00106$:
	ld	a, c
	or	a, a
	jr	Z,00101$
;src/main.c:21: createEntity();
	push	bc
	call	_createEntity
	pop	bc
;src/main.c:20: for(u8 i = 5; i > 0; --i)
	dec	c
	jr	00106$
00101$:
;src/main.c:22: sys_physics_update();
	call	_sys_physics_update
;src/main.c:24: while(1);
00103$:
	jr	00103$
	.area _CODE
	.area _INITIALIZER
	.area _CABS (ABS)
