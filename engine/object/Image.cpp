#include "Image.h"

RE::Image::Image(const char* name/* = "" */) 
	: GameObject(name)
{
	init();
}

void RE::Image::OnDraw(const Affine& viewMat) {
	if (renderer != nullptr) {
		auto& verts = renderer->triangles.verts;
		auto size = verts.size;
		auto data = verts.data;
		for (decltype(size) i = 0; i < size; ++i) {
			memcpy(data[i].color, &color.r, sizeof(float) * 4);
		}
		renderer->draw(viewMat);
	}
}

bool RE::Image::init() {
	renderer = AddComponent<TriangleRenderer>();
	renderer->canRemove = false;
	transform.ax = transform.ay = 0.5f;
	return true;
}
