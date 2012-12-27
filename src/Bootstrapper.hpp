#ifndef ALPHA_BOOTSTRAPPER_HEADER
#define ALPHA_BOOTSTRAPPER_HEADER

#include "ArrayVoxmap.hpp"
#include "gl/PerspectiveProjection.hpp"
#include "gl/Viewport.hpp"
#include "gl/DirectRenderLayer.hpp"
#include "gl/VoxmapRenderLayer.hpp"
#include "gl/Screen.hpp"

using namespace nt;

class Bootstrapper
{
    typedef Vector3<float> Voxel;
    typedef ArrayVoxmap<Voxel> Voxmap;


    gl::PerspectiveProjection _projection;
    gl::Viewport _viewport;
    Voxmap _world;

    gl::DirectRenderLayer<double, void()> _unitsLayer;
    gl::VoxmapRenderLayer<double, Voxmap, void(Voxel, const Vector3<double>&)> _worldLayer;

    gl::Screen _screen;

    bool _initialized;
    void initialize();

    void populateWorld();
public:
    Bootstrapper();

    gl::Screen& getScreen();
};

#endif // ALPHA_BOOTSTRAPPER_HEADER
