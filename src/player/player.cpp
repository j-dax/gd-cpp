#include "player.h"

#include <godot_cpp/variant/signal.hpp>
#include <godot_cpp/classes/animated_sprite2d.hpp>
#include <godot_cpp/classes/canvas_item.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/node.hpp>

using namespace godot;

Player::Player() {
	speed = 400;
}

void Player::setSpeed(const int pSpeed) {
	speed = pSpeed;
}

int Player::getSpeed() const {
	return speed;
}

void Player::_ready() {
	screenSize = get_viewport_rect().size;
}

void Player::_process(double delta) {
	// if this line isn't present, the editor gets flooded with errors
	//	suggesting that an input mapping is missing, found work around
	// https://github.com/godotengine/godot/issues/74993
	if (Engine::get_singleton()->is_editor_hint()) return;

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

	auto newPosition = this->get_position();
	newPosition += velocity * delta;

	newPosition.x = Math::clamp(newPosition.x, 0.0f, screenSize.x);
	newPosition.y = Math::clamp(newPosition.y, 0.0f, screenSize.y);

	this->set_position(newPosition);
}

void Player::_on_body_entered(Node2D body) {
	this->hide();
	signal
}
