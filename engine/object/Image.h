#pragma once
#include "engine/object/GameObject.h"
#include "engine/component/TriangleRenderer.h"

namespace RE {
	class Image : public GameObject {
	public:
		Image();

	public:
		virtual void Render() override;

		virtual void OnGUI() override;
	public:
		TriangleRenderer* renderer = nullptr;
		Color color = Color::White;
	};
}