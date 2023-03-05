#ifndef _POINT_2D_H_
#define _POINT_2D_H_

template <typename T>
class Point2D
{
    private:
        T _x, _y;
    public:
        Point2D();
        Point2D(T x, T y) noexcept;
        ~Point2D();

        void set_point(const T data_x, const T data_y);
        T get_x() const;
        T get_y() const;

        void set_x(T x);
        void set_y(T y);
};

template <typename T>
void swap_values(T &value_1, T &value_2);

#endif
