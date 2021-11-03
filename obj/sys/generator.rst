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
   412E                      53 _generateNewStar::
                             54 ;src/sys/generator.c:27: Entity_t* e = man_entity_create();
   412E CD 4C 40      [17]   55 	call	_man_entity_create
   4131 4D            [ 4]   56 	ld	c, l
   4132 44            [ 4]   57 	ld	b, h
                             58 ;src/sys/generator.c:28: cpct_memcpy(e, &init_e, sizeof(Entity_t));
   4133 59            [ 4]   59 	ld	e, c
   4134 50            [ 4]   60 	ld	d, b
   4135 C5            [11]   61 	push	bc
   4136 21 07 00      [10]   62 	ld	hl, #0x0007
   4139 E5            [11]   63 	push	hl
   413A 21 6C 41      [10]   64 	ld	hl, #_init_e
   413D E5            [11]   65 	push	hl
   413E D5            [11]   66 	push	de
   413F CD 8B 42      [17]   67 	call	_cpct_memcpy
   4142 C1            [10]   68 	pop	bc
                             69 ;src/sys/generator.c:29: e->y  = cpct_rand() % 200;
   4143 59            [ 4]   70 	ld	e, c
   4144 50            [ 4]   71 	ld	d, b
   4145 13            [ 6]   72 	inc	de
   4146 13            [ 6]   73 	inc	de
   4147 C5            [11]   74 	push	bc
   4148 D5            [11]   75 	push	de
   4149 CD B1 42      [17]   76 	call	_cpct_getRandom_mxor_u8
   414C 65            [ 4]   77 	ld	h, l
   414D 3E C8         [ 7]   78 	ld	a, #0xc8
   414F F5            [11]   79 	push	af
   4150 33            [ 6]   80 	inc	sp
   4151 E5            [11]   81 	push	hl
   4152 33            [ 6]   82 	inc	sp
   4153 CD 17 42      [17]   83 	call	__moduchar
   4156 F1            [10]   84 	pop	af
   4157 7D            [ 4]   85 	ld	a, l
   4158 D1            [10]   86 	pop	de
   4159 C1            [10]   87 	pop	bc
   415A 12            [ 7]   88 	ld	(de), a
                             89 ;src/sys/generator.c:30: e->vx = -1-(cpct_rand() & 0x03);
   415B 03            [ 6]   90 	inc	bc
   415C 03            [ 6]   91 	inc	bc
   415D 03            [ 6]   92 	inc	bc
   415E C5            [11]   93 	push	bc
   415F CD B1 42      [17]   94 	call	_cpct_getRandom_mxor_u8
   4162 C1            [10]   95 	pop	bc
   4163 7D            [ 4]   96 	ld	a, l
   4164 E6 03         [ 7]   97 	and	a, #0x03
   4166 5F            [ 4]   98 	ld	e, a
   4167 3E FF         [ 7]   99 	ld	a, #0xff
   4169 93            [ 4]  100 	sub	a, e
   416A 02            [ 7]  101 	ld	(bc), a
   416B C9            [10]  102 	ret
   416C                     103 _init_e:
   416C 01                  104 	.db #0x01	; 1
   416D 4F                  105 	.db #0x4f	; 79	'O'
   416E 01                  106 	.db #0x01	; 1
   416F FF                  107 	.db #0xff	; -1
   4170 80                  108 	.db #0x80	; 128
   4171 00 00               109 	.dw #0x0000
                            110 ;src/sys/generator.c:43: void sys_generator_update() {
                            111 ;	---------------------------------
                            112 ; Function sys_generator_update
                            113 ; ---------------------------------
   4173                     114 _sys_generator_update::
                            115 ;src/sys/generator.c:44: u8 free = man_entity_freeSpace();
   4173 CD E2 40      [17]  116 	call	_man_entity_freeSpace
                            117 ;src/sys/generator.c:45: if (free) 
   4176 7D            [ 4]  118 	ld	a, l
   4177 B7            [ 4]  119 	or	a, a
   4178 C8            [11]  120 	ret	Z
                            121 ;src/sys/generator.c:46: generateNewStar();   
   4179 C3 2E 41      [10]  122 	jp  _generateNewStar
                            123 	.area _CODE
                            124 	.area _INITIALIZER
                            125 	.area _CABS (ABS)
