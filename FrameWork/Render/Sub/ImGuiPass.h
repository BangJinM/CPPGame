#pragma once
#include "../ISubPass.h"
#include "ShaderManager.h"
#include "imgui.h"
#include "../Platform/OpenGL/imgui_impl_glfw.h"
#include "../Platform/OpenGL/imgui_impl_opengl3.h"

namespace GameEngine
{
    extern ShaderManager *g_pShaderManager;
    class ImGuiPass : public ISubPass
    {
    public:
        virtual void Initialize() override
        {
        }

        virtual void BeginDraw() override
        {
        }

        virtual void Draw(SharedCamera camera) override
        {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
            static bool show_another_window, show_demo_window = true;
            // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
            if (show_demo_window)
                ImGui::ShowDemoWindow(&show_demo_window);

            // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
            {
                static float f = 0.0f;
                static int counter = 0;

                ImGui::Begin("Hello, world!");  // Create a window called "Hello, world!" and append into it.

                ImGui::Text("This is some useful text.");  // Display some text (you can use a format strings too)

                ImGui::SliderFloat("float", &f, 0.0f, 1.0f);  // Edit 1 float using a slider from 0.0f to 1.0f

                if (ImGui::Button("Button"))  // Buttons return true when clicked (most widgets return true when edited/activated)
                    counter++;
                ImGui::SameLine();
                ImGui::Text("counter = %d", counter);

                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
                ImGui::End();
            }

            // 3. Show another simple window.
            if (show_another_window)
            {
                ImGui::Begin("Another Window", &show_another_window);  // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
                ImGui::Text("Hello from another window!");
                if (ImGui::Button("Close Me"))
                    show_another_window = false;
                ImGui::End();
            }
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        }

        virtual void EndDraw() override
        {
        }

        int m_ShaderID;
    };
}  // namespace GameEngine
