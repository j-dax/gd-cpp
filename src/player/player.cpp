#include "player.h"

#include <godot_cpp/classes/animated_sprite2d.hpp>
#include <godot_cpp/classes/collision_shape2d.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_map.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void Player::_bind_methods() {
    ClassDB::bind_method(D_METHOD("getSpeed"), &Player::getSpeed);
    ClassDB::bind_method(D_METHOD("setSpeed", "speed"), &Player::setSpeed);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "speed"), "setSpeed", "getSpeed");

    ADD_SIGNAL(MethodInfo(PropertyInfo(Variant::OBJECT, "node"), "player_hit"));
    ClassDB::bind_method(D_METHOD("_onBodyEntered", "node"), &Player::_onBodyEntered);
}

Player::Player() {
    speed = 400;
    connect("player_hit", Callable(this, "_onBodyEntered"));
}

void Player::setSpeed(const int pSpeed) {
    speed = pSpeed;
}

int Player::getSpeed() const {
    return speed;
}

void Player::start(Vector2 position) {
    set_position(position);
    show();
    get_node<CollisionShape2D>("CollisionShape2D")->set_disabled(false);
}

void Player::_ready() {
    // https://github.com/godotengine/godot/issues/74993
    // workaround available: in _ready
    auto im = InputMap::get_singleton();
    im->load_from_project_settings();

    start(get_position());

    screenSize = get_viewport_rect().size;
}

void Player::_process(double delta) {
    auto input = Input::get_singleton();
    auto velocity = Vector2(0, 0);
    if (input->is_action_pressed("move_up")) {
        velocity.y -= 1;
    }
    if (input->is_action_pressed("move_down")) {
        velocity.y += 1;
    }
    if (input->is_action_pressed("move_left")) {
        velocity.x -= 1;
    }
    if (input->is_action_pressed("move_right")) {
        velocity.x += 1;
    }

    auto animatedSprite2D = Node::get_node<AnimatedSprite2D>("AnimatedSprite2D");
    if (velocity.x != 0) {
        animatedSprite2D->set_animation("walk");
        animatedSprite2D->set_flip_v(false);
        animatedSprite2D->set_flip_h(velocity.x < 0);
    } else if (velocity.y != 0) {
        animatedSprite2D->set_animation("up");
        animatedSprite2D->set_flip_v(velocity.y > 0);
    }

    if (velocity.length() > 0) {
        velocity = velocity.normalized() * speed;
        animatedSprite2D->play();
    } else {
        animatedSprite2D->stop();
    }

    auto newPosition = get_position();
    newPosition += velocity * delta;

    newPosition.x = Math::clamp(newPosition.x, 0.0f, screenSize.x);
    newPosition.y = Math::clamp(newPosition.y, 0.0f, screenSize.y);

    set_position(newPosition);
}

void Player::_onBodyEntered(Node2D *node) {
    hide();
    // emit signal is connected in the editor
    get_node<CollisionShape2D>("CollisionShape2D")->set_deferred(StringName("set_disabled"), true);
}
