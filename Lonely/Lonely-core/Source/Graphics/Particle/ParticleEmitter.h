#pragma once

#include "ParticleRenderer.h"

#include "Timer.h"

#include <vector>

namespace lonely { namespace graphics {
	
	class Particle;
	class Sprite;
	class Shader;
	class Texture;

	class ParticleEmitter
	{
	private:
		std::vector<Particle> m_Particles;

		ParticleRenderer m_Renderer;
		Texture* m_Texture;
		Shader* m_Shader;

		Sprite* m_Sprite;

		Timer m_Timer;

		maths::vec2 m_BaseOffset;

		float m_LifeMin, m_LifeMax;
		float m_XOffsetMin, m_XOffsetMax;
		float m_YOffsetMin, m_YOffsetMax;
		float m_brightnessMin, m_brightnessMax;
		maths::vec2 m_Velocity;

		float m_RespawnRate;
		unsigned int m_nrParticles;
		unsigned int m_LastUsedParticle;

	public:
		ParticleEmitter(Texture* texture, Shader* shader,
			            const maths::mat4& projection_matrix, float size,
			            float life_max, float life_min,
			            float x_offset_max, float x_offset_min,
						float y_offset_max, float y_offset_min,
			            float brightness_max, float brightness_min,
			            unsigned int amount, unsigned int respawn_rate);
		~ParticleEmitter();

		void Render(double delta_time);
		void Render(double delta_time, const maths::mat4& projectionMatrix);

		inline void AttachEmitterTo(Sprite* sprite) { m_Sprite = sprite; };

		inline void SetVelocity(const maths::vec2& velocity) { m_Velocity = velocity; }
		inline void SetBaseOffset(const maths::vec2& offset) { m_BaseOffset = offset; }

	private:
		void UpdateAndSubmitParticles(double delta_time);
		void RespawnParticle(Particle& particle);
		
		unsigned int FirstUnusedParticle();
	};

} }