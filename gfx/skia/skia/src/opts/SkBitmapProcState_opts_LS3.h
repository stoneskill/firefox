/*
 * Copyright 2017 The Android Open Source Project
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkBitmapProcState_opts_LS3_DEFINED
#define SkBitmapProcState_opts_LS3_DEFINED

#include "SkBitmapProcState.h"

void S32_opaque_D32_filter_DX_LS3(const SkBitmapProcState& s,
                                   const uint32_t* xy,
                                   int count, uint32_t* colors);
void S32_alpha_D32_filter_DX_LS3(const SkBitmapProcState& s,
                                  const uint32_t* xy,
                                  int count, uint32_t* colors);
void ClampX_ClampY_filter_scale_LS3(const SkBitmapProcState& s, uint32_t xy[],
                                     int count, int x, int y);
void ClampX_ClampY_nofilter_scale_LS3(const SkBitmapProcState& s,
                                       uint32_t xy[], int count, int x, int y);
void ClampX_ClampY_filter_affine_LS3(const SkBitmapProcState& s,
                                      uint32_t xy[], int count, int x, int y);
void ClampX_ClampY_nofilter_affine_LS3(const SkBitmapProcState& s,
                                        uint32_t xy[], int count, int x, int y);

#endif
