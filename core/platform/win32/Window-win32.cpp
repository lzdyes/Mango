#include "platform/Window.h"

#include <imgui/imgui.h>
#include "imgui_impl_glfw_gl3.h"
#include <stdio.h>
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <string>
#include "../FileUtils.h"
#include "base/String.h"
#include "imgui/imgui_tab_demo.h"

using namespace RE;

GLFWwindow* window = nullptr;

static void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error %d: %s\n", error, description);
}

bool Window::initGL()
{
	if (window != nullptr) {
		close();
	}

	// Setup window
	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
		return false;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	window = glfwCreateWindow(1280, 720, "ImGui OpenGL3 example", NULL, NULL);
	glfwMakeContextCurrent(window);
	gl3wInit();

	// Setup ImGui binding
	ImGui_ImplGlfwGL3_Init(window, true);

	return true;
}

bool Window::close()
{
	if (window == nullptr) return true;

	// Cleanup
	ImGui_ImplGlfwGL3_Shutdown();
	glfwTerminate();
	window = nullptr;

	return true;
}

bool Window::loop()
{
	bool show_test_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImColor(114, 144, 154);

	int display_w, display_h;

	glfwGetFramebufferSize(window, &display_w, &display_h);

	// Main loop
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		ImGui_ImplGlfwGL3_NewFrame();

		ImGui::RootDock(ImVec2(0, 0), ImVec2(display_w, display_h));

		{
			static bool is_opened = true;
			if (ImGui::BeginDock("Navigation1", &is_opened, ImGuiWindowFlags_NoScrollWithMouse))
			{		
				{
					static float f = 0.0f;
					ImGui::Text("Hello Mango");
					ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
					ImGui::ColorEdit3("clear color", (float*)&clear_color);
					if (ImGui::Button("Test Window")) show_test_window ^= 1;
					if (ImGui::Button("Another Window")) show_another_window ^= 1;
					ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
				}

				static float color[4] = {0, 0, 0, 0};
				ImGui::ColorPicker(color, true);
			}
			ImGui::EndDock();
		}
		{
			static bool is_opened = true;
			if (ImGui::BeginDock("Navigation2", &is_opened, ImGuiWindowFlags_MenuBar))
			{
				{
					static float f = 0.0f;
					ImGui::Text("Hello Mango");
					ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
					ImGui::ColorEdit3("clear color", (float*)&clear_color);
					if (ImGui::Button("Test Window")) show_test_window ^= 1;
					if (ImGui::Button("Another Window")) show_another_window ^= 1;
					ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
					static float color[4] = { 0, 0, 0, 0 };
					ImGui::ColorPicker(color, true);
				}
			}
			ImGui::EndDock();
		}
		{
			static bool is_opened = true;
			if (ImGui::BeginDock("Navigation3", &is_opened))
			{
				{
					static float f = 0.0f;
					ImGui::Text("Hello Mango");
					ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
					ImGui::ColorEdit3("clear color", (float*)&clear_color);
					if (ImGui::Button("Test Window")) show_test_window ^= 1;
					if (ImGui::Button("Another Window")) show_another_window ^= 1;
					ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
					static float color[4] = { 0, 0, 0, 0 };
					ImGui::ColorPicker(color, true);
				}
			}
			ImGui::EndDock();
		}

		// 1. Show a simple window
		// Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets appears in a window automatically called "Debug"
		//{
		//	static float f = 0.0f;
		//	ImGui::Text("Hello Mango");
		//	ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
		//	ImGui::ColorEdit3("clear color", (float*)&clear_color);
		//	if (ImGui::Button("Test Window")) show_test_window ^= 1;
		//	if (ImGui::Button("Another Window")) show_another_window ^= 1;
		//	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		//}

		//// 2. Show another simple window, this time using an explicit Begin/End pair
		//if (show_another_window)
		//{
		//	ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_FirstUseEver);
		//	ImGui::Begin("Another Window", &show_another_window);
		//	ImGui::Text("Hello");
		//	ImGui::End();
		//}

		//// 3. Show the ImGui test window. Most of the sample code is in ImGui::ShowTestWindow()
		//if (show_test_window)
		//{
		//	ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiSetCond_FirstUseEver);
		//	ImGui::ShowTestWindow(&show_test_window);
		//}

		//ShowTabDemo();

		// Rendering
		glfwGetFramebufferSize(window, &display_w, &display_h);

		glViewport(0, 0, display_w, display_h);
		glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui::Render();
		glfwSwapBuffers(window);
	}

	return true;
}

Window::Window()
{
	initGL();
}

Window::~Window()
{
	close();
}