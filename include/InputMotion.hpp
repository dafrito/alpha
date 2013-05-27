#ifndef ALPHA_INPUTMOTION_HEADER
#define ALPHA_INPUTMOTION_HEADER

// XXX This is a hack until PlayerInput's header fix is done
#include <QObject>

#include "PlayerInput.h"
#include "Physical.hpp"

namespace nt {

class InputMotion
{

    PlayerInput* _input;
    Physical<double>* _physical;

public:
    InputMotion();

    void tick(const double& elapsed) const;

    void setInput(PlayerInput* const input);
    void setPhysical(Physical<double>* const physical);
};

} // namespace nt

#endif // ALPHA_INPUTMOTION_HEADER
