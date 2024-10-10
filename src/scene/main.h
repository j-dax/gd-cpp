#pragma once

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/packed_scene.hpp>

using namespace godot;

class Main : public Node {
    GDCLASS(Main, Node)

private:
    Ref<PackedScene> mobScene;
    int _score;

    static void _bind_methods();
public:
    Main();
    ~Main() = default;

    // engine bindings
    Ref<PackedScene> getMobScene();
    void setMobScene(Ref<PackedScene> pScene);
    void gameOver();
    void newGame();

    // signal receivers
    void onScoreTimerTimeout();
    void onStartTimerTimeout();
    void onMobTimerTimeout();

    void _ready() override;
};
