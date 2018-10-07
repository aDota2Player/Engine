#pragma once

#include "Sprite.h"

#include "../Buffers/VertexArray.h"
#include "../Buffers/VertexBuffer.h"

#define RENDERER_MAX_SPRITES	50000
#define RENDERER_VERTEX_SIZE	4 * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE	6 * RENDERER_MAX_SPRITES
#define RENDERER_BUFFER_SIZE	RENDERER_VERTEX_SIZE * sizeof(VertexData)

#define VERTEX_POSITION_INDEX	0
#define VERTEX_TEXCOORD_INDEX	1
#define VERTEX_TEXID_INDEX		2
#define VERTEX_COLOR_INDEX		3

#include <vector>

namespace lonely { namespace graphics { 

	class Renderer
	{
	private:
		VertexData* m_Buffer;
		VertexBuffer m_VertexBuffer;
		VertexArray m_VertexArray;

		unsigned int EBO;
		unsigned int m_IndexCount;

		std::vector<int> m_TextureSlots;

	public:
		Renderer();
		~Renderer();

		void Begin();
		void Submit(const Sprite* sprite);
		void End();
		void Draw();

	private:
		void Initialize();
	};

} } 
