#pragma once

#include "BaseBuffer.h"

#include <string>
#include <unordered_map>

#include "glm/glm.hpp"

namespace Engine {

	class Shader : public BaseBuffer
	{
	private:
		mutable std::unordered_map<std::string, int> m_UniformLocationCache;
	public:
		Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
		~Shader();

		void Bind() const override;
		void UnBind() const override;

		void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
		void SetUniformMatrix4f(const std::string& name, glm::mat4& matrix);
	private:
		unsigned int CreateShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
		std::string ParseShader(const std::string& filePath);
		unsigned int CompileShader(unsigned int type, const std::string& source);
		int GetUniformLocation(const std::string& name) const;
		
	};
}