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
                             11 	.globl _sys_generator_update
                             12 	.globl _generateNewStar
                             13 	.globl _man_entity_create
                             14 	.globl _cpct_getRandom_mxor_u8
                             15 	.globl _cpct_memcpy
                             16 	.globl _init_e
                             17 ;--------------------------------------------------------
                             18 ; special function registers
                             19 ;--------------------------------------------------------
                             20 ;--------------------------------------------------------
                             21 ; ram data
                             22 ;--------------------------------------------------------
                             23 	.area _DATA
                             24 ;--------------------------------------------------------
                             25 ; ram data
                             26 ;--------------------------------------------------------
                             27 	.area _INITIALIZED
                             28 ;--------------------------------------------------------
                             29 ; absolute external ram data
                             30 ;--------------------------------------------------------
                             31 	.area _DABS (ABS)
                             32 ;--------------------------------------------------------
                             33 ; global & static initialisations
                             34 ;--------------------------------------------------------
                             35 	.area _HOME
                             36 	.area _GSINIT
                             37 	.area _GSFINAL
                             38 	.area _GSINIT
                             39 ;--------------------------------------------------------
                             40 ; Home
                             41 ;--------------------------------------------------------
                             42 	.area _HOME
                             43 	.area _HOME
                             44 ;--------------------------------------------------------
                             45 ; code
                             46 ;--------------------------------------------------------
                             47 	.area _CODE
                             48 ;src/sys/generator.c:25: void generateNewStar() {
                             49 ;	---------------------------------
                             50 ; Function generateNewStar
                             51 ; ---------------------------------
   4119                      52 _generateNewStar::
                             53 ;src/sys/generator.c:26: Entity_t* e = man_entity_create();
   4119 CD 47 40      [17]   54 	call	_man_entity_create
   411C 4D            [ 4]   55 	ld	c, l
   411D 44            [ 4]   56 	ld	b, h
                             57 ;src/sys/generator.c:27: cpct_memcpy(e, &init_e, sizeof(Entity_t));
   411E 59            [ 4]   58 	ld	e, c
   411F 50            [ 4]   59 	ld	d, b
   4120 C5            [11]   60 	push	bc
   4121 21 07 00      [10]   61 	ld	hl, #0x0007
   4124 E5            [11]   62 	push	hl
   4125 21 57 41      [10]   63 	ld	hl, #_init_e
   4128 E5            [11]   64 	push	hl
   4129 D5            [11]   65 	push	de
   412A CD 45 42      [17]   66 	call	_cpct_memcpy
   412D C1            [10]   67 	pop	bc
                             68 ;src/sys/generator.c:28: e->y  = cpct_rand() % 200;
   412E 59            [ 4]   69 	ld	e, c
   412F 50            [ 4]   70 	ld	d, b
   4130 13            [ 6]   71 	inc	de
   4131 13            [ 6]   72 	inc	de
   4132 C5            [11]   73 	push	bc
   4133 D5            [11]   74 	push	de
   4134 CD 6B 42      [17]   75 	call	_cpct_getRandom_mxor_u8
   4137 65            [ 4]   76 	ld	h, l
   4138 3E C8         [ 7]   77 	ld	a, #0xc8
   413A F5            [11]   78 	push	af
   413B 33            [ 6]   79 	inc	sp
   413C E5            [11]   80 	push	hl
   413D 33            [ 6]   81 	inc	sp
   413E CD D1 41      [17]   82 	call	__moduchar
   4141 F1            [10]   83 	pop	af
   4142 7D            [ 4]   84 	ld	a, l
   4143 D1            [10]   85 	pop	de
   4144 C1            [10]   86 	pop	bc
   4145 12            [ 7]   87 	ld	(de), a
                             88 ;src/sys/generator.c:29: e->vx = -1-(cpct_rand() & 0x03);
   4146 03            [ 6]   89 	inc	bc
   4147 03            [ 6]   90 	inc	bc
   4148 03            [ 6]   91 	inc	bc
   4149 C5            [11]   92 	push	bc
   414A CD 6B 42      [17]   93 	call	_cpct_getRandom_mxor_u8
   414D C1            [10]   94 	pop	bc
   414E 7D            [ 4]   95 	ld	a, l
   414F E6 03         [ 7]   96 	and	a, #0x03
   4151 5F            [ 4]   97 	ld	e, a
   4152 3E FF         [ 7]   98 	ld	a, #0xff
   4154 93            [ 4]   99 	sub	a, e
   4155 02            [ 7]  100 	ld	(bc), a
   4156 C9            [10]  101 	ret
   4157                     102 _init_e:
   4157 01                  103 	.db #0x01	; 1
   4158 4F                  104 	.db #0x4f	; 79	'O'
   4159 01                  105 	.db #0x01	; 1
   415A FF                  106 	.db #0xff	; -1
   415B FF                  107 	.db #0xff	; 255
   415C 00 00               108 	.dw #0x0000
                            109 ;src/sys/generator.c:42: void sys_generator_update() {
                            110 ;	---------------------------------
                            111 ; Function sys_generator_update
                            112 ; ---------------------------------
   415E                     113 _sys_generator_update::
                            114 ;src/sys/generator.c:44: generateNewStar();   
   415E C3 19 41      [10]  115 	jp  _generateNewStar
                            116 	.area _CODE
                            117 	.area _INITIALIZER
                            118 	.area _CABS (ABS)
