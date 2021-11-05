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
                             49 ;src/sys/generator.c:27: void generateNewStar() {
                             50 ;	---------------------------------
                             51 ; Function generateNewStar
                             52 ; ---------------------------------
   412E                      53 _generateNewStar::
                             54 ;src/sys/generator.c:28: Entity_t* e = man_entity_create();           // Puntero a la entidad reservada en el array
   412E CD 4C 40      [17]   55 	call	_man_entity_create
   4131 EB            [ 4]   56 	ex	de,hl
                             57 ;src/sys/generator.c:29: cpct_memcpy(e, &init_e, sizeof(Entity_t));   // Inicializamos la entidad con los valores standar
   4132 4B            [ 4]   58 	ld	c, e
   4133 42            [ 4]   59 	ld	b, d
   4134 D5            [11]   60 	push	de
   4135 21 07 00      [10]   61 	ld	hl, #0x0007
   4138 E5            [11]   62 	push	hl
   4139 21 89 41      [10]   63 	ld	hl, #_init_e
   413C E5            [11]   64 	push	hl
   413D C5            [11]   65 	push	bc
   413E CD D7 42      [17]   66 	call	_cpct_memcpy
   4141 D1            [10]   67 	pop	de
                             68 ;src/sys/generator.c:30: e->y  = cpct_rand() % 200;                   // Asignamos una posición y aleatoria (0 a 200)
   4142 4B            [ 4]   69 	ld	c, e
   4143 42            [ 4]   70 	ld	b, d
   4144 03            [ 6]   71 	inc	bc
   4145 03            [ 6]   72 	inc	bc
   4146 C5            [11]   73 	push	bc
   4147 D5            [11]   74 	push	de
   4148 CD FD 42      [17]   75 	call	_cpct_getRandom_mxor_u8
   414B 65            [ 4]   76 	ld	h, l
   414C 3E C8         [ 7]   77 	ld	a, #0xc8
   414E F5            [11]   78 	push	af
   414F 33            [ 6]   79 	inc	sp
   4150 E5            [11]   80 	push	hl
   4151 33            [ 6]   81 	inc	sp
   4152 CD 63 42      [17]   82 	call	__moduchar
   4155 F1            [10]   83 	pop	af
   4156 7D            [ 4]   84 	ld	a, l
   4157 D1            [10]   85 	pop	de
   4158 C1            [10]   86 	pop	bc
   4159 02            [ 7]   87 	ld	(bc), a
                             88 ;src/sys/generator.c:31: e->vx = -1-(cpct_rand() & 0x03);             // Asignamos una velocidad x aleatoria (-1 a -3 )
   415A 6B            [ 4]   89 	ld	l, e
   415B 62            [ 4]   90 	ld	h, d
   415C 23            [ 6]   91 	inc	hl
   415D 23            [ 6]   92 	inc	hl
   415E 23            [ 6]   93 	inc	hl
   415F E5            [11]   94 	push	hl
   4160 D5            [11]   95 	push	de
   4161 CD FD 42      [17]   96 	call	_cpct_getRandom_mxor_u8
   4164 7D            [ 4]   97 	ld	a, l
   4165 D1            [10]   98 	pop	de
   4166 E1            [10]   99 	pop	hl
   4167 E6 03         [ 7]  100 	and	a, #0x03
   4169 4F            [ 4]  101 	ld	c, a
   416A 3E FF         [ 7]  102 	ld	a, #0xff
   416C 91            [ 4]  103 	sub	a, c
   416D 47            [ 4]  104 	ld	b, a
   416E 70            [ 7]  105 	ld	(hl), b
                            106 ;src/sys/generator.c:34: switch ( e->vx ) {
   416F 4E            [ 7]  107 	ld	c, (hl)
                            108 ;src/sys/generator.c:36: e->color = 0x88;
   4170 21 04 00      [10]  109 	ld	hl, #0x0004
   4173 19            [11]  110 	add	hl, de
                            111 ;src/sys/generator.c:34: switch ( e->vx ) {
   4174 78            [ 4]  112 	ld	a, b
   4175 D6 FD         [ 7]  113 	sub	a, #0xfd
   4177 28 0D         [12]  114 	jr	Z,00103$
   4179 79            [ 4]  115 	ld	a, c
   417A D6 FE         [ 7]  116 	sub	a, #0xfe
   417C 28 05         [12]  117 	jr	Z,00102$
   417E 0C            [ 4]  118 	inc	c
   417F C0            [11]  119 	ret	NZ
                            120 ;src/sys/generator.c:36: e->color = 0x88;
   4180 36 88         [10]  121 	ld	(hl), #0x88
                            122 ;src/sys/generator.c:37: break;
   4182 C9            [10]  123 	ret
                            124 ;src/sys/generator.c:38: case -2:
   4183                     125 00102$:
                            126 ;src/sys/generator.c:39: e->color = 0x08;
   4183 36 08         [10]  127 	ld	(hl), #0x08
                            128 ;src/sys/generator.c:40: break;
   4185 C9            [10]  129 	ret
                            130 ;src/sys/generator.c:41: case -3:
   4186                     131 00103$:
                            132 ;src/sys/generator.c:42: e->color = 0x80;
   4186 36 80         [10]  133 	ld	(hl), #0x80
                            134 ;src/sys/generator.c:43: }
   4188 C9            [10]  135 	ret
   4189                     136 _init_e:
   4189 01                  137 	.db #0x01	; 1
   418A 9E                  138 	.db #0x9e	; 158
   418B 01                  139 	.db #0x01	; 1
   418C FF                  140 	.db #0xff	; -1
   418D 80                  141 	.db #0x80	; 128
   418E 00 00               142 	.dw #0x0000
                            143 ;src/sys/generator.c:57: void sys_generator_update() {
                            144 ;	---------------------------------
                            145 ; Function sys_generator_update
                            146 ; ---------------------------------
   4190                     147 _sys_generator_update::
                            148 ;src/sys/generator.c:58: u8 free = man_entity_freeSpace();
   4190 CD E2 40      [17]  149 	call	_man_entity_freeSpace
   4193 4D            [ 4]  150 	ld	c, l
                            151 ;src/sys/generator.c:59: if( free > 2 ) free = 2;
   4194 3E 02         [ 7]  152 	ld	a, #0x02
   4196 91            [ 4]  153 	sub	a, c
   4197 30 02         [12]  154 	jr	NC,00110$
   4199 0E 02         [ 7]  155 	ld	c, #0x02
                            156 ;src/sys/generator.c:60: while( free ) {
   419B                     157 00110$:
   419B                     158 00103$:
   419B 79            [ 4]  159 	ld	a, c
   419C B7            [ 4]  160 	or	a, a
   419D C8            [11]  161 	ret	Z
                            162 ;src/sys/generator.c:61: generateNewStar();   
   419E C5            [11]  163 	push	bc
   419F CD 2E 41      [17]  164 	call	_generateNewStar
   41A2 C1            [10]  165 	pop	bc
                            166 ;src/sys/generator.c:62: --free;
   41A3 0D            [ 4]  167 	dec	c
   41A4 18 F5         [12]  168 	jr	00103$
                            169 	.area _CODE
                            170 	.area _INITIALIZER
                            171 	.area _CABS (ABS)
