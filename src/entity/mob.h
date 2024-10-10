#pragma once

#include <godot_cpp/classes/rigid_body2d.hpp>
#include <godot_cpp/classes/animated_sprite2d.hpp>

using namespace godot;

class Mob : public RigidBody2D {
    GDCLASS(Mob, RigidBody2D)

private:
    static void _bind_methods();
public:
    Mob();
    ~Mob() = default;

    void start(Vector2 position, float rotation);

    // signals
    void _on_screen_leave();

    // engine binding
    void _ready() override;
};
