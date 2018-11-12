#ifndef CURSES_EX_H_
#define CURSES_EX_H_

#include <curses.h>

typedef enum {
    ALIGN_LEFT = 0x01,
    ALIGN_HCENTER = 0x02,
    ALIGN_RIGHT = 0x04,
    ALIGN_XFIXED = 0x08,
    
    ALIGN_TOP = 0x10,
    ALIGN_VCENTER = 0x20,
    ALIGN_BOTTOM = 0x40,
    ALIGN_YFIXED = 0x80,

    ALIGN_CENTER = ALIGN_HCENTER | ALIGN_VCENTER,
    ALIGN_FIXED  = ALIGN_XFIXED | ALIGN_YFIXED,
} alignment_e;

// use screen coordinates
inline int mvaddstr_ex(int y, int x, const char* str, alignment_e align, int y_off, int x_off) {
    int yy, xx;
    
    if (align & ALIGN_LEFT) xx = x_off;
    if (align & ALIGN_HCENTER) xx = (x-strlen(str))/2 + x_off;
    if (align & ALIGN_RIGHT) xx = x - strlen(str) + x_off;
    if (align & ALIGN_XFIXED) xx = x + x_off;

    if (align & ALIGN_TOP) yy = y_off;
    if (align & ALIGN_VCENTER) yy = y/2 + y_off;
    if (align & ALIGN_BOTTOM) yy = y + y_off;
    if (align & ALIGN_YFIXED) yy = y + y_off;

    return mvaddstr(yy, xx, str);
}

#endif  // CURSES_EX_H_
