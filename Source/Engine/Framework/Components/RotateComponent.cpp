#include "RotateComponent.h"
#include"Framework/Framework.h"
#include <Core/Math/MathUtils.h>

namespace nc {
    CLASS_DEFINITION(RotateComponent)

    bool RotateComponent::Initialize()
    {
        return false;
    }

    void RotateComponent::Update(float dt)
    {
        m_owner->transform.euler += euler * dt;

        glm::quat rotation = EulerToQuaternion(euler * dt);
        m_owner->transform.rotation = m_owner->transform.rotation * rotation;
    }

    void RotateComponent::SetProgram(const res_t<Program> program)
    {
        program->SetUniform("euler", euler);
    }

    void RotateComponent::ProcessGui()
    {
        ImGui::DragFloat3("euler", glm::value_ptr(euler), 1);
    }

    void RotateComponent::Read(const nc::json_t& value)
    {
        READ_DATA(value, euler);
    }

}