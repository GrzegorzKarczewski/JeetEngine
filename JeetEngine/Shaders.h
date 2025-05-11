#pragma once

class Shader {
public:
	Shader();
	~Shader();
	void ApplyShaderProgram();

private:
	const char* m_vertexShaderSource;
	const char* m_fragmentShaderSource;
	unsigned int m_shaderProgram;
	unsigned int m_fragmentShader;
	unsigned int m_vertexShader;

};
