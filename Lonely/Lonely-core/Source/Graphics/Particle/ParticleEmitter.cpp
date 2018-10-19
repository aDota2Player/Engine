#include "ParticleEmitter.h"
#include "Particle.h"

#include "../Renderer/Sprite.h"

#include "../Shader/Shader.h"
#include "../Texture/Texture.h"


namespace lonely { namespace  graphics {

	ParticleEmitter::ParticleEmitter(Texture* texture, Shader* shader,
		                             const maths::mat4& projection_matrix, float size,
	                                 float life_max, float life_min,
		                             float x_offset_max, float x_offset_min,
		                             float y_offset_max, float y_offset_min,
		                             float brightness_max, float brightness_min,
		                             unsigned int amount, unsigned int respawn_rate)
		: m_Texture(texture), m_Shader(shader),
		  m_LifeMax(life_max), m_LifeMin(life_min),
		  m_XOffsetMax(x_offset_max), m_XOffsetMin(x_offset_min), m_YOffsetMax(y_offset_max), m_YOffsetMin(y_offset_min), m_BaseOffset(0.0f),
		  m_brightnessMax(brightness_max), m_brightnessMin(brightness_min),
		  m_nrParticles(amount), m_RespawnRate(1.0f / respawn_rate), m_LastUsedParticle(0)
	{
		m_Shader->Bind();
		m_Shader->SetUniformMat4("u_ProjectionMatrix", projection_matrix);
		m_Shader->UnBind();

		for (int i = 0; i < m_nrParticles; i++)
			m_Particles.push_back(Particle(maths::vec2(0.0f), maths::vec2(size, size)));
	}
	
	ParticleEmitter::~ParticleEmitter() { }

	void ParticleEmitter::Render(double delta_time)
	{
		m_Shader->Bind();
		m_Texture->Bind();
	
		m_Renderer.Begin();

		UpdateAndSubmitParticles(delta_time);

		m_Renderer.End();

		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		m_Renderer.Draw();
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		m_Shader->UnBind();
		m_Texture->UnBind();
	}

	void ParticleEmitter::Render(double delta_time, const maths::mat4& projectionMatrix)
	{
		m_Shader->Bind();
		m_Shader->SetUniformMat4("u_ProjectionMatrix", projectionMatrix);

		m_Texture->Bind();
		m_Renderer.Begin();

		UpdateAndSubmitParticles(delta_time);

		m_Renderer.End();

		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		m_Renderer.Draw();
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		m_Shader->UnBind();
		m_Texture->UnBind();
	}

	void ParticleEmitter::UpdateAndSubmitParticles(double delta_time)
	{
		if (m_RespawnRate - m_Timer.ElapsedTime() <= 0.0f)
		{
			m_Timer.reset();
			int unusedParticle = FirstUnusedParticle();
			RespawnParticle(m_Particles[unusedParticle]);
		}

		for (Particle& particle : m_Particles)
		{
			// Update
			particle.life -= delta_time;

			if (particle.life > 0.0f)
			{
				particle.position += particle.velocity * delta_time;
				particle.color.a -= delta_time / particle.lifeSpan;

				m_Renderer.Submit(&particle);
			}
		}
	}

	void ParticleEmitter::RespawnParticle(Particle& particle)
	{
		particle.velocity = m_Velocity;
		particle.life = 1.0f;
		particle.lifeSpan = particle.life;
		particle.position = m_Sprite->GetPosition() + maths::vec2(maths::random(m_XOffsetMin, m_XOffsetMax), maths::random(m_YOffsetMax, m_YOffsetMin)) + m_BaseOffset;
		
		float brightness = maths::random(m_brightnessMin, m_brightnessMax);
		particle.color = maths::vec4(brightness, brightness, brightness, 1.0f);
	}

	unsigned int ParticleEmitter::FirstUnusedParticle()
	{
		for (unsigned int i = m_LastUsedParticle; i < m_nrParticles; i++)
		{
			if (m_Particles[i].life <= 0.0f)
			{
				m_LastUsedParticle = i;
				return i;
			}
		}

		for (unsigned int i = 0; i < m_LastUsedParticle; i++)
		{
			if (m_Particles[i].life <= 0.0f)
			{
				m_LastUsedParticle = i;
				return i;
			}
		}

		m_LastUsedParticle = 0;
		return 0;
	}

} }