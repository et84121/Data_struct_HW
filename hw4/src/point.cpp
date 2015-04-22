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

void point::write_into_map(int *a_map,int row,int column){
    for(int a=0;a<row;a++){
        for(int b=0;b<column;b++){
            if( b==point::y && a==point::x)
                {
                    *(a_map+a*(column)+b) = 2;
//                    std::cout<<"pin row:"<<a<<" column:"<<b<<std::endl;
                }
        }
    }
}
