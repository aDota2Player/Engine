#pragma once

#include <vector>

namespace lonely { namespace graphics {

	class VertexBuffer;

	struct Elements
	{
		unsigned int count;
		unsigned int type;
		unsigned int normalized;
	};

	class VertexArray
	{
	private:
		unsigned int m_ArrayID;

		std::vector<Elements> m_Elements;
		unsigned int m_Stride;

	public:
		VertexArray();
		~VertexArray();

		void Bind() const;
		void UnBind() const;

		void Compile(const VertexBuffer& buffer);

		template <typename>
		void Push(unsigned int count, unsigned int type, unsigned int normalized)
		{
			static_assert(false, "using base template")
		}
		
		template<>
		void Push<char>(unsigned int count, unsigned int type, unsigned int normalized)
		{
			m_Elements.push_back({ count, type, normalized });
			m_Stride += count * sizeof(char);
		}

		template<>
		void Push<short>(unsigned int count, unsigned int type, unsigned int normalized)
		{
			m_Elements.push_back({ count, type, normalized });
			m_Stride += count * sizeof(short);
		}

		template<>
		void Push<int>(unsigned int count, unsigned int type, unsigned int normalized)
		{
			m_Elements.push_back({ count, type, normalized });
			m_Stride += count * sizeof(int);
		}
		
		template<>
		void Push<float>(unsigned int count, unsigned int type, unsigned int normalized)
		{
			m_Elements.push_back({ count, type, normalized });
			m_Stride += count * sizeof(float);
		}

		template<>
		void Push<double>(unsigned int count, unsigned int type, unsigned int normalized)
		{
			m_Elements.push_back({ count, type, normalized });
			m_Stride += count * sizeof(double);
		}

	private:
		static unsigned int SizeOfType(unsigned int type);
	};

} }