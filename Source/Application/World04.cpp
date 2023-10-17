#include "World04.h"
#include "Framework/Framework.h"
#include "Input/InputSystem.h"

#include <glm/glm/gtc/type_ptr.hpp>

#define INTERLEAVE

namespace nc
{
    bool World04::Initialize()
    {
        auto material = GET_RESOURCE(Material, "materials/object.mtrl");
        m_model = std::make_shared<Model>();
        m_model->SetMaterial(material);
        m_model->Load("models/squirrel.glb");

        // vertex data
        float vertexData[] = {
            -0.8f, -0.8f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
            -0.8f,  0.8f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
             0.8f, -0.8f,  0.0f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
             0.8f,  0.8f,  0.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f
        };

        m_vertexBuffer = std::make_shared<VertexBuffer>();
        m_vertexBuffer->CreateVertexBuffer(sizeof(vertexData), 4, vertexData);

        m_vertexBuffer->SetAttribute(0, 3, 8 * sizeof(GLfloat), 0);                  // position 
        m_vertexBuffer->SetAttribute(1, 3, 8 * sizeof(GLfloat), 3 * sizeof(float));  // color 
        m_vertexBuffer->SetAttribute(2, 2, 8 * sizeof(GLfloat), 6 * sizeof(float));  // texcoord

        return true;
    }

    void World04::Shutdown()
    {
    }

    void World04::Update(float dt)
    {
        ENGINE.GetSystem<Gui>()->BeginFrame();

        ImGui::Begin("Transform");
        ImGui::DragFloat3("Position", &m_transform.position[0]);
        ImGui::DragFloat3("Scale", &m_transform.scale[0]);
        ImGui::DragFloat3("Rotation", &m_transform.rotation[0]);
        ImGui::End();

        m_transform.position.x += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_A) ? m_speed * -dt : 0;
        m_transform.position.x += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_D) ? m_speed *  dt : 0;
        m_transform.position.z += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_S) ? m_speed * -dt : 0;
        m_transform.position.z += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_W) ? m_speed *  dt : 0;

        m_time += dt;

        auto material = m_model->GetMaterial();

        material->ProcessGUI();
        material->Bind();

        // model matrix
        material->GetProgram()->SetUniform("model", m_transform.GetMatrix());

        // view matrix
        glm::mat4 view = glm::lookAt(glm::vec3{ 0, 0, 3 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }); // Where the camera is, where the camera is looking, up vector
        material->GetProgram()->SetUniform("view", view);

        // projection matrix
        glm::mat4 projection = glm::perspective(glm::radians(70.0f), 800.0f / 600.0f, 0.01f, 100.0f);
        material->GetProgram()->SetUniform("projection", projection);

        ENGINE.GetSystem<Gui>()->EndFrame();
    }

    void World04::Draw(Renderer& renderer)
    {
        // pre-render
        renderer.BeginFrame();

        // render
        m_model->Draw();
        ENGINE.GetSystem<Gui>()->Draw();

        // post-render
        renderer.EndFrame();
    }
}
