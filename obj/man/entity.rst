                              1 ;--------------------------------------------------------
                              2 ; File Created by SDCC : free open source ANSI-C Compiler
                              3 ; Version 3.6.8 #9946 (Linux)
                              4 ;--------------------------------------------------------
                              5 	.module entity
                              6 	.optsdcc -mz80
                              7 	
                              8 ;--------------------------------------------------------
                              9 ; Public variables in this module
                             10 ;--------------------------------------------------------
                             11 	.globl _cpct_memcpy
                             12 	.globl _cpct_memset
                             13 	.globl _m_num_entities
                             14 	.globl _m_next_free_entity
                             15 	.globl _m_entities
                             16 	.globl _man_entity_init
                             17 	.globl _man_entity_create
                             18 	.globl _man_entity_forall
                             19 	.globl _man_entity_destroy
                             20 	.globl _man_entity_set4destruction
                             21 	.globl _man_entity_update
                             22 	.globl _man_entity_freeSpace
                             23 ;--------------------------------------------------------
                             24 ; special function registers
                             25 ;--------------------------------------------------------
                             26 ;--------------------------------------------------------
                             27 ; ram data
                             28 ;--------------------------------------------------------
                             29 	.area _DATA
   42EB                      30 _m_entities::
   42EB                      31 	.ds 70
   4331                      32 _m_next_free_entity::
   4331                      33 	.ds 2
   4333                      34 _m_num_entities::
   4333                      35 	.ds 1
                             36 ;--------------------------------------------------------
                             37 ; ram data
                             38 ;--------------------------------------------------------
                             39 	.area _INITIALIZED
                             40 ;--------------------------------------------------------
                             41 ; absolute external ram data
                             42 ;--------------------------------------------------------
                             43 	.area _DABS (ABS)
                             44 ;--------------------------------------------------------
                             45 ; global & static initialisations
                             46 ;--------------------------------------------------------
                             47 	.area _HOME
                             48 	.area _GSINIT
                             49 	.area _GSFINAL
                             50 	.area _GSINIT
                             51 ;--------------------------------------------------------
                             52 ; Home
                             53 ;--------------------------------------------------------
                             54 	.area _HOME
                             55 	.area _HOME
                             56 ;--------------------------------------------------------
                             57 ; code
                             58 ;--------------------------------------------------------
                             59 	.area _CODE
                             60 ;src/man/entity.c:12: void man_entity_init (void) {
                             61 ;	---------------------------------
                             62 ; Function man_entity_init
                             63 ; ---------------------------------
   4128                      64 _man_entity_init::
                             65 ;src/man/entity.c:13: cpct_memset (m_entities, 0, sizeof(m_entities));
   4128 21 46 00      [10]   66 	ld	hl, #0x0046
   412B E5            [11]   67 	push	hl
   412C AF            [ 4]   68 	xor	a, a
   412D F5            [11]   69 	push	af
   412E 33            [ 6]   70 	inc	sp
   412F 21 EB 42      [10]   71 	ld	hl, #_m_entities
   4132 E5            [11]   72 	push	hl
   4133 CD 60 42      [17]   73 	call	_cpct_memset
                             74 ;src/man/entity.c:14: m_next_free_entity = m_entities;
   4136 21 EB 42      [10]   75 	ld	hl, #_m_entities
   4139 22 31 43      [16]   76 	ld	(_m_next_free_entity), hl
                             77 ;src/man/entity.c:15: m_num_entities = 0;
   413C 21 33 43      [10]   78 	ld	hl,#_m_num_entities + 0
   413F 36 00         [10]   79 	ld	(hl), #0x00
   4141 C9            [10]   80 	ret
                             81 ;src/man/entity.c:25: Entity_t* man_entity_create (void) {
                             82 ;	---------------------------------
                             83 ; Function man_entity_create
                             84 ; ---------------------------------
   4142                      85 _man_entity_create::
                             86 ;src/man/entity.c:26: Entity_t* e = m_next_free_entity;
   4142 ED 4B 31 43   [20]   87 	ld	bc, (_m_next_free_entity)
                             88 ;src/man/entity.c:27: m_next_free_entity = e + 1;
   4146 21 07 00      [10]   89 	ld	hl, #0x0007
   4149 09            [11]   90 	add	hl,bc
   414A 22 31 43      [16]   91 	ld	(_m_next_free_entity), hl
                             92 ;src/man/entity.c:28: e->type = e_type_default;
   414D 3E 7F         [ 7]   93 	ld	a, #0x7f
   414F 02            [ 7]   94 	ld	(bc), a
                             95 ;src/man/entity.c:29: ++m_num_entities;
   4150 21 33 43      [10]   96 	ld	hl, #_m_num_entities+0
   4153 34            [11]   97 	inc	(hl)
                             98 ;src/man/entity.c:30: return e;
   4154 69            [ 4]   99 	ld	l, c
   4155 60            [ 4]  100 	ld	h, b
   4156 C9            [10]  101 	ret
                            102 ;src/man/entity.c:39: void man_entity_forall (void (*ptrfunc) (Entity_t*)) {
                            103 ;	---------------------------------
                            104 ; Function man_entity_forall
                            105 ; ---------------------------------
   4157                     106 _man_entity_forall::
                            107 ;src/man/entity.c:40: Entity_t* e = m_entities;
   4157 01 EB 42      [10]  108 	ld	bc, #_m_entities+0
                            109 ;src/man/entity.c:41: while (e->type != e_type_invalid) {
   415A                     110 00101$:
   415A 0A            [ 7]  111 	ld	a, (bc)
   415B B7            [ 4]  112 	or	a, a
   415C C8            [11]  113 	ret	Z
                            114 ;src/man/entity.c:42: ptrfunc(e);
   415D C5            [11]  115 	push	bc
   415E C5            [11]  116 	push	bc
   415F 21 06 00      [10]  117 	ld	hl, #6
   4162 39            [11]  118 	add	hl, sp
   4163 7E            [ 7]  119 	ld	a, (hl)
   4164 23            [ 6]  120 	inc	hl
   4165 66            [ 7]  121 	ld	h, (hl)
   4166 6F            [ 4]  122 	ld	l, a
   4167 CD 49 42      [17]  123 	call	___sdcc_call_hl
   416A F1            [10]  124 	pop	af
   416B C1            [10]  125 	pop	bc
                            126 ;src/man/entity.c:43: ++e;
   416C 21 07 00      [10]  127 	ld	hl, #0x0007
   416F 09            [11]  128 	add	hl,bc
   4170 4D            [ 4]  129 	ld	c, l
   4171 44            [ 4]  130 	ld	b, h
   4172 18 E6         [12]  131 	jr	00101$
                            132 ;src/man/entity.c:56: void man_entity_destroy (Entity_t* dead_e) {
                            133 ;	---------------------------------
                            134 ; Function man_entity_destroy
                            135 ; ---------------------------------
   4174                     136 _man_entity_destroy::
   4174 DD E5         [15]  137 	push	ix
   4176 DD 21 00 00   [14]  138 	ld	ix,#0
   417A DD 39         [15]  139 	add	ix,sp
                            140 ;src/man/entity.c:57: Entity_t* de = dead_e;
   417C DD 5E 04      [19]  141 	ld	e,4 (ix)
   417F DD 56 05      [19]  142 	ld	d,5 (ix)
                            143 ;src/man/entity.c:58: Entity_t* last = m_next_free_entity;
   4182 2A 31 43      [16]  144 	ld	hl, (_m_next_free_entity)
                            145 ;src/man/entity.c:59: --last;
   4185 01 F9 FF      [10]  146 	ld	bc, #0xfff9
   4188 09            [11]  147 	add	hl,bc
   4189 4D            [ 4]  148 	ld	c, l
   418A 44            [ 4]  149 	ld	b, h
                            150 ;src/man/entity.c:60: if (de != last) 
   418B 7B            [ 4]  151 	ld	a, e
   418C 91            [ 4]  152 	sub	a, c
   418D 20 04         [12]  153 	jr	NZ,00109$
   418F 7A            [ 4]  154 	ld	a, d
   4190 90            [ 4]  155 	sub	a, b
   4191 28 17         [12]  156 	jr	Z,00102$
   4193                     157 00109$:
                            158 ;src/man/entity.c:61: cpct_memcpy(dead_e, last, sizeof(Entity_t));
   4193 69            [ 4]  159 	ld	l, c
   4194 60            [ 4]  160 	ld	h, b
   4195 DD 5E 04      [19]  161 	ld	e, 4 (ix)
   4198 DD 56 05      [19]  162 	ld	d, 5 (ix)
   419B D5            [11]  163 	push	de
   419C FD E1         [14]  164 	pop	iy
   419E C5            [11]  165 	push	bc
   419F 11 07 00      [10]  166 	ld	de, #0x0007
   41A2 D5            [11]  167 	push	de
   41A3 E5            [11]  168 	push	hl
   41A4 FD E5         [15]  169 	push	iy
   41A6 CD 6E 42      [17]  170 	call	_cpct_memcpy
   41A9 C1            [10]  171 	pop	bc
   41AA                     172 00102$:
                            173 ;src/man/entity.c:62: last->type = e_type_invalid;
   41AA AF            [ 4]  174 	xor	a, a
   41AB 02            [ 7]  175 	ld	(bc), a
                            176 ;src/man/entity.c:63: m_next_free_entity = last;
   41AC ED 43 31 43   [20]  177 	ld	(_m_next_free_entity), bc
                            178 ;src/man/entity.c:64: --m_num_entities;
   41B0 21 33 43      [10]  179 	ld	hl, #_m_num_entities+0
   41B3 35            [11]  180 	dec	(hl)
   41B4 DD E1         [14]  181 	pop	ix
   41B6 C9            [10]  182 	ret
                            183 ;src/man/entity.c:75: void man_entity_set4destruction (Entity_t* dead_e) {
                            184 ;	---------------------------------
                            185 ; Function man_entity_set4destruction
                            186 ; ---------------------------------
   41B7                     187 _man_entity_set4destruction::
                            188 ;src/man/entity.c:76: dead_e->type |= e_type_dead;
   41B7 D1            [10]  189 	pop	de
   41B8 C1            [10]  190 	pop	bc
   41B9 C5            [11]  191 	push	bc
   41BA D5            [11]  192 	push	de
   41BB 0A            [ 7]  193 	ld	a, (bc)
   41BC CB FF         [ 8]  194 	set	7, a
   41BE 02            [ 7]  195 	ld	(bc), a
   41BF C9            [10]  196 	ret
                            197 ;src/man/entity.c:83: void man_entity_update (void) {
                            198 ;	---------------------------------
                            199 ; Function man_entity_update
                            200 ; ---------------------------------
   41C0                     201 _man_entity_update::
                            202 ;src/man/entity.c:84: Entity_t* e = m_entities;
   41C0 21 EB 42      [10]  203 	ld	hl, #_m_entities+0
                            204 ;src/man/entity.c:85: while(e->type != e_type_invalid) {
   41C3                     205 00104$:
   41C3 7E            [ 7]  206 	ld	a, (hl)
   41C4 B7            [ 4]  207 	or	a, a
   41C5 C8            [11]  208 	ret	Z
                            209 ;src/man/entity.c:86: if (e->type & e_type_dead) {
   41C6 07            [ 4]  210 	rlca
   41C7 30 09         [12]  211 	jr	NC,00102$
                            212 ;src/man/entity.c:87: man_entity_destroy(e);
   41C9 E5            [11]  213 	push	hl
   41CA E5            [11]  214 	push	hl
   41CB CD 74 41      [17]  215 	call	_man_entity_destroy
   41CE F1            [10]  216 	pop	af
   41CF E1            [10]  217 	pop	hl
   41D0 18 F1         [12]  218 	jr	00104$
   41D2                     219 00102$:
                            220 ;src/man/entity.c:89: ++e;
   41D2 01 07 00      [10]  221 	ld	bc, #0x0007
   41D5 09            [11]  222 	add	hl, bc
   41D6 18 EB         [12]  223 	jr	00104$
                            224 ;src/man/entity.c:100: u8 man_entity_freeSpace() {
                            225 ;	---------------------------------
                            226 ; Function man_entity_freeSpace
                            227 ; ---------------------------------
   41D8                     228 _man_entity_freeSpace::
                            229 ;src/man/entity.c:101: return MAX_ENTITIES - m_num_entities;
   41D8 21 33 43      [10]  230 	ld	hl, #_m_num_entities
   41DB 3E 0A         [ 7]  231 	ld	a, #0x0a
   41DD 96            [ 7]  232 	sub	a, (hl)
   41DE 6F            [ 4]  233 	ld	l, a
   41DF C9            [10]  234 	ret
                            235 	.area _CODE
                            236 	.area _INITIALIZER
                            237 	.area _CABS (ABS)
