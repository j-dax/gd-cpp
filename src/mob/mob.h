#pragma once

#include <godot_cpp/classes/rigid_body2d.hpp>
#include <godot_cpp/classes/animated_sprite2d.hpp>

using namespace godot;

class Mob : public RigidBody2D {
    GDCLASS(Mob, RigidBody2D)

private:
    int speed;
    Size2 screenSize;

    static void _bind_methods();
public:
    Mob();
    ~Mob() = default;

    void start(Vector2 position);

    // signals
    void _onScreenLeave();

    // engine binding
    void _ready() override;
};
