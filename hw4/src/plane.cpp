#include "plane.h"


plane::plane()
{
    //ctor
}

plane::~plane()
{
    //dtor
}

void plane::write_into_map(point *a_map,int row,int column){
    for(int a=0;a<row;a++){
        for(int b=0;b<column;b++){
            if( (plane::L_y<=(b))&&((b)<=plane::R_y)
            &&  (plane::R_x>=(a))&&((a)>=plane::L_x) )
                {
                    (a_map+a*(column)+b)->data = 1;
                    (a_map+a*(column)+b)->x = a;
                    (a_map+a*(column)+b)->y = b;
                }
        }
    }
}
