#pragma once

#include <godot_cpp/classes/area2d.hpp>

using namespace godot;

class Player : public Area2D {
    GDCLASS(Player, Area2D)

private:
    int speed;
    Size2 screen_size;

    static void _bind_methods();
public:
    Player();
    ~Player() = default;

    void start(Vector2 position);

    // signals
    void set_speed(const int);
    int get_speed() const;
    void _on_body_entered(Node2D *node);

    // engine binding
    void _ready() override;
    void _process(double) override;
};
