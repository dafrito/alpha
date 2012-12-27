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
class VoxmapRenderLayer : public RenderLayer
{
    const Voxmap* _voxmap;
    const VoxRenderer* _renderer;
    Vector3<Scalar> _voxelSize;
public:
    VoxmapRenderLayer();
    void render(const Vector3<double>& position) const;
    void setVoxmap(Voxmap* const voxmap);
    void setRenderer(VoxRenderer* const voxmap);
    void setVoxelSize(const Vector3<Scalar> voxelSize);
};

template <typename Scalar, typename Voxmap, typename VoxRenderer>
VoxmapRenderLayer<Scalar, Voxmap, VoxRenderer>::VoxmapRenderLayer() :
    _voxmap(0),
    _renderer(0),
    _voxelSize()
{}

template <typename Scalar, typename Voxmap, typename VoxRenderer>
void VoxmapRenderLayer<Scalar, Voxmap, VoxRenderer>::render(const Vector3<double>& position) const
{
    if  (_voxmap == 0 || _renderer == 0) {
        // Voxmap or render aren't set, so just return
        return;
    }

    const Vector3<int>& size = _voxmap->size();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    for (int x = 0; x < size.x(); ++x) {
        for (int y = 0; y < size.y(); ++y) {
            for (int z = 0; z < size.z(); ++z) {
                glPushMatrix();
                gl::glTranslate(
                    x * _voxelSize.x(),
                    y * _voxelSize.y(),
                    z * _voxelSize.z()
                );
                (*_renderer)(_voxmap->get(x, y, z), _voxelSize);
                glPopMatrix();
            }
        }
    }

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
}

template <typename Scalar, typename Voxmap, typename VoxRenderer>
void VoxmapRenderLayer<Scalar, Voxmap, VoxRenderer>::setVoxmap(Voxmap* const voxmap)
{
    _voxmap = voxmap;
}

template <typename Scalar, typename Voxmap, typename VoxRenderer>
void VoxmapRenderLayer<Scalar, Voxmap, VoxRenderer>::setRenderer(VoxRenderer* const renderer)
{
    _renderer = renderer;
}

template <typename Scalar, typename Voxmap, typename VoxRenderer>
void VoxmapRenderLayer<Scalar, Voxmap, VoxRenderer>::setVoxelSize(const Vector3<Scalar> voxelSize)
{
    _voxelSize = voxelSize;
}

} // namespace gl
} // namespace nt

#endif // ALPHA_VOXMAPRENDERLAYER_HEADER
