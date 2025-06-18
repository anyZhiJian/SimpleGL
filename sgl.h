#ifndef __SIMPLEGL_H
#define __SIMPLEGL_H

#include <stdint.h>
#include "font.h"

#define sgl_FORMAT_STRING_BUFFERSIZE 256

#define color_mono_light 0
#define color_mono_dark 1
#define color_mono_inverse 2

typedef enum
{
    SGL_DIR_UP = 0,
    SGL_DIR_DOWN,
    SGL_DIR_LEFT,
    SGL_DIR_RIGHT,
} sgl_dir_t;

#define SGL_DIR_DEFAULT SGL_DIR_UP

/**
 * alignment:
 *
 *     up_left           up_center           up_right
 *             +-------------+-------------+
 *             |                           |
 *             |                           |
 * left_center +        center(x,y)        + right_center
 *             |                           |
 *             |                           |
 *             +-------------+-------------+
 *   down_left          down_center          down_right
 *
 */

typedef enum
{
    SGL_ALIGN_UP_LEFT = 0,
    SGL_ALIGN_UP_RIGHT,
    SGL_ALIGN_DOWN_LEFT,
    SGL_ALIGN_DOWN_RIGHT,
    SGL_ALIGN_CENTER,
    SGL_ALIGN_UP_CENTER,
    SGL_ALIGN_DOWN_CENTER,
    SGL_ALIGN_LEFT_CENTER,
    SGL_ALIGN_RIGHT_CENTER,
} sgl_align_t;

#define SGL_ALIGN_DEFAULT SGL_ALIGN_UP_LEFT

/**
 * rotate shape:坐标轴固定，图像旋转
 *
 * -------------------------
 * |rotate |   x'  |   y'  |
 * |-------|-------|-------|
 * |   0   |   x   |   y   |
 * |   90  |  w-y  |   x   |
 * |  -90  |   y   |  h-x  |
 * |  180  |  w-x  |  h-y  |
 * -------------------------
 *
 * rotate axis:图像固定，坐标轴旋转
 *
 * -------------------------
 * |rotate |   x'  |   y'  |
 * |-------|-------|-------|
 * |   0   |   x   |   y   |
 * |   90  |   y   |  w-x  |
 * |  -90  |  h-y  |   x   |
 * |  180  |  w-x  |  h-y  |
 * -------------------------
 *
 * w(width):hor_res-1  h(height):ver_res-1
 *
 */

typedef enum
{
    SGL_ROTATE_0 = 0,
    SGL_ROTATE_90,
    SGL_ROTATE_180,
    SGL_ROTATE_270,
} sgl_rotate_t;

#define SGL_ROTATE_DEFAULT SGL_ROTATE_0

typedef enum
{
    SGL_CIRCLE_UPPER_RIGHT = 0x01,
    SGL_CIRCLE_UPPER_LEFT = 0x02,
    SGL_CIRCLE_LOWER_RIGHT = 0x04,
    SGL_CIRCLE_LOWER_LEFT = 0x08,
    SGL_CIRCLE_ALL = 0xFF,
} sgl_circle_t;

typedef struct
{
    int left;
    int right;
    int top;
    int bottom;
} sgl_rect_t;

typedef struct sgl_t
{
    void *buffer;                                      // 缓冲区指针
    int buffer_size;                                   // 缓冲区大小
    int hor_res;                                       // 屏幕水平分辨率(X坐标范围的大小)
    int ver_res;                                       // 屏幕垂直分辨率(Y坐标范围的大小)
    int max_x;                                         // x坐标最大值
    int max_y;                                         // y坐标最大值
    int page_start;                                    // 页起始y坐标
    int page_width;                                    // 页宽
    int page_num;                                      // 页数
    int offset_x;                                      // x坐标偏移
    int offset_y;                                      // y坐标偏移
    sgl_rect_t page;                                   // 页矩形
    sgl_rect_t visible;                                // 可见矩形
    font_info_t font_info;                             // 字体信息
    sgl_rotate_t rotate;                               // 屏幕旋转参数
    void (*draw)(struct sgl_t *sgl);                   // 绘制回调函数
    void (*flush)(void *buffer, uint32_t buffer_size); // 发送数据回调函数
    void (*frame_start_cb)(void);                      // 帧起始回调函数
    void (*frame_end_cb)(void);                        // 帧结束回调函数
    void (*draw_piexl)(struct sgl_t *sgl,              // 绘制像素函数指针
                       int x, int y, uint32_t color);
} sgl_t;

// 初始化函数
void sgl_init(sgl_t *sgl, void *buffer, uint32_t buffer_size, uint32_t page_num, uint32_t hor_res, uint32_t ver_res);
void sgl_display(sgl_t *sgl);
void sgl_set_draw(sgl_t *sgl, void (*draw)(struct sgl_t *));
void sgl_set_flush(sgl_t *sgl, void (*flush)(void *, uint32_t));
void sgl_clear(sgl_t *sgl, uint8_t data);
// 设置函数
void sgl_set_buffer(sgl_t *sgl, void *buffer);
void sgl_set_draw_piexl(sgl_t *sgl, void (*draw_piexl)(sgl_t *, int, int, uint32_t));
void sgl_set_frame_start_cb(sgl_t *sgl, void (*frame_start_cb)(void));
void sgl_set_frame_end_cb(sgl_t *sgl, void (*frame_end_cb)(void));
void sgl_set_font(sgl_t *sgl, font_t font);
void sgl_set_screen_rotation(sgl_t *sgl, sgl_rotate_t rotate);
void sgl_paint_start(sgl_t *sgl);
void sgl_paint_end(sgl_t *sgl);
void sgl_set_visible_rect(sgl_t *sgl, int left, int top, int right, int bottom);
void sgl_reset_visible_rect(sgl_t *sgl);
void sgl_draw_piexl_mono(sgl_t *sgl, int x, int y, uint32_t color);
void sgl_draw_piexl_rgb565(sgl_t *sgl, int x, int y, uint32_t color);
// 功能函数
inline void sgl_swap_int(int *var0, int *var1);
inline int sgl_min(int var0, int var1);
inline int sgl_max(int var0, int var1);
inline int sgl_check_rect(int left, int top, int right, int bottom, sgl_rect_t visible);
inline int sgl_clip_hline(int *x, int *y, int *len, sgl_rect_t visible);
inline int sgl_clip_vline(int *x, int *y, int *len, sgl_rect_t visible);
inline void sgl_rotated2original(int *x, int *y, int max_x, int max_y, sgl_rotate_t rotate);
inline void sgl_original2rotated(int *x, int *y, int max_x, int max_y, sgl_rotate_t rotate);
inline void sgl_align(int *x, int *y, int w, int h, sgl_align_t align);
// 图型函数
void sgl_draw_point(sgl_t *sgl, int x, int y, uint32_t color);
void sgl_draw_hline(sgl_t *sgl, int x, int y, int len, uint32_t color);
void sgl_draw_vline(sgl_t *sgl, int x, int y, int len, uint32_t color);
void sgl_draw_line(sgl_t *sgl, int x0, int y0, int x1, int y1, uint32_t color);
void sgl_draw_rectangle(sgl_t *sgl, int x, int y, int w, int h, int is_filled, uint32_t color);
void sgl_draw_round_rectangle(sgl_t *sgl, int x, int y, int w, int h, int r, int is_filled, uint32_t color);
void sgl_draw_circle(sgl_t *sgl, int xc, int yc, int r, int is_filled, uint32_t color);
void sgl_draw_ellipse(sgl_t *sgl, int xc, int yc, int rx, int ry, int is_filled, uint32_t color);
void sgl_draw_outlined_circle_section(sgl_t *sgl, int xc, int yc, int r, sgl_circle_t dir, uint32_t color);
void sgl_draw_filled_circle_section(sgl_t *sgl, int xc, int yc, int r, sgl_circle_t dir, uint32_t color);
void sgl_draw_outlined_ellipse_section(sgl_t *sgl, int xc, int yc, int rx, int ry, sgl_circle_t dir, uint32_t color);
void sgl_draw_filled_ellipse_section(sgl_t *sgl, int xc, int yc, int rx, int ry, sgl_circle_t dir, uint32_t color);
// 字符函数
void sgl_show_mono_bitmap(sgl_t *sgl, int x, int y, int w, int h, const uint8_t *bitmap, sgl_dir_t dir, uint32_t color);
void sgl_show_string(sgl_t *sgl, int x, int y, const char *str, int length, sgl_align_t align, sgl_dir_t dir, uint32_t color);
int sgl_show_format_string(sgl_t *sgl, int x, int y, sgl_align_t align, sgl_dir_t dir, uint32_t color, const char *format, ...);

#endif