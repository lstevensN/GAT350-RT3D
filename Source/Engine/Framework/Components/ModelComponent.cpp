#include "ModelComponent.h"
#include "Framework/Actor.h"
#include "Framework/Resource/ResourceManager.h"
#include "Core/StringUtils.h"
#include "Renderer/Gui.h"

namespace nc
{
	CLASS_DEFINITION(ModelComponent)

	bool ModelComponent::Initialize()
	{
		if (!modelName.empty())
		{
			model = GET_RESOURCE(Model, modelName);
		}

		if (model && !materialName.empty())
		{
			material = GET_RESOURCE(Material, materialName);
		}

		return true;
	}

	void ModelComponent::Update(float dt)
	{
	}

	void ModelComponent::Draw(Renderer& renderer)
	{
		material->Bind();
		material->GetProgram()->SetUniform("model", m_owner->transform.GetMatrix());

		glDepthMask(enableDepth);
		glCullFace(cullface);

		model->Draw();
	}

	void ModelComponent::ProcessGui()
	{
		ImGui::Checkbox("Cast Shadow", &castShadow);
		ImGui::Checkbox("Enable Depth", &enableDepth);
	}

	void ModelComponent::Read(const json_t& value)
	{
		READ_DATA(value, modelName);
		READ_DATA(value, materialName);

		READ_DATA(value, castShadow);
		READ_DATA(value, enableDepth);

		std::string cullfaceName;
		if (READ_NAME_DATA(value, "cullface", cullfaceName))
		{
			if (StringUtils::IsEqualIgnoreCase(cullfaceName, "front")) cullface = GL_FRONT;
			if (StringUtils::IsEqualIgnoreCase(cullfaceName, "none")) cullface = GL_NONE;
		}
	}
}
