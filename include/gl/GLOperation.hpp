#ifndef ALPHA_GLOPERATION_HEADER
#define ALPHA_GLOPERATION_HEADER

#include <vector>

namespace nt {
namespace gl {

enum glOperation {
    OP_popMatrix,
    OP_end
};

/**
 * A RAII-based way to setup GL operations.
 *
 * This class, while keeping GL operations in a sane state when in the
 * face of exceptions, isn't easy or convenient enough to be used
 * regularly. If it can't be extended to provide more useful behavior,
 * it will likely be scrapped altogether.
 */
class GLOperation
{
protected:
    std::vector<glOperation> operations;
public:
    // Operations
    GLOperation& pushMatrix();
    GLOperation& beginQuads();

    // Manual pop
    GLOperation& pop();

    ~GLOperation();
};

} // namespace gl
} // namespace nt

#endif // ALPHA_GLOPERATION_HEADER
