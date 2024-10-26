#ifndef __M_UTILS_H
#define __M_UTILS_H

#define MAX_ANGLE 360

#define sign(x) (x < 0 ? -1 : (x > 0 ? 1 : 0))
extern float SINCOSTABLE[MAX_ANGLE];

#define SIN(x) (SINCOSTABLE[x%360])
#define COS(x) (SINCOSTABLE[(x+90)%360])

#endif