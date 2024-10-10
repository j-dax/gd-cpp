#include "main.h"
#include "entity/player.h"
#include "entity/mob.h"
#include "scene/hud.h"

#include <godot_cpp/core/property_info.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/timer.hpp>
#include <godot_cpp/classes/marker2d.hpp>
#include <godot_cpp/classes/path_follow2d.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

Main::Main() {
    score = 0;
}

void Main::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_mob_scene"), &Main::get_mob_scene);
    ClassDB::bind_method(D_METHOD("set_mob_scene", "packed_scene"), &Main::set_mob_scene);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "packed_scene", PROPERTY_HINT_RESOURCE_TYPE, "PackedScene"), "set_mob_scene", "get_mob_scene");

    // game start/end
    ClassDB::bind_method(D_METHOD("game_over"), &Main::game_over);
    ClassDB::bind_method(D_METHOD("new_game"), &Main::new_game);

    // timers
    ClassDB::bind_method(D_METHOD("_on_score_timer_timeout"), &Main::_on_score_timer_timeout);
    ClassDB::bind_method(D_METHOD("_on_start_timer_timeout"), &Main::_on_start_timer_timeout);
    ClassDB::bind_method(D_METHOD("_on_mob_timer_timeout"), &Main::_on_mob_timer_timeout);
}

Ref<PackedScene> Main::get_mob_scene() {
    return mob_scene;
}

void Main::set_mob_scene(Ref<PackedScene> packed_scene) {
    mob_scene = packed_scene;
}

void Main::game_over() {
    get_node<Timer>("MobTimer")->stop();
    get_node<Timer>("ScoreTimer")->stop();

    get_node<Hud>("Hud")->_on_loss();
}

void Main::new_game() {
    score = 0;

    auto player = get_node<Player>("Player");
    auto start_position = get_node<Marker2D>("StartPosition");
    player->start(start_position->get_position());

    get_node<Timer>("StartTimer")->start();

    auto hud = get_node<Hud>("Hud");
    hud->_on_score_change(score);
    hud->show_message("Get Ready!");
}

void Main::_on_score_timer_timeout() {
    score++;
    get_node<Hud>("Hud")->_on_score_change(score);
}

void Main::_on_start_timer_timeout() {
    get_node<Timer>("MobTimer")->start();
    get_node<Timer>("ScoreTimer")->start();
}

void Main::_on_mob_timer_timeout() {
    auto mob = reinterpret_cast<Mob*>(mob_scene->instantiate());

    auto mob_spawn_location = get_node<PathFollow2D>("MobPath/MobSpawnLocation");
    mob_spawn_location->set_progress_ratio(UtilityFunctions::randf());

    Vector2 vec2 = mob_spawn_location->get_global_position();
    float rotation = mob_spawn_location->get_global_rotation();
    mob->start(vec2, rotation);

    add_child(mob);
}

//void Main::_ready() {
// don't start the timers unless we're playing.
// This prevents a Mob from spawning every second while editing.
//    if (Engine::get_singleton()->is_editor_hint()) return;
//    new_game();
// }
