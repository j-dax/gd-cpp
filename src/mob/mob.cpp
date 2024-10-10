#include "mob.h"

#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/animated_sprite2d.hpp>
#include <godot_cpp/classes/sprite_frames.hpp>

void Mob::_bind_methods() {
    ADD_SIGNAL(MethodInfo("screen_exited"));
    ClassDB::bind_method(D_METHOD("_onScreenLeave", "node"), &Mob::_onScreenLeave);
}

Mob::Mob() {
    connect("screen_exited", Callable(this, "_onScreenLeave"));
}

void Mob::start(Vector2 position) {
    set_position(position);
}

void Mob::_onScreenLeave() {
    UtilityFunctions::print("[:< Mob leaving");
    queue_free();
    UtilityFunctions::print("[:< Mob leaving END");
}

void Mob::_ready() {
    auto animatedSprite2D = get_node<AnimatedSprite2D>("AnimatedSprite2D");
    auto mobTypes = animatedSprite2D->get_sprite_frames()->get_animation_names();
    animatedSprite2D->play(mobTypes[UtilityFunctions::randi_range(0, mobTypes.size()-1)]);
}
