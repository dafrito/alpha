#ifndef ALPHA_PROJECTION_HEADER
#define ALPHA_PROJECTION_HEADER

#include "Box2.hpp"

namespace nt {
namespace gl {

class Projection
{
public:
    virtual void apply(const Box2<int>& viewArea) const=0;
};

} // namespace gl
} // namespace nt

#endif // ALPHA_PROJECTION_HEADER
