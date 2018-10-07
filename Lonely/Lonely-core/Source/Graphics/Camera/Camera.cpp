#include "Camera.h"

namespace lonely { namespace graphics {

	Camera::Camera(const maths::mat4& projection,
	 	           double speed, const maths::vec3& position, const maths::vec3& front, const maths::vec3& up)
		: m_Projection(projection), m_Position(position), m_Front(front), m_Up(up), m_Speed(speed)
	{
		m_ViewMatrix = maths::mat4::LookAt(position, position + front, up);
	}

	void Camera::ProcessKeyboard(CameraMovement dir, double deltaTime)
	{
		double velocity = m_Speed * deltaTime;

		if (dir == LEFT)
			m_Position.x -= (float)velocity;
		if (dir == RIGHT)	
			m_Position.x += (float)velocity;

		if (dir == UP)
			m_Position.y -= (float)velocity;
		if (dir == DOWN)
			m_Position.y += (float)velocity;

		UpdateViewMatrix();
	}

} }