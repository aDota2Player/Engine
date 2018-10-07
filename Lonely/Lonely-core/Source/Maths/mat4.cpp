#include "Maths.h"

namespace lonely { namespace maths {


	mat4::mat4()
	{
		memset(elements, 0, 4 * 4 * sizeof(float));
	}

	mat4::mat4(float diagonal)
	{
		memset(elements, 0, 4 * 4 * sizeof(float));

		elements[0 + 0 * 4] = diagonal;
		elements[1 + 1 * 4] = diagonal;
		elements[2 + 2 * 4] = diagonal;
		elements[3 + 3 * 4] = diagonal;
	}

	mat4::mat4(float* elements)
	{
		memcpy(this->elements, elements, 4 * 4 * sizeof(float));
	}

	mat4::mat4(const vec4& row0, const vec4& row1, const vec4& row2, const vec4& row3)
	{
		rows[0] = row0;
		rows[1] = row1;
		rows[2] = row2;
		rows[3] = row3;
	}

	mat4 mat4::Indentity()
	{
		return mat4(1.0f);
	}

	mat4 mat4::Orthographic(float left, float right, float bottom, float top, float near, float far)
	{
		mat4 result(1.0f);

		result.elements[0 + 0 * 4] = 2.0f / (right - left);
		result.elements[1 + 1 * 4] = 2.0f / (top - bottom);
		result.elements[2 + 2 * 4] = 2.0f / (near - far);

		result.elements[3 + 0 * 4] = (left + right) / (left - right);
		result.elements[3 + 1 * 4] = (bottom + top) / (bottom - top);
		result.elements[3 + 2 * 4] = (far + near) / (far - near);

		return result;
	}

	mat4 mat4::Perspective(float fov, float aspectRatio, float near, float far)
	{
		mat4 result;
		
		float const tanHalfFovy = tan(fov / 2.0f);
		
		result.elements[0 + 0 * 4] = 1.0f / (aspectRatio * tanHalfFovy);
		result.elements[1 + 1 * 4] = 1.0f / tanHalfFovy;
		result.elements[2 + 2 * 4] = -(far + near) / (far - near);
									 
		result.elements[3 + 2 * 4] = -1.0f;
		result.elements[2 + 3 * 4] = -(2.0f * far * near) / (far - near);
		
		return result;
	}

	mat4 mat4::LookAt(const vec3& camera, const vec3& target, const vec3& up)
	{
		mat4 result(1.0f);

		vec3 f = (target - camera).Normalize();
		vec3 s = (f.Cross(up)).Normalize();
		vec3 u = s.Cross(f);

		result.elements[0 + 0 * 4] = s.x;
		result.elements[1 + 0 * 4] = s.y;
		result.elements[2 + 0 * 4] = s.z;

		result.elements[0 + 1 * 4] = u.x;
		result.elements[1 + 1 * 4] = u.y;
		result.elements[2 + 1 * 4] = u.z;

		result.elements[0 + 2 * 4] = -f.x;
		result.elements[1 + 2 * 4] = -f.y;
		result.elements[2 + 2 * 4] = -f.z;

		result.elements[3 + 0 * 4] = -(s.Dot(camera));
		result.elements[3 + 1 * 4] = -(u.Dot(camera));
		result.elements[3 + 2 * 4] = f.Dot(camera);

		return result;
	}

	mat4 mat4::Translate(mat4 matrix, const vec3& translation)
	{
		matrix.elements[3 + 0 * 4] += translation.x;
		matrix.elements[3 + 1 * 4] += translation.y;
		matrix.elements[3 + 2 * 4] += translation.z;
		return matrix;
	}

	mat4 mat4::Rotate(mat4 matrix, float rotation, const vec3& axis)
	{
		mat4 Rotate(1.0f);

		float r = rotation;
		float c = cos(r);
		float s = sin(r);
		float omc = 1.0f - c;

		float x = axis.x;
		float y = axis.y;
		float z = axis.z;

		Rotate.elements[0 + 0 * 4] = x * x * omc + c;
		Rotate.elements[0 + 1 * 4] = y * x * omc + z * s;
		Rotate.elements[0 + 2 * 4] = x * z * omc - y * s;

		Rotate.elements[1 + 0 * 4] = x * y * omc - z * s;
		Rotate.elements[1 + 1 * 4] = y * y * omc + c;
		Rotate.elements[1 + 2 * 4] = y * z * omc + x * s;

		Rotate.elements[2 + 0 * 4] = x * z * omc + y * s;
		Rotate.elements[2 + 1 * 4] = y * z * omc - x * s;
		Rotate.elements[2 + 2 * 4] = z * z * omc + c;

		mat4 Result;
		Result.rows[0] = matrix.rows[0] * Rotate.elements[0 + 0 * 4] + matrix.rows[1] * Rotate.elements[0 + 1 * 4] + matrix.rows[2] * Rotate.elements[0 + 2 * 4];
		Result.rows[1] = matrix.rows[0] * Rotate.elements[1 + 0 * 4] + matrix.rows[1] * Rotate.elements[1 + 1 * 4] + matrix.rows[2] * Rotate.elements[1 + 2 * 4];
		Result.rows[2] = matrix.rows[0] * Rotate.elements[2 + 0 * 4] + matrix.rows[1] * Rotate.elements[2 + 1 * 4] + matrix.rows[2] * Rotate.elements[2 + 2 * 4];
		Result.rows[3] = matrix.rows[3];
		return Result;

	}

	mat4 mat4::Scale(mat4 matrix, const vec3& scale)
	{
		matrix.elements[0 + 0 * 4] *= scale.x;
		matrix.elements[1 + 1 * 4] *= scale.y;
		matrix.elements[2 + 2 * 4] *= scale.z;
		matrix.elements[3 + 3 * 4] *= 1.0f;
		return matrix;
	}


	mat4& mat4::Multiply(const mat4& other)
	{
		float data[16];

		for (int y = 0; y < 4; y++)
		{
			for (int x = 0; x < 4; x++)
			{
				float sum = 0.0f;
				for (int e = 0; e < 4; e++)
				{
					sum += elements[x + e * 4] * other.elements[e + y * 4];
				}
				data[x + y * 4] = sum;
			}
		}
	
		memcpy(elements, data, 4 * 4 * sizeof(float));
		return *this;
	}
	
	mat4 operator*(mat4 left, const mat4& right)
	{
		return left.Multiply(right);
	}


	mat4& mat4::operator*=(const mat4& other)
	{
		return this->Multiply(other);
	}

} }