#ifndef ALPHA_SCREEN_HEADER
#define ALPHA_SCREEN_HEADER

#include "gl/Viewport.hpp"
#include "Box2.hpp"
#include <vector>

namespace nt {
namespace gl {

struct ViewportEntry;

class Screen
{
    std::vector<ViewportEntry> viewports;

public:
    void render(const Box2<int>& screenArea) const;

    void addViewport(const Viewport* const viewport);
    void addViewport(const Viewport* const viewport, const Box2<double>& extent);
    void removeViewport(const Viewport* const viewport);
};

struct ViewportEntry {
    const Viewport* viewport;

    Box2<double> extent;
    ViewportEntry () :
        viewport(0),
        extent()
    {}
};

} // namespace gl
} // namespace nt

#endif // ALPHA_SCREEN_HEADER
