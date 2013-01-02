#include "PlayerInputFilter.hpp"

#include <QKeyEvent>
#include <QMouseEvent>

namespace nt {
namespace input {

bool PlayerInputFilter::eventFilter(QObject* obj, QEvent* event)
{
    if (_playerInput) {
        switch (event->type()) {
            case QEvent::KeyPress:
                return _playerInput->handleKeyPress(
                    static_cast<QKeyEvent*>(event)
                );
            case QEvent::KeyRelease:
                return _playerInput->handleKeyRelease(
                    static_cast<QKeyEvent*>(event)
                );
            case QEvent::MouseButtonPress:
                return _playerInput->handleMousePress(
                    static_cast<QMouseEvent*>(event)
                );
            case QEvent::MouseButtonRelease:
                return _playerInput->handleMouseRelease(
                    static_cast<QMouseEvent*>(event)
                );
            default:
                break;
        }
    }
    return QObject::eventFilter(obj, event);
}

void PlayerInputFilter::setPlayerInput(PlayerInput* const playerInput)
{
    _playerInput = playerInput;
}

} // namespace input
} // namespace nt
