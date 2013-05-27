#ifndef ALPHA_VOXMAPRENDERLAYER_HEADER
#define ALPHA_VOXMAPRENDERLAYER_HEADER

#include "../Vector3.hpp"
#include "RenderLayer.hpp"
#include "util.hpp"

#include <GL/gl.h>

namespace nt {
namespace gl {

/**
 * Renders a voxmap.
 *
 * This render layer will render a collection of voxels, contained in
 * a voxmap, at regular intervals on-screen. It assumes each entry in the
 * voxmap is regularly spaced and uses a constant size, which allows it
 * to omit having to store physical locations for each voxel. It also uses
 * a single renderer for all voxels, which also contributes to keeping voxel
 * data as light as possible.
 *
 * When using this class, clients are able to specify the voxel type as well
 * as the renderer type used to draw them. It's preferable to keep voxel data
 * as light as possible and lean heavily on the renderer type to draw the
 * specific voxel.
 *
 * @see DirectRenderLayer
 * @see RenderLayer
 */
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
    void render(const Physical<double>&, const Projection&) const;
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
void VoxmapRenderLayer<Scalar, Voxmap, VoxRenderer>::render(const Physical<double>& position, const Projection&) const
{
    if  (_voxmap == 0 || _renderer == 0) {
        // The voxmap or the voxel renderer isn't set, so just return
        return;
    }

    const Vector3<int>& size = _voxmap->size();
    Vector3<Scalar> halfVoxelSize(_voxelSize);
    halfVoxelSize /= 2;

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    for (int x = 0; x < size.x(); ++x) {
        for (int y = 0; y < size.y(); ++y) {
            for (int z = 0; z < size.z(); ++z) {
                glPushMatrix();
                gl::glTranslate(
                    x * _voxelSize.x() + halfVoxelSize.x(),
                    y * _voxelSize.y() + halfVoxelSize.y(),
                    z * _voxelSize.z() + halfVoxelSize.z()
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
