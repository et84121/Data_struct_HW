#ifndef POINT_H
#define POINT_H


class point
{
    public:
        point();
        virtual ~point();
        int x;
        int y;
        int data;//0->可以走的地  1->為obs障礙物  2->為pin點
        void write_into_map(point *,int,int);
    protected:
    private:
};

#endif // POINT_H
