#ifndef MESH_INCLUDED_H
#define MESH_INCLUDED_H

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <string>
#include <vector>
#include "model.hpp"
#include "obj_loader.h"

enum mesh_type { none, line_segment, substation };
struct Vertex {
 public:
  Vertex(const glm::vec3& pos, const glm::vec2& texCoord,
         const glm::vec3& normal) {
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

enum MeshBufferPositions { POSITION_VB, TEXCOORD_VB, NORMAL_VB, INDEX_VB };

class Mesh {
 public:
  Mesh(const std::string fileName, glm::vec3 pos = glm::vec3(),
       glm::vec3 rot = glm::vec3(),
       glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f),
       mesh_type type = mesh_type::substation
       );
  Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices,
       unsigned int numIndices);

  line* _line_ptr =NULL ;
  void Draw();

  glm::mat4 GetModel(glm::mat4 coord = glm::mat4(1.0f)) const {
    glm::mat4 posMat = glm::translate(_pos);

    glm::mat4 scaleMat = glm::scale(_scale);
    glm::mat4 rotX = glm::rotate(_rot.x, glm::vec3(1.0, 0.0, 0.0));
    glm::mat4 rotY = glm::rotate(_rot.y, glm::vec3(0.0, 1.0, 0.0));
    glm::mat4 rotZ = glm::rotate(_rot.z, glm::vec3(0.0, 0.0, 1.0));

    glm::mat4 rotMat = rotX * rotY * rotZ;
    // if(test_cord) {
    // posMat = glm::translate(rotMat ,_pos);
    // rotZ = glm::rotate(0.0f, glm::vec3(0.0, 0.0, 1.0));

    // }

    return (_coord * posMat * rotMat * scaleMat);
  }

  virtual ~Mesh();
  double GetFlow();
  inline glm::vec3* GetPos() { return &_pos; }
  inline glm::vec3* GetRot() { return &_rot; }
  inline glm::vec3* GetScale() { return &_scale; }
  inline glm::mat4& GetCoord() { return _coord; }
  inline mesh_type GetType() { return _type; }

  inline void SetPos(glm::vec3 pos) { this->_pos = pos; }
  inline void SetCoord(glm::mat4 coord) { this->_coord = coord; }
  inline void SetRot(glm::vec3 rot) { this->_rot = rot; }
  inline void SetScale(glm::vec3 scale) { this->_scale = scale; }
  void operator=(const Mesh& mesh) {}
  Mesh(const Mesh& mesh) {}
  bool test_cord = false;

 protected:
 private:
  glm::vec3 _pos;
  glm::vec3 _rot;
  glm::vec3 _scale;
  glm::mat4 _coord = glm::mat4(1.0);
  static const unsigned int NUM_BUFFERS = 4;

  void InitMesh(const IndexedModel& model);

  GLuint m_vertexArrayObject;
  GLuint m_vertexArrayBuffers[NUM_BUFFERS];
  unsigned int m_numIndices;
  mesh_type _type;
};

#endif
