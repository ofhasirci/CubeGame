#include "Shader.h"

#include "GLBullet.h"

#include <fstream>
#include <iostream>

namespace Engine {
	Shader::Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
	{
		m_BufferID = CreateShader(vertexShaderPath, fragmentShaderPath);
		glUseProgram(m_BufferID);
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_BufferID);
	}

	void Shader::Bind() const
	{
		glUseProgram(m_BufferID);
	}

	void Shader::UnBind() const
	{
		glUseProgram(0);
	}

	void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
	{
		glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
	}

	void Shader::SetUniformMatrix4f(const std::string& name, glm::mat4& matrix)
	{
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
	}
	
	unsigned int Shader::CreateShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
	{
		std::string vertexShader = ParseShader(vertexShaderPath);
		std::string fragmentShader = ParseShader(fragmentShaderPath);
		unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
		unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

		unsigned int program = glCreateProgram();
		glAttachShader(program, vs);
		glAttachShader(program, fs);
		glLinkProgram(program);
		glValidateProgram(program);

		glDeleteShader(vs);
		glDeleteShader(fs);

		return program;
	}

	std::string Shader::ParseShader(const std::string& filePath)
	{
		std::string shaderSource;
		std::ifstream stream(filePath, std::ios::in | std::ios::binary);
		if (stream)
		{
			stream.seekg(0, stream.end);
			shaderSource.resize((size_t)stream.tellg());
			stream.seekg(0, stream.beg);
			stream.read(&shaderSource[0], shaderSource.size());
			stream.close();
		}
		else
		{
			std::cout << "Could not open the file: " << filePath << std::endl;
		}


		return shaderSource;
	}

	unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
	{
		unsigned int id = glCreateShader(type);
		const char* src = source.c_str();
		glShaderSource(id, 1, &src, nullptr);
		glCompileShader(id);

		int result;
		glGetShaderiv(id, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			int length;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
			char* message = (char*)alloca(length * sizeof(char));
			glGetShaderInfoLog(id, length, &length, message);
			std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") << " shader!" << std::endl;
			std::cout << message << std::endl;

			glDeleteShader(id);
			return 0;
		}

		return id;
	}

	int Shader::GetUniformLocation(const std::string& name) const
	{
		if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		{
			return m_UniformLocationCache[name];
		}

		int location = glGetUniformLocation(m_BufferID, name.c_str());
		if (location == -1)
		{
			std::cout << "Uniform: " << name << " does not exist!" << std::endl;
		}

		m_UniformLocationCache[name] = location;
		return location;
	}
}

