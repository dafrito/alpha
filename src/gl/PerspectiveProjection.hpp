#ifndef ALPHA_PERSPECTIVEPROJECTION_HEADER
#define ALPHA_PERSPECTIVEPROJECTION_HEADER

#include "gl/Projection.hpp"

namespace nt {
namespace gl {

class PerspectiveProjection : public Projection
{
    double _fov;
    double _viewDistance;

public:
    PerspectiveProjection() :
        _fov(65),
        _viewDistance(800)
    {}

    void apply(const Box2<int>& viewArea) const;

    const double& getFOV() const;
    void setFOV(const double& fov);

    const double& getViewDistance() const;
    void setViewDistance(const double& viewDistance);
};

} // namespace gl
} // namespace nt

#endif // ALPHA_PERSPECTIVEPROJECTION_HEADER
