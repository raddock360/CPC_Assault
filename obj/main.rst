                              1 ;--------------------------------------------------------
                              2 ; File Created by SDCC : free open source ANSI-C Compiler
                              3 ; Version 3.6.8 #9946 (Linux)
                              4 ;--------------------------------------------------------
                              5 	.module main
                              6 	.optsdcc -mz80
                              7 	
                              8 ;--------------------------------------------------------
                              9 ; Public variables in this module
                             10 ;--------------------------------------------------------
                             11 	.globl _main
                             12 	.globl _wait
                             13 	.globl _sys_generator_update
                             14 	.globl _sys_render_update
                             15 	.globl _sys_physics_update
                             16 	.globl _man_entity_update
                             17 	.globl _man_entity_init
                             18 	.globl _cpct_waitVSYNC
                             19 	.globl _cpct_waitHalts
                             20 	.globl _cpct_disableFirmware
                             21 ;--------------------------------------------------------
                             22 ; special function registers
                             23 ;--------------------------------------------------------
                             24 ;--------------------------------------------------------
                             25 ; ram data
                             26 ;--------------------------------------------------------
                             27 	.area _DATA
                             28 ;--------------------------------------------------------
                             29 ; ram data
                             30 ;--------------------------------------------------------
                             31 	.area _INITIALIZED
                             32 ;--------------------------------------------------------
                             33 ; absolute external ram data
                             34 ;--------------------------------------------------------
                             35 	.area _DABS (ABS)
                             36 ;--------------------------------------------------------
                             37 ; global & static initialisations
                             38 ;--------------------------------------------------------
                             39 	.area _HOME
                             40 	.area _GSINIT
                             41 	.area _GSFINAL
                             42 	.area _GSINIT
                             43 ;--------------------------------------------------------
                             44 ; Home
                             45 ;--------------------------------------------------------
                             46 	.area _HOME
                             47 	.area _HOME
                             48 ;--------------------------------------------------------
                             49 ; code
                             50 ;--------------------------------------------------------
                             51 	.area _CODE
                             52 ;src/main.c:7: void wait(u8 n) {
                             53 ;	---------------------------------
                             54 ; Function wait
                             55 ; ---------------------------------
   4000                      56 _wait::
                             57 ;src/main.c:8: do {
   4000 21 02 00      [10]   58 	ld	hl, #2+0
   4003 39            [11]   59 	add	hl, sp
   4004 4E            [ 7]   60 	ld	c, (hl)
   4005                      61 00101$:
                             62 ;src/main.c:9: cpct_waitHalts(2);
   4005 C5            [11]   63 	push	bc
   4006 2E 02         [ 7]   64 	ld	l, #0x02
   4008 CD E8 41      [17]   65 	call	_cpct_waitHalts
   400B CD 3D 42      [17]   66 	call	_cpct_waitVSYNC
   400E C1            [10]   67 	pop	bc
                             68 ;src/main.c:11: } while(--n);
   400F 0D            [ 4]   69 	dec c
   4010 20 F3         [12]   70 	jr	NZ,00101$
   4012 C9            [10]   71 	ret
                             72 ;src/main.c:14: void main(void) {
                             73 ;	---------------------------------
                             74 ; Function main
                             75 ; ---------------------------------
   4013                      76 _main::
                             77 ;src/main.c:15: cpct_disableFirmware();
   4013 CD 5B 42      [17]   78 	call	_cpct_disableFirmware
                             79 ;src/main.c:17: man_entity_init();
   4016 CD 32 40      [17]   80 	call	_man_entity_init
                             81 ;src/main.c:18: sys_render_init();
   4019 CD A8 41      [17]   82 	call	_sys_render_init
                             83 ;src/main.c:20: while(1) {
   401C                      84 00102$:
                             85 ;src/main.c:21: sys_physics_update();
   401C CD 10 41      [17]   86 	call	_sys_physics_update
                             87 ;src/main.c:22: sys_generator_update();
   401F CD 5E 41      [17]   88 	call	_sys_generator_update
                             89 ;src/main.c:23: sys_render_update();
   4022 CD BC 41      [17]   90 	call	_sys_render_update
                             91 ;src/main.c:25: man_entity_update();
   4025 CD BD 40      [17]   92 	call	_man_entity_update
                             93 ;src/main.c:26: wait(10);
   4028 3E 0A         [ 7]   94 	ld	a, #0x0a
   402A F5            [11]   95 	push	af
   402B 33            [ 6]   96 	inc	sp
   402C CD 00 40      [17]   97 	call	_wait
   402F 33            [ 6]   98 	inc	sp
   4030 18 EA         [12]   99 	jr	00102$
                            100 	.area _CODE
                            101 	.area _INITIALIZER
                            102 	.area _CABS (ABS)
