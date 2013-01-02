#ifndef ALPHA_RENDERLAYERTESTS_HEADER
#define ALPHA_RENDERLAYERTESTS_HEADER

#include <QtTest/QtTest>
#include <gl/DirectRenderLayer.hpp>
#include <gl/PerspectiveProjection.hpp>

namespace
{

int FLAG = 0;
void dummyRender()
{
    ++FLAG;
}

}

class RenderLayerTests : public QObject
{
    Q_OBJECT
private slots:

    void testDirectRenderLayer()
    {
        using namespace nt;
        using namespace nt::gl;

        DirectRenderLayer<float> layer;

        Physical<float> physical;

        QCOMPARE(layer.numRenderables(), 0);
        layer.add(&physical, dummyRender);
        QCOMPARE(layer.numRenderables(), 1);

        FLAG = 0;
        Physical<double> origin;
        PerspectiveProjection projection;
        layer.render(origin, projection);
        QCOMPARE(FLAG, 1);

        layer.remove(&physical);
        QCOMPARE(layer.numRenderables(), 0);
    }
};

#endif // ALPHA_RENDERLAYERTESTS_HEADER
