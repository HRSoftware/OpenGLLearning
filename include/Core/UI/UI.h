#pragma once

namespace UI {
    inline void updateUI(GLFWwindow* _window)
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        float rotation = 0;
        ImGui::SliderFloat("rotation", &rotation, 0, 2 * 3.1425);


        if(ImGui::Button("Exit"))
            glfwSetWindowShouldClose(_window, true);

        
    }

    inline void selectList(std::map<std::string, GameObject>& GOs)
    {
        int num;
        if(ImGui::TreeNode("Models"))
        {
            for ( auto &go : GOs )
            {
                if(ImGui::TreeNode(go.first.c_str()))
                {
                    ImGui::Columns(3, NULL, false);
                    if(ImGui::Selectable("Position", false))
                    {
                        go.second.rotateBy(0.1f, { 0, 1, 0 });
                    }
                    char name[32];
                    ImGui::LabelText(name, "(X:%.1f", go.second.getPosition().x);
                    ImGui::NextColumn();
                    ImGui::LabelText(name, "(Y:%.1f", go.second.getPosition().y);
                    ImGui::NextColumn();
                    ImGui::LabelText(name, "(Z:%.1f", go.second.getPosition().z);
                    ImGui::NextColumn();

                    ImGui::TreePop();
                }
                ImGui::Columns(1);
            }
            ImGui::TreePop();
        }
        
    }
}
