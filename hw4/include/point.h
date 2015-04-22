#ifndef POINT_H
#define POINT_H


class point
{
    public:
        point();
        virtual ~point();
        int x;
        int y;
        void write_into_map(int *,int,int);
    protected:
    private:
};

#endif // POINT_H
