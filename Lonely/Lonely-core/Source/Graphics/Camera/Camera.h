#pragma once

#include "Maths.h"

namespace lonely { namespace graphics {

	enum CameraMovement
	{
		NONE = 0,
		LEFT,
		RIGHT,
		UP,
		DOWN,
	};

	class Camera
	{
	protected:
		maths::mat4 m_Projection;
		maths::mat4 m_ViewMatrix;		

		maths::vec3 m_Position;
		maths::vec3 m_Front;
		maths::vec3 m_Up;

		double m_Speed;

	public:
		Camera(const maths::mat4& projection,
			   double speed = 50.0,
			   const maths::vec3& position = maths::vec3(0.0f, 0.0f, 0.0f ),
			   const maths::vec3& front    = maths::vec3(0.0f, 0.0f, -1.0f),
			   const maths::vec3& up       = maths::vec3(0.0f, 1.0f, 0.0f ));

		// Getters
		// ---------------------------------------------------------------------------
	
		//
		inline const maths::mat4& GetProjectionMatrix() const { return m_Projection; }
		inline const maths::mat4& GetViewMatrix      () const { return m_ViewMatrix; }

		inline const maths::vec3& GetPosition() const { return m_Position; }
		inline const maths::vec3& GetFront   () const { return m_Front;    }
		inline const maths::vec3& GetUp      () const { return m_Up;       }

		inline double GetSpeed() const { return m_Speed; }

		// Setters
		// ---------------------------------------------------------------------------

		inline void SetProjectionMatrix(const maths::mat4& projection) { m_Projection = projection; UpdateViewMatrix(); }
		inline void SetViewMatrix      (const maths::mat4& view      ) { m_ViewMatrix = view;       UpdateViewMatrix(); }

		inline void SetPosition(const maths::vec3& position) { m_Position = position; UpdateViewMatrix(); }
		inline void SetFront   (const maths::vec3& front   ) { m_Front = front;       UpdateViewMatrix(); }
		inline void SetUp      (const maths::vec3& up      ) { m_Up = up;             UpdateViewMatrix(); }

		inline void SetSpeed(double speed) { m_Speed = speed; }

		void ProcessKeyboard(CameraMovement dir, double deltaTime);

	private:
		inline void UpdateViewMatrix() { m_ViewMatrix = maths::mat4::LookAt(m_Position, m_Position + m_Front, m_Up); }
	
	};

} }
