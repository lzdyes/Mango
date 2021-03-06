#include <functional>

#include "InputSystem.h"
#include "core/platform/Platform.h"
#include "engine/object/GameObject.h"
#include "engine/Engine.h"

namespace RE {


	void InputSystem::OnMouseDown(float x, float y, int idx/* = 0*/) {
		Log("Mouse Begin: %.2f  %.2f", x, y);

		curMousePos.Set(x, y);
		mouseState[idx] = true;
	}

	void InputSystem::OnMouseUp(float x, float y, int idx/* = 0*/) {
		Log("Mouse End: %.2f  %.2f", x, y);

		curMousePos.Set(x, y);
		mouseState[idx] = false;
	}

	void InputSystem::OnMouseMove(float x, float y, float dx, float dy, int idx/* = 0*/) {
		Log("Mouse Move: %.2f  %.2f %.2f  %.2f", x, y, dx, dy);

		curMousePos.Set(x, y);
		curMouseDelta.Set(dx, dy);
	}

	GameObject* InputSystem::PickUp(GameObject* root, float x, float y) {
		Array<GameObject*> list;
		std::function<void(GameObject*)> trav = [&](GameObject* root) {
			list.Push(root);
			for (int idx = 0; idx < root->children.size; ++idx) {
				trav(root->children[idx]);
			}
		};

		for (int idx = 0; idx < root->children.size; ++idx) {
			trav(root->children[idx]);
		}

		for (int idx = list.size - 1; idx >= 0; --idx) {
			auto& trans = list[idx]->transform;
			Vec2 localPos = trans.WorldToLocal(Vec2(x, y));

			if (Rect(0, 0, trans.w, trans.h).Contains(localPos)) {
				return list[idx];
			}
		}
		return nullptr;
	}

}