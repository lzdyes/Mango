#pragma once

#include "core/base/String.h"
#include "renderer/GL/REGL.h"

namespace RE {
	class Texture2D {
	public:
		static GLuint CurHandle;
	public:
		Texture2D();
		Texture2D(const char* filepath);
		Texture2D(UI32 width, UI32 height, UI8* data, UI32 len);
		~Texture2D();

		bool InitWithData(UI32 width, UI32 height, UI8* data, UI32 len);
		bool InitWithFile(const char* filepath);
		GLuint GetHandle();

		void Bind();

		void OnGUI();
	public:
		StaticString<128> path;
		Vec2 size;

	protected:
		void clear();

	protected:
		GLuint _handle = 0;
	};
}