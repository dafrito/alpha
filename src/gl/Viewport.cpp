#include "Viewport.hpp"

namespace nt {
namespace gl {

void ProjectionPerspective::setFOV(const double& fov)
{
    _fov = fov;
}

const double& ProjectionPerspective::getFOV() const
{
    return _fov;
}

void ProjectionPerspective::setViewDistance(const double& viewDistance)
{
    _viewDistance = viewDistance;
}

const double& ProjectionPerspective::getViewDistance() const
{
    return _viewDistance;
}

} // namespace gl
} // namespace nt
