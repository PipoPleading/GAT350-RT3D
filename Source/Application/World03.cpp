#include "World03.h"
#include "Framework/Framework.h"
#include "Renderer/Renderer.h"
#include "Input/InputSystem.h"
#include "glm/glm/gtc/type_ptr.hpp"


#define INTERLEAVE //

namespace nc
{
    bool World03::Initialize()
    {
        m_program = GET_RESOURCE(Program, "shaders/unlit_texture.prog");
        m_program->Use();

        m_texture = GET_RESOURCE(Texture, "textures/llama.jpg");
        m_texture->Bind();
        m_texture->SetActive(GL_TEXTURE0);

        //preprocess directives

       float vertexData[] = {
           -0.8f, -0.8f, 0.0f,  0.0f, 1.0f, 1.0f,  0.0f, 0.0f,
            0.8f, -0.8f, 0.0f,  0.6f, 0.0f, 0.6f,  1.0f, 0.0f,
            0.8f,  0.8f, 0.0f,  1.0f, 0.0f, 1.0f,  1.0f, 1.0f,
            -0.8f, 0.8f, 0.0f,  0.0f, 0.0f, 0.0f,  0.0f, 1.0f
        };
       //GLuint vbo;

       m_vertexBuffer = GET_RESOURCE(VertexBuffer, "vb");
       m_vertexBuffer->CreateVertexBuffer(sizeof(vertexData), 4, vertexData);
       m_vertexBuffer->SetAttribute(0, 3, 8 * sizeof(GLfloat), 0);                  // position 
       m_vertexBuffer->SetAttribute(1, 3, 8 * sizeof(GLfloat), 3 * sizeof(float));  // color 
       m_vertexBuffer->SetAttribute(2, 2, 8 * sizeof(GLfloat), 6 * sizeof(float));  // texcoord

       

       // old code 

       ////position
       //glGenBuffers(1, &vbo);
       //glBindBuffer(GL_ARRAY_BUFFER, vbo);
       //glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData , GL_STATIC_DRAW);
      
       //glGenVertexArrays(1, &m_vao);
       //glBindVertexArray(m_vao);

       //glBindVertexBuffer(0, vbo, 0, 8 * sizeof(GLfloat)); //stride is the distance between data chunks, so 6 here

       ////position
       //glEnableVertexAttribArray(0); 
       //glVertexAttribFormat(0, 3, GL_FLOAT, GL_FALSE, 0);
       //glVertexAttribBinding(0, 0);

       ////color
       //glEnableVertexAttribArray(1);
       //glVertexAttribFormat(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat));
       //glVertexAttribBinding(1, 0);

       ////color
       //glEnableVertexAttribArray(2);
       //glVertexAttribFormat(2, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat));
       //glVertexAttribBinding(2, 0);

       //deleted interleaves

       return true;
    }

    void World03::Shutdown()
    {
    }

    void World03::Update(float dt)
    {
        ENGINE.GetSystem<Gui>()->BeginFrame();


        ImGui::Begin("Transform");
        ImGui::DragFloat3("Position", &m_transform.position[0]);
        ImGui::DragFloat3("Rotation", &m_transform.rotation[0]);
        ImGui::DragFloat3("Scale", &m_transform.scale[0]);
        ImGui::DragFloat2("Offset", &m_offset[0]);
        ImGui::DragFloat2("Tile", &m_tile[0]);
        ImGui::End();

        m_program->SetUniform("offset", m_offset);
        m_program->SetUniform("tiling", m_tile);

        //m_transform.rotation.z += 180 * dt;

        //controls
        m_transform.position.x += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_A) ? -dt * m_speed : 0;
        m_transform.position.x += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_D) ? dt * m_speed : 0;

        m_transform.position.z += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_BACKSPACE) ? -dt * m_speed : 0;
        m_transform.position.z += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_SPACE) ? dt * m_speed : 0;

        m_transform.position.y += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_S) ? -dt * m_speed: 0;
        m_transform.position.y += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_W) ? dt * m_speed : 0;

        m_time += dt;



        //model matrix
        //glm::mat4 position = glm::translate(glm::mat4{ 1 }, m_position);
        //glm::mat4 rotation = glm::rotate(glm::mat4{ 1 }, m_angle, glm::vec3{ 0, 0, 1 });
        //glm::mat4 model = position * rotation;
        m_program->SetUniform("model", m_transform.GetMatrix());

        //view matrix
        glm::mat4 view = glm::lookAt(glm::vec3{ 0, 0, 5 }, glm::vec3{ 0 ,0 ,3 }, glm::vec3{ 0, 1, 0 });
        m_program->SetUniform("view", view);
        //uniform = glGetUniformLocation(m_program->m_program, "view");
        //glUniformMatrix4fv(uniform, 1, GL_FALSE, glm::value_ptr(view));

        // projection matrix
        glm::mat4 projection = glm::perspective(glm::radians(70.0f), 800.0f/600.0f, 0.01f, 100.0f);
        m_program->SetUniform("projection", projection);/*
        uniform = glGetUniformLocation(m_program->m_program, "projection");
        glUniformMatrix4fv(uniform, 1, GL_FALSE, glm::value_ptr(projection));*/

        ENGINE.GetSystem<Gui>()->EndFrame();
    }

    void World03::Draw(Renderer& renderer)
    {
       // pre-render
        renderer.BeginFrame();
        // render
        m_vertexBuffer->Draw(GL_QUADS);
        ENGINE.GetSystem<Gui>()->Draw();
        // post-render
        renderer.EndFrame();

        // old code
        
        //// pre-render
        //renderer.BeginFrame();

        //// render
        //glBindVertexArray(m_vao);
        //glDrawArrays(GL_QUADS, 0, 4);

        //ENGINE.GetSystem<Gui>()->Draw();


        // post-render
    }
}
