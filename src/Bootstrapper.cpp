#include "Bootstrapper.hpp"

#include "GL/glut.h"

#include <cstdlib>

namespace {

/**
 * A named series of stages for rendering. There's no magic here; these are
 * just a guess at the stages we'll eventually have. The order is significant,
 * since these are passed to SystemLoop. For example, all INPUT systems will
 * execute before any RENDERING system is executed.
 */
enum SYSTEM_STAGE {
    INPUT,
    PHYSICS,
    RENDERING
};

/**
 * Frames per second, used by the timer to determine when the system loop is
 * executed.  Since the system loops contains not only rendering systems but
 * physics and potentially AI systems, this is in effect the rate of execution
 * for the entire game.
 */
const int FPS = 60;

} // namespace anonymous

void renderBlock(Vector3<float> voxel, const Vector3<double>& blockSize)
{
    glColor3f(voxel.x(), voxel.y(), voxel.z());

    // Subtract one here so that "buried" cubes are visible through the
    // cracks. This would not be here in a real implementation.
    glutSolidCube(blockSize.x() - 1);
}

Bootstrapper::Bootstrapper() :
    _projection(),
    _viewport(),
    _world(),
    _unitsLayer(),
    _worldLayer(),
    _screen(),
    _screenWidget(),
    _loop(),
    _timer(1000 / FPS),
    _initialized(false)
{}

void Bootstrapper::initialize()
{
    if (_initialized) {
        return;
    }
    _initialized = true;

    _playerInputFilter.setPlayerInput(&_playerInput);

    _screenWidget.setFocusPolicy(Qt::ClickFocus);
    _screenWidget.installEventFilter(&_playerInputFilter);

    _viewport.setProjection(&_projection);

    // Adjust the camera to a better default location
    _viewport.getCamera().getPosition().setX(50);
    _viewport.getCamera().getPosition().setY(50);
    _viewport.getCamera().getPosition().setZ(50);

    populateWorld();

    // Setup the voxmap for rendering
    _worldLayer.setVoxmap(&_world);
    _worldLayer.setVoxelSize(Vector3<double>(5, 5, 5));
    _worldLayer.setRenderer(renderBlock);
    _viewport.addRenderLayer(&_worldLayer);

    // Add a direct render layer for rendering individual units
    _viewport.addRenderLayer(&_unitsLayer);

    // Finish up the render pipeline, using a screen and a Qt widget.
    // The box specifies where the screen will be rendered, in relative
    // [0,1] coordinates. Since OpenGL has the screen's origin at the
    // bottom left corner, the vertical bounds are a bit unusual.
    _screen.addViewport(&_viewport, Box2<double>(0, 1, 0, 1));
    _screenWidget.setScreen(&_screen);

    // Add the screen widget to the system loop. A lambda is used here
    // to discard the elapsed time - the rendering system is intended to
    // be time-independent.
    _loop.addTimelessSystem(
        [&]() { _screenWidget.updateGL(); },
        SYSTEM_STAGE::RENDERING
    );

    // Finally, start the system loop
    connect(
        &_timer, SIGNAL(timeout(const double&)),
        this, SLOT(tick(const double&))
    );
    _timer.start();
}

void Bootstrapper::populateWorld()
{
    Vector3<int> worldSize(50, 50, 4);
    _world.resize(worldSize);

    for (int x = 0; x < worldSize.x(); ++x) {
        for (int y = 0; y < worldSize.y(); ++y) {
            for (int z = 0; z < worldSize.z(); ++z) {
                Vector3<float> color;
                color.set(
                    static_cast<float>(rand() % 100) / 100,
                    static_cast<float>(rand() % 100) / 100,
                    static_cast<float>(rand() % 100) / 100
                );

                _world.set(x, y, z, color);
            }
        }
    }
}

void Bootstrapper::tick(const double& elapsed)
{
    _loop.tick(elapsed);
}

gl::ScreenGLWidget& Bootstrapper::getScreenGLWidget()
{
    initialize();
    return _screenWidget;
}
