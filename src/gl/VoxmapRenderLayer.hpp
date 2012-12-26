#ifndef ALPHA_VOXMAPRENDERLAYER_HEADER
#define ALPHA_VOXMAPRENDERLAYER_HEADER

#include "Vector3.hpp"
#include "RenderLayer.hpp"

#include <GL/gl.h>
#include <gl/util.hpp>

namespace nt {
namespace gl {

template <
    typename Scalar,
    typename Voxmap,
    typename VoxRenderer
>
class VoxmapRenderLayer : public RenderLayer<Scalar>
{
    const Voxmap& voxmap;
    const VoxRenderer& renderer;
    const Vector3<Scalar> bitSize;
public:
    VoxmapRenderLayer(
        const Voxmap& voxmap,
        const VoxRenderer& renderer,
        const Vector3<Scalar> bitSize);

    void render(const Vector3<Scalar>& position);
};

VoxmapRenderLayer::VoxmapRenderLayer(
    const Voxmap& voxmap,
    const VoxRenderer& renderer,
    const Vector3<Scalar> bitSize) :
        voxmap(voxmap),
        renderer(renderer),
        bitSize(bitSize)
{}

void VoxmapRenderLayer::render(cosnt Vector3<Scalar>& position)
{
    const Vector3<int>& size = voxmap.size();

    for (int x = 0; x < size.x(); ++x) {
        for (int y = 0; y < size.y(); ++y) {
            for (int z = 0; z < size.z(); ++z) {
                glPushMatrix();
                gl::glTranslate(
                    x * bitSize.x(),
                    y * bitSize.y(),
                    z * bitSize.z()
                );
                renderer(voxmap.get(x, y, z));
                glPopMatrix();
            }
        }
    }
}


} // namespace gl
} // namespace nt

#endif // ALPHA_VOXMAPRENDERLAYER_HEADER
