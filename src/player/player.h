#pragma once

#include <godot_cpp/classes/area2d.hpp>

using namespace godot;

class Player : public Area2D {
    GDCLASS(Player, Area2D)

private:
    int speed;
    Size2 screenSize;

    static void _bind_methods();
public:
    Player();
    ~Player() = default;

    void start(Vector2 position);

    // signals
    void setSpeed(const int);
    int getSpeed() const;
    void _onBodyEntered(Node2D *node);

    // engine binding
    void _ready() override;
    void _process(double) override;
};
