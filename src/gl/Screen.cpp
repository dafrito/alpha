#include "Screen.hpp"

#include "gl/util.hpp"

namespace nt {
namespace gl {

void Screen::render(const Box2<int>& screenArea) const
{
    glEnable(GL_SCISSOR_TEST);
    glScissor(screenArea);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (std::vector<ViewportEntry>::const_iterator i = viewports.begin(); i != viewports.end(); ++i) {
        Box2<int> viewportArea;

        viewportArea.setLeft(
            static_cast<int>(screenArea.left() * i->extent.left())
        );
        viewportArea.setRight(
            static_cast<int>(screenArea.right() * i->extent.right())
        );
        viewportArea.setTop(
            static_cast<int>(screenArea.top() * i->extent.top())
        );
        viewportArea.setBottom(
            static_cast<int>(screenArea.bottom() * i->extent.bottom())
        );

        i->viewport->render(viewportArea);
    }
}

void Screen::addViewport(const Viewport* const viewport)
{
    addViewport(viewport, Box2<double>(0, 1, 0, 1));
}

void Screen::addViewport(const Viewport* const viewport, const Box2<double>& extent)
{
    ViewportEntry entry;
    entry.viewport = viewport;
    entry.extent = extent;
    viewports.push_back(entry);
}

void Screen::removeViewport(const Viewport* const viewport)
{
    for (std::vector<ViewportEntry>::iterator i = viewports.begin(); i != viewports.end(); ++i) {
        if (i->viewport == viewport) {
            viewports.erase(i);
            return;
        }
    }
}

} // namespace gl
} // namespace nt
