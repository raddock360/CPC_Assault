                              1 ;--------------------------------------------------------
                              2 ; File Created by SDCC : free open source ANSI-C Compiler
                              3 ; Version 3.6.8 #9946 (Linux)
                              4 ;--------------------------------------------------------
                              5 	.module generator
                              6 	.optsdcc -mz80
                              7 	
                              8 ;--------------------------------------------------------
                              9 ; Public variables in this module
                             10 ;--------------------------------------------------------
                             11 	.globl _generateNewStar
                             12 	.globl _man_entity_freeSpace
                             13 	.globl _man_entity_create
                             14 	.globl _cpct_getRandom_mxor_u8
                             15 	.globl _cpct_memcpy
                             16 	.globl _init_e
                             17 	.globl _sys_generator_update
                             18 ;--------------------------------------------------------
                             19 ; special function registers
                             20 ;--------------------------------------------------------
                             21 ;--------------------------------------------------------
                             22 ; ram data
                             23 ;--------------------------------------------------------
                             24 	.area _DATA
                             25 ;--------------------------------------------------------
                             26 ; ram data
                             27 ;--------------------------------------------------------
                             28 	.area _INITIALIZED
                             29 ;--------------------------------------------------------
                             30 ; absolute external ram data
                             31 ;--------------------------------------------------------
                             32 	.area _DABS (ABS)
                             33 ;--------------------------------------------------------
                             34 ; global & static initialisations
                             35 ;--------------------------------------------------------
                             36 	.area _HOME
                             37 	.area _GSINIT
                             38 	.area _GSFINAL
                             39 	.area _GSINIT
                             40 ;--------------------------------------------------------
                             41 ; Home
                             42 ;--------------------------------------------------------
                             43 	.area _HOME
                             44 	.area _HOME
                             45 ;--------------------------------------------------------
                             46 ; code
                             47 ;--------------------------------------------------------
                             48 	.area _CODE
                             49 ;src/sys/generator.c:26: void generateNewStar() {
                             50 ;	---------------------------------
                             51 ; Function generateNewStar
                             52 ; ---------------------------------
   4032                      53 _generateNewStar::
                             54 ;src/sys/generator.c:27: Entity_t* e = man_entity_create();
   4032 CD 42 41      [17]   55 	call	_man_entity_create
   4035 4D            [ 4]   56 	ld	c, l
   4036 44            [ 4]   57 	ld	b, h
                             58 ;src/sys/generator.c:28: cpct_memcpy(e, &init_e, sizeof(Entity_t));
   4037 59            [ 4]   59 	ld	e, c
   4038 50            [ 4]   60 	ld	d, b
   4039 C5            [11]   61 	push	bc
   403A 21 07 00      [10]   62 	ld	hl, #0x0007
   403D E5            [11]   63 	push	hl
   403E 21 70 40      [10]   64 	ld	hl, #_init_e
   4041 E5            [11]   65 	push	hl
   4042 D5            [11]   66 	push	de
   4043 CD 6E 42      [17]   67 	call	_cpct_memcpy
   4046 C1            [10]   68 	pop	bc
                             69 ;src/sys/generator.c:29: e->y  = cpct_rand() % 200;
   4047 59            [ 4]   70 	ld	e, c
   4048 50            [ 4]   71 	ld	d, b
   4049 13            [ 6]   72 	inc	de
   404A 13            [ 6]   73 	inc	de
   404B C5            [11]   74 	push	bc
   404C D5            [11]   75 	push	de
   404D CD 86 42      [17]   76 	call	_cpct_getRandom_mxor_u8
   4050 65            [ 4]   77 	ld	h, l
   4051 3E C8         [ 7]   78 	ld	a, #0xc8
   4053 F5            [11]   79 	push	af
   4054 33            [ 6]   80 	inc	sp
   4055 E5            [11]   81 	push	hl
   4056 33            [ 6]   82 	inc	sp
   4057 CD EC 41      [17]   83 	call	__moduchar
   405A F1            [10]   84 	pop	af
   405B 7D            [ 4]   85 	ld	a, l
   405C D1            [10]   86 	pop	de
   405D C1            [10]   87 	pop	bc
   405E 12            [ 7]   88 	ld	(de), a
                             89 ;src/sys/generator.c:30: e->vx = -1-(cpct_rand() & 0x03);
   405F 03            [ 6]   90 	inc	bc
   4060 03            [ 6]   91 	inc	bc
   4061 03            [ 6]   92 	inc	bc
   4062 C5            [11]   93 	push	bc
   4063 CD 86 42      [17]   94 	call	_cpct_getRandom_mxor_u8
   4066 C1            [10]   95 	pop	bc
   4067 7D            [ 4]   96 	ld	a, l
   4068 E6 03         [ 7]   97 	and	a, #0x03
   406A 5F            [ 4]   98 	ld	e, a
   406B 3E FF         [ 7]   99 	ld	a, #0xff
   406D 93            [ 4]  100 	sub	a, e
   406E 02            [ 7]  101 	ld	(bc), a
   406F C9            [10]  102 	ret
   4070                     103 _init_e:
   4070 01                  104 	.db #0x01	; 1
   4071 4F                  105 	.db #0x4f	; 79	'O'
   4072 01                  106 	.db #0x01	; 1
   4073 FF                  107 	.db #0xff	; -1
   4074 FF                  108 	.db #0xff	; 255
   4075 00 00               109 	.dw #0x0000
                            110 ;src/sys/generator.c:43: void sys_generator_update() {
                            111 ;	---------------------------------
                            112 ; Function sys_generator_update
                            113 ; ---------------------------------
   4077                     114 _sys_generator_update::
                            115 ;src/sys/generator.c:44: u8 free = man_entity_freeSpace();
   4077 CD D8 41      [17]  116 	call	_man_entity_freeSpace
                            117 ;src/sys/generator.c:45: if (free) 
   407A 7D            [ 4]  118 	ld	a, l
   407B B7            [ 4]  119 	or	a, a
   407C C8            [11]  120 	ret	Z
                            121 ;src/sys/generator.c:46: generateNewStar();   
   407D C3 32 40      [10]  122 	jp  _generateNewStar
                            123 	.area _CODE
                            124 	.area _INITIALIZER
                            125 	.area _CABS (ABS)
