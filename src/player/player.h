#pragma once

#include <godot_cpp/classes/area2d.hpp>

using namespace godot;

class Player : public Area2D {
	GDCLASS(Player, Area2D)

private:
	int speed;
	Size2 screenSize;

	static void _bind_methods() {
		ClassDB::bind_method(D_METHOD("getSpeed"), &Player::getSpeed);
		ClassDB::bind_method(D_METHOD("setSpeed", "speed"), &Player::setSpeed);
		ADD_PROPERTY(PropertyInfo(Variant::INT, "speed"), "setSpeed", "getSpeed");
	}
public:
	Player();
	~Player() = default;

	// signals
	void setSpeed(const int pSpeed); 
	int getSpeed() const; 

	// engine binding
	void _ready() override;
	void _process(double) override;
	void _on_body_entered(Node2D) override;
};
