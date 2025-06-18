//#ifndef __SGL_UI_H
//#define __SGL_UI_H

//#include "sgl.h"
//#include "list.h"
//#include "dsal.h"
//#include <stdlib.h>

//#define SGL_UI_FLAG_VISIBLE 0x01

//typedef enum
//{
//    SGL_UI_TYPE_RECT,
//    SGL_UI_TYPE_ROUNDRECT,
//    SGL_UI_TYPE_STRING,
//    SGL_UI_TYPE_MONO_BITMAP,
//    SGL_UI_TYPE_CIRCLE,
//    SGL_UI_TYPE_ELLIPSE,
//    SGL_UI_TYPE_LIST,
//} sgl_ui_type_t;

//typedef struct
//{
//    int x;
//    int y;
//    int w;
//    int h;
//    int r;
//    uint32_t color;
//} sgl_ui_base_t;

//typedef struct sgl_widget_t
//{
//    sgl_ui_base_t base;
//    struct sgl_widget_t *parent;
//    dsal_list_handle_t son;
//    sgl_ui_type_t type;
//    void *param;
//    uint8_t flag;
//} sgl_widget_t, *sgl_widget_handle_t;

//typedef struct
//{
//    sgl_t *sgl;
//    sgl_widget_t act_screen;
//    int fps;
//} sgl_ui_t;

//void sgl_ui_init(sgl_ui_t *ui, sgl_t *sgl);
//void sgl_ui_handler(sgl_ui_t *ui);
//void sgl_ui_proc(sgl_ui_t *ui);

//#endif
