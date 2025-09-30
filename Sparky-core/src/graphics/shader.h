#pragma once

#include <iostream>
#include <vector>
#include <GL/glew.h>

#include "../maths/maths.h"
#include "../utils/fileutils.h"

namespace sparky::graphics {

	class Shader
	{
	private:
		GLuint m_ShaderID;
		const char* m_VertPath;
		const char* m_FragPath;

	public:
		Shader(const char* vertPath, const char* fragPath);
		~Shader();

		void SetUniform1f(const GLchar* name, float value);
		void SetUniform1i(const GLchar* name, int value );
		void SetUniform2f(const GLchar* name, const maths::vec2& vector);
		void SetUniform3f(const GLchar* name, const maths::vec3& vector);
		void SetUniform4f(const GLchar* name, const maths::vec4& vector);
		void SetUniformMat4(const GLchar* name, const maths::mat4& matrix);

		void enable() const;
		void disable() const;

	private:
		GLuint load();
		GLint getUniformLocation(const GLchar* name);
	};

}