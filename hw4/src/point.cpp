#include "point.h"
#include <iostream>
point::point()
{
    //ctor
}

point::~point()
{
    //dtor
}

void point::write_into_map(point *a_map,int row,int column){
    for(int a=0;a<row;a++){
        for(int b=0;b<column;b++){
            if( b==point::y && a==point::x)
                {
                    (a_map+a*(column)+b)->data = 2;
                    (a_map+a*(column)+b)->x = a;
                    (a_map+a*(column)+b)->y = b;
//                    std::cout<<"pin row:"<<a<<" column:"<<b<<std::endl;
                }
        }
    }
}
