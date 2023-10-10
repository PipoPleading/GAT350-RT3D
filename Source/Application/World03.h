#pragma once
#include "Framework/World.h"
#include "Renderer/Renderer.h"
#include <vector>

namespace nc
{
	class World03 : public World
	{
	public:
		bool Initialize() override;
		void Shutdown() override;
		void Update(float dt) override;
		void Draw(Renderer& renderer) override;

	private:
		float m_angle = 0;
		float m_speed = 5;

		Transform m_transform;

		GLuint m_vao = 0;
		res_t<Program> m_program;
	};
}