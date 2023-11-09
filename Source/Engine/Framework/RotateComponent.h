#pragma once
#include "Components/Component.h"
#include "Actor.h"

namespace nc
{
	class RotateComponent : public Component
	{
	public:
		CLASS_DECLARATION(RotateComponent)

		bool Initialize() override;
		void Update(float dt) override;

		void ProcessGui();

	private:
		glm::vec3 euler{ 0 };
	};
}