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
	.globl _sys_generator_update
	.globl _sys_render_init
	.globl _sys_render_update
	.globl _sys_physics_update
	.globl _man_entity_update
	.globl _man_entity_init
	.globl _cpct_waitVSYNC
	.globl _cpct_waitHalts
	.globl _cpct_disableFirmware
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
;src/main.c:7: void wait (u8 n) {
;	---------------------------------
; Function wait
; ---------------------------------
_wait::
;src/main.c:8: do {
	ld	hl, #2+0
	add	hl, sp
	ld	c, (hl)
00101$:
;src/main.c:9: cpct_waitHalts(2);
	push	bc
	ld	l, #0x02
	call	_cpct_waitHalts
	call	_cpct_waitVSYNC
	pop	bc
;src/main.c:11: } while(--n);
	dec c
	jr	NZ,00101$
	ret
;src/main.c:14: void main(void) {
;	---------------------------------
; Function main
; ---------------------------------
_main::
;src/main.c:15: cpct_disableFirmware();
	call	_cpct_disableFirmware
;src/main.c:17: man_entity_init();
	call	_man_entity_init
;src/main.c:18: sys_render_init();
	call	_sys_render_init
;src/main.c:20: while(1) {
00102$:
;src/main.c:21: sys_physics_update();
	call	_sys_physics_update
;src/main.c:22: sys_generator_update();
	call	_sys_generator_update
;src/main.c:23: sys_render_update();
	call	_sys_render_update
;src/main.c:25: man_entity_update();
	call	_man_entity_update
;src/main.c:26: cpct_waitVSYNC();
	call	_cpct_waitVSYNC
	jr	00102$
	.area _CODE
	.area _INITIALIZER
	.area _CABS (ABS)
