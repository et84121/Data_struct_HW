#ifndef PLANE_H
#define PLANE_H
#include "point.h"

class plane
{
    public:
        plane();
        virtual ~plane();
        int L_x,L_y;//左上
        int R_x,R_y;//右下
        void write_into_map(point *,int,int);
    protected:
    private:
};

#endif // PLANE_H
