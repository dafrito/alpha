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

void renderBlock(const Vector3<float>& voxel, const Vector3<double>& origin, const Vector3<double>& radius)
{
	if (voxel.x() == -1) {
		//Blocks with color values of (-1,y,z) are treated as air and not rendered.
	}
	else {
        glBegin(GL_QUADS);
            glColor3f(voxel.x() * .8, voxel.y() * .8, voxel.z() * .8);
            // Top side
            glVertex3f(origin.x() - radius.x(), origin.y() - radius.y(), origin.z() - radius.z());
            glVertex3f(origin.x() - radius.x(), origin.y() - radius.y(), origin.z() + radius.z());
            glVertex3f(origin.x() + radius.x(), origin.y() - radius.y(), origin.z() + radius.z());
            glVertex3f(origin.x() + radius.x(), origin.y() - radius.y(), origin.z() - radius.z());

            // Bottom side
            glVertex3f(origin.x() - radius.x(), origin.y() + radius.y(), origin.z() - radius.z());
            glVertex3f(origin.x() - radius.x(), origin.y() + radius.y(), origin.z() + radius.z());
            glVertex3f(origin.x() + radius.x(), origin.y() + radius.y(), origin.z() + radius.z());
            glVertex3f(origin.x() + radius.x(), origin.y() + radius.y(), origin.z() - radius.z());

            // Front side
            glColor3f(voxel.x(), voxel.y(), voxel.z());
            glVertex3f(origin.x() + radius.x(), origin.y() + radius.y(), origin.z() + radius.z());
            glVertex3f(origin.x() - radius.x(), origin.y() + radius.y(), origin.z() + radius.z());
            glVertex3f(origin.x() - radius.x(), origin.y() - radius.y(), origin.z() + radius.z());
            glVertex3f(origin.x() + radius.x(), origin.y() - radius.y(), origin.z() + radius.z());

            // Back side
            glColor3f(voxel.x() * .8, voxel.y() * .8, voxel.z() * .8);
            glVertex3f(origin.x() + radius.x(), origin.y() + radius.y(), origin.z() - radius.z());
            glVertex3f(origin.x() - radius.x(), origin.y() + radius.y(), origin.z() - radius.z());
            glVertex3f(origin.x() - radius.x(), origin.y() - radius.y(), origin.z() - radius.z());
            glVertex3f(origin.x() + radius.x(), origin.y() - radius.y(), origin.z() - radius.z());

            // Left side
            glVertex3f(origin.x() - radius.x(), origin.y() + radius.y(), origin.z() + radius.z());
            glVertex3f(origin.x() - radius.x(), origin.y() + radius.y(), origin.z() - radius.z());
            glVertex3f(origin.x() - radius.x(), origin.y() - radius.y(), origin.z() - radius.z());
            glVertex3f(origin.x() - radius.x(), origin.y() - radius.y(), origin.z() + radius.z());

            // Right side
            glVertex3f(origin.x() + radius.x(), origin.y() + radius.y(), origin.z() + radius.z());
            glVertex3f(origin.x() + radius.x(), origin.y() - radius.y(), origin.z() + radius.z());
            glVertex3f(origin.x() + radius.x(), origin.y() - radius.y(), origin.z() - radius.z());
            glVertex3f(origin.x() + radius.x(), origin.y() + radius.y(), origin.z() - radius.z());
        glEnd();
	}
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
    //PerlinNoise(double _persistence, double _frequency, double _amplitude, int _octaves, int _randomseed);
    _pnoise.Set(0.3, 0.9, 7, 3, 17);
    _width = 128;
    _depth = 128;
    _height = 64;

    _screenWidget.setFocusPolicy(Qt::ClickFocus);
    _screenWidget.installEventFilter(&_playerInputFilter);

    _viewport.setProjection(&_projection);

    populateWorld();

    const Vector3<double> voxelSize(5, 5, 5);

    // Setup the voxmap for rendering
    _worldLayer.setVoxmap(&_world);
    _worldLayer.setVoxelSize(voxelSize);
    _worldLayer.setRenderer(renderBlock);
    _viewport.addRenderLayer(&_worldLayer);

    // Add a direct render layer for rendering individual units
    _viewport.addRenderLayer(&_unitsLayer);

    // Adjust the camera to a better default location
    _viewport.getCamera().getPosition().set(
        _width * voxelSize.x() / 2,
        10 * voxelSize.y(),
        _depth * voxelSize.z()
    );

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

    _cameraMotion.setInput(&_playerInput);
    _cameraMotion.setPhysical(&_viewport.getCamera());

    _loop.addSystem(
        [&](const double& elapsed) { _cameraMotion.tick(elapsed); },
        SYSTEM_STAGE::INPUT
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
    Vector3<int> worldSize(_width, _height, _depth);
    Vector3<float> blocktypes [] = {Vector3<float> {.7,.7,.4}, Vector3<float> {.3,.3,.3}, Vector3<float> {.3,.5,.9},  Vector3<float> {.1,.4,.1}, Vector3<float> {-1,-1,-1}};
    _world.resize(worldSize);
    int blockIndex = 0;
    //The idea here will be to create a function that generates 2D perlin noise over an area of x*y,
    //which will give the height of the terrain for each location, this will be what generates the terrain.
    float perlinTest[_width][_depth];
    for (int i = 0; i < _width;++i) {
    	for (int j = 0; j < _depth;++j) {
    		perlinTest[i][j] = (int) _pnoise.GetHeight(i, j);
    	}
    }
    // 0 : purple
    // 1 : green
    // 2 : grey
    // 3 : blue
    // 4 : air (Not-rendered)

    for (int x = 0; x < worldSize.x(); ++x) {
        for (int y = 0; y < worldSize.y(); ++y) {
            for (int z = 0; z < worldSize.z(); ++z) {
            	if (y == perlinTest[x][z]) {
            		//This sets the top layer of blocks to be the "green grass" block.
            		blockIndex = 3;
            	}
            	else {
            		//Randomizing other blocks below that.
            		blockIndex = rand() % 3;
            	};
            	if (y > perlinTest[x][z]) {
            		//Setting a region to test for "air" blocks not being rendered.
            		blockIndex = 4;
            	};
                //_world.set(x, y, z, blocktypes[rand() % 4]);
           		_world.set(x, y, z, blocktypes[blockIndex]);
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

