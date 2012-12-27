#ifndef ALPHA_BOX2_HEADER
#define ALPHA_BOX2_HEADER

#include <cmath>

namespace nt {

template <typename Scalar>
class Box2
{
    Scalar _left;
    Scalar _right;
    Scalar _top;
    Scalar _bottom;

public:
    const Scalar& left() const;
    const Scalar& right() const;
    const Scalar& top() const;
    const Scalar& bottom() const;

    const Scalar width() const;
    const Scalar height() const;

    void set(const Scalar& left, const Scalar& right, const Scalar& top, const Scalar& bottom);
    void setVertical(const Scalar& left, const Scalar& right);
    void setHorizontal(const Scalar& left, const Scalar& right);

    void setLeft(const Scalar& left);
    void setRight(const Scalar& right);
    void setTop(const Scalar& top);
    void setBottom(const Scalar& bottom);

    void clear();
};

template <typename Scalar>
const Scalar& Box2<Scalar>::left() const
{
    return _left;
}

template <typename Scalar>
const Scalar& Box2<Scalar>::right() const
{
    return _right;
}

template <typename Scalar>
const Scalar& Box2<Scalar>::top() const
{
    return _top;
}

template <typename Scalar>
const Scalar& Box2<Scalar>::bottom() const
{
    return _bottom;
}

template <typename Scalar>
const Scalar Box2<Scalar>::width() const
{
    return std::abs(right() - left());
}

template <typename Scalar>
const Scalar Box2<Scalar>::height() const
{
    return std::abs(bottom() - top());
}

template <typename Scalar>
void Box2<Scalar>::setVertical(const Scalar& top, const Scalar& bottom)
{
    setTop(top);
    setBottom(bottom);
}

template <typename Scalar>
void Box2<Scalar>::setHorizontal(const Scalar& left, const Scalar& right)
{
    setLeft(left);
    setRight(right);
}

template <typename Scalar>
void Box2<Scalar>::setLeft(const Scalar& left)
{
    _left = left;
}

template <typename Scalar>
void Box2<Scalar>::setRight(const Scalar& right)
{
    _right = right;
}

template <typename Scalar>
void Box2<Scalar>::setTop(const Scalar& top)
{
    _top = top;
};

template <typename Scalar>
void Box2<Scalar>::setBottom(const Scalar& bottom)
{
    _bottom = bottom;
};

template <typename Scalar>
void Box2<Scalar>::clear()
{
    set(0, 0, 0, 0);
}

} // namespace nt

#endif // ALPHA_BOX2_HEADER
