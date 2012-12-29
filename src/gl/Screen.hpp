#ifndef ALPHA_SCREEN_HEADER
#define ALPHA_SCREEN_HEADER

#include "gl/Viewport.hpp"
#include "Box2.hpp"
#include <vector>

namespace nt {
namespace gl {

struct ViewportEntry;

/**
 * A screen containing rendered scenes.
 *
 * A screen contains a number of viewports, each rendered into a
 * specified area. Since the area is specified using relative
 * positions, the screen can be resized with the rendered viewports
 * able to resize themselves immediately.
 *
 * @see ScreenGLWidget
 * @see Viewport
 */
class Screen
{
    std::vector<ViewportEntry> viewports;

public:
    void render(const Box2<int>& screenArea) const;

    /**
     * Add a viewport to this screen that will cover the full area of the screen.
     */
    void addViewport(const Viewport* const viewport);

    /**
     * Adds a viewport to this screen.
     *
     * The specified extent determines where the viewport will be rendered on-screen.
     * The extent's bounds should be in the range [0,1], since they are relative.
     */
    void addViewport(const Viewport* const viewport, const Box2<double>& extent);

    /**
     * Remove the specified viewport from this screen.
     */
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
