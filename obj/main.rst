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
   4000 CD 4C 41      [17]   63 	call	_man_entity_create
   4003 4D            [ 4]   64 	ld	c, l
   4004 44            [ 4]   65 	ld	b, h
                             66 ;src/main.c:15: cpct_memcpy(e, &init_e, sizeof(Entity_t));
   4005 59            [ 4]   67 	ld	e, c
   4006 50            [ 4]   68 	ld	d, b
   4007 C5            [11]   69 	push	bc
   4008 21 05 00      [10]   70 	ld	hl, #0x0005
   400B E5            [11]   71 	push	hl
   400C 21 3E 40      [10]   72 	ld	hl, #_init_e
   400F E5            [11]   73 	push	hl
   4010 D5            [11]   74 	push	de
   4011 CD 46 42      [17]   75 	call	_cpct_memcpy
   4014 C1            [10]   76 	pop	bc
                             77 ;src/main.c:16: e->y  = cpct_rand() % 200;
   4015 59            [ 4]   78 	ld	e, c
   4016 50            [ 4]   79 	ld	d, b
   4017 13            [ 6]   80 	inc	de
   4018 13            [ 6]   81 	inc	de
   4019 C5            [11]   82 	push	bc
   401A D5            [11]   83 	push	de
   401B CD 5E 42      [17]   84 	call	_cpct_getRandom_mxor_u8
   401E 65            [ 4]   85 	ld	h, l
   401F 3E C8         [ 7]   86 	ld	a, #0xc8
   4021 F5            [11]   87 	push	af
   4022 33            [ 6]   88 	inc	sp
   4023 E5            [11]   89 	push	hl
   4024 33            [ 6]   90 	inc	sp
   4025 CD C4 41      [17]   91 	call	__moduchar
   4028 F1            [10]   92 	pop	af
   4029 7D            [ 4]   93 	ld	a, l
   402A D1            [10]   94 	pop	de
   402B C1            [10]   95 	pop	bc
   402C 12            [ 7]   96 	ld	(de), a
                             97 ;src/main.c:17: e->vx = -1-(cpct_rand() & 0x03);
   402D 03            [ 6]   98 	inc	bc
   402E 03            [ 6]   99 	inc	bc
   402F 03            [ 6]  100 	inc	bc
   4030 C5            [11]  101 	push	bc
   4031 CD 5E 42      [17]  102 	call	_cpct_getRandom_mxor_u8
   4034 C1            [10]  103 	pop	bc
   4035 7D            [ 4]  104 	ld	a, l
   4036 E6 03         [ 7]  105 	and	a, #0x03
   4038 5F            [ 4]  106 	ld	e, a
   4039 3E FF         [ 7]  107 	ld	a, #0xff
   403B 93            [ 4]  108 	sub	a, e
   403C 02            [ 7]  109 	ld	(bc), a
   403D C9            [10]  110 	ret
   403E                     111 _init_e:
   403E 01                  112 	.db #0x01	; 1
   403F 4F                  113 	.db #0x4f	; 79	'O'
   4040 01                  114 	.db #0x01	; 1
   4041 FF                  115 	.db #0xff	; -1
   4042 FF                  116 	.db #0xff	; 255
                            117 ;src/main.c:20: void wait(u8 n) {
                            118 ;	---------------------------------
                            119 ; Function wait
                            120 ; ---------------------------------
   4043                     121 _wait::
                            122 ;src/main.c:21: do {
   4043 21 02 00      [10]  123 	ld	hl, #2+0
   4046 39            [11]  124 	add	hl, sp
   4047 4E            [ 7]  125 	ld	c, (hl)
   4048                     126 00101$:
                            127 ;src/main.c:22: cpct_waitHalts(2);
   4048 C5            [11]  128 	push	bc
   4049 2E 02         [ 7]  129 	ld	l, #0x02
   404B CD DB 41      [17]  130 	call	_cpct_waitHalts
   404E CD 22 42      [17]  131 	call	_cpct_waitVSYNC
   4051 C1            [10]  132 	pop	bc
                            133 ;src/main.c:24: } while(--n);
   4052 0D            [ 4]  134 	dec c
   4053 20 F3         [12]  135 	jr	NZ,00101$
   4055 C9            [10]  136 	ret
                            137 ;src/main.c:27: void main(void) {
                            138 ;	---------------------------------
                            139 ; Function main
                            140 ; ---------------------------------
   4056                     141 _main::
                            142 ;src/main.c:28: cpct_disableFirmware();
   4056 CD 4E 42      [17]  143 	call	_cpct_disableFirmware
                            144 ;src/main.c:29: cpct_setVideoMode(0);
   4059 2E 00         [ 7]  145 	ld	l, #0x00
   405B CD 2A 42      [17]  146 	call	_cpct_setVideoMode
                            147 ;src/main.c:30: cpct_setBorder(HW_BLACK);
   405E 21 10 14      [10]  148 	ld	hl, #0x1410
   4061 E5            [11]  149 	push	hl
   4062 CD B8 41      [17]  150 	call	_cpct_setPALColour
                            151 ;src/main.c:31: cpct_setPALColour(0, HW_BLACK);
   4065 21 00 14      [10]  152 	ld	hl, #0x1400
   4068 E5            [11]  153 	push	hl
   4069 CD B8 41      [17]  154 	call	_cpct_setPALColour
                            155 ;src/main.c:33: man_entity_init();
   406C CD 37 41      [17]  156 	call	_man_entity_init
                            157 ;src/main.c:34: for(u8 i = 5; i > 0; --i)
   406F 0E 05         [ 7]  158 	ld	c, #0x05
   4071                     159 00106$:
   4071 79            [ 4]  160 	ld	a, c
   4072 B7            [ 4]  161 	or	a, a
   4073 28 08         [12]  162 	jr	Z,00103$
                            163 ;src/main.c:35: createEntity();
   4075 C5            [11]  164 	push	bc
   4076 CD 00 40      [17]  165 	call	_createEntity
   4079 C1            [10]  166 	pop	bc
                            167 ;src/main.c:34: for(u8 i = 5; i > 0; --i)
   407A 0D            [ 4]  168 	dec	c
   407B 18 F4         [12]  169 	jr	00106$
                            170 ;src/main.c:37: while(1) {
   407D                     171 00103$:
                            172 ;src/main.c:38: sys_physics_update();
   407D CD C8 40      [17]  173 	call	_sys_physics_update
                            174 ;src/main.c:39: sys_render_update();
   4080 CD 2E 41      [17]  175 	call	_sys_render_update
                            176 ;src/main.c:40: wait(10);
   4083 3E 0A         [ 7]  177 	ld	a, #0x0a
   4085 F5            [11]  178 	push	af
   4086 33            [ 6]  179 	inc	sp
   4087 CD 43 40      [17]  180 	call	_wait
   408A 33            [ 6]  181 	inc	sp
   408B 18 F0         [12]  182 	jr	00103$
                            183 	.area _CODE
                            184 	.area _INITIALIZER
                            185 	.area _CABS (ABS)
