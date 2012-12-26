#ifndef ALPHA_ARRAYVOXMAP_HEADER
#define ALPHA_ARRAYVOXMAP_HEADER

#include "Vector3.hpp"
#include <vector>

namespace nt {

template <class Voxel>
class ArrayVoxmap
{
    std::vector<Voxel> _voxmap;
    const Vector3<int> _size;
public:
    ArrayVoxmap(const Vector3<int>& size);
    const Vector3<int>& size() const;
};

ArrayVoxmap(const Vector3<int>& size) :
    _voxmap(),
    _size(size)
{
    _voxmap.resize(_size.x() * _size.y() * _size.z());
}

const Vector3<int>& ArrayVoxmap::size() const
{
    return _size;
}

Voxel& get(const int x, const int y, const int z)
{
    return _voxmap.at(x + _size.x() * y + z * _size.x() * _size.y());
}


} // namespace nt

#endif // ALPHA_ARRAYVOXMAP_HEADER
