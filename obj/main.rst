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
                             13 	.globl _createEntity
                             14 	.globl _sys_render_update
                             15 	.globl _sys_physics_update
                             16 	.globl _man_entity_create
                             17 	.globl _man_entity_init
                             18 	.globl _cpct_getRandom_mxor_u8
                             19 	.globl _cpct_setPALColour
                             20 	.globl _cpct_waitVSYNC
                             21 	.globl _cpct_setVideoMode
                             22 	.globl _cpct_waitHalts
                             23 	.globl _cpct_memcpy
                             24 	.globl _cpct_disableFirmware
                             25 	.globl _init_e
                             26 ;--------------------------------------------------------
                             27 ; special function registers
                             28 ;--------------------------------------------------------
                             29 ;--------------------------------------------------------
                             30 ; ram data
                             31 ;--------------------------------------------------------
                             32 	.area _DATA
                             33 ;--------------------------------------------------------
                             34 ; ram data
                             35 ;--------------------------------------------------------
                             36 	.area _INITIALIZED
                             37 ;--------------------------------------------------------
                             38 ; absolute external ram data
                             39 ;--------------------------------------------------------
                             40 	.area _DABS (ABS)
                             41 ;--------------------------------------------------------
                             42 ; global & static initialisations
                             43 ;--------------------------------------------------------
                             44 	.area _HOME
                             45 	.area _GSINIT
                             46 	.area _GSFINAL
                             47 	.area _GSINIT
                             48 ;--------------------------------------------------------
                             49 ; Home
                             50 ;--------------------------------------------------------
                             51 	.area _HOME
                             52 	.area _HOME
                             53 ;--------------------------------------------------------
                             54 ; code
                             55 ;--------------------------------------------------------
                             56 	.area _CODE
                             57 ;src/main.c:13: void  createEntity() {
                             58 ;	---------------------------------
                             59 ; Function createEntity
                             60 ; ---------------------------------
   4000                      61 _createEntity::
                             62 ;src/main.c:14: Entity_t* e = man_entity_create();
   4000 CD 8E 40      [17]   63 	call	_man_entity_create
   4003 4D            [ 4]   64 	ld	c, l
   4004 44            [ 4]   65 	ld	b, h
                             66 ;src/main.c:15: cpct_memcpy(e, &init_e, sizeof(Entity_t));
   4005 59            [ 4]   67 	ld	e, c
   4006 50            [ 4]   68 	ld	d, b
   4007 C5            [11]   69 	push	bc
   4008 21 05 00      [10]   70 	ld	hl, #0x0005
   400B E5            [11]   71 	push	hl
   400C 21 2A 40      [10]   72 	ld	hl, #_init_e
   400F E5            [11]   73 	push	hl
   4010 D5            [11]   74 	push	de
   4011 CD CB 41      [17]   75 	call	_cpct_memcpy
   4014 C1            [10]   76 	pop	bc
                             77 ;src/main.c:16: e->y = cpct_rand() % 200;
   4015 03            [ 6]   78 	inc	bc
   4016 03            [ 6]   79 	inc	bc
   4017 C5            [11]   80 	push	bc
   4018 CD E3 41      [17]   81 	call	_cpct_getRandom_mxor_u8
   401B 55            [ 4]   82 	ld	d, l
   401C 3E C8         [ 7]   83 	ld	a, #0xc8
   401E F5            [11]   84 	push	af
   401F 33            [ 6]   85 	inc	sp
   4020 D5            [11]   86 	push	de
   4021 33            [ 6]   87 	inc	sp
   4022 CD 49 41      [17]   88 	call	__moduchar
   4025 F1            [10]   89 	pop	af
   4026 7D            [ 4]   90 	ld	a, l
   4027 C1            [10]   91 	pop	bc
   4028 02            [ 7]   92 	ld	(bc), a
   4029 C9            [10]   93 	ret
   402A                      94 _init_e:
   402A 01                   95 	.db #0x01	; 1
   402B 4F                   96 	.db #0x4f	; 79	'O'
   402C 01                   97 	.db #0x01	; 1
   402D FF                   98 	.db #0xff	; -1
   402E FF                   99 	.db #0xff	; 255
                            100 ;src/main.c:19: void wait(u8 n) {
                            101 ;	---------------------------------
                            102 ; Function wait
                            103 ; ---------------------------------
   402F                     104 _wait::
                            105 ;src/main.c:20: do {
   402F 21 02 00      [10]  106 	ld	hl, #2+0
   4032 39            [11]  107 	add	hl, sp
   4033 4E            [ 7]  108 	ld	c, (hl)
   4034                     109 00101$:
                            110 ;src/main.c:21: cpct_waitHalts(2);
   4034 C5            [11]  111 	push	bc
   4035 2E 02         [ 7]  112 	ld	l, #0x02
   4037 CD 60 41      [17]  113 	call	_cpct_waitHalts
   403A CD A7 41      [17]  114 	call	_cpct_waitVSYNC
   403D C1            [10]  115 	pop	bc
                            116 ;src/main.c:23: } while(--n);
   403E 0D            [ 4]  117 	dec c
   403F 20 F3         [12]  118 	jr	NZ,00101$
   4041 C9            [10]  119 	ret
                            120 ;src/main.c:26: void main(void) {
                            121 ;	---------------------------------
                            122 ; Function main
                            123 ; ---------------------------------
   4042                     124 _main::
                            125 ;src/main.c:27: cpct_disableFirmware();
   4042 CD D3 41      [17]  126 	call	_cpct_disableFirmware
                            127 ;src/main.c:28: cpct_setVideoMode(0);
   4045 2E 00         [ 7]  128 	ld	l, #0x00
   4047 CD AF 41      [17]  129 	call	_cpct_setVideoMode
                            130 ;src/main.c:29: cpct_setBorder(HW_BLACK);
   404A 21 10 14      [10]  131 	ld	hl, #0x1410
   404D E5            [11]  132 	push	hl
   404E CD 3D 41      [17]  133 	call	_cpct_setPALColour
                            134 ;src/main.c:30: cpct_setPALColour(0, HW_BLACK);
   4051 21 00 14      [10]  135 	ld	hl, #0x1400
   4054 E5            [11]  136 	push	hl
   4055 CD 3D 41      [17]  137 	call	_cpct_setPALColour
                            138 ;src/main.c:32: man_entity_init();
   4058 CD 79 40      [17]  139 	call	_man_entity_init
                            140 ;src/main.c:33: for(u8 i = 5; i > 0; --i)
   405B 0E 05         [ 7]  141 	ld	c, #0x05
   405D                     142 00106$:
   405D 79            [ 4]  143 	ld	a, c
   405E B7            [ 4]  144 	or	a, a
   405F 28 08         [12]  145 	jr	Z,00103$
                            146 ;src/main.c:34: createEntity();
   4061 C5            [11]  147 	push	bc
   4062 CD 00 40      [17]  148 	call	_createEntity
   4065 C1            [10]  149 	pop	bc
                            150 ;src/main.c:33: for(u8 i = 5; i > 0; --i)
   4066 0D            [ 4]  151 	dec	c
   4067 18 F4         [12]  152 	jr	00106$
                            153 ;src/main.c:36: while(1) {
   4069                     154 00103$:
                            155 ;src/main.c:37: sys_physics_update();
   4069 CD FD 40      [17]  156 	call	_sys_physics_update
                            157 ;src/main.c:38: sys_render_update();
   406C CD 34 41      [17]  158 	call	_sys_render_update
                            159 ;src/main.c:39: wait(10);
   406F 3E 0A         [ 7]  160 	ld	a, #0x0a
   4071 F5            [11]  161 	push	af
   4072 33            [ 6]  162 	inc	sp
   4073 CD 2F 40      [17]  163 	call	_wait
   4076 33            [ 6]  164 	inc	sp
   4077 18 F0         [12]  165 	jr	00103$
                            166 	.area _CODE
                            167 	.area _INITIALIZER
                            168 	.area _CABS (ABS)
