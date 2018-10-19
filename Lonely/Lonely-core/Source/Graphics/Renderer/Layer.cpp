#include "Layer.h"

#include "../Shader/Shader.h"

#include "Sprite.h"

#include "Maths.h"

namespace lonely { namespace graphics {

	Layer::Layer(Shader* shader, const maths::mat4& projection_matrix)
		: m_Shader(shader), m_ProjectionMatrix(projection_matrix)
	{
		m_Shader->Bind();
		m_Shader->SetUniformMat4("u_ProjectionMatrix", m_ProjectionMatrix);

		for (int i = 0; i < 32; i++)
			m_Shader->SetUniform1i("u_Textures[" + std::to_string(i) + ']', i);

		m_Shader->UnBind();
	}

	Layer::~Layer()
	{
		for (unsigned int i = 0; i < m_Sprites.size(); i++)
			if(m_Sprites[i])
				delete m_Sprites[i];
	}

	void Layer::Add(Sprite* sprite)
	{
		m_Sprites.push_back(sprite);
	}

	void Layer::Remove(Sprite* sprite)
	{
		const auto it = std::find(m_Sprites.begin(), m_Sprites.end(), sprite);

		if (it != m_Sprites.end())
		{
			m_Sprites.erase(it);
			delete sprite;
		}
		else
			std::cout << "[ WARNING ]: Sprite has not found" << std::endl;
	} 

	void Layer::Render()
	{
		m_Shader->Bind();
		m_Renderer.Begin();

		for (const Sprite* sprite : m_Sprites)
			if(sprite->IsVisible())
				m_Renderer.Submit(sprite);
			
		m_Renderer.End();
		m_Renderer.Draw();
		m_Shader->UnBind();
	}

	void Layer::Render(const maths::mat4& projection_matrix)
	{
		m_Shader->Bind();
		m_Shader->SetUniformMat4("u_ProjectionMatrix", projection_matrix);

		m_Renderer.Begin();

		for (const Sprite* sprite : m_Sprites)
			if (sprite->IsVisible())
				m_Renderer.Submit(sprite);

		m_Renderer.End();
		m_Renderer.Draw();
		m_Shader->UnBind();
	}

	void Layer::Render(const maths::mat4& projection_matrix, const maths::mat4& view_matrix)
	{
		m_Shader->Bind();
		m_Shader->SetUniformMat4("u_ProjectionMatrix", projection_matrix);
		m_Shader->SetUniformMat4("u_ViewMatrix", view_matrix);

		m_Renderer.Begin();

		for (const Sprite* sprite : m_Sprites)
			if (sprite->IsVisible())
				m_Renderer.Submit(sprite);

		m_Renderer.End();
		m_Renderer.Draw();
		m_Shader->UnBind();
	}

} }