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
   42F5                      30 _m_entities::
   42F5                      31 	.ds 70
   433B                      32 _m_next_free_entity::
   433B                      33 	.ds 2
   433D                      34 _m_num_entities::
   433D                      35 	.ds 1
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
   4032                      64 _man_entity_init::
                             65 ;src/man/entity.c:13: cpct_memset (m_entities, 0, sizeof(m_entities));
   4032 21 46 00      [10]   66 	ld	hl, #0x0046
   4035 E5            [11]   67 	push	hl
   4036 AF            [ 4]   68 	xor	a, a
   4037 F5            [11]   69 	push	af
   4038 33            [ 6]   70 	inc	sp
   4039 21 F5 42      [10]   71 	ld	hl, #_m_entities
   403C E5            [11]   72 	push	hl
   403D CD 72 42      [17]   73 	call	_cpct_memset
                             74 ;src/man/entity.c:14: m_next_free_entity = m_entities;
   4040 21 F5 42      [10]   75 	ld	hl, #_m_entities
   4043 22 3B 43      [16]   76 	ld	(_m_next_free_entity), hl
                             77 ;src/man/entity.c:15: m_num_entities = 0;
   4046 21 3D 43      [10]   78 	ld	hl,#_m_num_entities + 0
   4049 36 00         [10]   79 	ld	(hl), #0x00
   404B C9            [10]   80 	ret
                             81 ;src/man/entity.c:25: Entity_t* man_entity_create (void) {
                             82 ;	---------------------------------
                             83 ; Function man_entity_create
                             84 ; ---------------------------------
   404C                      85 _man_entity_create::
                             86 ;src/man/entity.c:26: Entity_t* e = m_next_free_entity;
   404C ED 4B 3B 43   [20]   87 	ld	bc, (_m_next_free_entity)
                             88 ;src/man/entity.c:27: m_next_free_entity = e + 1;
   4050 21 07 00      [10]   89 	ld	hl, #0x0007
   4053 09            [11]   90 	add	hl,bc
   4054 22 3B 43      [16]   91 	ld	(_m_next_free_entity), hl
                             92 ;src/man/entity.c:28: e->type = e_type_default;
   4057 3E 7F         [ 7]   93 	ld	a, #0x7f
   4059 02            [ 7]   94 	ld	(bc), a
                             95 ;src/man/entity.c:29: ++m_num_entities;
   405A 21 3D 43      [10]   96 	ld	hl, #_m_num_entities+0
   405D 34            [11]   97 	inc	(hl)
                             98 ;src/man/entity.c:30: return e;
   405E 69            [ 4]   99 	ld	l, c
   405F 60            [ 4]  100 	ld	h, b
   4060 C9            [10]  101 	ret
                            102 ;src/man/entity.c:39: void man_entity_forall (void (*ptrfunc) (Entity_t*)) {
                            103 ;	---------------------------------
                            104 ; Function man_entity_forall
                            105 ; ---------------------------------
   4061                     106 _man_entity_forall::
                            107 ;src/man/entity.c:40: Entity_t* e = m_entities;
   4061 01 F5 42      [10]  108 	ld	bc, #_m_entities+0
                            109 ;src/man/entity.c:43: while( counter < MAX_ENTITIES ) {
   4064 1E 00         [ 7]  110 	ld	e, #0x00
   4066                     111 00103$:
   4066 7B            [ 4]  112 	ld	a, e
   4067 D6 0A         [ 7]  113 	sub	a, #0x0a
   4069 D0            [11]  114 	ret	NC
                            115 ;src/man/entity.c:44: if( e->type != e_type_invalid ) {
   406A 0A            [ 7]  116 	ld	a, (bc)
   406B B7            [ 4]  117 	or	a, a
   406C 28 17         [12]  118 	jr	Z,00102$
                            119 ;src/man/entity.c:45: ptrfunc( e );
   406E C5            [11]  120 	push	bc
   406F D5            [11]  121 	push	de
   4070 C5            [11]  122 	push	bc
   4071 21 08 00      [10]  123 	ld	hl, #8
   4074 39            [11]  124 	add	hl, sp
   4075 7E            [ 7]  125 	ld	a, (hl)
   4076 23            [ 6]  126 	inc	hl
   4077 66            [ 7]  127 	ld	h, (hl)
   4078 6F            [ 4]  128 	ld	l, a
   4079 CD 53 42      [17]  129 	call	___sdcc_call_hl
   407C F1            [10]  130 	pop	af
   407D D1            [10]  131 	pop	de
   407E C1            [10]  132 	pop	bc
                            133 ;src/man/entity.c:46: ++e;
   407F 21 07 00      [10]  134 	ld	hl, #0x0007
   4082 09            [11]  135 	add	hl,bc
   4083 4D            [ 4]  136 	ld	c, l
   4084 44            [ 4]  137 	ld	b, h
   4085                     138 00102$:
                            139 ;src/man/entity.c:48: ++counter;
   4085 1C            [ 4]  140 	inc	e
   4086 18 DE         [12]  141 	jr	00103$
                            142 ;src/man/entity.c:66: void man_entity_destroy (Entity_t* dead_e) {
                            143 ;	---------------------------------
                            144 ; Function man_entity_destroy
                            145 ; ---------------------------------
   4088                     146 _man_entity_destroy::
   4088 DD E5         [15]  147 	push	ix
   408A DD 21 00 00   [14]  148 	ld	ix,#0
   408E DD 39         [15]  149 	add	ix,sp
                            150 ;src/man/entity.c:67: Entity_t* de = dead_e;
   4090 DD 5E 04      [19]  151 	ld	e,4 (ix)
   4093 DD 56 05      [19]  152 	ld	d,5 (ix)
                            153 ;src/man/entity.c:68: Entity_t* last = m_next_free_entity;
   4096 2A 3B 43      [16]  154 	ld	hl, (_m_next_free_entity)
                            155 ;src/man/entity.c:69: --last;
   4099 01 F9 FF      [10]  156 	ld	bc, #0xfff9
   409C 09            [11]  157 	add	hl,bc
   409D 4D            [ 4]  158 	ld	c, l
   409E 44            [ 4]  159 	ld	b, h
                            160 ;src/man/entity.c:70: if (de != last) 
   409F 7B            [ 4]  161 	ld	a, e
   40A0 91            [ 4]  162 	sub	a, c
   40A1 20 04         [12]  163 	jr	NZ,00109$
   40A3 7A            [ 4]  164 	ld	a, d
   40A4 90            [ 4]  165 	sub	a, b
   40A5 28 17         [12]  166 	jr	Z,00102$
   40A7                     167 00109$:
                            168 ;src/man/entity.c:71: cpct_memcpy(dead_e, last, sizeof(Entity_t));
   40A7 69            [ 4]  169 	ld	l, c
   40A8 60            [ 4]  170 	ld	h, b
   40A9 DD 5E 04      [19]  171 	ld	e, 4 (ix)
   40AC DD 56 05      [19]  172 	ld	d, 5 (ix)
   40AF D5            [11]  173 	push	de
   40B0 FD E1         [14]  174 	pop	iy
   40B2 C5            [11]  175 	push	bc
   40B3 11 07 00      [10]  176 	ld	de, #0x0007
   40B6 D5            [11]  177 	push	de
   40B7 E5            [11]  178 	push	hl
   40B8 FD E5         [15]  179 	push	iy
   40BA CD 6A 42      [17]  180 	call	_cpct_memcpy
   40BD C1            [10]  181 	pop	bc
   40BE                     182 00102$:
                            183 ;src/man/entity.c:72: last->type = e_type_invalid;
   40BE AF            [ 4]  184 	xor	a, a
   40BF 02            [ 7]  185 	ld	(bc), a
                            186 ;src/man/entity.c:73: m_next_free_entity = last;
   40C0 ED 43 3B 43   [20]  187 	ld	(_m_next_free_entity), bc
                            188 ;src/man/entity.c:74: --m_num_entities;
   40C4 21 3D 43      [10]  189 	ld	hl, #_m_num_entities+0
   40C7 35            [11]  190 	dec	(hl)
   40C8 DD E1         [14]  191 	pop	ix
   40CA C9            [10]  192 	ret
                            193 ;src/man/entity.c:85: void man_entity_set4destruction (Entity_t* dead_e) {
                            194 ;	---------------------------------
                            195 ; Function man_entity_set4destruction
                            196 ; ---------------------------------
   40CB                     197 _man_entity_set4destruction::
                            198 ;src/man/entity.c:86: dead_e->type |= e_type_dead;
   40CB D1            [10]  199 	pop	de
   40CC C1            [10]  200 	pop	bc
   40CD C5            [11]  201 	push	bc
   40CE D5            [11]  202 	push	de
   40CF 0A            [ 7]  203 	ld	a, (bc)
   40D0 CB FF         [ 8]  204 	set	7, a
   40D2 02            [ 7]  205 	ld	(bc), a
   40D3 C9            [10]  206 	ret
                            207 ;src/man/entity.c:93: void man_entity_update (void) {
                            208 ;	---------------------------------
                            209 ; Function man_entity_update
                            210 ; ---------------------------------
   40D4                     211 _man_entity_update::
                            212 ;src/man/entity.c:94: Entity_t* e = m_entities;
   40D4 21 F5 42      [10]  213 	ld	hl, #_m_entities+0
                            214 ;src/man/entity.c:95: while(e->type != e_type_invalid) {
   40D7                     215 00104$:
   40D7 7E            [ 7]  216 	ld	a, (hl)
   40D8 B7            [ 4]  217 	or	a, a
   40D9 C8            [11]  218 	ret	Z
                            219 ;src/man/entity.c:96: if (e->type & e_type_dead) {
   40DA 07            [ 4]  220 	rlca
   40DB 30 09         [12]  221 	jr	NC,00102$
                            222 ;src/man/entity.c:97: man_entity_destroy(e);
   40DD E5            [11]  223 	push	hl
   40DE E5            [11]  224 	push	hl
   40DF CD 88 40      [17]  225 	call	_man_entity_destroy
   40E2 F1            [10]  226 	pop	af
   40E3 E1            [10]  227 	pop	hl
   40E4 18 F1         [12]  228 	jr	00104$
   40E6                     229 00102$:
                            230 ;src/man/entity.c:99: ++e;
   40E6 01 07 00      [10]  231 	ld	bc, #0x0007
   40E9 09            [11]  232 	add	hl, bc
   40EA 18 EB         [12]  233 	jr	00104$
                            234 ;src/man/entity.c:110: u8 man_entity_freeSpace() {
                            235 ;	---------------------------------
                            236 ; Function man_entity_freeSpace
                            237 ; ---------------------------------
   40EC                     238 _man_entity_freeSpace::
                            239 ;src/man/entity.c:111: return MAX_ENTITIES - m_num_entities;
   40EC 21 3D 43      [10]  240 	ld	hl, #_m_num_entities
   40EF 3E 0A         [ 7]  241 	ld	a, #0x0a
   40F1 96            [ 7]  242 	sub	a, (hl)
   40F2 6F            [ 4]  243 	ld	l, a
   40F3 C9            [10]  244 	ret
                            245 	.area _CODE
                            246 	.area _INITIALIZER
                            247 	.area _CABS (ABS)
