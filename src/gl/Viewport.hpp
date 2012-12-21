#ifndef ALPHA_VIEWPORT_HEADER
#define ALPHA_VIEWPORT_HEADER

namespace nt {
namespace gl {

template <typename Scalar, typename Perspective>
class Viewport : public Perspective
{
    // Camera property
    // Perspective policy
    // Render Layers list of layers

public:
    void render();
};

} // namespace gl
} // namespace nt

#endif // ALPHA_VIEWPORT_HEADER
