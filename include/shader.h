#ifndef SHADER_INCLUDED_H
#define SHADER_INCLUDED_H

#include <string>
#include <GL/glew.h>
#include "transform.h"
#include "mesh.h"
#include<complex>

class Shader
{
public:
	Shader(const std::string& fileName);

	void Bind();
	void Update(const Transform& transform, const Camera& camera,  Mesh& mesh);
	std::pair<std::complex<double>, std::complex<double>> _minmax_colors;

	virtual ~Shader();
	model* _model;
protected:
private:
	static const unsigned int NUM_SHADERS = 2;
	static const unsigned int NUM_UNIFORMS = 4;
	void operator=(const Shader& shader) {}
	Shader(const Shader& shader) {}

	std::string LoadShader(const std::string& fileName);
	void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	GLuint CreateShader(const std::string& text, unsigned int type);

	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];
	GLuint m_uniforms[NUM_UNIFORMS];
};

#endif
