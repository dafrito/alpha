#include <QtTest/QtTest>
#include <QDebug>

#include <ArrayVoxmap.hpp>
#include <Vector3.hpp>

using nt::Vector3;
using nt::ArrayVoxmap;

class VoxmapTests : public QObject
{
	Q_OBJECT

private slots:

    void testVoxmapBoundaryConditions()
    {
        ArrayVoxmap<int> voxmap(Vector3<int>(4, 4, 4));
        voxmap.get(0, 0, 0);
        voxmap.get(0, 0, 3);
        voxmap.get(0, 3, 0);
        voxmap.get(0, 3, 3);
        voxmap.get(3, 0, 0);
        voxmap.get(3, 0, 3);
        voxmap.get(3, 3, 0);
        voxmap.get(3, 3, 3);
    }

    void testVoxmapBoundaryConditionsWithResize()
    {
        ArrayVoxmap<int> voxmap;
        voxmap.resize(Vector3<int>(4, 4, 4));
        voxmap.get(0, 0, 0);
        voxmap.get(0, 0, 3);
        voxmap.get(0, 3, 0);
        voxmap.get(0, 3, 3);
        voxmap.get(3, 0, 0);
        voxmap.get(3, 0, 3);
        voxmap.get(3, 3, 0);
        voxmap.get(3, 3, 3);
    }
};
