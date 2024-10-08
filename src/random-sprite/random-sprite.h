#pragma once

#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/classes/image_texture.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>

using namespace godot;

class RandomSprite : public Sprite2D {
	GDCLASS(RandomSprite, Sprite2D)

private:
	bool dirty;
	int width;
	int height;
	Color color;
	Ref<ImageTexture> imageTexture;

	static void _bind_methods() {
		ClassDB::bind_method(D_METHOD("getWidth"), &RandomSprite::getWidth);
		ClassDB::bind_method(D_METHOD("setWidth", "width"), &RandomSprite::setWidth);
		ADD_PROPERTY(PropertyInfo(Variant::INT, "width"), "setWidth", "getWidth");

		ClassDB::bind_method(D_METHOD("getHeight"), &RandomSprite::getHeight);
		ClassDB::bind_method(D_METHOD("setHeight", "height"), &RandomSprite::setHeight);
		ADD_PROPERTY(PropertyInfo(Variant::INT, "height"), "setHeight", "getHeight");

		ClassDB::bind_method(D_METHOD("getColor"), &RandomSprite::getColor);
		ClassDB::bind_method(D_METHOD("setColor", "color"), &RandomSprite::setColor);
		ADD_PROPERTY(PropertyInfo(Variant::COLOR, "color"), "setColor", "getColor");
	}

	// helper
	Ref<ImageTexture> createRandomTexture(Ref<RandomNumberGenerator> rng);
	void onDirty();
protected:

public:
	RandomSprite();
	~RandomSprite() = default;

	// engine binding
	void _ready() override;

	// signals
	void setWidth(const int p_width);
	int getWidth() const;

	void setHeight(const int p_height);
	int getHeight() const;

	void setColor(const Color p_color);
	Color getColor() const;
};
