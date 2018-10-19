#pragma once

#include "../Buffers/VertexArray.h"

#ifndef RENDERER_MAX_SPRITES
#define RENDERER_MAX_SPRITES	50000
#endif
#define RENDERER_VERTEX_SIZE	4 * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE	6 * RENDERER_MAX_SPRITES
#define RENDERER_BUFFER_SIZE	RENDERER_VERTEX_SIZE * sizeof(VertexData)

#include <vector>

namespace lonely { namespace graphics { 

	class Sprite;
	struct VertexData;

	class Renderer
	{
	private:
		VertexData* m_Buffer;
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
