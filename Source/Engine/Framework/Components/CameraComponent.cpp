#include "CameraComponent.h"
#include "Framework/Actor.h"
#include "Framework/Engine.h"

namespace nc
{
	CLASS_DEFINITION(CameraComponent)

	bool CameraComponent::Initialize()
	{
		// get aspect from window if not set
		if (aspect == 0)
		{
			aspect = (float)ENGINE.GetSystem<Renderer>()->GetWidth() / (float)ENGINE.GetSystem<Renderer>()->GetHeight();
		}

		return true;
	}

	void CameraComponent::Update(float dt)
	{
		view = glm::lookAt(m_owner->transform.position, m_owner->transform.position + m_owner->transform.Forward(), m_owner->transform.Up());
		projection = glm::perspective(glm::radians(fov), aspect, near, far);
	}

	void CameraComponent::SetPerspective(float fov, float aspect, float near, float far)
	{
		// set this class fov, aspect, near and far values with parameters (this->fov = fov, ...)
		this->fov = fov;
		this->aspect = aspect;
		this->near = near;
		this->far = far;

		projection = glm::perspective(glm::radians(fov), aspect, near, far);
	}

	void CameraComponent::SetLookAt(const glm::vec3& eye, const glm::vec3& center, const glm::vec3& up)
	{
		view = glm::lookAt(eye, center, up);
	}

	void CameraComponent::SetProgram(res_t<Program> program)
	{
		program->SetUniform("view", view);
		program->SetUniform("projection", projection);
	}

	void CameraComponent::ProcessGui()
	{
		ImGui::DragFloat("fov", &fov, 0.1f);
		ImGui::DragFloat("aspect", &aspect, 0.1f);
		ImGui::DragFloat("near", &near, 0.1f);
		ImGui::DragFloat("far", &far, 0.1f);
	}

	void CameraComponent::Read(const json_t& value)
	{
		READ_DATA(value, fov);
		READ_DATA(value, aspect);
		READ_DATA(value, near);
		READ_DATA(value, far);
	}
}