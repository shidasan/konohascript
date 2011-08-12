/****************************************************************************
 * KONOHA COPYRIGHT, LICENSE NOTICE, AND DISCRIMER
 *
 * Copyright (c) 2006-2011, Kimio Kuramitsu <kimio at ynu.ac.jp>
 *           (c) 2008-      Konoha Team konohaken@googlegroups.com
 * All rights reserved.
 *
 * You may choose one of the following two licenses when you use konoha.
 * If you want to use the latter license, please contact us.
 *
 * (1) GNU General Public License 3.0 (with K_UNDER_GPL)
 * (2) Konoha Non-Disclosure License 1.0
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER
 * OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/* ************************************************************************ */

#include"commons.h"
#include <errno.h>

/* ************************************************************************ */

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------------------------------ */

int knh_bytes_parseint(knh_bytes_t t, knh_int_t *value)
{
	knh_uint_t n = 0, prev = 0, base = 10;
	size_t i = 0;
	if(t.len > 1) {
		if(t.utext[0] == '0') {
			if(t.utext[1] == 'x') {
				base = 16; i = 2;
			}
			else if(t.utext[1] == 'b') {
				base = 2;  i = 2;
			}
		}else if(t.utext[0] == '-') {
			base = 10; i = 1;
		}
	}
	for(;i < t.len; i++) {
		int c = t.utext[i];
		if('0' <= c && c <= '9') {
			prev = n;
			n = n * base + (c - '0');
		}else if(base == 16) {
			if('A' <= c && c <= 'F') {
				prev = n;
				n = n * 16 + (10 + c - 'A');
			}else if('a' <= c && c <= 'f') {
				prev = n;
				n = n * 16 + (10 + c - 'a');
			}else {
				break;
			}
		}else if(c == '_') {
			continue;
		}else {
			break;
		}
		if(!(n >= prev)) {
			*value = 0;
			return 0;
		}
	}
	if(t.utext[0] == '-') n = -((knh_int_t)n);
	*value = n;
	return 1;
}

int knh_bytes_parsefloat(knh_bytes_t t, knh_float_t *value)
{
#if defined(K_USING_NOFLOAT)
	{
		knh_int_t v = 0;
		knh_bytes_parseint(t, &v);
		*value = (knh_float_t)v;
	}
#else
	*value = strtod(t.text, NULL);
#endif
	return 1;
}


knh_index_t knh_bytes_indexOf(knh_bytes_t base, knh_bytes_t sub)
{
	const char *const str0 = base.text;  /* ide version */
	const char *const str1 = sub.text;
	knh_index_t len  = sub.len;
	knh_index_t loop = base.len - len;
	knh_index_t index = -1;
	if (loop >= 0) {
		knh_index_t i;
		const char *s0 = str0, *s1 = str1;
		const char *const s0end = s0 + loop;
		while(s0 <= s0end) {
			for (i = 0; i < len; i++) {
				if (s0[i] != s1[i]) {
					goto L_END;
				}
			}
			if (i == len) {
				return s0 - str0;
			}
			L_END:
			s0++;
		}
	}
	return index;
}

int knh_bytes_strcmp(knh_bytes_t v1, knh_bytes_t v2)
{
	int len, res1, res;
	if (v1.len == v2.len)     { len = v1.len; res1 =  0;}
	else if (v1.len < v2.len) { len = v1.len; res1 = -1;}
	else                      { len = v2.len; res1 =  1;}
	res = knh_strncmp(v1.text, v2.text, len);
	res1 = (res == 0) ? res1 : res;
	return res1;
}


/* ------------------------------------------------------------------------ */
/* These utf8 functions were originally written by Shinpei Nakata */

#define utf8_isLead(c)      ((c & 0xC0) != 0x80)
#define utf8_isTrail(c)     ((0x80 <= c) && (c <= 0xBF))
#define utf8_isSingleton(c) (c <= 0x7f)

static const knh_uchar_t _utf8len[] = {
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
		2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
		3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
		4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 0, 0,
};

#define utf8len(c)    _utf8len[(knh_uchar_t)c]

int knh_utf8len(int c)
{
	return _utf8len[c];
}

/* ------------------------------------------------------------------------ */

knh_bool_t knh_bytes_checkENCODING(knh_bytes_t v)
{
#ifdef K_USING_UTF8
	const unsigned char *s = v.utext;
	const unsigned char *e = s + v.len;
	while (s < e) {
		size_t ulen = utf8len(s[0]);
		switch(ulen) {
		case 1: s++; break;
		case 2:
			if(!utf8_isTrail(s[1])) return 0;
			s+=2; break;
		case 3:
			if(!utf8_isTrail(s[1])) return 0;
			if(!utf8_isTrail(s[2])) return 0;
			s+=3; break;
		case 4:
			if(!utf8_isTrail(s[1])) return 0;
			if(!utf8_isTrail(s[2])) return 0;
			if(!utf8_isTrail(s[3])) return 0;
			s+=4; break;
		case 5: case 6: case 0: default:
			return 0;
		}
	}
	return (s == e);
#else
	return 1;
#endif
}

size_t knh_bytes_mlen(knh_bytes_t v)
{
#ifdef K_USING_UTF8
	size_t size = 0;
	const unsigned char *s = v.utext;
	const unsigned char *e = s + v.len;
	while (s < e) {
		size_t ulen = utf8len(s[0]);
		size ++;
		s += ulen;
	}
	return size;
#else
	return v.len;
#endif
}

knh_bytes_t knh_bytes_mofflen(knh_bytes_t v, size_t moff, size_t mlen)
{
#ifdef K_USING_UTF8
	size_t i;
	const unsigned char *s = v.utext;
	const unsigned char *e = s + v.len;
	for(i = 0; i < moff; i++) {
		s += utf8len(s[0]);
	}
	v.ubuf = (knh_uchar_t*)s;
	for(i = 0; i < mlen; i++) {
		s += utf8len(s[0]);
	}
	KNH_ASSERT(s <= e);
	v.len = (const char*)s - v.text;
	return v;
#else
	return knh_bytes_subbytes(m, moff, mlen); /* if K_ENCODING is not set */
#endif
}

knh_int_t knh_uchar_toucs4(knh_utext_t *utf8)   /* utf8 -> ucs4 */
{
#if defined(K_USING_UTF8)
	knh_int_t ucs4 = 0;
	int i= 0;
	knh_uchar_t ret = 0;
	if (!utf8_isSingleton(utf8[0])) {
		knh_ushort_t length_utf8 = utf8len(utf8[i]);
		knh_uchar_t mask = (knh_uchar_t)(1 << 0 | 1 << 1 | 1 << 2 | 1 << 3);

		switch(length_utf8){
		case 2:
			/* 110xxxxx 10xxxxxx */
			TODO();
			break;
		case 3:
			/* format 1110xxxx 10xxxxxx 10xxxxxx */
			// first 4 bits
			ucs4 = 0;
			ret = utf8[0] & mask;
			ucs4 = ucs4 | ret;
			// second bit
			ucs4 = ucs4 << 6;
			mask = mask | 1 << 4 | 1 << 5;
			ret = utf8[1] & mask;
			ucs4 = ucs4  | ret;
			// third bit
			ucs4 = ucs4 << 6;
			ret = mask & utf8[2];
			ucs4 = ucs4 | ret;
			break;
		default:
			/* TODO: */
			break;
		}
	} else {
		/* ASCII, let it goes...*/
		ucs4 = utf8[0];
	}
	return ucs4;
#else
	return (knh_int_t)utf8[0];
#endif
}

/* ------------------------------------------------------------------------ */
/* ucs4 -> utf8 */

char *knh_format_utf8(char *buf, size_t bufsiz, knh_uint_t ucs4)
{
	/* TODO: here, we assume that BOM bigEndian
	 and only 3 bytes or 1 byte UTF
	 */
	knh_uint_t mask = 0x0;
	knh_uint_t byte1 = 0x7F;
	knh_uint_t byte2 = 0x7FF;
	knh_uint_t byte3 = 0xFFFF;

	char *ret = buf;
	unsigned char utf8[8];
	if (ucs4 <= byte1) {
		/* 7 bits */
		knh_snprintf(buf, bufsiz, "%c", (int)(0xffff & ucs4));
		ret = buf;
	} else if (ucs4 <= byte2) {
		/* cut last 6 bits */
		TODO();
		/* first 5 bits */
	} else if (ucs4 <= byte3) {
		/* cut last 6 bits */
		mask = 1 << 0 | 1 << 1 | 1 << 2 | 1 << 3| 1 << 4 | 1 << 5;
		utf8[2] = (unsigned char)(ucs4 & mask);
		utf8[2] = utf8[2] | 1 << 7;
		/* cut next 6 bits */
		ucs4 = ucs4 >> 6;
		utf8[1] = (unsigned char)(ucs4 & mask);
		utf8[1] = utf8[1] | 1 << 7;
		/* first 4 bits */
		mask = 1 << 0 | 1 << 1 | 1 << 2 | 1 << 3;
		ucs4 = ucs4 >> 6;
		utf8[0] = (unsigned char)(ucs4 & mask);
		utf8[0] = utf8[0] | 1 << 7 | 1 << 6 | 1 << 5;
		utf8[3] = '\0';
		knh_snprintf(buf, bufsiz, "%s", utf8);
	} else {
		TODO();
	}
	return ret;
}
/* ------------------------------------------------------------------------ */
/* [String] */

static void knh_String_checkASCII(knh_String_t *o)
{
	unsigned char ch = 0;
	long len = S_size(o);
	const knh_uchar_t *p = (const knh_uchar_t *) S_tochar(o);
#ifdef K_USING_FASTESTFASTMODE /* written by ide */
	int len = S_size(o), n = (len + 3) / 4;
	/* Duff's device */
	switch(len%4){
	case 0: do{ ch |= *p++;
	case 3:     ch |= *p++;
	case 2:     ch |= *p++;
	case 1:     ch |= *p++;
	} while(--n>0);
	}
#else
	const knh_uchar_t *const e = p + len;
	while(p < e) {
		int n = len % 8;
		switch(n) {
			case 0: ch |= *p++;
			case 7: ch |= *p++;
			case 6: ch |= *p++;
			case 5: ch |= *p++;
			case 4: ch |= *p++;
			case 3: ch |= *p++;
			case 2: ch |= *p++;
			case 1: ch |= *p++;
		}
		len -= n;
	}
#endif
	String_setASCII(o, (ch < 128));
}

/* ------------------------------------------------------------------------ */

#ifdef K_USING_STRINGPOOL

#define CHECK_CONST(ctx, V, S, L) \
	if(ct->constPoolMapNULL != NULL) {     \
		V = knh_PtrMap_getS(ctx, ct->constPoolMapNULL, S, L); \
		if(V != NULL) {           \
			return V;             \
		}                         \
	}                             \

#define SET_CONST(ctx, V) \
	if(ct->constPoolMapNULL != NULL) {     \
		knh_PtrMap_addS(ctx, ct->constPoolMapNULL, V); \
	}                             \

#else

#define CHECK_CONST(ctx, V, S, L)
#define SET_CONST(ctx, V)

#endif

KNHAPI2(knh_String_t*) new_String_(CTX ctx, knh_class_t cid, knh_bytes_t t, knh_String_t *memoNULL)
{
	knh_String_t *s;
	const knh_ClassTBL_t *ct = ClassTBL(cid);
	CHECK_CONST(ctx, s, t.text, t.len);
	s = (knh_String_t*)new_hObject_(ctx, ct);
	if(t.len + 1 < sizeof(void*) * 2) {
		s->str.ubuf = (knh_uchar_t*)(&(s->hashCode));
		s->str.len = t.len;
		knh_memcpy(s->str.ubuf, t.utext, t.len);
		s->str.ubuf[s->str.len] = '\0';
		String_setTextSgm(s, 1);
	}
	else {
		s->str.len = t.len;
		s->str.ubuf = (knh_uchar_t*)KNH_MALLOC(ctx, KNH_SIZE(s->str.len+1));
		knh_memcpy(s->str.ubuf, t.utext, t.len);
		s->str.ubuf[s->str.len] = '\0';
		s->hashCode = 0;
	}
	if(memoNULL != NULL && String_isASCII(memoNULL)) {
		String_setASCII(s, 1);
	}
	else {
		knh_String_checkASCII(s);
	}
	SET_CONST(ctx, s);
	return s;
}

KNHAPI2(knh_String_t*) new_String(CTX ctx, const char *str)
{
	if(str == NULL) {
		return KNH_TNULL(String);
	}
	else if(str[0] == 0) {
		return TS_EMPTY;
	}
	else {
		knh_bytes_t t = {{str}, knh_strlen(str)};
		return new_String_(ctx, CLASS_String, t, NULL);
	}
}

knh_String_t *new_TEXT(CTX ctx, knh_class_t cid, knh_TEXT_t text, int isASCII)
{
	size_t len = knh_strlen(text);
	knh_String_t *s;
	const knh_ClassTBL_t *ct = ClassTBL(cid);
	CHECK_CONST(ctx, s, text, len);
	s = (knh_String_t*)new_hObject_(ctx, ct);
	s->str.text = text;
	s->str.len = len;
	s->hashCode = 0;
	String_setASCII(s, isASCII);
	String_setTextSgm(s, 1);
	SET_CONST(ctx, s);
	return s;
}


/* ------------------------------------------------------------------------ */

static knh_conv_t* strconv_open(CTX ctx, const char* to, const char *from)
{
	knh_iconv_t rc = ctx->spi->iconv_openSPI(to, from);
	if(rc == (knh_iconv_t)-1){
		LOGSFPDATA = {LOGMSG("unknown codec"), sDATA("spi", ctx->spi->iconvspi),
			sDATA("from", from), sDATA("to", to)};
		LIB_Failed("iconv", "IO!!");
		return NULL;
	}
	return (knh_conv_t*)rc;
}

static knh_bool_t strconv(Ctx *ctx, knh_conv_t *iconvp, knh_bytes_t from, knh_Bytes_t *to)
{
	char buffer[4096], *ibuf = (char*)from.ubuf;
	size_t ilen = from.len, rsize = 0;//, ilen_prev = ilen;
	knh_iconv_t cd = (knh_iconv_t)iconvp;
	knh_bytes_t bbuf = {{(const char*)buffer}, 0};
	while(ilen > 0) {
		char *obuf = buffer;
		size_t olen = sizeof(buffer);
		size_t rc = ctx->spi->iconvSPI(cd, &ibuf, &ilen, &obuf, &olen);
		olen = sizeof(buffer) - olen; rsize += olen;
		if(rc == (size_t)-1 && errno == EILSEQ) {
			LOGSFPDATA = {LOGMSG("invalid sequence"), sDATA("spi", ctx->spi->iconvspi)};
			NOTE_Failed("iconv");
			return 0;
		}
		bbuf.len = olen;
		knh_Bytes_write(ctx, to, bbuf);
	}
	return 1;
}
static void strconv_close(CTX ctx, knh_conv_t *conv)
{
	ctx->spi->iconv_closeSPI((knh_iconv_t)conv);
}

static knh_ConvDSPI_t SCONV = {
	K_DSPI_CONVTO, "md5",
	strconv_open, // open,
	strconv,  // byte->byte     :conv
	strconv,  // String->byte   :enc
	strconv,   // byte->String   :dec
	NULL,  // String->String :sconv
	strconv_close,
	NULL
};

knh_StringDecoder_t* new_StringDecoderNULL(CTX ctx, knh_bytes_t t)
{
	if(knh_bytes_strcasecmp(t, STEXT(K_ENCODING)) == 0) {
		return KNH_TNULL(StringDecoder);
	}
	else {
		knh_iconv_t id = ctx->spi->iconv_openSPI(K_ENCODING, t.text);
		if(id != (knh_iconv_t)(-1)) {
			knh_StringDecoder_t *c = new_(StringDecoder);
			c->conv = (knh_conv_t*)id;
			c->dpi = &SCONV;
			return c;
		}
	}
	return NULL;
}

knh_StringEncoder_t* new_StringEncoderNULL(CTX ctx, knh_bytes_t t)
{
	if(knh_bytes_strcasecmp(t, STEXT(K_ENCODING)) == 0) {
		return KNH_TNULL(StringEncoder);
	}
	else {
		knh_iconv_t id = ctx->spi->iconv_openSPI(K_ENCODING, t.text);
		if(id != (knh_iconv_t)(-1)) {
			knh_StringEncoder_t *c = new_(StringEncoder);
			c->conv = (knh_conv_t*)id;
			c->dpi = &SCONV;
			return c;
		}
	}
	return NULL;
}

/* ------------------------------------------------------------------------ */

knh_String_t *knh_cwb_newStringDECODE(CTX ctx, knh_cwb_t *cwb, knh_StringDecoder_t *c)
{
	BEGIN_LOCAL(ctx, lsfp, 1);
	LOCAL_NEW(ctx, lsfp, 0, knh_String_t*, s, knh_cwb_newString(ctx, cwb));
	if(!String_isASCII(s)) {
		c->dpi->dec(ctx, c->conv, S_tobytes(s), cwb->ba);
		s = knh_cwb_newString(ctx, cwb);
		KNH_SETv(ctx, lsfp[0].o, KNH_NULL); //
	}
	END_LOCAL(ctx, lsfp, s);
	return s;
}

/* ------------------------------------------------------------------------ */

int knh_bytes_strcasecmp(knh_bytes_t v1, knh_bytes_t v2)
{
	if(v1.len < v2.len) {
		int res = knh_strncasecmp(v1.text, v2.text, v1.len);
		return (res == 0) ? -1 : res;
	}
	else if(v1.len > v2.len) {
		int res = knh_strncasecmp(v1.text, v2.text, v2.len);
		return (res == 0) ? 1 : res;
	}
	else {
		return knh_strncasecmp(v1.text, v2.text, v1.len);
	}
}

/* ------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------ */
/* regex */

static knh_regex_t* strregex_malloc(CTX ctx, knh_String_t *pattern)
{
	return (knh_regex_t*)pattern;
}
static int strregex_parsecflags(CTX ctx, const char *opt)
{
	return 0;
}
static int strregex_parseeflags(CTX ctx, const char *opt)
{
	return 0;
}
static int strregex_nmatchsize(CTX ctx, knh_regex_t *reg)
{
	return 1;
}
static int strregex_regcomp(CTX ctx, knh_regex_t *reg, const char *pattern, int cflags)
{
	return 0;
}
static size_t strregex_regerror(int errcode, knh_regex_t *reg, char *ebuf, size_t ebuf_size)
{
	ebuf[0] = 0;
	return 0;
}
static int strregex_regexec(CTX ctx, knh_regex_t *reg, const char *str, size_t nmatch, knh_regmatch_t p[], int flags)
{
	size_t e = 0;
	knh_String_t *ptn = (knh_String_t*)reg;
	const char *po = strstr(str, S_tochar(ptn));
	if(po != NULL) {
		p[e].rm_so = po - str;
		p[e].rm_eo = p[e].rm_so + S_size(ptn);
		p[e].rm_name.ubuf = NULL;
		p[e].rm_name.len = 0;
		e++;
	}
	DBG_ASSERT(e < nmatch);
	p[e].rm_so = -1;
	p[e].rm_eo = -1;
	p[e].rm_name.ubuf = NULL;
	p[e].rm_name.len = 0;
	return (po) ? 0 : -1;
}

static void strregex_regfree(CTX ctx, knh_regex_t *reg) { }

static const knh_RegexSPI_t REGEX_STR = {
	"strregex",
	strregex_malloc, strregex_parsecflags, strregex_parseeflags,
	strregex_regcomp, strregex_nmatchsize, strregex_regexec, strregex_regerror,
	strregex_regfree
};

static const knh_RegexSPI_t* REGEX_DEFAULT = &REGEX_STR;

const knh_RegexSPI_t* knh_getStrRegexSPI(void)
{
	return &REGEX_STR;
}

knh_bool_t Regex_isSTRREGEX(knh_Regex_t *re)
{
	return (re->spi == &REGEX_STR);
}

const knh_RegexSPI_t* knh_getRegexSPI(void)
{
	return REGEX_DEFAULT;
}

/* ------------------------------------------------------------------------ */
/* [pcre] */

//#include <pcre.h>
//#define PCRE_MAX_ERROR_MESSAGE_LEN 512

// from pcre.h
struct real_pcre;
typedef struct real_pcre pcre;
typedef void pcre_extra;

static const char* (*pcre_version)(void);
static void  (*pcre_free)(void *);
static int  (*pcre_fullinfo)(const pcre *, const pcre_extra *, int, void *);
static pcre* (*pcre_compile)(const char *, int, const char **, int *, const unsigned char *);
static int  (*pcre_exec)(const pcre *, const pcre_extra *, const char*, int, int, int, int *, int);

static knh_bool_t knh_linkDynamicPCRE(CTX ctx)
{
	void *h = knh_dlopen(ctx, "libpcre" K_OSDLLEXT);
	if(h == NULL) return 0;
	pcre_version = (const char* (*)(void))knh_dlsym(ctx, h, "pcre_version", 0/*isTest*/);
	pcre_free = (void (*)(void*))knh_dlsym(ctx, h, "free", 0/*isTest*/);
	pcre_fullinfo = (int (*)(const pcre*, const pcre_extra*, int, void*))knh_dlsym(ctx, h, "pcre_fullinfo", 0/*isTest*/);
	pcre_compile = (pcre* (*)(const char *, int, const char **, int *, const unsigned char *))knh_dlsym(ctx, h, "pcre_compile", 0/*isTest*/);
	pcre_exec = (int  (*)(const pcre *, const pcre_extra *, const char*, int, int, int, int *, int))knh_dlsym(ctx, h, "pcre_exec", 0/*isTest*/);
	if(pcre_free == NULL || pcre_fullinfo == NULL || pcre_compile == NULL || pcre_exec == NULL) return 0;
	return 1;
}

#define PCRE_CASELESS           0x00000001  /* Compile */
#define PCRE_MULTILINE          0x00000002  /* Compile */
#define PCRE_DOTALL             0x00000004  /* Compile */
#define PCRE_EXTENDED           0x00000008  /* Compile */
#define PCRE_ANCHORED           0x00000010  /* Compile, exec, DFA exec */
#define PCRE_DOLLAR_ENDONLY     0x00000020  /* Compile */
#define PCRE_EXTRA              0x00000040  /* Compile */
#define PCRE_NOTBOL             0x00000080  /* Exec, DFA exec */
#define PCRE_NOTEOL             0x00000100  /* Exec, DFA exec */
#define PCRE_UNGREEDY           0x00000200  /* Compile */
#define PCRE_NOTEMPTY           0x00000400  /* Exec, DFA exec */
#define PCRE_UTF8               0x00000800  /* Compile */
#define PCRE_NO_AUTO_CAPTURE    0x00001000  /* Compile */
#define PCRE_NO_UTF8_CHECK      0x00002000  /* Compile, exec, DFA exec */
#define PCRE_AUTO_CALLOUT       0x00004000  /* Compile */
#define PCRE_PARTIAL_SOFT       0x00008000  /* Exec, DFA exec */
#define PCRE_PARTIAL            0x00008000  /* Backwards compatible synonym */
#define PCRE_DFA_SHORTEST       0x00010000  /* DFA exec */
#define PCRE_DFA_RESTART        0x00020000  /* DFA exec */
#define PCRE_FIRSTLINE          0x00040000  /* Compile */
#define PCRE_DUPNAMES           0x00080000  /* Compile */
#define PCRE_NEWLINE_CR         0x00100000  /* Compile, exec, DFA exec */
#define PCRE_NEWLINE_LF         0x00200000  /* Compile, exec, DFA exec */
#define PCRE_NEWLINE_CRLF       0x00300000  /* Compile, exec, DFA exec */
#define PCRE_NEWLINE_ANY        0x00400000  /* Compile, exec, DFA exec */
#define PCRE_NEWLINE_ANYCRLF    0x00500000  /* Compile, exec, DFA exec */
#define PCRE_BSR_ANYCRLF        0x00800000  /* Compile, exec, DFA exec */
#define PCRE_BSR_UNICODE        0x01000000  /* Compile, exec, DFA exec */
#define PCRE_JAVASCRIPT_COMPAT  0x02000000  /* Compile */
#define PCRE_NO_START_OPTIMIZE  0x04000000  /* Compile, exec, DFA exec */
#define PCRE_NO_START_OPTIMISE  0x04000000  /* Synonym */
#define PCRE_PARTIAL_HARD       0x08000000  /* Exec, DFA exec */
#define PCRE_NOTEMPTY_ATSTART   0x10000000  /* Exec, DFA exec */
#define PCRE_UCP                0x20000000  /* Compile */

#define PCRE_INFO_OPTIONS            0
#define PCRE_INFO_SIZE               1
#define PCRE_INFO_CAPTURECOUNT       2
#define PCRE_INFO_BACKREFMAX         3
#define PCRE_INFO_FIRSTBYTE          4
#define PCRE_INFO_FIRSTCHAR          4  /* For backwards compatibility */
#define PCRE_INFO_FIRSTTABLE         5
#define PCRE_INFO_LASTLITERAL        6
#define PCRE_INFO_NAMEENTRYSIZE      7
#define PCRE_INFO_NAMECOUNT          8
#define PCRE_INFO_NAMETABLE          9
#define PCRE_INFO_STUDYSIZE         10
#define PCRE_INFO_DEFAULT_TABLES    11
#define PCRE_INFO_OKPARTIAL         12
#define PCRE_INFO_JCHANGED          13
#define PCRE_INFO_HASCRORLF         14
#define PCRE_INFO_MINLENGTH         15

/* This part was implemented by Yutaro Hiraoka */

typedef struct {
	pcre *re;
	const char *err;
	int erroffset;
} PCRE_regex_t;


static knh_regex_t* pcre_regmalloc(CTX ctx, knh_String_t* s)
{
	PCRE_regex_t *preg = (PCRE_regex_t*) KNH_MALLOC(ctx,sizeof(PCRE_regex_t));
	return (knh_regex_t *) preg;
}

static void pcre_regfree(CTX ctx, knh_regex_t *reg)
{
	PCRE_regex_t *preg = (PCRE_regex_t*)reg;
	pcre_free(preg->re);
	KNH_FREE(ctx, preg, sizeof(PCRE_regex_t));
}

static int pcre_nmatchsize(CTX ctx, knh_regex_t *reg)
{
	PCRE_regex_t *preg = (PCRE_regex_t*)reg;
	int capsize = 0;
	if (pcre_fullinfo(preg->re, NULL, PCRE_INFO_CAPTURECOUNT, &capsize) != 0) {
		return K_REGEX_MATCHSIZE;
	}
	return capsize + 1;
}

static int pcre_parsecflags(CTX ctx, const char *option)
{
	int i, cflags = PCRE_UTF8;
	int optlen = strlen(option);
	for (i = 0; i < optlen; i++) {
		switch(option[i]) {
		case 'i': // caseless
			cflags |= PCRE_CASELESS;
			break;
		case 'm': // multiline
			cflags |= PCRE_MULTILINE;
			break;
		case 's': // dotall
			cflags |= PCRE_DOTALL;
			break;
		case 'x': //extended
			cflags |= PCRE_EXTENDED;
			break;
		default: break;
		}
	}
	return cflags;
}

static int pcre_parseeflags(CTX ctx, const char *option)
{
	int i, eflags = 0;
	int optlen = strlen(option);
	for (i = 0; i < optlen; i++) {
		switch(option[i]){
		default: break;
		}
	}
	return eflags;
}

static size_t pcre_regerror(int res, knh_regex_t *reg, char *ebuf, size_t ebufsize)
{
	PCRE_regex_t *pcre = (PCRE_regex_t*)reg;
	snprintf(ebuf, ebufsize, "[%d]: %s", pcre->erroffset, pcre->err);
	return 0;
}

static int pcre_regcomp(CTX ctx, knh_regex_t *reg, const char *pattern, int cflags)
{
	PCRE_regex_t* preg = (PCRE_regex_t*)reg;
	preg->re = pcre_compile(pattern, cflags, &preg->err, &preg->erroffset, NULL);
	return (preg->re != NULL) ? 0 : -1;
}

static int pcre_regexec(CTX ctx, knh_regex_t *reg, const char *str, size_t nmatch, knh_regmatch_t p[], int eflags)
{
	PCRE_regex_t *preg = (PCRE_regex_t*)reg;
	int res, nm_count, nvector[nmatch*3];
	nvector[0] = 0;
	size_t idx, matched = nmatch;
	if (strlen(str) == 0) return -1;
	if ((res = pcre_exec(preg->re, NULL, str, strlen(str), 0, eflags, nvector, nmatch*3)) >= 0) {
		if (res > 0 && res < nmatch) {
			matched = res;
			res = 0;
		}
		for (idx = 0; idx < matched; idx++) {
			p[idx].rm_so = nvector[2*idx];
			p[idx].rm_eo = nvector[2*idx+1];
		}
		p[idx].rm_so = -1;
		nm_count = 0;
		pcre_fullinfo(preg->re, NULL, PCRE_INFO_NAMECOUNT, &nm_count);
		if (nm_count > 0) {
			unsigned char *nm_table;
			int nm_entry_size = 0;
			pcre_fullinfo(preg->re, NULL, PCRE_INFO_NAMETABLE, &nm_table);
			pcre_fullinfo(preg->re, NULL, PCRE_INFO_NAMEENTRYSIZE, &nm_entry_size);
			unsigned char *tbl_ptr = nm_table;
			for (idx = 0; idx < nm_count; idx++) {
				int n_idx = (tbl_ptr[0] << 8) | tbl_ptr[1];
				unsigned char *n_name = tbl_ptr + 2;
				p[n_idx].rm_name.utext = n_name;
				p[n_idx].rm_name.len = strlen((char*)n_name);
				tbl_ptr += nm_entry_size;
			}
		}
	}
	return res;
}

static const knh_RegexSPI_t REGEX_PCRE = {
	"pcre",
	pcre_regmalloc,
	pcre_parsecflags,
	pcre_parseeflags,
	pcre_regcomp,
	pcre_nmatchsize,
	pcre_regexec,
	pcre_regerror,
	pcre_regfree
};

/* ------------------------------------------------------------------------ */
/* [re2] */

static knh_bool_t knh_linkDynamicRe2(CTX ctx)
{
#ifdef __cplusplus
	void *h = knh_dlopen(ctx, "libre2" K_OSDLLEXT);
	if(h != NULL) return 1;
#endif
	return 0;
}

#ifdef __cplusplus
} /* cancel extern "C" */

#include <re2/re2.h>
#include <vector>

extern "C" {

#define RE2_CASELESS           0x00000001
#define RE2_MULTILINE          0x00000002
#define RE2_DOTALL             0x00000004

typedef struct {
	re2::RE2 *r;
} RE2_regex_t;

static knh_regex_t* re2_regex_malloc(CTX ctx, knh_String_t* s)
{
	RE2_regex_t *reg = (RE2_regex_t*)KNH_MALLOC(ctx, sizeof(RE2_regex_t));
	reg->r = NULL;
	return (knh_regex_t*)reg;
}

static void re2_regex_regfree(CTX ctx, knh_regex_t *reg)
{
	RE2_regex_t *re = (RE2_regex_t*)reg;
	if (re->r != NULL) {
		re2::RE2 *r = static_cast<re2::RE2*>(re->r);
		delete r;
	}
	KNH_FREE(ctx, reg, sizeof(RE2_regex_t));
}

static size_t re2_regex_regerror(int res, knh_regex_t *reg, char *ebuf, size_t ebufsize)
{
	re2::RE2 *r = static_cast<re2::RE2*>(((RE2_regex_t*)reg)->r);
	snprintf(ebuf, ebufsize, "%s", (*r).error().c_str());
	return 0;
}

static int re2_regex_parsecflags(CTX ctx, const char *option)
{
	int i, cflags = 0;
	int optlen = strlen(option);
	for (i = 0; i < optlen; i++) {
		switch(option[i]) {
		case 'i': // caseless
				cflags |= RE2_CASELESS;
				break;
		case 'm': // multiline
			cflags |= RE2_MULTILINE;
			break;
		case 's': // dotall
			cflags |= RE2_DOTALL;
			break;
		default: break;
		}
	}
	return cflags;
}

static int re2_regex_regcomp(CTX ctx, knh_regex_t *reg, const char *pattern, int cflags)
{
	RE2_regex_t* re = (RE2_regex_t*)reg;
	re2::RE2::Options opt;
	opt.Copy(re2::RE2::Quiet);
	opt.set_perl_classes(true);
	if (cflags != 0) {
		if (cflags & RE2_CASELESS) {
			opt.set_case_sensitive(false);
		}
		if (cflags & RE2_MULTILINE) {
			opt.set_never_nl(true);
		}
		if (cflags & RE2_DOTALL) {
			opt.set_one_line(true);
		}
	}
	re->r = new re2::RE2(pattern, opt);
	return ((*(re->r)).ok()) ? 0 : 1;
}

static int re2_regex_nmatchsize(CTX ctx, knh_regex_t *reg)
{
	re2::RE2 *r = static_cast<re2::RE2*>(((RE2_regex_t*)reg)->r);
	return 1 + (*r).NumberOfCapturingGroups(); // patern + groups
}

static int re2_regex_parseeflags(CTX ctx, const char *option)
{
	int i, eflags = 0;
	int optlen = strlen(option);
	for (i = 0; i < optlen; i++) {
		switch(option[i]){
		default: break;
		}
	}
	return eflags;
}

static int re2_regex_regexec(CTX ctx, knh_regex_t *reg, const char *str, size_t nmatch, knh_regmatch_t p[], int eflags)
{
	re2::RE2 *r = static_cast<re2::RE2*>(((RE2_regex_t*)reg)->r);
	re2::StringPiece base(str);
	re2::StringPiece s[nmatch], *sp = s;
	size_t remain = nmatch;
	p[0].rm_so = -1;
	if ((*r).Match(base, 0, re2::RE2::UNANCHORED, sp, nmatch)) {
		size_t grpcount = (*r).NumberOfCapturingGroups();
		std::vector<std::string> names(grpcount+1);
		if (grpcount > 0) {
			std::map<std::string, int> m = (*r).NamedCapturingGroups();
			std::map<std::string, int>::iterator it, m_end = m.end();
			for (it = m.begin(); it != m_end; it++) {
				names[(*it).second] = (*it).first;
			}
		}
		size_t i, spoffset = sp->data() - base.data();
		p[0].rm_so = spoffset;
		p[0].rm_eo = spoffset + sp->length();
		p[0].rm_name.len = 0; // clear name
		for (i = 1, remain--, sp++; (!sp->empty() && remain > 0); i++, remain--, sp++) {
			spoffset = sp->data() - base.data();
			p[i].rm_so = spoffset;
			p[i].rm_eo = spoffset + sp->length();
			p[i].rm_name.len = 0; // clear name
			std::string *name = &names[i];
			if (name != NULL && !name->empty()) {
				p[i].rm_name = B(name->c_str());
			}
		}
		if (i < nmatch) p[i].rm_so = -1;
	}
	return (remain < nmatch && r->ok()) ? 0 : 1;
}

#endif /* __cplusplus */

static knh_RegexSPI_t REGEX_RE2 = {
	"re2",
#ifdef __cplusplus
	re2_regex_malloc, re2_regex_parsecflags, re2_regex_parseeflags, re2_regex_regcomp,
	re2_regex_nmatchsize, re2_regex_regexec, re2_regex_regerror, re2_regex_regfree
#else
	// dummy (never used)
	strregex_malloc, strregex_parsecflags, strregex_parseeflags, strregex_regcomp,
	strregex_nmatchsize, strregex_regexec, strregex_regerror, strregex_regfree
#endif
};

/* ------------------------------------------------------------------------ */
/* [onig] */

// from oniguruma.h
typedef unsigned char  OnigUChar;
typedef struct OnigEncodingTypeST*  OnigEncoding;
typedef unsigned int        OnigOptionType;
typedef struct OnigSyntaxType OnigSyntaxType;
typedef struct re_registers {
	int  allocated;
	int  num_regs;
	int* beg;
	int* end;
	/* extended */
	struct OnigCaptureTreeNodeStruct* history_root;  /* capture history tree root */
} OnigRegion;
typedef struct OnigErrorInfo OnigErrorInfo;
typedef struct re_pattern_buffer*  OnigRegex;

/* options */
#define ONIG_OPTION_NONE                 0U
#define ONIG_OPTION_IGNORECASE           1U
#define ONIG_OPTION_EXTEND               (ONIG_OPTION_IGNORECASE         << 1)
#define ONIG_OPTION_MULTILINE            (ONIG_OPTION_EXTEND             << 1)
#define ONIG_OPTION_SINGLELINE           (ONIG_OPTION_MULTILINE          << 1)
#define ONIG_OPTION_FIND_LONGEST         (ONIG_OPTION_SINGLELINE         << 1)
#define ONIG_OPTION_FIND_NOT_EMPTY       (ONIG_OPTION_FIND_LONGEST       << 1)
#define ONIG_OPTION_NEGATE_SINGLELINE    (ONIG_OPTION_FIND_NOT_EMPTY     << 1)
#define ONIG_OPTION_DONT_CAPTURE_GROUP   (ONIG_OPTION_NEGATE_SINGLELINE  << 1)
#define ONIG_OPTION_CAPTURE_GROUP        (ONIG_OPTION_DONT_CAPTURE_GROUP << 1)
/* options (search time) */
#define ONIG_OPTION_NOTBOL               (ONIG_OPTION_CAPTURE_GROUP << 1)
#define ONIG_OPTION_NOTEOL               (ONIG_OPTION_NOTBOL << 1)
#define ONIG_OPTION_POSIX_REGION         (ONIG_OPTION_NOTEOL << 1)
#define ONIG_OPTION_MAXBIT               ONIG_OPTION_POSIX_REGION  /* limit */

#define ONIG_OPTION_DEFAULT            ONIG_OPTION_NONE

#define ONIG_OPTION_ON(options,regopt)      ((options) |= (regopt))
#define ONIG_OPTION_OFF(options,regopt)     ((options) &= ~(regopt))
#define ONIG_IS_OPTION_ON(options,option)   ((options) & (option))

/* normal return */
#define ONIG_NORMAL                                            0
#define ONIG_MISMATCH                                         -1
#define ONIG_NO_SUPPORT_CONFIG                                -2


static int (*onig_error_code_to_str)(OnigUChar*, int, ...);
static int (*onig_new)(OnigRegex*, OnigUChar*, OnigUChar*, OnigOptionType, OnigEncoding, OnigSyntaxType*, OnigErrorInfo*);
static int (*onig_number_of_captures)(OnigRegex);
static OnigRegion* (*onig_region_new)(void);
static int (*onig_search)(OnigRegex, OnigUChar*, OnigUChar*, OnigUChar*, OnigUChar*, OnigRegion*, OnigOptionType);
static int (*onig_foreach_name)(OnigRegex, int (*)(const OnigUChar*, const OnigUChar*, int, int*, OnigRegex, void*), void*);
static void (*onig_region_free)(OnigRegion*, int);
static void (*onig_free)(OnigRegex);
static OnigEncoding encutf8;
static OnigSyntaxType** defaultsyntax;

static knh_bool_t knh_linkDynamicOnig(CTX ctx)
{
	void *h = knh_dlopen(ctx, "libonig" K_OSDLLEXT);
	if(h == NULL) return 0;
	onig_error_code_to_str = (int (*)(OnigUChar*, int, ...))knh_dlsym(ctx, h, "onig_error_code_to_str", 0/*isTest*/);
	onig_new = (int (*)(OnigRegex*, OnigUChar*, OnigUChar*, OnigOptionType, OnigEncoding, OnigSyntaxType*, OnigErrorInfo*))knh_dlsym(ctx, h, "onig_new", 0/*isTest*/);
	onig_number_of_captures = (int (*)(OnigRegex))knh_dlsym(ctx, h, "onig_number_of_captures", 0/*isTest*/);
	onig_region_new = (OnigRegion* (*)(void))knh_dlsym(ctx, h, "onig_region_new", 0/*isTest*/);
	onig_search = (int (*)(OnigRegex, OnigUChar*, OnigUChar*, OnigUChar*, OnigUChar*, OnigRegion*, OnigOptionType))knh_dlsym(ctx, h, "onig_search", 0/*isTest*/);
	onig_foreach_name = (int (*)(OnigRegex, int (*)(const OnigUChar*, const OnigUChar*, int, int*, OnigRegex, void*), void*))knh_dlsym(ctx, h, "onig_foreach_name", 0/*isTest*/);
	onig_region_free = (void (*)(OnigRegion*, int))knh_dlsym(ctx, h, "onig_region_free", 0/*isTest*/);
	onig_free = (void (*)(OnigRegex))knh_dlsym(ctx, h, "onig_free", 0/*isTest*/);

	encutf8 = (OnigEncoding)knh_dlsym(ctx, h, "OnigEncodingUTF8", 0/*isTest*/);
	defaultsyntax = (OnigSyntaxType**)knh_dlsym(ctx, h, "OnigDefaultSyntax", 0/*isTest*/);
	if(onig_error_code_to_str == NULL || onig_new == NULL || onig_number_of_captures == NULL || onig_region_new == NULL || onig_search == NULL || onig_foreach_name == NULL || onig_region_free == NULL || onig_free == NULL || encutf8 == NULL || defaultsyntax == NULL) return 0;
	return 1;
}

typedef struct {
	OnigRegex reg;
	OnigErrorInfo *einfo;
} ONIG_regex_t;

static knh_regex_t* onig_regex_malloc(CTX ctx, knh_String_t *s)
{
	ONIG_regex_t *r = (ONIG_regex_t*)KNH_MALLOC(ctx, sizeof(ONIG_regex_t));
	r->einfo = NULL;
	r->reg = NULL;
	return (knh_regex_t*) r;
}

static int onig_regex_parse_cflags(CTX ctx, const char *option)
{
	OnigOptionType cflags = ONIG_OPTION_DEFAULT;
	int i, optlen = strlen(option);
	for (i = 0; i < optlen; i++) {
		switch(option[i]) {
		case 'i':
			ONIG_OPTION_ON(cflags, ONIG_OPTION_IGNORECASE);
			break;
		case 'm':
			ONIG_OPTION_ON(cflags, ONIG_OPTION_MULTILINE);
			break;
		case 'x':
			ONIG_OPTION_ON(cflags, ONIG_OPTION_EXTEND);
			break;
		default: break;
		}
	}
	return (int)cflags;
}

static int onig_regex_parse_eflags(CTX ctx, const char *option)
{
	OnigOptionType eflags = ONIG_OPTION_NONE;
	int i, optlen = strlen(option);
	for (i = 0; i < optlen; i++) {
		switch(option[i]) {
		default: break;
		}
	}
	return eflags;
}

static size_t onig_regex_regerror(int res, knh_regex_t *reg, char* ebuf, size_t ebuf_size)
{
	ONIG_regex_t *oreg = (ONIG_regex_t*)reg;
	return onig_error_code_to_str((OnigUChar*)ebuf, res, oreg->einfo);
}

static int onig_regex_regcomp(CTX ctx, knh_regex_t *reg, const char *pattern, int cflag)
{
	ONIG_regex_t *oreg = (ONIG_regex_t*)reg;
	OnigUChar* upatt = (OnigUChar*) pattern;
	OnigUChar* end = upatt + strlen(pattern);
	int cmp = onig_new(&(oreg->reg), upatt, end, cflag, encutf8, *defaultsyntax, oreg->einfo);
	return (cmp == ONIG_NORMAL) ? 0 : 1;
}

static int onig_regex_nmatchsize(CTX ctx, knh_regex_t *reg)
{
	ONIG_regex_t *oreg = (ONIG_regex_t*)reg;
	int cap = onig_number_of_captures(oreg->reg);
	return 1 + cap; // pattern & groups
}

static int knh_regex_onig_setNames(const OnigUChar* name, const OnigUChar* name_end, int num_of_group, int* num_of_group_list, OnigRegex reg, void *arg)
{
	knh_regmatch_t *p = (knh_regmatch_t*)arg;
	int i, len = name_end - name;
	for (i = 0; i < num_of_group; i++) {
		int j = num_of_group_list[i];
		p[j].rm_name.buf = (char*)name;
		p[j].rm_name.len = len;
	}
	return 0;
}

static int onig_regex_regexec(CTX ctx, knh_regex_t *reg, const char *str, size_t nmatch, knh_regmatch_t p[], int eflag)
{
	ONIG_regex_t *oreg = (ONIG_regex_t*)reg;
	OnigUChar *head = (OnigUChar*)str;
	OnigUChar *end = head + strlen(str);
	OnigRegion* region = onig_region_new();
	int res = 0;
	p[0].rm_so = -1;
	if ((res = onig_search(oreg->reg, head, end, head, end, region, eflag)) >= 0) {
		size_t i, matched = region->num_regs;
		for (i = 0; i < nmatch && i < matched; i++) {
			p[i].rm_so = region->beg[i];
			p[i].rm_eo = region->end[i];
		}
		if (i < nmatch) p[i].rm_so = -1;
		onig_foreach_name(oreg->reg, knh_regex_onig_setNames, p);
	}
	onig_region_free(region, 1); /* 1:free self, 0:free contents only */
	return (res >= 0) ? 0 : res; /* >=0: not error(matched bytes), <0:error */
}

static void onig_regex_regfree(CTX ctx, knh_regex_t *reg)
{
	ONIG_regex_t *oreg = (ONIG_regex_t*)reg;
	OnigRegex r = oreg->reg;
	onig_free(r);
	KNH_FREE(ctx, oreg, sizeof(ONIG_regex_t));
}

static const knh_RegexSPI_t REGEX_ONIG = {
	"oniguruma",
	onig_regex_malloc,
	onig_regex_parse_cflags,
	onig_regex_parse_eflags,
	onig_regex_regcomp,
	onig_regex_nmatchsize,
	onig_regex_regexec,
	onig_regex_regerror,
	onig_regex_regfree
};

/* ------------------------------------------------------------------------ */
/* [regex] */

void knh_linkDynamicRegex(CTX ctx)
{
	if(REGEX_DEFAULT == &REGEX_STR) {
		if(knh_linkDynamicRe2(ctx)) {
			REGEX_DEFAULT = &REGEX_RE2;
			return;
		}
		if(knh_linkDynamicPCRE(ctx)) {
			REGEX_DEFAULT = &REGEX_PCRE;
			return;
		}
		if(knh_linkDynamicOnig(ctx)) {
			REGEX_DEFAULT = &REGEX_ONIG;
			return;
		}
	}
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif

