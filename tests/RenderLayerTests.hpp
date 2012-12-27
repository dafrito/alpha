#ifndef ALPHA_RENDERLAYERTESTS_HEADER
#define ALPHA_RENDERLAYERTESTS_HEADER

#include <QtTest/QtTest>
#include <gl/DirectRenderLayer.hpp>

namespace
{

int FLAG = 0;
void dummyRender()
{
    ++FLAG;
}

}

using nt::Vector3;
using namespace nt::gl;

class RenderLayerTests : public QObject
{
    Q_OBJECT
private slots:

    void testDirectRenderLayer()
    {
        DirectRenderLayer<float, void()> layer;

        Physical<float> physical;

        QCOMPARE(layer.numRenderables(), 0);
        layer.add(&physical, dummyRender);
        QCOMPARE(layer.numRenderables(), 1);

        FLAG = 0;
        Vector3<float> origin;
        layer.render(origin);
        QCOMPARE(FLAG, 1);

        layer.remove(&physical, dummyRender);
        QCOMPARE(layer.numRenderables(), 0);
    }
};

#endif // ALPHA_RENDERLAYERTESTS_HEADER
