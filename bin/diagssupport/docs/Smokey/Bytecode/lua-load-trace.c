/*

TODO:

- Save the important docs to radar

- Use "luac -s" to strip debug info

Links

http://www.google.com

	lua bytecode portability

http://lua-users.org/wiki/LuaTools

	Assembler / Disassembler / Bytecodes
	[LuaDec51] (5.1) - decompiles VM bytecodes back to Lua source.
	[unluac] (5.1) - A Lua 5.1 decompiler.
	[ChunkSpy] (5.0/5.1) - a binary chunk disassembler, with interactive mode, reading custom binary chunk formats, etc. Disassembles 5.0.2 and 5.1 binary chunks.
	[ChunkBake] (5.0) - a line-oriented assembler for Lua 5.0.2 virtual machine instructions.
	[LuaDec] (5.0) - a Lua 5.0.2 decompiler.
	[LuaDC] (4.0) - a Lua decompiler. (download broken)
	[Batch Lua Decompiler] (4.0) - based on LuaDC above.
	[CFLuaDC] (4.0) - another Lua 4 decompiler.
	[LuaAssemblyTools] (5.1) - Provides utilities for virtually all aspects of Lua bytecode manipulation
	[lbci] (5.1) - A bytecode inspector library using Lua internals.
	
http://www.lua.org/manual/5.2/luac.html

	Precompiled chunks are not portable across different architectures.
	Moreover, the internal format of precompiled chunks is likely to change
	when a new version of Lua is released. Make sure you save the source files
	of all Lua programs that you precompile.

ILP32 vs LP64
http://www.unix.org/version2/whatsnew/lp64_wp.html

	Datatype	LP64	ILP64	LLP64	ILP32	LP32
	char		8		8		8		8		8
	short		16		16		16		16		16
	_int32		x		32		x		x		x
	int			32		64		32		32		16
	long		64		64		32		32		32
	long long	x		x		64		x		x
	pointer		64		64		64		32		32


https://developer.apple.com/library/ios/documentation/General/Conceptual/CocoaTouch64BitGuide/Major64-BitChanges/Major64-BitChanges.html

	The 32-bit runtime uses a convention called ILP32, in which integers, long
	integers, and pointers are 32-bit quantities. The 64-bit runtime uses the
	LP64 convention; integers are 32-bit quantities, and long integers and
	pointers are 64-bit quantities. These conventions match the ABI for apps
	running on OS X (and similarly, the Cocoa Touch conventions match the data
	types used in Cocoa), making it easy to write interoperable code between
	the two operating systems.

	The 64-bit ARM environment uses a little-endian environment; this matches
	the 32-bit iOS runtime used by devices with ARM processors that support the
	ARMv7 architecture.

http://luaforge.net/docman/83/98/ANoFrillsIntroToLua51VMInstructions.pdf

	This is a no-frills introduction to the instruction set of the Lua 5.1
	virtual machine. Compared to Perl or Python, the compactness of Lua makes
	it relatively easier for someone to peek under the hood and understand its
	internals. I think that one cannot completely grok a scripting language, or
	any complex system for that matter, without slitting the animal open and
	examining the entrails, organs and other yucky stuff that isn’t normally
	seen. So this document is supposed to help with the “peek under the hood”
	bit.

http://files.catwell.info/misc/mirror/lua-5.2-bytecode-vm-dirk-laurie/lua52vm.html

	I wrote this because writing out something is the only way I can get to
	understand it for myself. It's aimed at readers who think they know the Lua
	5.2 Reference Manual (LRM5.2) pretty well, have a little experience with
	the machine instructions of at least one machine (Knuth's MIX will do) and
	would like to do some tinkering with code for the Lua 5.2 Virtual Machine
	(VM5.2).

	Thanks: I've borrowed a lot from Elijah Frederickson's site
	https://github.com/mlnlover11/LuaAssemblyTools (LAT), which not only has a set
	of assembly tools for Lua 5.1 and Lua 5.2, but also a fairly complete
	collection of useful earlier stuff by other people, in particular, Kein-Hong
	Man's A No-Frills Introduction to Lua 5.1 VM Instructions (NFI), which despite
	being written for Lua 5.1 is still extremely useful. And of course, sooner or
	later you will feel compelled to read the very condensed but absolutely
	definitive comments in the Lua 5.2 source code, particularly lopcodes.h and
	lundump.c.

	Byte numbers are in origin-1 decimal (mostly showing the arithmetic) and
	origin-0 hex.

	1 x00: 1b 4c 75 61
		LUA_SIGNATURE from lua.h.
	5 x04: 52  00
		Binary-coded decimal 52 for the Lua version, 00 to say the bytecode is
		compatible with the "official" PUC-Rio implementation.
	5+2 x06: 01  04  04  04  08  00
		Six system parameters. On x386 machines they mean: little-endian,
		4-byte integers, 4-byte VM instructions, 4-byte size_t numbers, 8-byte
		Lua numbers, floating-point. These parameters must all match up between
		the bytecode file and the Lua interpreter, otherwise the bytecode is
		invalid.
	7+6 x0c: 19 93 0d 0a 1a 0a
		Present in all bytecode produced by Lua 5.2 from PUC-Rio. Described in
		lundump.h as "data to catch conversion errors". Might be constructed
		from binary-coded decimal 1993 (the year it all started), Windows line
		terminator, MS-DOS text file terminator, Unix line terminator.

https://github.com/mlnlover11/LuaAssemblyTools

	Lua Bytecode/Assembly Tools (LAT) is a Lua bytecode library written in Lua
	5.1 (but should be 5.2 compatible)

	Eventually, i hope to have full support for all available Lua versions.
	This is not going to happen in the near future though.

	Language Implementations
	--------------------------------------------------------
	2.4-5.0          No
	5.1              Yes
	5.2              Yes
	5.3              No

http://stackoverflow.com/questions/1480678/luas-bytecode-specification

	The bytecode specification is purposefully not published. You shouldn't
	depend on the VM to retain compatibility between Lua versions (and
	especially not among various implementations). For academic curiosity's
	sake, see the other answers.

http://www.lua.org/doc/jucs05.pdf

	The instructions in Lua’s virtual machine take 32 bits divided into three
	or four ﬁelds, as shown in Figure 6. The OP ﬁeld identiﬁes the instruction
	and takes 6 bits. The other ﬁelds represent operands. Field A is always
	present and takes 8 bits. Fields B and C take 9 bits each. They can be
	combined into an 18-bit ﬁeld: Bx (unsigned) and sBx (signed).

*/

//////////////////////////////////////////////////////////////////////////////
// luaconf.h
//////////////////////////////////////////////////////////////////////////////

/*
@@ LUAI_BITSINT defines the number of bits in an int.
** CHANGE here if Lua cannot automatically detect the number of bits of
** your machine. Probably you do not need to change this.
*/
/* avoid overflows in comparison */
#if INT_MAX-20 < 32760		/* { */
#define LUAI_BITSINT	16
#elif INT_MAX > 2147483640L	/* }{ */
/* int has at least 32 bits */
#define LUAI_BITSINT	32
#else				/* }{ */
#error "you must define LUA_BITSINT with number of bits in an integer"
#endif				/* } */


/*
@@ LUA_INT32 is an signed integer with exactly 32 bits.
@@ LUAI_UMEM is an unsigned integer big enough to count the total
@* memory used by Lua.
@@ LUAI_MEM is a signed integer big enough to count the total memory
@* used by Lua.
** CHANGE here if for some weird reason the default definitions are not
** good enough for your machine. Probably you do not need to change
** this.
*/
#if LUAI_BITSINT >= 32		/* { */
#define LUA_INT32	int
#define LUAI_UMEM	size_t
#define LUAI_MEM	ptrdiff_t
#else				/* }{ */
/* 16-bit ints */
#define LUA_INT32	long
#define LUAI_UMEM	unsigned long
#define LUAI_MEM	long
#endif				/* } */

//////////////////////////////////////////////////////////////////////////////
// lbaselib.c
//////////////////////////////////////////////////////////////////////////////

static int luaB_load (lua_State *L) {
  int status;
  size_t l;
  int top = lua_gettop(L);
  const char *s = lua_tolstring(L, 1, &l);
  const char *mode = luaL_optstring(L, 3, "bt");
  if (s != NULL) {  /* loading a string? */
    const char *chunkname = luaL_optstring(L, 2, s);
    status = luaL_loadbufferx(L, s, l, chunkname, mode);
  }
  else {  /* loading from a reader function */
    const char *chunkname = luaL_optstring(L, 2, "=(load)");
    luaL_checktype(L, 1, LUA_TFUNCTION);
    lua_settop(L, RESERVEDSLOT);  /* create reserved slot */
    status = lua_load(L, generic_reader, NULL, chunkname, mode);
  }
  if (status == LUA_OK && top >= 4) {  /* is there an 'env' argument */
    lua_pushvalue(L, 4);  /* environment for loaded function */
    lua_setupvalue(L, -2, 1);  /* set it as 1st upvalue */
  }
  return load_aux(L, status);
}

//////////////////////////////////////////////////////////////////////////////
// lauxlib.c
//////////////////////////////////////////////////////////////////////////////

LUALIB_API int luaL_loadbufferx (lua_State *L, const char *buff, size_t size,
                                 const char *name, const char *mode) {
  LoadS ls;
  ls.s = buff;
  ls.size = size;
  return lua_load(L, getS, &ls, name, mode);
}

//////////////////////////////////////////////////////////////////////////////
// lapi.c
//////////////////////////////////////////////////////////////////////////////

LUA_API int lua_load (lua_State *L, lua_Reader reader, void *data,
                      const char *chunkname, const char *mode) {
  ZIO z;
  int status;
  lua_lock(L);
  if (!chunkname) chunkname = "?";
  luaZ_init(L, &z, reader, data);
  status = luaD_protectedparser(L, &z, chunkname, mode);
  if (status == LUA_OK) {  /* no errors? */
    LClosure *f = clLvalue(L->top - 1);  /* get newly created function */
    if (f->nupvalues == 1) {  /* does it have one upvalue? */
      /* get global table from registry */
      Table *reg = hvalue(&G(L)->l_registry);
      const TValue *gt = luaH_getint(reg, LUA_RIDX_GLOBALS);
      /* set global table as 1st upvalue of 'f' (may be LUA_ENV) */
      setobj(L, f->upvals[0]->v, gt);
      luaC_barrier(L, f->upvals[0], gt);
    }
  }
  lua_unlock(L);
  return status;
}

//////////////////////////////////////////////////////////////////////////////
// ldump.c
// NOTE: Looks like 'int' is used here, despite LUA_INT32 beign defined
//////////////////////////////////////////////////////////////////////////////

/*
** dump Lua function as precompiled chunk
*/
int luaU_dump (lua_State* L, const Proto* f, lua_Writer w, void* data, int strip)
{
 DumpState D;
 D.L=L;
 D.writer=w;
 D.data=data;
 D.strip=strip;
 D.status=0;
 DumpHeader(&D);
 DumpFunction(f,&D);
 return D.status;
}

static void DumpHeader(DumpState* D)
{
 lu_byte h[LUAC_HEADERSIZE];
 luaU_header(h);
 DumpBlock(h,LUAC_HEADERSIZE,D);
}

/*
* make header for precompiled chunks
* if you change the code below be sure to update LoadHeader and FORMAT above
* and LUAC_HEADERSIZE in lundump.h
*/
void luaU_header (lu_byte* h)
{
 int x=1;
 memcpy(h,LUA_SIGNATURE,sizeof(LUA_SIGNATURE)-sizeof(char));
 h+=sizeof(LUA_SIGNATURE)-sizeof(char);
 *h++=cast_byte(VERSION);
 *h++=cast_byte(FORMAT);
 *h++=cast_byte(*(char*)&x);			/* endianness */
 *h++=cast_byte(sizeof(int));
 *h++=cast_byte(sizeof(size_t));
 *h++=cast_byte(sizeof(Instruction));
 *h++=cast_byte(sizeof(lua_Number));
 *h++=cast_byte(((lua_Number)0.5)==0);		/* is lua_Number integral? */
 memcpy(h,LUAC_TAIL,sizeof(LUAC_TAIL)-sizeof(char));
}

typedef unsigned LUA_INT32 lu_int32;
typedef lu_int32 Instruction;

#define LUA_NUMBER	double
typedef LUA_NUMBER lua_Number;

static void DumpBlock(const void* b, size_t size, DumpState* D)
{
 if (D->status==0)
 {
  lua_unlock(D->L);
  D->status=(*D->writer)(D->L,b,size,D->data);
  lua_lock(D->L);
 }
}

//////////////////////////////////////////////////////////////////////////////
// lundump.c
//////////////////////////////////////////////////////////////////////////////

/*
** load precompiled chunk
*/
Proto* luaU_undump (lua_State* L, ZIO* Z, Mbuffer* buff, const char* name)
{
 LoadState S;
 if (*name=='@' || *name=='=')
  S.name=name+1;
 else if (*name==LUA_SIGNATURE[0])
  S.name="binary string";
 else
  S.name=name;
 S.L=L;
 S.Z=Z;
 S.b=buff;
 LoadHeader(&S);
 return luai_verifycode(L,buff,LoadFunction(&S));
}

/* mark for precompiled code ('<esc>Lua') */
#define LUA_SIGNATURE	"\033Lua"

/* data to catch conversion errors */
#define LUAC_TAIL		"\x19\x93\r\n\x1a\n"

/* size in bytes of header of binary files */
#define LUAC_HEADERSIZE		(sizeof(LUA_SIGNATURE)-sizeof(char)+2+6+sizeof(LUAC_TAIL)-sizeof(char))

/* the code below must be consistent with the code in luaU_header */
#define N0	LUAC_HEADERSIZE
#define N1	(sizeof(LUA_SIGNATURE)-sizeof(char))
#define N2	N1+2
#define N3	N2+6

static void LoadHeader(LoadState* S)
{
 lu_byte h[LUAC_HEADERSIZE];
 lu_byte s[LUAC_HEADERSIZE];
 luaU_header(h);
 memcpy(s,h,sizeof(char));			/* first char already read */
 LoadBlock(S,s+sizeof(char),LUAC_HEADERSIZE-sizeof(char));
 if (memcmp(h,s,N0)==0) return;
 if (memcmp(h,s,N1)!=0) error(S,"not a");
 if (memcmp(h,s,N2)!=0) error(S,"version mismatch in");
 if (memcmp(h,s,N3)!=0) error(S,"incompatible"); else error(S,"corrupted");
}


//////////////////////////////////////////////////////////////////////////////
// Uses of long
//////////////////////////////////////////////////////////////////////////////

#ifndef TARGET_EFI
#define LUA_USE_MACOSX
#define LUA_COMPAT_ALL
#endif



#if defined(LUA_USE_MACOSX)
#define LUA_USE_POSIX
#define LUA_USE_DLOPEN		/* does not need -ldl */
#define LUA_USE_READLINE	/* needs an extra library: -lreadline */
#define LUA_USE_STRTODHEX	/* assume 'strtod' handles hexa formats */
#define LUA_USE_AFORMAT		/* assume 'printf' handles 'aA' specifiers */
#define LUA_USE_LONGLONG	/* assume support for long long */
#endif

/*
** LUA_INTFRMLEN is the length modifier for integer conversions in
** 'string.format'; LUA_INTFRM_T is the integer type corresponding to
** the previous length
*/
#if !defined(LUA_INTFRMLEN)	/* { */
#if defined(LUA_USE_LONGLONG)

#define LUA_INTFRMLEN           "ll"
#define LUA_INTFRM_T            long long

#else

#define LUA_INTFRMLEN           "l"
#define LUA_INTFRM_T            long

#endif
#endif				/* } */





/*
@@ LUA_INT32 is an signed integer with exactly 32 bits.
@@ LUAI_UMEM is an unsigned integer big enough to count the total
@* memory used by Lua.
@@ LUAI_MEM is a signed integer big enough to count the total memory
@* used by Lua.
** CHANGE here if for some weird reason the default definitions are not
** good enough for your machine. Probably you do not need to change
** this.
*/
#if LUAI_BITSINT >= 32		/* { */
#define LUA_INT32	int
#define LUAI_UMEM	size_t
#define LUAI_MEM	ptrdiff_t
#else				/* }{ */
/* 16-bit ints */
#define LUA_INT32	long
#define LUAI_UMEM	unsigned long
#define LUAI_MEM	long
#endif				/* } */





#if !defined(lua_fseek)	/* { */

#if defined(LUA_USE_POSIX)

#define l_fseek(f,o,w)		fseeko(f,o,w)
#define l_ftell(f)		ftello(f)
#define l_seeknum		off_t

#elif defined(LUA_WIN) && !defined(_CRTIMP_TYPEINFO) \
   && defined(_MSC_VER) && (_MSC_VER >= 1400)
/* Windows (but not DDK) and Visual C++ 2005 or higher */

#define l_fseek(f,o,w)		_fseeki64(f,o,w)
#define l_ftell(f)		_ftelli64(f)
#define l_seeknum		__int64

#else

#define l_fseek(f,o,w)		fseek(f,o,w)
#define l_ftell(f)		ftell(f)
#define l_seeknum		long

#endif

#endif			/* } */




static int f_seek (lua_State *L) {
  static const int mode[] = {SEEK_SET, SEEK_CUR, SEEK_END};
  static const char *const modenames[] = {"set", "cur", "end", NULL};
  FILE *f = tofile(L);
  int op = luaL_checkoption(L, 2, "cur", modenames);
  lua_Number p3 = luaL_optnumber(L, 3, 0);
  l_seeknum offset = (l_seeknum)p3;
  luaL_argcheck(L, (lua_Number)offset == p3, 3,
                  "not an integer in proper range");
  op = l_fseek(f, offset, mode[op]);
  if (op)
    return luaL_fileresult(L, 0, NULL);  /* error */
  else {
    lua_pushnumber(L, (lua_Number)l_ftell(f));
    return 1;
  }
}






#if !defined(LUAI_USER_ALIGNMENT_T)
#define LUAI_USER_ALIGNMENT_T	union { double u; void *s; long l; }
#endif

typedef LUAI_USER_ALIGNMENT_T L_Umaxalign;


/*
** Header for string value; string bytes follow the end of this structure
*/
typedef union TString {
  L_Umaxalign dummy;  /* ensures maximum alignment for strings */
  struct {
    CommonHeader;
    lu_byte reserved;
    unsigned int hash;
    size_t len;  /* number of characters in string */
  } tsv;
} TString;


/* get the actual string (array of bytes) from a TString */
#define getstr(ts)	cast(const char *, (ts) + 1)

/* get the actual string (array of bytes) from a Lua value */
#define svalue(o)       getstr(rawtsvalue(o))


/*
** Header for userdata; memory area follows the end of this structure
*/
typedef union Udata {
  L_Umaxalign dummy;  /* ensures maximum alignment for `local' udata */
  struct {
    CommonHeader;
    struct Table *metatable;
    struct Table *env;
    size_t len;  /* number of bytes */
  } uv;
} Udata;





#if defined(TRACEMEM)
  { /* auxiliary patch to monitor garbage collection.
    ** To plot, gnuplot with following command:
    ** plot TRACEMEM using 1:2 with lines, TRACEMEM using 1:3 with lines
    */
    static unsigned long total = 0;  /* our "time" */
    static FILE *f = NULL;  /* output file */
    total++;  /* "time" always grows */
    if ((total % 200) == 0) {
      if (f == NULL) f = fopen(TRACEMEM, "w");
      fprintf(f, "%lu %u %d %d\n", total,
              gettotalbytes(g), g->GCdebt, g->gcstate * 10000);
    }
  }
#endif




//////////////////////////////////////////////////////////////////////////////
// load() function chain
//////////////////////////////////////////////////////////////////////////////

LUA_API int lua_load (lua_State *L, lua_Reader reader, void *data,
                      const char *chunkname, const char *mode) {
  ZIO z;
  int status;
  lua_lock(L);
  if (!chunkname) chunkname = "?";
  luaZ_init(L, &z, reader, data);
  status = luaD_protectedparser(L, &z, chunkname, mode);
  if (status == LUA_OK) {  /* no errors? */
    LClosure *f = clLvalue(L->top - 1);  /* get newly created function */
    if (f->nupvalues == 1) {  /* does it have one upvalue? */
      /* get global table from registry */
      Table *reg = hvalue(&G(L)->l_registry);
      const TValue *gt = luaH_getint(reg, LUA_RIDX_GLOBALS);
      /* set global table as 1st upvalue of 'f' (may be LUA_ENV) */
      setobj(L, f->upvals[0]->v, gt);
      luaC_barrier(L, f->upvals[0], gt);
    }
  }
  lua_unlock(L);
  return status;
}

void luaZ_init (lua_State *L, ZIO *z, lua_Reader reader, void *data) {
  z->L = L;
  z->reader = reader;
  z->data = data;
  z->n = 0;
  z->p = NULL;
}

int luaD_protectedparser (lua_State *L, ZIO *z, const char *name,
                                        const char *mode) {
  struct SParser p;
  int status;
  L->nny++;  /* cannot yield during parsing */
  p.z = z; p.name = name; p.mode = mode;
  p.dyd.actvar.arr = NULL; p.dyd.actvar.size = 0;
  p.dyd.gt.arr = NULL; p.dyd.gt.size = 0;
  p.dyd.label.arr = NULL; p.dyd.label.size = 0;
  luaZ_initbuffer(L, &p.buff);
  status = luaD_pcall(L, f_parser, &p, savestack(L, L->top), L->errfunc);
  luaZ_freebuffer(L, &p.buff);
  luaM_freearray(L, p.dyd.actvar.arr, p.dyd.actvar.size);
  luaM_freearray(L, p.dyd.gt.arr, p.dyd.gt.size);
  luaM_freearray(L, p.dyd.label.arr, p.dyd.label.size);
  L->nny--;
  return status;
}

static void f_parser (lua_State *L, void *ud) {
  int i;
  Proto *tf;
  Closure *cl;
  struct SParser *p = cast(struct SParser *, ud);
  int c = zgetc(p->z);  /* read first character */
  if (c == LUA_SIGNATURE[0]) {
    checkmode(L, p->mode, "binary");
    tf = luaU_undump(L, p->z, &p->buff, p->name);
  }
  else {
    checkmode(L, p->mode, "text");
    tf = luaY_parser(L, p->z, &p->buff, &p->dyd, p->name, c);
  }
  setptvalue2s(L, L->top, tf);
  incr_top(L);
  cl = luaF_newLclosure(L, tf);
  setclLvalue(L, L->top - 1, cl);
  for (i = 0; i < tf->sizeupvalues; i++)  /* initialize upvalues */
    cl->l.upvals[i] = luaF_newupval(L);
}

/*
** load precompiled chunk
*/
Proto* luaU_undump (lua_State* L, ZIO* Z, Mbuffer* buff, const char* name)
{
 LoadState S;
 if (*name=='@' || *name=='=')
  S.name=name+1;
 else if (*name==LUA_SIGNATURE[0])
  S.name="binary string";
 else
  S.name=name;
 S.L=L;
 S.Z=Z;
 S.b=buff;
 LoadHeader(&S);
 return luai_verifycode(L,buff,LoadFunction(&S));
}

static void LoadHeader(LoadState* S)
{
 lu_byte h[LUAC_HEADERSIZE];
 lu_byte s[LUAC_HEADERSIZE];
 luaU_header(h);
 memcpy(s,h,sizeof(char));			/* first char already read */
 LoadBlock(S,s+sizeof(char),LUAC_HEADERSIZE-sizeof(char));
 if (memcmp(h,s,N0)==0) return;
 if (memcmp(h,s,N1)!=0) error(S,"not a");
 if (memcmp(h,s,N2)!=0) error(S,"version mismatch in");
 if (memcmp(h,s,N3)!=0) error(S,"incompatible"); else error(S,"corrupted");
}

static Proto* LoadFunction(LoadState* S)
{
 Proto* f=luaF_newproto(S->L);
 setptvalue2s(S->L,S->L->top,f); incr_top(S->L);
 f->linedefined=LoadInt(S); //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
 f->lastlinedefined=LoadInt(S); //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
 f->numparams=LoadByte(S); //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
 f->is_vararg=LoadByte(S); //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
 f->maxstacksize=LoadByte(S); //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
 LoadCode(S,f); //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
 LoadConstants(S,f); //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
 LoadUpvalues(S,f); //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
 LoadDebug(S,f); //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
 S->L->top--;
 return f;
}

static int LoadInt(LoadState* S)
{
 int x; // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
 LoadVar(S,x);
 if (x<0) error(S,"corrupted");
 return x;
}

#define LoadVar(S,x)		LoadMem(S,&x,1,sizeof(x))

#define LoadMem(S,b,n,size)	LoadBlock(S,b,(n)*(size))

static void LoadBlock(LoadState* S, void* b, size_t size)
{
 if (luaZ_read(S->Z,b,size)!=0) error(S,"truncated");
}

size_t luaZ_read (ZIO *z, void *b, size_t n) {
  while (n) {
    size_t m;
    if (z->n == 0) {  /* no bytes in buffer? */
      if (luaZ_fill(z) == EOZ)  /* try to read more */
        return n;  /* no more input; return number of missing bytes */
      else {
        z->n++;  /* luaZ_fill consumed first byte; put it back */
        z->p--;
      }
    }
    m = (n <= z->n) ? n : z->n;  /* min. between n and z->n */
    memcpy(b, z->p, m);
    z->n -= m;
    z->p += m;
    b = (char *)b + m;
    n -= m;
  }
  return 0;
}

#define LoadByte(S)		(lu_byte)LoadChar(S)

static int LoadChar(LoadState* S)
{
 char x; // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
 LoadVar(S,x);
 return x;
}

static void LoadCode(LoadState* S, Proto* f)
{
 int n=LoadInt(S); // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
 f->code=luaM_newvector(S->L,n,Instruction);
 f->sizecode=n;
 LoadVector(S,f->code,n,sizeof(Instruction)); // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<
}

#define LoadVector(S,b,n,size)	LoadMem(S,b,n,size)

typedef lu_int32 Instruction;
typedef unsigned LUA_INT32 lu_int32; // <<<<<<<<<<<<<<<<<<<<<<<< see luaconf.h

static void LoadConstants(LoadState* S, Proto* f)
{
 int i,n;
 n=LoadInt(S); // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
 f->k=luaM_newvector(S->L,n,TValue);
 f->sizek=n;
 for (i=0; i<n; i++) setnilvalue(&f->k[i]);
 for (i=0; i<n; i++)
 {
  TValue* o=&f->k[i];
  int t=LoadChar(S); // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  switch (t)
  {
   case LUA_TNIL:
	setnilvalue(o);
	break;
   case LUA_TBOOLEAN:
	setbvalue(o,LoadChar(S)); //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	break;
   case LUA_TNUMBER:
	setnvalue(o,LoadNumber(S)); //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	break;
   case LUA_TSTRING:
	setsvalue2n(S->L,o,LoadString(S)); //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	break;
  }
 }
 n=LoadInt(S);
 f->p=luaM_newvector(S->L,n,Proto*);
 f->sizep=n;
 for (i=0; i<n; i++) f->p[i]=NULL;
 for (i=0; i<n; i++) f->p[i]=LoadFunction(S);
}

static lua_Number LoadNumber(LoadState* S)
{
 lua_Number x; // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
 LoadVar(S,x);
 return x;
}

static TString* LoadString(LoadState* S)
{
 size_t size; // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
 LoadVar(S,size);
 if (size==0)
  return NULL;
 else
 {
  char* s=luaZ_openspace(S->L,S->b,size);
  LoadBlock(S,s,size*sizeof(char)); // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  return luaS_newlstr(S->L,s,size-1);		/* remove trailing '\0' */
 }
}

static void LoadUpvalues(LoadState* S, Proto* f)
{
 int i,n;
 n=LoadInt(S); // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
 f->upvalues=luaM_newvector(S->L,n,Upvaldesc);
 f->sizeupvalues=n;
 for (i=0; i<n; i++) f->upvalues[i].name=NULL;
 for (i=0; i<n; i++)
 {
  f->upvalues[i].instack=LoadByte(S); // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  f->upvalues[i].idx=LoadByte(S); // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
 }
}

static void LoadDebug(LoadState* S, Proto* f)
{
 int i,n;
 f->source=LoadString(S); // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
 n=LoadInt(S); // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
 f->lineinfo=luaM_newvector(S->L,n,int);
 f->sizelineinfo=n;
 LoadVector(S,f->lineinfo,n,sizeof(int)); // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
 n=LoadInt(S); // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
 f->locvars=luaM_newvector(S->L,n,LocVar);
 f->sizelocvars=n;
 for (i=0; i<n; i++) f->locvars[i].varname=NULL;
 for (i=0; i<n; i++)
 {
  f->locvars[i].varname=LoadString(S); // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  f->locvars[i].startpc=LoadInt(S); // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  f->locvars[i].endpc=LoadInt(S); // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
 }
 n=LoadInt(S); // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
 for (i=0; i<n; i++) f->upvalues[i].name=LoadString(S); // <<<<<<<<<<<<<<<<<<<
}


