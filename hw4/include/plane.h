#ifndef PLANE_H
#define PLANE_H


class plane
{
    public:
        plane();
        virtual ~plane();
        int L_x,L_y;//左上
        int R_x,R_y;//右下
        void write_into_map(int *,int,int);
    protected:
    private:
};

#endif // PLANE_H
