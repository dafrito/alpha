#ifndef ALPHA_GLOPERATION_HEADER
#define ALPHA_GLOPERATION_HEADER

#include <vector>

namespace
{

enum glOperation {
    OP_popMatrix,
    OP_end
};

}

namespace nt
{

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

} // namespace nt

#endif // ALPHA_GLOPERATION_HEADER
