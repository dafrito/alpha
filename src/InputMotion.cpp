#include "InputMotion.hpp"

#include "Vector3.hpp"

#include <boost/math/constants/constants.hpp>
using namespace boost::math;

namespace {
const double PLAYER_MOVESPEED = 50;
const double TURN_SPEED = constants::pi<double>();
} // namespace anonymous

namespace nt {

InputMotion::InputMotion() :
    _input(nullptr),
    _physical(nullptr)
{}

void InputMotion::tick(const double& elapsed) const
{
    if (!_physical || !_input) {
        return;
    }

    Physical<double>& target = *_physical;

    // XXX This should be const, but that requires the
    // getters being const. Once that's done, clean this up
    PlayerInput& input = *_input;

    Vector3<double> velocity;

    double da = TURN_SPEED * elapsed;

    if (input.turnLeft()) {
        target.getRotation().addZ(-da);
    } else if (input.turnRight()) {
        target.getRotation().addZ(da);
    }

    if (input.strafeLeft()) {
        velocity.addX(-1);
    } else if (input.strafeRight()) {
        velocity.addX(1);
    }

    if (input.moveForward()) {
        velocity.addZ(-1);
    } else if (input.moveBackward()) {
        velocity.addZ(1);
    }

    // Move the character vertically up and down.
    if (input.verticalUp()) {
        velocity.addY(1);
    } else if (input.verticalDown()) {
        velocity.addY(-1);
    }

    velocity.normalize();

    // up/down commands now move you up/down relative to the world
    if (velocity.z() == 0) {
        velocity.rotateX(target.getRotation().x());
    }
    velocity.rotateZ(target.getRotation().z());

    velocity *= PLAYER_MOVESPEED * elapsed;
    target.getPosition() += velocity;
}

void InputMotion::setInput(PlayerInput* const input)
{
    _input = input;
}

void InputMotion::setPhysical(Physical<double>* const physical)
{
    _physical = physical;
}

} // namespace nt
