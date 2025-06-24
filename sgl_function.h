#ifndef __SGL_FUNCTION_H
#define __SGL_FUNCTION_H

#ifdef __cplusplus
extern "C" {
#endif

#include "sgl_core.h"

void sgl_swap_int(int *var0, int *var1);
int sgl_min(int var0, int var1);
int sgl_max(int var0, int var1);
int sgl_check_rect(int left, int top, int right, int bottom,
                   sgl_rect_t visible);
void sgl_rotated2original(int *x, int *y, int max_x, int max_y,
                          sgl_rotate_t rotate);
void sgl_original2rotated(int *x, int *y, int max_x, int max_y,
                          sgl_rotate_t rotate);
void sgl_align(int *x, int *y, int w, int h, sgl_align_t align);

#ifdef __cplusplus
}
#endif

#endif