#pragma once
#include "Framework/World.h"
#include "Renderer/Renderer.h"
#include "Core/Math/Transform.h"
#include <vector>

namespace nc
{
	class World04 : public World
	{
	public:
		bool Initialize() override;
		void Shutdown() override;
		void Update(float dt) override;
		void Draw(Renderer& renderer) override;

	private:
		float m_time;
		float m_speed = 5;

		glm::vec3 m_ambientLight = { 0.2, 0.2, 0.2 };
		glm::vec3 m_diffuseLight = { 1, 1, 1 };
		glm::vec3 m_lightPosition = { 0, 8, 0 };

		Transform m_transform;
		res_t<Model> m_model;
		
		res_t<VertexBuffer> m_vertexBuffer;
		res_t<Program> m_program;
		res_t<Texture> m_texture;
		res_t<Material> m_material;
	};
}