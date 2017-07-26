/*
 * Copyright 2017 The Android Open Source Project
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkColor_opts_LS3_DEFINED
#define SkColor_opts_LS3_DEFINED

#include "MMIHelpers.h"

#define ASSERT_EQ(a,b) SkASSERT(0xffff == _mm_movemask_epi8(_mm_cmpeq_epi8((a), (b))))

// Portable version SkAlphaMulQ is in SkColorPriv.h.
static inline __m128i SkAlphaMulQ_LS3(const __m128i& c, const __m128i& scale) {
    const __m128i mask = _mm_set1_epi32(0xFF00FF);
    __m128i s = _mm_or_si128(_mm_slli_epi32(scale, 16), scale);

    // uint32_t rb = ((c & mask) * scale) >> 8
    __m128i rb = _mm_and_si128(mask, c);
    rb = _mm_mullo_epi16(rb, s);
    rb = _mm_srli_epi16(rb, 8);

    // uint32_t ag = ((c >> 8) & mask) * scale
    __m128i ag = _mm_srli_epi16(c, 8);
    ASSERT_EQ(ag, _mm_and_si128(mask, ag));  // ag = _mm_srli_epi16(c, 8) did this for us.
    ag = _mm_mullo_epi16(ag, s);

    // (rb & mask) | (ag & ~mask)
    ASSERT_EQ(rb, _mm_and_si128(mask, rb));  // rb = _mm_srli_epi16(rb, 8) did this for us.
    ag = _mm_andnot_si128(mask, ag);
    return _mm_or_si128(rb, ag);
}
#define SkAlphaMulQ_SSE2 SkAlphaMulQ_LS3

// Fast path for SkAlphaMulQ_LS3 with a constant scale factor.
static inline __m128i SkAlphaMulQ_LS3(const __m128i& c, const unsigned scale) {
    const __m128i mask = _mm_set1_epi32(0xFF00FF);
    __m128i s = _mm_set1_epi16(scale << 8); // Move scale factor to upper byte of word.

    // With mulhi, red and blue values are already in the right place and
    // don't need to be divided by 256.
    __m128i rb = _mm_and_si128(mask, c);
    rb = _mm_mulhi_epu16(rb, s);

    __m128i ag = _mm_andnot_si128(mask, c);
    ag = _mm_mulhi_epu16(ag, s);     // Alpha and green values are in the higher byte of each word.
    ag = _mm_andnot_si128(mask, ag);

    return _mm_or_si128(rb, ag);
}
#define SkAlphaMulQ_SSE2 SkAlphaMulQ_LS3

// Portable version SkFastFourByteInterp256 is in SkColorPriv.h.
static inline __m128i SkFastFourByteInterp256_LS3(const __m128i& src, const __m128i& dst, const unsigned src_scale) {
    // Computes dst + (((src - dst)*src_scale)>>8)
    const __m128i mask = _mm_set1_epi32(0x00FF00FF);

    // Unpack the 16x8-bit source into 2 8x16-bit splayed halves.
    __m128i src_rb = _mm_and_si128(mask, src);
    __m128i src_ag = _mm_srli_epi16(src, 8);
    __m128i dst_rb = _mm_and_si128(mask, dst);
    __m128i dst_ag = _mm_srli_epi16(dst, 8);

    // Compute scaled differences.
    __m128i diff_rb = _mm_sub_epi16(src_rb, dst_rb);
    __m128i diff_ag = _mm_sub_epi16(src_ag, dst_ag);
    __m128i s = _mm_set1_epi16(src_scale);
    diff_rb = _mm_mullo_epi16(diff_rb, s);
    diff_ag = _mm_mullo_epi16(diff_ag, s);

    // Pack the differences back together.
    diff_rb = _mm_srli_epi16(diff_rb, 8);
    diff_ag = _mm_andnot_si128(mask, diff_ag);
    __m128i diff = _mm_or_si128(diff_rb, diff_ag);

    // Add difference to destination.
    return _mm_add_epi8(dst, diff);
}
#define SkFastFourByteInterp256_SSE2 SkFastFourByteInterp256_LS3

// Portable version SkPMLerp is in SkColorPriv.h
static inline __m128i SkPMLerp_LS3(const __m128i& src, const __m128i& dst, const unsigned scale) {
#ifdef SK_SUPPORT_LEGACY_BROKEN_LERP
    return _mm_add_epi8(SkAlphaMulQ_LS3(src, scale), SkAlphaMulQ_LS3(dst, 256 - scale));
#else
    return SkFastFourByteInterp256_SSE2(src, dst, scale);
#endif
}
#define SkPMLerp_SSE2 SkPMLerp_LS3

static inline __m128i SkGetPackedA32_LS3(const __m128i& src) {
#if SK_A32_SHIFT == 24                // It's very common (universal?) that alpha is the top byte.
    return _mm_srli_epi32(src, 24);   // You'd hope the compiler would remove the left shift then,
#else                                 // but I've seen Clang just do a dumb left shift of zero. :(
    __m128i a = _mm_slli_epi32(src, (24 - SK_A32_SHIFT));
    return _mm_srli_epi32(a, 24);
#endif
}
#define SkGetPackedA32_SSE2 SkGetPackedA32_LS3

static inline __m128i SkMul16ShiftRound_LS3(const __m128i& a,
                                             const __m128i& b, int shift) {
    __m128i prod = _mm_mullo_epi16(a, b);
    prod = _mm_add_epi16(prod, _mm_set1_epi16(1 << (shift - 1)));
    prod = _mm_add_epi16(prod, _mm_srli_epi16(prod, shift));
    prod = _mm_srli_epi16(prod, shift);

    return prod;
}
#define SkMul16ShiftRound_SSE2 SkMul16ShiftRound_LS3

static inline __m128i SkPackRGB16_LS3(const __m128i& r,
                                       const __m128i& g, const __m128i& b) {
    __m128i dr = _mm_slli_epi16(r, SK_R16_SHIFT);
    __m128i dg = _mm_slli_epi16(g, SK_G16_SHIFT);
    __m128i db = _mm_slli_epi16(b, SK_B16_SHIFT);

    __m128i c = _mm_or_si128(dr, dg);
    return _mm_or_si128(c, db);
}
#define SkPackRGB16_SSE2 SkPackRGB16_LS3

static inline __m128i SkPixel32ToPixel16_ToU16_LS3(const __m128i& src_pixel1,
                                                    const __m128i& src_pixel2) {
    // Calculate result r.
    __m128i r1 = _mm_srli_epi32(src_pixel1,
                                SK_R32_SHIFT + (8 - SK_R16_BITS));
    r1 = _mm_and_si128(r1, _mm_set1_epi32(SK_R16_MASK));
    __m128i r2 = _mm_srli_epi32(src_pixel2,
                                SK_R32_SHIFT + (8 - SK_R16_BITS));
    r2 = _mm_and_si128(r2, _mm_set1_epi32(SK_R16_MASK));
    __m128i r = _mm_packs_epi32(r1, r2);

    // Calculate result g.
    __m128i g1 = _mm_srli_epi32(src_pixel1,
                                SK_G32_SHIFT + (8 - SK_G16_BITS));
    g1 = _mm_and_si128(g1, _mm_set1_epi32(SK_G16_MASK));
    __m128i g2 = _mm_srli_epi32(src_pixel2,
                                SK_G32_SHIFT + (8 - SK_G16_BITS));
    g2 = _mm_and_si128(g2, _mm_set1_epi32(SK_G16_MASK));
    __m128i g = _mm_packs_epi32(g1, g2);

    // Calculate result b.
    __m128i b1 = _mm_srli_epi32(src_pixel1,
                                SK_B32_SHIFT + (8 - SK_B16_BITS));
    b1 = _mm_and_si128(b1, _mm_set1_epi32(SK_B16_MASK));
    __m128i b2 = _mm_srli_epi32(src_pixel2,
                                SK_B32_SHIFT + (8 - SK_B16_BITS));
    b2 = _mm_and_si128(b2, _mm_set1_epi32(SK_B16_MASK));
    __m128i b = _mm_packs_epi32(b1, b2);

    // Store 8 16-bit colors in dst.
    __m128i d_pixel = SkPackRGB16_LS3(r, g, b);

    return d_pixel;
}
#define SkPixel32ToPixel16_ToU16_SSE2 SkPixel32ToPixel16_ToU16_LS3

// Portable version is SkPMSrcOver in SkColorPriv.h.
static inline __m128i SkPMSrcOver_LS3(const __m128i& src, const __m128i& dst) {
    return _mm_add_epi32(src,
                         SkAlphaMulQ_LS3(dst, _mm_sub_epi32(_mm_set1_epi32(256),
                                                             SkGetPackedA32_LS3(src))));
}
#define SkPMSrcOver_SSE2 SkPMSrcOver_LS3

// Fast path for SkBlendARGB32_LS3 with a constant alpha factor.
static inline __m128i SkBlendARGB32_LS3(const __m128i& src, const __m128i& dst,
                                         const unsigned aa) {
    unsigned alpha = SkAlpha255To256(aa);
#ifdef SK_SUPPORT_LEGACY_BROKEN_LERP
     __m128i src_scale = _mm_set1_epi32(alpha);
     // SkAlpha255To256(255 - SkAlphaMul(SkGetPackedA32(src), src_scale))
     __m128i dst_scale = SkGetPackedA32_LS3(src);
     dst_scale = _mm_mullo_epi16(dst_scale, src_scale);
     dst_scale = _mm_srli_epi16(dst_scale, 8);
     dst_scale = _mm_sub_epi32(_mm_set1_epi32(256), dst_scale);

     __m128i result = SkAlphaMulQ_LS3(src, alpha);
     return _mm_add_epi8(result, SkAlphaMulQ_LS3(dst, dst_scale));
#else
    __m128i src_scale = _mm_set1_epi16(alpha);
    // SkAlphaMulInv256(SkGetPackedA32(src), src_scale)
    __m128i dst_scale = SkGetPackedA32_LS3(src);
    // High words in dst_scale are 0, so it's safe to multiply with 16-bit src_scale.
    dst_scale = _mm_mullo_epi16(dst_scale, src_scale);
    dst_scale = _mm_sub_epi32(_mm_set1_epi32(0xFFFF), dst_scale);
    dst_scale = _mm_add_epi32(dst_scale, _mm_srli_epi32(dst_scale, 8));
    dst_scale = _mm_srli_epi32(dst_scale, 8);
    // Duplicate scales into 2x16-bit pattern per pixel.
    dst_scale = _mm_shufflelo_epi16(dst_scale, _MM_SHUFFLE(2, 2, 0, 0));
    dst_scale = _mm_shufflehi_epi16(dst_scale, _MM_SHUFFLE(2, 2, 0, 0));

    const __m128i mask = _mm_set1_epi32(0x00FF00FF);

    // Unpack the 16x8-bit source/destination into 2 8x16-bit splayed halves.
    __m128i src_rb = _mm_and_si128(mask, src);
    __m128i src_ag = _mm_srli_epi16(src, 8);
    __m128i dst_rb = _mm_and_si128(mask, dst);
    __m128i dst_ag = _mm_srli_epi16(dst, 8);

    // Scale them.
    src_rb = _mm_mullo_epi16(src_rb, src_scale);
    src_ag = _mm_mullo_epi16(src_ag, src_scale);
    dst_rb = _mm_mullo_epi16(dst_rb, dst_scale);
    dst_ag = _mm_mullo_epi16(dst_ag, dst_scale);

    // Add the scaled source and destination.
    dst_rb = _mm_add_epi16(src_rb, dst_rb);
    dst_ag = _mm_add_epi16(src_ag, dst_ag);

    // Unsplay the halves back together.
    dst_rb = _mm_srli_epi16(dst_rb, 8);
    dst_ag = _mm_andnot_si128(mask, dst_ag);
    return _mm_or_si128(dst_rb, dst_ag);
#endif
}
#define SkBlendARGB32_SSE2 SkBlendARGB32_LS3

#undef ASSERT_EQ
#endif // SkColor_opts_LS3_DEFINED
