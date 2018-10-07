#include "Renderer.h"

#include <GL/glew.h>

namespace lonely { namespace graphics {

	Renderer::Renderer()
		: m_IndexCount(0), m_VertexBuffer(NULL, RENDERER_BUFFER_SIZE, GL_DYNAMIC_DRAW)
	{
		Initialize();
	}

	Renderer::~Renderer()
	{
	// 	delete m_Buffer;
	}

	void Renderer::Initialize()
	{
		unsigned int* indices = new unsigned int[RENDERER_BUFFER_SIZE];
		unsigned int offset = 0;

		for (int i = 0; i < RENDERER_INDICES_SIZE; i += 6)
		{
			indices[i] = offset + 0;
			indices[i + 1] = offset + 1;
			indices[i + 2] = offset + 2;

			indices[i + 3] = offset + 2;
			indices[i + 4] = offset + 3;
			indices[i + 5] = offset + 0;

			offset += 4;
		}

		m_VertexArray.Push<float>(2, GL_FLOAT, GL_FALSE); // Position 
		m_VertexArray.Push<float>(2, GL_FLOAT, GL_FALSE); // Texture coordinates
		m_VertexArray.Push<float>(1, GL_FLOAT, GL_FALSE); // Texture index
		m_VertexArray.Push<float>(4, GL_FLOAT, GL_FALSE); // Color

		m_VertexArray.Compile(m_VertexBuffer);

		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, RENDERER_INDICES_SIZE, indices, GL_DYNAMIC_DRAW);
		
		delete indices;
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}


	void Renderer::Begin()
	{
		m_VertexBuffer.Bind();
		m_Buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	}

	void Renderer::Submit(const Sprite* sprite)
	{
		const maths::vec2& position = sprite->GetPosition();
		const maths::vec2& size     = sprite->GetSize();
		const maths::vec4& color    = sprite->GetColor();

		const unsigned int texID = sprite->GetTexID();
		
		float textureIndex = 0.0f;
		bool textureExists = false;
		
		for (unsigned char i = 0; i < m_TextureSlots.size(); i++)
		{
			if (m_TextureSlots[i] == texID)
			{
				textureIndex = (float)i;
				textureExists = true;
				break;
			}
		}

		if (!textureExists)
		{
			textureIndex = (float)m_TextureSlots.size();
			m_TextureSlots.push_back(texID);
		}
		 
		m_Buffer->position = position;
		m_Buffer->textureCoordinate = maths::vec2(0.0f, 0.0f);
		m_Buffer->textureID = textureIndex;
		m_Buffer->color = color;
		m_Buffer++;

		m_Buffer->position = maths::vec2(position.x, position.y + size.y);
		m_Buffer->textureCoordinate = maths::vec2(0.0f, 1.0f);
		m_Buffer->textureID = textureIndex;
		m_Buffer->color = color;
		m_Buffer++;

		m_Buffer->position = maths::vec2(position.x + size.x, position.y + size.y);
		m_Buffer->textureCoordinate = maths::vec2(1.0f, 1.0f);
		m_Buffer->textureID = textureIndex;
		m_Buffer->color = color;
		m_Buffer++;

		m_Buffer->position = maths::vec2(position.x + size.x, position.y);
		m_Buffer->textureCoordinate = maths::vec2(1.0f, 0.0f);
		m_Buffer->textureID = textureIndex;
		m_Buffer->color = color;
		m_Buffer++;

		m_IndexCount += 6;
	}

	void Renderer::End()
	{
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	
	void Renderer::Draw()
	{
		
		for (unsigned int i = 0; i < m_TextureSlots.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, m_TextureSlots[i]);
		}

		m_VertexArray.Bind();
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

		glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, NULL);
		m_IndexCount = 0;

		glBindVertexArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

} }