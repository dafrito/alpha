#include "gl/Screen.hpp"

#include <algorithm>

#include "gl/util.hpp"

namespace nt {
namespace gl {

void Screen::initialize()
{
    for (auto entry : viewports) {
        entry.viewport->initialize();
    }
}

void Screen::render(const Box2<int>& screenArea) const
{
    glEnable(GL_SCISSOR_TEST);
    glScissor(screenArea);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (std::vector<ViewportEntry>::const_iterator i = viewports.begin(); i != viewports.end(); ++i) {
        Box2<int> viewportArea;

        viewportArea.setLeft(
            static_cast<int>(screenArea.width() * i->extent.left())
        );
        viewportArea.setRight(
            static_cast<int>(screenArea.width() * i->extent.right())
        );
        viewportArea.setTop(
            static_cast<int>(screenArea.height() * i->extent.top())
        );
        viewportArea.setBottom(
            static_cast<int>(screenArea.height() * i->extent.bottom())
        );

        i->viewport->render(viewportArea);
    }
}

void Screen::addViewport(Viewport* const viewport)
{
    addViewport(viewport, Box2<double>(0, 1, 0, 1));
}

void Screen::addViewport(Viewport* const viewport, const Box2<double>& extent)
{
    ViewportEntry entry;
    entry.viewport = viewport;
    entry.extent = extent;
    viewports.push_back(entry);
}

void Screen::removeViewport(Viewport* const viewport)
{
    viewports.erase(
        std::remove_if(begin(viewports), end(viewports),
            [&](ViewportEntry& entry) { return entry.viewport == viewport; }
        ),
        end(viewports)
    );
}

} // namespace gl
} // namespace nt
