#pragma once

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/packed_scene.hpp>

using namespace godot;

class Main : public Node {
    GDCLASS(Main, Node)

private:
    Ref<PackedScene> mob_scene;
    int score;

    static void _bind_methods();
public:
    Main();
    ~Main() = default;

    // engine bindings
    Ref<PackedScene> get_mob_scene();
    void set_mob_scene(Ref<PackedScene>);
    void game_over();
    void new_game();

    // signal receivers
    void _on_score_timer_timeout();
    void _on_start_timer_timeout();
    void _on_mob_timer_timeout();

    // void _ready() override;
};
