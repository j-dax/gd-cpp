#pragma once

#include <godot_cpp/classes/canvas_layer.hpp>

using namespace godot;

class Hud : public CanvasLayer {
    GDCLASS(Hud, CanvasLayer)

private:
    int speed;
    bool reset;
    Size2 screenSize;

    static void _bind_methods();
public:
    Hud();
    ~Hud() = default;

    void show_message(String text);
    void show_start_button();

    void _on_loss();
    void _on_reset();
    void _on_start();
    void _on_message_timer_timeout();
    void _on_score_change(int64_t score);
};
