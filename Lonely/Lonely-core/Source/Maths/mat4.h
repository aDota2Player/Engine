#pragma once

#include "vec4.h"
#include "vec3.h"

namespace lonely { namespace maths {

	struct mat4
	{
		union 
		{
			// [column index + row index * 4] 
			float elements[16];
			vec4 rows[4]; 
		};

		mat4(); // elements = 0
		mat4(float diagonal);	
		mat4(float* elements);
		mat4(const vec4& row0, const vec4& row1, const vec4& row2, const vec4& row3);


		static mat4 Indentity();

		static mat4 Orthographic(float left, float right, float bottom, float top, float near, float far);
		static mat4 Perspective (float fov, float aspectRatio, float near, float far                    );	
		
		static mat4 LookAt(const vec3& camera, const vec3& target, const vec3& up);
	
		static mat4 Rotate   (mat4 matrix, float rotation, const vec3& axis = vec3(0.0f, 0.0f, 1.0f));
		static mat4 Translate(mat4 matrix, const vec3& translation                                  );
		static mat4 Scale    (mat4 matrix, const vec3& scale                                        );

		mat4& Multiply       (const mat4& other           );
		friend mat4 operator*(mat4 left, const mat4& right);
		mat4& operator*=     (const mat4& other           );
	};

} }
