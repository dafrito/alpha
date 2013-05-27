#ifndef ALPHA_PLAYERINPUTFILTER_HEADER
#define ALPHA_PLAYERINPUTFILTER_HEADER

#include <QObject>
#include "../PlayerInput.h"

namespace nt {
namespace input {

/**
 * This class sends input to PlayerInput. As you'll
 * see, the class does very little, so it should
 * probably be merged into PlayerInput itself.
 */
class PlayerInputFilter : public QObject
{
    Q_OBJECT

    PlayerInput* _playerInput;

protected:
    bool eventFilter(QObject *obj, QEvent *event);

public:
    PlayerInputFilter();

    void setPlayerInput(PlayerInput* const playerInput);
};

} // namespace input
} // namespace nt

#endif // ALPHA_PLAYERINPUTFILTER_HEADER
