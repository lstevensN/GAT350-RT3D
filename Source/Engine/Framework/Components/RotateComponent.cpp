#include "RotateComponent.h"

namespace nc
{
    CLASS_DEFINITION(RotateComponent)

    bool RotateComponent::Initialize()
    {
        return true;
    }

    void RotateComponent::Update(float dt)
    {
        m_owner->transform.euler += euler * dt;

        glm::quat rotation = EulerToQuaternion(euler * dt);

        m_owner->transform.rotation = m_owner->transform.rotation * rotation;
    }

    void RotateComponent::ProcessGui()
    {
        ImGui::DragFloat3("Rotate Speed", glm::value_ptr(euler), 1.0f);
    }

    void RotateComponent::Read(const json_t& value)
    {
        READ_NAME_DATA(value, "rotation", euler);
    }
}
