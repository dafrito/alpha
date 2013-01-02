#include "Bootstrapper.hpp"

#include "GL/glut.h"

#include <cstdlib>

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
    _initialized(false)
{}

void Bootstrapper::initialize()
{
    if (_initialized) {
        return;
    }
    _initialized = true;

    _viewport.setProjection(&_projection);

    _viewport.getCamera().getPosition().setX(50);
    _viewport.getCamera().getPosition().setY(50);
    _viewport.getCamera().getPosition().setZ(50);

    populateWorld();

    _worldLayer.setVoxmap(&_world);
    _worldLayer.setVoxelSize(Vector3<double>(5, 5, 5));
    _worldLayer.setRenderer(renderBlock);
    _viewport.addRenderLayer(&_worldLayer);

    _viewport.addRenderLayer(&_unitsLayer);

    _screen.addViewport(&_viewport, Box2<double>(0, 1, 0, 1));
    _screenWidget.setScreen(&_screen);
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

gl::ScreenGLWidget& Bootstrapper::getScreenGLWidget()
{
    initialize();
    return _screenWidget;
}
