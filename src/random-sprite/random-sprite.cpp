#include "random-sprite.h"

using namespace godot;

RandomSprite::RandomSprite() {
	width = 8;
	height = 8;
	color = Color::hex(0x000000FF);
}

void RandomSprite::setWidth(const int p_width) {
	width = p_width;
	onDirty();
}

int RandomSprite::getWidth() const {
	return width;
}

void RandomSprite::setHeight(const int p_height) {
	height = p_height;
	onDirty();
}

int RandomSprite::getHeight() const {
	return height;
}

void RandomSprite::setColor(const Color p_color) {
	color = p_color;
	onDirty();
}

Color RandomSprite::getColor() const {
	return color;
}


Ref<ImageTexture> RandomSprite::createRandomTexture(Ref<RandomNumberGenerator> rng) {
	auto img = Image::create_empty(width, height, false, Image::FORMAT_RGBA8);
	img->fill(Color::named("TRANSPARENT"));
	// TODO: THIS SHIT NEEDS TO NOT CHANGE FOR EVERY INSTANCE
	for (int col = 0; col < width; col++) {
		for (int row = 0; row < height; row++) {
			if (rng->randi_range(0, 1)) {
				img->set_pixel(col, row, color);
			}
		}
	}
	img->resize(width << 4, height << 4, Image::INTERPOLATE_NEAREST);
	return ImageTexture::create_from_image(img);
}

void RandomSprite::onDirty() {
	Ref<RandomNumberGenerator> rng;
	rng.instantiate();
	this->set_texture(createRandomTexture(rng));
	this->queue_redraw();
}

void RandomSprite::_ready() {
	onDirty();
}
