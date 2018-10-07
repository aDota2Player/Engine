#include "Layer.h"

namespace lonely { namespace graphics {

	Layer::Layer(Shader* shader, const maths::mat4& projectionMatrix)
		: m_Shader(shader), m_ProjectionMatrix(projectionMatrix)
	{
		m_Renderer = new Renderer();

		m_Shader->Bind();
		m_Shader->SetUniformMat4("u_ProjectionMatrix", m_ProjectionMatrix);

		for (int i = 0; i < 32; i++)
			m_Shader->SetUniform1i("u_Textures[" + std::to_string(i) + ']', i);

		m_Shader->UnBind();
	}

	Layer::~Layer()
	{
		delete m_Renderer;

		for (unsigned int i = 0; i < m_Sprites.size(); i++)
			if(m_Sprites[i])
				delete m_Sprites[i];
		
		ResourceManager::DeleteShader(m_Shader->GetName());
	}

	void Layer::Bind() const
	{
		m_Shader->Bind();
	}

	void Layer::UnBind() const
	{
		m_Shader->UnBind();
	}

	void Layer::Add(Sprite* sprite)
	{
		m_Sprites.push_back(sprite);
	}

	void Layer::Remove(Sprite* sprite)
	{
		const auto it = std::find(m_Sprites.begin(), m_Sprites.end(), sprite);

		if (it != m_Sprites.end())
			m_Sprites.erase(it);
		else
			std::cout << "[ WARNING ]: Sprite has not found" << std::endl;
	} 

	void Layer::Render()
	{
		m_Renderer->Begin();

		for (const Sprite* sprite : m_Sprites)
			if(sprite->IsVisible())
				m_Renderer->Submit(sprite);
			
		m_Renderer->End();
		m_Renderer->Draw();
	}

	void Layer::SetProjectionMatrix(const maths::mat4& projectionMatrix)
	{
		m_Shader->SetUniformMat4("u_ProjectionMatrix", projectionMatrix);
	}

	void Layer::SetModelMatrix(const maths::mat4& modelMatrix)
	{
		m_Shader->SetUniformMat4("u_ModelMatrix", modelMatrix);
	}

	void Layer::SetViewMatrix(const maths::mat4& viewMatrix)
	{
		m_Shader->SetUniformMat4("u_ViewMatrix", viewMatrix);
	}

	void Layer::SetModelViewMatrix(const maths::mat4& modelMatrix, const maths::mat4& viewMatrix)
	{
		m_Shader->SetUniformMat4("u_ModelMatrix", modelMatrix);
		m_Shader->SetUniformMat4("u_ViewMatrix", viewMatrix);
	}

} }