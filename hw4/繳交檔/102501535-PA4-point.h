#ifndef POINT_H
#define POINT_H


class point
{
    public:
        point();
        virtual ~point();
        int x;
        int y;
        int data;//0->�i�H�����a  1->��obs��ê��  2->��pin�I
        void write_into_map(point *,int,int);
    protected:
    private:
};

#endif // POINT_H
