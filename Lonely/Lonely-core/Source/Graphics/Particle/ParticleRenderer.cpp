#include "ParticleRenderer.h"
#include "Graphics/Buffers/VertexBuffer.h"

#include <GL/glew.h>

namespace lonely { namespace graphics {
	
	ParticleRenderer::ParticleRenderer()
	{
		unsigned int* indices = new unsigned int[PARTICLE_RENDERER_BUFFER_SIZE];
		unsigned int offset = 0;

		for (int i = 0; i < PARTICLE_RENDERER_INDICES_SIZE; i += 6)
		{
			indices[i] = offset + 0;
			indices[i + 1] = offset + 1;
			indices[i + 2] = offset + 2;

			indices[i + 3] = offset + 2;
			indices[i + 4] = offset + 3;
			indices[i + 5] = offset + 0;

			offset += 4;
		}

		VertexBuffer vertexBuffer;
		vertexBuffer.Compile(NULL, PARTICLE_RENDERER_BUFFER_SIZE, GL_DYNAMIC_DRAW);

		m_VertexArray.Push<float>(2, GL_FLOAT, GL_FALSE);
		m_VertexArray.Push<float>(2, GL_FLOAT, GL_FALSE);
		m_VertexArray.Push<float>(4, GL_FLOAT, GL_FALSE);
		m_VertexArray.Compile(vertexBuffer);

		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, PARTICLE_RENDERER_INDICES_SIZE, indices, GL_DYNAMIC_DRAW);

		delete indices;
		m_VertexArray.UnBindArray();
		m_VertexArray.UnBindBuffer();
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}


	ParticleRenderer::~ParticleRenderer()
	{
		delete m_Buffer;
	}

	void ParticleRenderer::Begin()
	{
		m_VertexArray.BindBuffer();
		m_Buffer = (ParticleVertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	}

	void ParticleRenderer::Submit(const Particle* particle)
	{
		const maths::vec2& position = particle->position;
		const maths::vec2& size = particle->size;
		const maths::vec4& color = particle->color;
	
	
		m_Buffer->position = position;
		m_Buffer->textureCoordinate = maths::vec2(0.0f, 0.0f);
		m_Buffer->color = color;
		m_Buffer++;

		m_Buffer->position = maths::vec2(position.x, position.y + size.y);
		m_Buffer->textureCoordinate = maths::vec2(0.0f, 1.0f);
		m_Buffer->color = color;
		m_Buffer++;

		m_Buffer->position = maths::vec2(position.x + size.x, position.y + size.y);
		m_Buffer->textureCoordinate = maths::vec2(1.0f, 1.0f);
		m_Buffer->color = color;
		m_Buffer++;

		m_Buffer->position = maths::vec2(position.x + size.x, position.y);
		m_Buffer->textureCoordinate = maths::vec2(1.0f, 0.0f);
		m_Buffer->color = color;
		m_Buffer++;

		m_IndexCount += 6;
	}

	void ParticleRenderer::End()
	{
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void ParticleRenderer::Draw()
	{
		m_VertexArray.BindArray();
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

		glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, NULL);
		m_IndexCount = 0;

		m_VertexArray.UnBindArray();
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

} }