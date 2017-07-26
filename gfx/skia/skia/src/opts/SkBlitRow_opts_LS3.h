/*
 * Copyright 2017 The Android Open Source Project
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkBlitRow_opts_LS3_DEFINED
#define SkBlitRow_opts_LS3_DEFINED

#include "SkBlitRow.h"

void S32_Blend_BlitRow32_LS3(SkPMColor* SK_RESTRICT dst,
                              const SkPMColor* SK_RESTRICT src,
                              int count, U8CPU alpha);

void S32A_Blend_BlitRow32_LS3(SkPMColor* SK_RESTRICT dst,
                               const SkPMColor* SK_RESTRICT src,
                               int count, U8CPU alpha);

void Color32A_D565_LS3(uint16_t dst[], SkPMColor src, int count, int x,
                        int y);

void SkBlitLCD16Row_LS3(SkPMColor dst[], const uint16_t src[],
                         SkColor color, int width, SkPMColor);
void SkBlitLCD16OpaqueRow_LS3(SkPMColor dst[], const uint16_t src[],
                               SkColor color, int width, SkPMColor opaqueDst);

void S32_D565_Opaque_LS3(uint16_t* SK_RESTRICT dst,
                          const SkPMColor* SK_RESTRICT src, int count,
                          U8CPU alpha, int /*x*/, int /*y*/);
void S32A_D565_Opaque_LS3(uint16_t* SK_RESTRICT dst,
                           const SkPMColor* SK_RESTRICT src,
                           int count, U8CPU alpha, int /*x*/, int /*y*/);
void S32_D565_Opaque_Dither_LS3(uint16_t* SK_RESTRICT dst,
                                 const SkPMColor* SK_RESTRICT src,
                                 int count, U8CPU alpha, int x, int y);
void S32A_D565_Opaque_Dither_LS3(uint16_t* SK_RESTRICT dst,
                                  const SkPMColor* SK_RESTRICT src,
                                  int count, U8CPU alpha, int x, int y);
#endif
