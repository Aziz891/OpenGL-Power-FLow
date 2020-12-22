#ifndef MESH_INCLUDED_H
#define MESH_INCLUDED_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "obj_loader.h"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

struct Vertex
{
public:
	Vertex(const glm::vec3& pos, const glm::vec2& texCoord, const glm::vec3& normal)
	{
		this->pos = pos;
		this->texCoord = texCoord;
		this->normal = normal;
	}

	glm::vec3* GetPos() { return &pos; }
	glm::vec2* GetTexCoord() { return &texCoord; }
	glm::vec3* GetNormal() { return &normal; }

private:
	glm::vec3 pos;
	glm::vec2 texCoord;
	glm::vec3 normal;
};

enum MeshBufferPositions
{
	POSITION_VB,
	TEXCOORD_VB,
	NORMAL_VB,
	INDEX_VB
};

class Mesh
{
public:
    Mesh(const std::string fileName,  glm::vec3 pos = glm::vec3(),  glm::vec3 rot = glm::vec3(),  glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f));
	Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);

	void Draw();

		 glm::mat4 GetModel() const
	{
		glm::mat4 posMat = glm::translate(_pos);
		glm::mat4 scaleMat = glm::scale(_scale);
		glm::mat4 rotX = glm::rotate(_rot.x, glm::vec3(1.0, 0.0, 0.0));
		glm::mat4 rotY = glm::rotate(_rot.y, glm::vec3(0.0, 1.0, 0.0));
		glm::mat4 rotZ = glm::rotate(_rot.z, glm::vec3(0.0, 0.0, 1.0));
		glm::mat4 rotMat = rotX * rotY * rotZ;

		return posMat * rotMat * scaleMat;
	}

	virtual ~Mesh();
		inline glm::vec3* GetPos() { return &_pos; }
	inline glm::vec3* GetRot() { return &_rot; }
	inline glm::vec3* GetScale() { return &_scale; }

	inline void SetPos(glm::vec3 pos) { this->_pos = pos; }
	inline void SetRot(glm::vec3 rot) { this->_rot = rot; }
	inline void SetScale(glm::vec3 scale) { this->_scale = scale; }
	void operator=(const Mesh& mesh) {}
	Mesh(const Mesh& mesh) {}
protected:
private:
	glm::vec3 _pos ;
	glm::vec3 _rot ;
	glm::vec3 _scale ;
	static const unsigned int NUM_BUFFERS = 4;

    void InitMesh(const IndexedModel& model);

	GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];
	unsigned int m_numIndices;
};

#endif