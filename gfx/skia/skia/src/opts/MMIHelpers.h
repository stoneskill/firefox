/*
 ============================================================================
 Name        : MMIHelpers.h
 Author      : Heiher <r@hev.cc>
 Version     : 0.0.1
 Copyright   : Copyright (c) 2017 everyone.
 Description : The helpers for x86 SSE to Loongson MMI.
 ============================================================================
 */

#ifndef __MMI_HELPERS_H__
#define __MMI_HELPERS_H__

typedef struct {
    double l;
    double h;
} __m128i __attribute__((aligned(16)));

static inline __m128i _mm_set1_epi8(int8_t val)
{
    __m128i v;
    double z;

    __asm__ volatile (
        "ins %[v], %[v], 8, 8 \n\t"
        "xor %[z], %[z], %[z] \n\t"
        "mtc1 %[v], %[l] \n\t"
        "pshufh %[l], %[l], %[z] \n\t"
        "mov.d %[h], %[l] \n\t"
        :[l]"=&f"(v.l), [h]"=&f"(v.h), [z]"=&f"(z)
        :[v]"r"(val)
    );

    return v;
}

static inline __m128i _mm_set1_epi16(int16_t val)
{
    __m128i v;
    double z;

    __asm__ volatile (
        "xor %[z], %[z], %[z] \n\t"
        "mtc1 %[v], %[l] \n\t"
        "pshufh %[l], %[l], %[z] \n\t"
        "mov.d %[h], %[l] \n\t"
        :[l]"=&f"(v.l), [h]"=&f"(v.h), [z]"=&f"(z)
        :[v]"r"(val)
    );

    return v;
}

static inline __m128i _mm_set1_epi32(int32_t val)
{
    __m128i v;

    __asm__ volatile (
        "mtc1 %[v], %[l] \n\t"
        "punpcklwd %[l], %[l], %[l] \n\t"
        "mov.d %[h], %[l] \n\t"
        :[l]"=&f"(v.l), [h]"=&f"(v.h)
        :[v]"r"(val)
    );

    return v;
}

static inline __m128i _mm_setr_epi8(int8_t a, int8_t b, int8_t c, int8_t d,
                                    int8_t e, int8_t f, int8_t g, int8_t h,
                                    int8_t i, int8_t j, int8_t k, int8_t l,
                                    int8_t m, int8_t n, int8_t o, int8_t p)
{
    __m128i v;

    __asm__ volatile (
        "dins %[a], %[b], 8, 8 \n\t"
        "dins %[a], %[c], 16, 8 \n\t"
        "dins %[a], %[d], 24, 8 \n\t"
        "dins %[a], %[e], 32, 8 \n\t"
        "dins %[a], %[f], 40, 8 \n\t"
        "dins %[a], %[g], 48, 8 \n\t"
        "dins %[a], %[h], 56, 8 \n\t"
        "dins %[i], %[j], 8, 8 \n\t"
        "dins %[i], %[k], 16, 8 \n\t"
        "dins %[i], %[l], 24, 8 \n\t"
        "dins %[i], %[m], 32, 8 \n\t"
        "dins %[i], %[n], 40, 8 \n\t"
        "dins %[i], %[o], 48, 8 \n\t"
        "dins %[i], %[p], 56, 8 \n\t"
        "dmtc1 %[a], %[vl] \n\t"
        "dmtc1 %[i], %[vh] \n\t"
        :[vl]"=&f"(v.l), [vh]"=&f"(v.h),
         [a]"+&r"(a), [i]"+&r"(i)
        :[b]"r"(b), [c]"r"(c), [d]"r"(d), [e]"r"(e), [f]"r"(f), [g]"r"(g), [h]"r"(h),
         [j]"r"(j), [k]"r"(k), [l]"r"(l), [m]"r"(m), [n]"r"(n), [o]"r"(o), [p]"r"(p)
    );

    return v;
}

static inline __m128i _mm_set_epi8(int8_t a, int8_t b, int8_t c, int8_t d,
                                    int8_t e, int8_t f, int8_t g, int8_t h,
                                    int8_t i, int8_t j, int8_t k, int8_t l,
                                    int8_t m, int8_t n, int8_t o, int8_t p)
{
    return _mm_setr_epi8(p, o, n, m, l, k, j, i, h, g, f, e, d, c, b, a);;
}

static inline __m128i _mm_setr_epi16(int16_t a, int16_t b, int16_t c, int16_t d,
                                     int16_t e, int16_t f, int16_t g, int16_t h)
{
    __m128i v;

    __asm__ volatile (
        "dins %[a], %[b], 16, 16 \n\t"
        "dins %[a], %[c], 32, 16 \n\t"
        "dins %[a], %[d], 48, 16 \n\t"
        "dins %[e], %[f], 16, 16 \n\t"
        "dins %[e], %[g], 32, 16 \n\t"
        "dins %[e], %[h], 48, 16 \n\t"
        "dmtc1 %[a], %[vl] \n\t"
        "dmtc1 %[e], %[vh] \n\t"
        :[vl]"=&f"(v.l), [vh]"=&f"(v.h),
         [a]"+&r"(a), [e]"+&r"(e)
        :[b]"r"(b), [c]"r"(c), [d]"r"(d),
         [f]"r"(f), [g]"r"(g), [h]"r"(h)
    );

    return v;
}

static inline __m128i _mm_set_epi16(int16_t a, int16_t b, int16_t c, int16_t d,
                                     int16_t e, int16_t f, int16_t g, int16_t h)
{
    return _mm_setr_epi16(h, g, f, e, d, c, b, a);
}

static inline __m128i _mm_setr_epi32(int32_t a, int32_t b, int32_t c, int32_t d)
{
    __m128i v;

    __asm__ volatile (
        "mtc1 %[a], %[l] \n\t"
        "mthc1 %[b], %[l] \n\t"
        "mtc1 %[c], %[h] \n\t"
        "mthc1 %[d], %[h] \n\t"
        :[l]"=&f"(v.l), [h]"=&f"(v.h)
        :[a]"r"(a), [b]"r"(b), [c]"r"(c), [d]"r"(d)
    );

    return v;
}

static inline __m128i _mm_set_epi32(int32_t a, int32_t b, int32_t c, int32_t d)
{
    return _mm_setr_epi32(d, c, b, a);
}

static inline __m128i _mm_cvtsi32_si128(int32_t a)
{
    __m128i v;

    __asm__ volatile (
        "mtc1 %[a], %[l] \n\t"
        "xor %[h], %[h], %[h] \n\t"
        :[l]"=&f"(v.l), [h]"=&f"(v.h)
        :[a]"r"(a)
    );

    return v;
}

static inline int32_t _mm_cvtsi128_si32(__m128i a)
{
    int32_t v;

    __asm__ volatile (
        "mfc1 %[v], %[l] \n\t"
        :[v]"=&r"(v)
        :[l]"f"(a.l)
    );

    return v;
}

static inline __m128i _mm_setzero_si128(void)
{
    __m128i v;

    __asm__ volatile (
        "xor %[l], %[l], %[l] \n\t"
        "xor %[h], %[h], %[h] \n\t"
        :[l]"=&f"(v.l), [h]"=&f"(v.h)
    );

    return v;
}

static inline __m128i _mm_loadl_epi64(const __m128i*ptr)
{
    __m128i v;

    __asm__ volatile (
        "gsldlc1 %[l], 0x7(%[p]) \n\t"
        "gsldrc1 %[l], 0x0(%[p]) \n\t"
        "xor %[h], %[h], %[h] \n\t"
        :[l]"=&f"(v.l), [h]"=&f"(v.h)
        :[p]"r"(ptr)
    );

    return v;
}

static inline __m128i _mm_load_si128(const __m128i*ptr)
{
    __m128i v;

    __asm__ volatile (
        "gslqc1 %[h], %[l], (%[p]) \n\t"
        :[l]"=&f"(v.l), [h]"=&f"(v.h)
        :[p]"r"(ptr)
    );

    return v;
}

static inline __m128i _mm_loadu_si128(const __m128i*ptr)
{
    __m128i v;

    __asm__ volatile (
        "gsldlc1 %[l], 0x7(%[p]) \n\t"
        "gsldrc1 %[l], 0x0(%[p]) \n\t"
        "gsldlc1 %[h], 0xf(%[p]) \n\t"
        "gsldrc1 %[h], 0x8(%[p]) \n\t"
        :[l]"=&f"(v.l), [h]"=&f"(v.h)
        :[p]"r"(ptr)
    );

    return v;
}

static inline void _mm_storel_epi64(__m128i*ptr, __m128i v)
{
    __asm__ volatile (
        "gssdlc1 %[l], 0x7(%[p]) \n\t"
        "gssdrc1 %[l], 0x0(%[p]) \n\t"
        ::[l]"f"(v.l), [p]"r"(ptr)
        :"memory"
    );
}

static inline void _mm_store_si128(__m128i*ptr, __m128i v)
{
    __asm__ volatile (
        "gssqc1 %[h], %[l], (%[p]) \n\t"
        ::[l]"f"(v.l), [h]"f"(v.h), [p]"r"(ptr)
        :"memory"
    );
}

static inline void _mm_storeu_si128(__m128i*ptr, __m128i v)
{
    __asm__ volatile (
        "gssdlc1 %[l], 0x7(%[p]) \n\t"
        "gssdrc1 %[l], 0x0(%[p]) \n\t"
        "gssdlc1 %[h], 0xf(%[p]) \n\t"
        "gssdrc1 %[h], 0x8(%[p]) \n\t"
        ::[l]"f"(v.l), [h]"f"(v.h), [p]"r"(ptr)
        :"memory"
    );
}

static inline __m128i _mm_add_epi8(__m128i a, __m128i b)
{
    __m128i v;

    __asm__ volatile (
        "paddb %[l], %[al], %[bl] \n\t"
        "paddb %[h], %[ah], %[bh] \n\t"
        :[l]"=&f"(v.l), [h]"=&f"(v.h)
        :[al]"f"(a.l), [ah]"f"(a.h), [bl]"f"(b.l), [bh]"f"(b.h)
    );

    return v;
}

static inline __m128i _mm_adds_epu8(__m128i a, __m128i b)
{
    __m128i v;

    __asm__ volatile (
        "paddusb %[l], %[al], %[bl] \n\t"
        "paddusb %[h], %[ah], %[bh] \n\t"
        :[l]"=&f"(v.l), [h]"=&f"(v.h)
        :[al]"f"(a.l), [ah]"f"(a.h), [bl]"f"(b.l), [bh]"f"(b.h)
    );

    return v;
}

static inline __m128i _mm_add_epi16(__m128i a, __m128i b)
{
    __m128i v;

    __asm__ volatile (
        "paddh %[l], %[al], %[bl] \n\t"
        "paddh %[h], %[ah], %[bh] \n\t"
        :[l]"=&f"(v.l), [h]"=&f"(v.h)
        :[al]"f"(a.l), [ah]"f"(a.h), [bl]"f"(b.l), [bh]"f"(b.h)
    );

    return v;
}

static inline __m128i _mm_add_epi32(__m128i a, __m128i b)
{
    __m128i v;

    __asm__ volatile (
        "paddw %[l], %[al], %[bl] \n\t"
        "paddw %[h], %[ah], %[bh] \n\t"
        :[l]"=&f"(v.l), [h]"=&f"(v.h)
        :[al]"f"(a.l), [ah]"f"(a.h), [bl]"f"(b.l), [bh]"f"(b.h)
    );

    return v;
}

static inline __m128i _mm_sub_epi8(__m128i a, __m128i b)
{
    __m128i v;

    __asm__ volatile (
        "psubb %[l], %[al], %[bl] \n\t"
        "psubb %[h], %[ah], %[bh] \n\t"
        :[l]"=&f"(v.l), [h]"=&f"(v.h)
        :[al]"f"(a.l), [ah]"f"(a.h), [bl]"f"(b.l), [bh]"f"(b.h)
    );

    return v;
}

static inline __m128i _mm_sub_epi16(__m128i a, __m128i b)
{
    __m128i v;

    __asm__ volatile (
        "psubh %[l], %[al], %[bl] \n\t"
        "psubh %[h], %[ah], %[bh] \n\t"
        :[l]"=&f"(v.l), [h]"=&f"(v.h)
        :[al]"f"(a.l), [ah]"f"(a.h), [bl]"f"(b.l), [bh]"f"(b.h)
    );

    return v;
}

static inline __m128i _mm_sub_epi32(__m128i a, __m128i b)
{
    __m128i v;

    __asm__ volatile (
        "psubw %[l], %[al], %[bl] \n\t"
        "psubw %[h], %[ah], %[bh] \n\t"
        :[l]"=&f"(v.l), [h]"=&f"(v.h)
        :[al]"f"(a.l), [ah]"f"(a.h), [bl]"f"(b.l), [bh]"f"(b.h)
    );

    return v;
}

static inline __m128i _mm_mullo_epi16(__m128i a, __m128i b)
{
    __m128i v;

    __asm__ volatile (
        "pmullh %[l], %[al], %[bl] \n\t"
        "pmullh %[h], %[ah], %[bh] \n\t"
        :[l]"=&f"(v.l), [h]"=&f"(v.h)
        :[al]"f"(a.l), [ah]"f"(a.h), [bl]"f"(b.l), [bh]"f"(b.h)
    );

    return v;
}

static inline __m128i _mm_mulhi_epi16(__m128i a, __m128i b)
{
    __m128i v;

    __asm__ volatile (
        "pmulhh %[l], %[al], %[bl] \n\t"
        "pmulhh %[h], %[ah], %[bh] \n\t"
        :[l]"=&f"(v.l), [h]"=&f"(v.h)
        :[al]"f"(a.l), [ah]"f"(a.h), [bl]"f"(b.l), [bh]"f"(b.h)
    );

    return v;
}

static inline __m128i _mm_mulhi_epu16(__m128i a, __m128i b)
{
    __m128i v;

    __asm__ volatile (
        "pmulhuh %[l], %[al], %[bl] \n\t"
        "pmulhuh %[h], %[ah], %[bh] \n\t"
        :[l]"=&f"(v.l), [h]"=&f"(v.h)
        :[al]"f"(a.l), [ah]"f"(a.h), [bl]"f"(b.l), [bh]"f"(b.h)
    );

    return v;
}

static inline __m128i _mm_mul_epu32(__m128i a, __m128i b)
{
    __m128i v;

    __asm__ volatile (
        "pmuluw %[l], %[al], %[bl] \n\t"
        "pmuluw %[h], %[ah], %[bh] \n\t"
        :[l]"=&f"(v.l), [h]"=&f"(v.h)
        :[al]"f"(a.l), [ah]"f"(a.h), [bl]"f"(b.l), [bh]"f"(b.h)
    );

    return v;
}

static inline __m128i _mm_and_si128(__m128i a, __m128i b)
{
    __m128i v;

    __asm__ volatile (
        "and %[l], %[al], %[bl] \n\t"
        "and %[h], %[ah], %[bh] \n\t"
        :[l]"=&f"(v.l), [h]"=&f"(v.h)
        :[al]"f"(a.l), [ah]"f"(a.h), [bl]"f"(b.l), [bh]"f"(b.h)
    );

    return v;
}

static inline __m128i _mm_andnot_si128(__m128i a, __m128i b)
{
    __m128i v;

    __asm__ volatile (
        "pandn %[l], %[al], %[bl] \n\t"
        "pandn %[h], %[ah], %[bh] \n\t"
        :[l]"=&f"(v.l), [h]"=&f"(v.h)
        :[al]"f"(a.l), [ah]"f"(a.h), [bl]"f"(b.l), [bh]"f"(b.h)
    );

    return v;
}

static inline __m128i _mm_or_si128(__m128i a, __m128i b)
{
    __m128i v;

    __asm__ volatile (
        "or %[l], %[al], %[bl] \n\t"
        "or %[h], %[ah], %[bh] \n\t"
        :[l]"=&f"(v.l), [h]"=&f"(v.h)
        :[al]"f"(a.l), [ah]"f"(a.h), [bl]"f"(b.l), [bh]"f"(b.h)
    );

    return v;
}

static inline __m128i _mm_xor_si128(__m128i a, __m128i b)
{
    __m128i v;

    __asm__ volatile (
        "xor %[l], %[al], %[bl] \n\t"
        "xor %[h], %[ah], %[bh] \n\t"
        :[l]"=&f"(v.l), [h]"=&f"(v.h)
        :[al]"f"(a.l), [ah]"f"(a.h), [bl]"f"(b.l), [bh]"f"(b.h)
    );

    return v;
}

static inline __m128i _mm_slli_epi16(__m128i a, int32_t shift)
{
    __m128i v;
    double s;

    *(uint64_t *) &s = shift;

    __asm__ volatile (
        "psllh %[l], %[al], %[s] \n\t"
        "psllh %[h], %[ah], %[s] \n\t"
        :[l]"=&f"(v.l), [h]"=&f"(v.h)
        :[al]"f"(a.l), [ah]"f"(a.h), [s]"f"(s)
    );

    return v;
}

static inline __m128i _mm_slli_epi32(__m128i a, int32_t shift)
{
    __m128i v;
    double s;

    *(uint64_t *) &s = shift;

    __asm__ volatile (
        "psllw %[l], %[al], %[s] \n\t"
        "psllw %[h], %[ah], %[s] \n\t"
        :[l]"=&f"(v.l), [h]"=&f"(v.h)
        :[al]"f"(a.l), [ah]"f"(a.h), [s]"f"(s)
    );

    return v;
}

static inline __m128i _mm_srli_epi16(__m128i a, int32_t shift)
{
    __m128i v;
    double s;

    *(uint64_t *) &s = shift;

    __asm__ volatile (
        "psrlh %[l], %[al], %[s] \n\t"
        "psrlh %[h], %[ah], %[s] \n\t"
        :[l]"=&f"(v.l), [h]"=&f"(v.h)
        :[al]"f"(a.l), [ah]"f"(a.h), [s]"f"(s)
    );

    return v;
}

static inline __m128i _mm_srli_epi32(__m128i a, int32_t shift)
{
    __m128i v;
    double s;

    *(uint64_t *) &s = shift;

    __asm__ volatile (
        "psrlw %[l], %[al], %[s] \n\t"
        "psrlw %[h], %[ah], %[s] \n\t"
        :[l]"=&f"(v.l), [h]"=&f"(v.h)
        :[al]"f"(a.l), [ah]"f"(a.h), [s]"f"(s)
    );

    return v;
}

static inline __m128i _mm_srli_si128(__m128i a, int32_t shift)
{
    __m128i v;
    double s, t;

    *(uint64_t *) &s = shift;
    *(uint64_t *) &t = 64 - shift;

    __asm__ volatile (
        "dsll %[t], %[ah], %[t] \n\t"
        "dsrl %[h], %[ah], %[s] \n\t"
        "dsrl %[l], %[al], %[s] \n\t"
        "or %[l], %[l], %[t] \n\t"
        :[l]"=&f"(v.l), [h]"=&f"(v.h), [t]"+&f"(t)
        :[al]"f"(a.l), [ah]"f"(a.h), [s]"f"(s)
    );

    return v;
}

static inline __m128i _mm_srai_epi16(__m128i a, int32_t shift)
{
    __m128i v;
    double s;

    *(uint64_t *) &s = shift;

    __asm__ volatile (
        "psrah %[l], %[al], %[s] \n\t"
        "psrah %[h], %[ah], %[s] \n\t"
        :[l]"=&f"(v.l), [h]"=&f"(v.h)
        :[al]"f"(a.l), [ah]"f"(a.h), [s]"f"(s)
    );

    return v;
}

static inline __m128i _mm_srai_epi32(__m128i a, int32_t shift)
{
    __m128i v;
    double s;

    *(uint64_t *) &s = shift;

    __asm__ volatile (
        "psraw %[l], %[al], %[s] \n\t"
        "psraw %[h], %[ah], %[s] \n\t"
        :[l]"=&f"(v.l), [h]"=&f"(v.h)
        :[al]"f"(a.l), [ah]"f"(a.h), [s]"f"(s)
    );

    return v;
}

static inline __m128i _mm_shufflelo_epi16(__m128i a, int32_t imm)
{
    __m128i v;
    double s;

    *(uint64_t *) &s = imm;

    __asm__ volatile (
        "pshufh %[l], %[al], %[s] \n\t"
        "mov.d %[h], %[ah] \n\t"
        :[l]"=&f"(v.l), [h]"=&f"(v.h)
        :[al]"f"(a.l), [ah]"f"(a.h), [s]"f"(s)
    );

    return v;
}

#define _MM_SHUFFLE(z, y, x, w) ((z << 6) | (y << 4) | (x << 2) | w)

static inline __m128i _mm_shufflehi_epi16(__m128i a, int32_t imm)
{
    __m128i v;
    double s;

    *(uint64_t *) &s = imm;

    __asm__ volatile (
        "mov.d %[l], %[al] \n\t"
        "pshufh %[h], %[ah], %[s] \n\t"
        :[l]"=&f"(v.l), [h]"=&f"(v.h)
        :[al]"f"(a.l), [ah]"f"(a.h), [s]"f"(s)
    );

    return v;
}

static inline __m128i _mm_shuffle_epi32_0000(__m128i a)
{
    __m128i v;
    uint64_t t;

    __asm__ volatile (
        "mfc1 %[t], %[al] \n\t"
        "mov.d %[l], %[al] \n\t"
        "mthc1 %[t], %[l] \n\t"
        "mov.d %[h], %[l] \n\t"
        :[l]"=&f"(v.l), [h]"=&f"(v.h),
         [t]"=&r"(t)
        :[al]"f"(a.l), [ah]"f"(a.h)
    );

    return v;
}

static inline __m128i _mm_shuffle_epi32_0020(__m128i a)
{
    __m128i v;
    uint64_t t;

    __asm__ volatile (
        "mfc1 %[t], %[ah] \n\t"
        "mov.d %[l], %[al] \n\t"
        "mov.d %[h], %[al] \n\t"
        "mthc1 %[t], %[l] \n\t"
        "mfc1 %[t], %[al] \n\t"
        "mthc1 %[t], %[h] \n\t"
        :[l]"=&f"(v.l), [h]"=&f"(v.h),
         [t]"=&r"(t)
        :[al]"f"(a.l), [ah]"f"(a.h)
    );

    return v;
}

static inline __m128i _mm_shuffle_epi32_3232(__m128i a)
{
    __m128i v;

    __asm__ volatile (
        "mov.d %[l], %[ah] \n\t"
        "mov.d %[h], %[ah] \n\t"
        :[l]"=&f"(v.l), [h]"=&f"(v.h)
        :[al]"f"(a.l), [ah]"f"(a.h)
    );

    return v;
}

static inline __m128i _mm_min_epu8(__m128i a, __m128i b)
{
    __m128i v;

    __asm__ volatile (
        "pminub %[l], %[al], %[bl] \n\t"
        "pminub %[h], %[ah], %[bh] \n\t"
        :[l]"=&f"(v.l), [h]"=&f"(v.h)
        :[al]"f"(a.l), [ah]"f"(a.h), [bl]"f"(b.l), [bh]"f"(b.h)
    );

    return v;
}

static inline __m128i _mm_min_epi16(__m128i a, __m128i b)
{
    __m128i v;

    __asm__ volatile (
        "pminsh %[l], %[al], %[bl] \n\t"
        "pminsh %[h], %[ah], %[bh] \n\t"
        :[l]"=&f"(v.l), [h]"=&f"(v.h)
        :[al]"f"(a.l), [ah]"f"(a.h), [bl]"f"(b.l), [bh]"f"(b.h)
    );

    return v;
}

static inline __m128i _mm_max_epu8(__m128i a, __m128i b)
{
    __m128i v;

    __asm__ volatile (
        "pmaxub %[l], %[al], %[bl] \n\t"
        "pmaxub %[h], %[ah], %[bh] \n\t"
        :[l]"=&f"(v.l), [h]"=&f"(v.h)
        :[al]"f"(a.l), [ah]"f"(a.h), [bl]"f"(b.l), [bh]"f"(b.h)
    );

    return v;
}

static inline __m128i _mm_max_epi16(__m128i a, __m128i b)
{
    __m128i v;

    __asm__ volatile (
        "pmaxsh %[l], %[al], %[bl] \n\t"
        "pmaxsh %[h], %[ah], %[bh] \n\t"
        :[l]"=&f"(v.l), [h]"=&f"(v.h)
        :[al]"f"(a.l), [ah]"f"(a.h), [bl]"f"(b.l), [bh]"f"(b.h)
    );

    return v;
}

static inline __m128i _mm_cmpeq_epi8(__m128i a, __m128i b)
{
    __m128i v;

    __asm__ volatile (
        "pcmpeqb %[l], %[al], %[bl] \n\t"
        "pcmpeqb %[h], %[ah], %[bh] \n\t"
        :[l]"=&f"(v.l), [h]"=&f"(v.h)
        :[al]"f"(a.l), [ah]"f"(a.h), [bl]"f"(b.l), [bh]"f"(b.h)
    );

    return v;
}

static inline __m128i _mm_cmpeq_epi16(__m128i a, __m128i b)
{
    __m128i v;

    __asm__ volatile (
        "pcmpeqh %[l], %[al], %[bl] \n\t"
        "pcmpeqh %[h], %[ah], %[bh] \n\t"
        :[l]"=&f"(v.l), [h]"=&f"(v.h)
        :[al]"f"(a.l), [ah]"f"(a.h), [bl]"f"(b.l), [bh]"f"(b.h)
    );

    return v;
}

static inline __m128i _mm_cmpeq_epi32(__m128i a, __m128i b)
{
    __m128i v;

    __asm__ volatile (
        "pcmpeqw %[l], %[al], %[bl] \n\t"
        "pcmpeqw %[h], %[ah], %[bh] \n\t"
        :[l]"=&f"(v.l), [h]"=&f"(v.h)
        :[al]"f"(a.l), [ah]"f"(a.h), [bl]"f"(b.l), [bh]"f"(b.h)
    );

    return v;
}

static inline __m128i _mm_cmplt_epi8(__m128i a, __m128i b)
{
    __m128i v;

    __asm__ volatile (
        "pcmpgtb %[l], %[bl], %[al] \n\t"
        "pcmpgtb %[h], %[bh], %[ah] \n\t"
        :[l]"=&f"(v.l), [h]"=&f"(v.h)
        :[al]"f"(a.l), [ah]"f"(a.h), [bl]"f"(b.l), [bh]"f"(b.h)
    );

    return v;
}

static inline __m128i _mm_cmplt_epi32(__m128i a, __m128i b)
{
    __m128i v;

    __asm__ volatile (
        "pcmpgtw %[l], %[bl], %[al] \n\t"
        "pcmpgtw %[h], %[bh], %[ah] \n\t"
        :[l]"=&f"(v.l), [h]"=&f"(v.h)
        :[al]"f"(a.l), [ah]"f"(a.h), [bl]"f"(b.l), [bh]"f"(b.h)
    );

    return v;
}

static inline __m128i _mm_cmpgt_epi32(__m128i a, __m128i b)
{
    __m128i v;

    __asm__ volatile (
        "pcmpgtw %[l], %[al], %[bl] \n\t"
        "pcmpgtw %[h], %[ah], %[bh] \n\t"
        :[l]"=&f"(v.l), [h]"=&f"(v.h)
        :[al]"f"(a.l), [ah]"f"(a.h), [bl]"f"(b.l), [bh]"f"(b.h)
    );

    return v;
}

static inline __m128i _mm_packus_epi16(__m128i a, __m128i b)
{
    __m128i v;
    double t;

    __asm__ volatile (
        "packushb %[t], %[ah], %[bh] \n\t"
        "packushb %[l], %[al], %[bl] \n\t"
        "punpckhwd %[h], %[l], %[t] \n\t"
        "punpcklwd %[l], %[l], %[t] \n\t"
        :[l]"=&f"(v.l), [h]"=&f"(v.h), [t]"=&f"(t)
        :[al]"f"(a.l), [ah]"f"(a.h), [bl]"f"(b.l), [bh]"f"(b.h)
    );

    return v;
}

static inline __m128i _mm_packs_epi32(__m128i a, __m128i b)
{
    __m128i v;
    double t;

    __asm__ volatile (
        "packsswh %[t], %[ah], %[bh] \n\t"
        "packsswh %[l], %[al], %[bl] \n\t"
        "punpckhwd %[h], %[l], %[t] \n\t"
        "punpcklwd %[l], %[l], %[t] \n\t"
        :[l]"=&f"(v.l), [h]"=&f"(v.h), [t]"=&f"(t)
        :[al]"f"(a.l), [ah]"f"(a.h), [bl]"f"(b.l), [bh]"f"(b.h)
    );

    return v;
}

static inline __m128i _mm_unpacklo_epi8(__m128i a, __m128i b)
{
    __m128i v;

    __asm__ volatile (
        "punpckhbh %[h], %[al], %[bl] \n\t"
        "punpcklbh %[l], %[al], %[bl] \n\t"
        :[l]"=&f"(v.l), [h]"=&f"(v.h)
        :[al]"f"(a.l), [bl]"f"(b.l)
    );

    return v;
}

static inline __m128i _mm_unpacklo_epi16(__m128i a, __m128i b)
{
    __m128i v;

    __asm__ volatile (
        "punpckhhw %[h], %[al], %[bl] \n\t"
        "punpcklhw %[l], %[al], %[bl] \n\t"
        :[l]"=&f"(v.l), [h]"=&f"(v.h)
        :[al]"f"(a.l), [bl]"f"(b.l)
    );

    return v;
}

static inline __m128i _mm_unpacklo_epi32(__m128i a, __m128i b)
{
    __m128i v;

    __asm__ volatile (
        "punpckhwd %[h], %[al], %[bl] \n\t"
        "punpcklwd %[l], %[al], %[bl] \n\t"
        :[l]"=&f"(v.l), [h]"=&f"(v.h)
        :[al]"f"(a.l), [bl]"f"(b.l)
    );

    return v;
}

static inline __m128i _mm_unpacklo_epi64(__m128i a, __m128i b)
{
    __m128i v;

    __asm__ volatile (
        "mov.d %[l], %[al] \n\t"
        "mov.d %[h], %[bl] \n\t"
        :[l]"=&f"(v.l), [h]"=&f"(v.h)
        :[al]"f"(a.l), [bl]"f"(b.l)
    );

    return v;
}

static inline __m128i _mm_unpackhi_epi8(__m128i a, __m128i b)
{
    __m128i v;

    __asm__ volatile (
        "punpcklbh %[l], %[ah], %[bh] \n\t"
        "punpckhbh %[h], %[ah], %[bh] \n\t"
        :[l]"=&f"(v.l), [h]"=&f"(v.h)
        :[ah]"f"(a.h), [bh]"f"(b.h)
    );

    return v;
}

static inline __m128i _mm_unpackhi_epi16(__m128i a, __m128i b)
{
    __m128i v;

    __asm__ volatile (
        "punpcklhw %[l], %[ah], %[bh] \n\t"
        "punpckhhw %[h], %[ah], %[bh] \n\t"
        :[l]"=&f"(v.l), [h]"=&f"(v.h)
        :[ah]"f"(a.h), [bh]"f"(b.h)
    );

    return v;
}

static inline __m128i _mm_unpackhi_epi32(__m128i a, __m128i b)
{
    __m128i v;

    __asm__ volatile (
        "punpcklwd %[l], %[ah], %[bh] \n\t"
        "punpckhwd %[h], %[ah], %[bh] \n\t"
        :[l]"=&f"(v.l), [h]"=&f"(v.h)
        :[ah]"f"(a.h), [bh]"f"(b.h)
    );

    return v;
}

static inline int32_t _mm_movemask_epi8(__m128i a)
{
    int32_t v;

    __asm__ volatile (
        "pmovmskb %[al], %[al] \n\t"
        "pmovmskb %[ah], %[ah] \n\t"
        "punpcklbh %[al], %[al], %[ah] \n\t"
        "mfc1 %[v], %[al] \n\t"
        :[v]"=&r"(v), [al]"+&f"(a.l), [ah]"+&f"(a.h)
    );

    return v;
}

#endif /* __MMI_HELPERS_H__ */

