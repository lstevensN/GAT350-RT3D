#pragma once
#include "Framework/World.h"
#include "Renderer/Renderer.h"
#include "Core/Math/Transform.h"
#include <vector>

namespace nc
{
	class World06 : public World
	{
	public:
		const uint32_t INVERT_MASK       = (1 << 0);
		const uint32_t GRAYSCALE_MASK    = (1 << 1);
		const uint32_t COLOR_TINT_MASK   = (1 << 2);
		const uint32_t GRAIN_MASK        = (1 << 3);
		const uint32_t SCANLINE_MASK     = (1 << 4);
		const uint32_t CUSTOM_MASK       = (1 << 5);

	public:
		bool Initialize() override;
		void Shutdown() override;
		void Update(float dt) override;
		void Draw(Renderer& renderer) override;

	private:
		float m_time;
		float m_speed = 5;
		float m_blend{ 1 };

		uint32_t m_params{ 0 };

		glm::vec3 m_ambientLight{ 1.0f };
		glm::vec3 m_tint{ 1.0f, 0.0f, 0.0f };
		float m_refraction{ 1 };
	};
}