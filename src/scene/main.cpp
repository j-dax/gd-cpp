#include "main.h"
#include "player/player.h"
#include "mob/mob.h"

#include <godot_cpp/core/property_info.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/timer.hpp>
#include <godot_cpp/classes/marker2d.hpp>
#include <godot_cpp/classes/path_follow2d.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

Main::Main() {
    _score = 0;
}

void Main::_bind_methods() {
    ClassDB::bind_method(D_METHOD("getMobScene"), &Main::getMobScene);
    ClassDB::bind_method(D_METHOD("setMobScene", "packedScene"), &Main::setMobScene);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "packedScene", PROPERTY_HINT_RESOURCE_TYPE, "PackedScene"), "setMobScene", "getMobScene");

    // game start/end
    ClassDB::bind_method(D_METHOD("gameOver"), &Main::gameOver);
    ClassDB::bind_method(D_METHOD("newGame"), &Main::newGame);

    // timers
    ClassDB::bind_method(D_METHOD("onScoreTimerTimeout"), &Main::onScoreTimerTimeout);
    ClassDB::bind_method(D_METHOD("onStartTimerTimeout"), &Main::onStartTimerTimeout);
    ClassDB::bind_method(D_METHOD("onMobTimerTimeout"), &Main::onMobTimerTimeout);
}

Ref<PackedScene> Main::getMobScene() {
    return mobScene;
}

void Main::setMobScene(Ref<PackedScene> pScene) {
    mobScene = pScene;
}

void Main::gameOver() {
    get_node<Timer>("MobTimer")->stop();
    get_node<Timer>("ScoreTimer")->stop();
}

void Main::newGame() {
    _score = 0;

    auto player = get_node<Player>("Player");
    auto startPosition = get_node<Marker2D>("StartPosition");
    player->start(startPosition->get_position());

    get_node<Timer>("StartTimer")->start();
}

void Main::onScoreTimerTimeout() {
    _score++;
}

void Main::onStartTimerTimeout() {
    get_node<Timer>("MobTimer")->start();
    get_node<Timer>("ScoreTimer")->start();
}

void Main::onMobTimerTimeout() {
    auto mob = reinterpret_cast<Mob*>(mobScene->instantiate());

    auto mobSpawnLocation = get_node<PathFollow2D>("MobPath/MobSpawnLocation");
    mobSpawnLocation->set_progress_ratio(UtilityFunctions::randf());

    mob->set_global_position(mobSpawnLocation->get_global_position());

    auto direction = mobSpawnLocation->get_rotation() + godot::Math::deg_to_rad(90.0);
    direction += UtilityFunctions::randf_range(-godot::Math::deg_to_rad(45.0), godot::Math::deg_to_rad(45.0));
    mob->set_rotation(direction);

    auto velocity = Vector2(UtilityFunctions::randf_range(150.0, 250.0), 0);
    mob->set_linear_velocity(velocity);

    add_child(mob);
}

void Main::_ready() {
    // don't start the timers unless we're playing.
    // This prevents a Mob from spawning every second while editing.
    if (Engine::get_singleton()->is_editor_hint()) return;
    newGame();
}
