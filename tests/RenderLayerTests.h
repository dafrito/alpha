#ifndef ALPHA_RENDERLAYERTESTS_HEADER
#define ALPHA_RENDERLAYERTESTS_HEADER

#include <QtTest/QtTest>
#include <DirectRenderLayer.hpp>

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
        DirectRenderLayer<float, void()> layer;

        Physical<float> physical;
        Renderable<float, void()> dummy(&physical, dummyRender);

        QCOMPARE(layer.numRenderables(), 0);
        layer.add(dummy);
        QCOMPARE(layer.numRenderables(), 1);

        FLAG = 0;
        Vector3<float> origin;
        layer.render(origin);
        QCOMPARE(FLAG, 1);

        layer.remove(dummy);
        QCOMPARE(layer.numRenderables(), 0);
    }
};

#endif // ALPHA_RENDERLAYERTESTS_HEADER
