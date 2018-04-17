//
// Created by genshen on 4/17/18.
//

#ifndef KIWI_COLORS_H
#define KIWI_COLORS_H

#define COLOR_ESCAPE "\x1b"
#define COLOR_END "m"
#define COLOR_CLEAR      COLOR_ESCAPE "[0"  COLOR_END
/* output log front regular color */
#define COLOR_R_HEAD        COLOR_ESCAPE "[0;"
#define COLOR_R_BLACK      COLOR_R_HEAD "30"  COLOR_END
#define COLOR_R_RED        COLOR_R_HEAD "31"  COLOR_END
#define COLOR_R_GREEN      COLOR_R_HEAD "32"  COLOR_END
#define COLOR_R_ORANGE     COLOR_R_HEAD "33"  COLOR_END
#define COLOR_R_BLUE       COLOR_R_HEAD "34"  COLOR_END
#define COLOR_R_MAGENTA    COLOR_R_HEAD "35"  COLOR_END
#define COLOR_R_CYAN       COLOR_R_HEAD "36"  COLOR_END
#define COLOR_R_LIGHT_GRAY COLOR_R_HEAD "37"  COLOR_END

#endif //KIWI_COLORS_H
