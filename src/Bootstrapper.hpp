#ifndef ALPHA_BOOTSTRAPPER_HEADER
#define ALPHA_BOOTSTRAPPER_HEADER

#include "ArrayVoxmap.hpp"
#include "gl/PerspectiveProjection.hpp"
#include "gl/Viewport.hpp"
#include "gl/DirectRenderLayer.hpp"
#include "gl/VoxmapRenderLayer.hpp"
#include "gl/Screen.hpp"

using namespace nt;

/**
 * A staging area, as well as a script, to set up the application.
 *
 * This class is the place where everything gets started, and as such it houses several
 * different classes. The complicated behavior should eventually get pushed to better
 * locations than this class, though it's common to have new concepts live here until
 * a more suitable design is created.
 */
class Bootstrapper
{
    typedef Vector3<float> Voxel;
    typedef ArrayVoxmap<Voxel> Voxmap;

    gl::PerspectiveProjection _projection;
    gl::Viewport _viewport;
    Voxmap _world;

    gl::DirectRenderLayer<double> _unitsLayer;
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
