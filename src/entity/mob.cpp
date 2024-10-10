#include "mob.h"

#include <godot_cpp/classes/animated_sprite2d.hpp>
#include <godot_cpp/classes/visible_on_screen_notifier2d.hpp>
#include <godot_cpp/classes/sprite_frames.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

void Mob::_bind_methods() {
    ClassDB::bind_method(D_METHOD("_on_screen_leave"), &Mob::_on_screen_leave);
}

Mob::Mob() {}

void Mob::start(Vector2 position, float rotation) {
    set_global_position(position);
    // send our mob in a random direction
    // FIXME: send the mob in an actual random direction, rather than
    // whatever this shit is
    auto direction = rotation + godot::Math::deg_to_rad(90.0);
    direction += UtilityFunctions::randf_range(-godot::Math::deg_to_rad(45.0), godot::Math::deg_to_rad(45.0));
    set_global_rotation(direction);

    auto velocity = Vector2(UtilityFunctions::randf_range(150.0, 250.0), 0);
    set_linear_velocity(velocity);

}

void Mob::_on_screen_leave() {
    queue_free();
}

void Mob::_ready() {
    auto animated_sprite_2d = get_node<AnimatedSprite2D>("AnimatedSprite2D");
    auto mob_types = animated_sprite_2d->get_sprite_frames()->get_animation_names();
    animated_sprite_2d->play(mob_types[UtilityFunctions::randi_range(0, mob_types.size()-1)]);

    auto vosn = get_node<VisibleOnScreenNotifier2D>("VisibleOnScreenNotifier2D");
    if (!vosn->is_connected("screen_exited", Callable(this, "_on_screen_leave"))) {
        vosn->connect("screen_exited", Callable(this, "_on_screen_leave"));
    }
}
