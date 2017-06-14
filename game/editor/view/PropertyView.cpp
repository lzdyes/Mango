#include "PropertyView.h"
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "renderer/PipeLine.h"


namespace RE {

	void PropertyView::OnGUI() {
		bool is_opened = true;
		if (ImGui::BeginDock("Property", &is_opened, ImGuiWindowFlags_NoScrollWithMouse)) {
			static float x = 0.0f, y = 0.0f, z = 0.0f;
			ImGui::DragFloat3("Position", &x, 0.1f);

			static float values[90] = { 0 };
			static int values_offset = 0;
			values[values_offset] = 1000.0f / ImGui::GetIO().Framerate;// cosf(phase);
			values_offset = (values_offset + 1) % IM_ARRAYSIZE(values);

			char status[200];
			sprintf(status, "FPS: %.0f/%.1f", ImGui::GetIO().Framerate, 1000.0f / ImGui::GetIO().Framerate);
			ImGui::PlotLines("##FPS", values, IM_ARRAYSIZE(values), values_offset, status, -10.0f, 10.0f, ImVec2(0, 80));

			if (ImGui::Button("Compile Shader")) {
				auto pl = PipeLine();
				pl.Init("shaders/default.vert", "shaders/default.frag");
			}

		}
		ImGui::EndDock();
	}

}