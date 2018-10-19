#pragma once


#include "Particle.h"
#include "Graphics/Buffers/VertexArray.h"


#ifndef PARTICLE_RENDERER_MAX_SPRITES
#define PARTICLE_RENDERER_MAX_SPRITES 50000
#endif
#define PARTICLE_RENDERER_VERTEX_SIZE  4 * PARTICLE_RENDERER_MAX_SPRITES
#define PARTICLE_RENDERER_INDICES_SIZE 6 * PARTICLE_RENDERER_MAX_SPRITES
#define PARTICLE_RENDERER_BUFFER_SIZE  PARTICLE_RENDERER_VERTEX_SIZE * sizeof(ParticleVertexData)

namespace lonely { namespace graphics {

	class ParticleRenderer
	{
	private:
		ParticleVertexData* m_Buffer;
		VertexArray m_VertexArray;

		unsigned int EBO;
		unsigned int m_IndexCount;

	public:
		ParticleRenderer();
		~ParticleRenderer();

		void Begin();
		void Submit(const Particle* particle);
		void End();
		void Draw();
	};

} }