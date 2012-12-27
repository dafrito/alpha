#ifndef ALPHA_ARRAYVOXMAP_HEADER
#define ALPHA_ARRAYVOXMAP_HEADER

#include "Vector3.hpp"
#include <vector>

namespace nt {

template <class Voxel>
class ArrayVoxmap
{
    std::vector<Voxel> _voxmap;
    Vector3<int> _size;
public:
    ArrayVoxmap() :
        _voxmap(),
        _size()
    {}
    ArrayVoxmap(const Vector3<int>& size) :
        _voxmap(size.x() * size.y() * size.z()),
        _size(size)
    {}

    const Vector3<int>& size() const;

    Voxel& get(const int x, const int y, const int z);
    const Voxel& get(const int x, const int y, const int z) const;

    void set(const int x, const int y, const int z, const Voxel& voxel);

    void resize(const Vector3<int>& size);
};

template <class Voxel>
const Vector3<int>& ArrayVoxmap<Voxel>::size() const
{
    return _size;
}

template <class Voxel>
void ArrayVoxmap<Voxel>::resize(const Vector3<int>& size)
{
    _voxmap.clear();
    _size.set(0, 0, 0);
    _voxmap.resize(size.x() * size.y() * size.z());
    _size = size;
}

template <class Voxel>
const Voxel& ArrayVoxmap<Voxel>::get(const int x, const int y, const int z) const
{
    return _voxmap.at(x + _size.x() * y + z * _size.x() * _size.y());
}

template <class Voxel>
Voxel& ArrayVoxmap<Voxel>::get(const int x, const int y, const int z)
{
    return _voxmap.at(x + _size.x() * y + z * _size.x() * _size.y());
}

template <class Voxel>
void ArrayVoxmap<Voxel>::set(const int x, const int y, const int z, const Voxel& voxel)
{
    get(x, y, z) = voxel;
}

} // namespace nt

#endif // ALPHA_ARRAYVOXMAP_HEADER
