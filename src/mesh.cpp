#include "mesh.h"

#include <stdlib.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>

#include "debugTimer.h"
#include "util.h"

Mesh::Mesh(std::string fileName, glm::vec3 pos, glm::vec3 rot, glm::vec3 scale,
           mesh_type type)
    : _pos(pos), _rot(rot), _scale(scale), _type(type) {
  InitMesh(OBJModel(fileName).ToIndexedModel());
  std::cout << "";
}

void Mesh::InitMesh(const IndexedModel& model) {
  m_numIndices = model.indices.size();

  glGenVertexArrays(1, &m_vertexArrayObject);
  glBindVertexArray(m_vertexArrayObject);

  glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);

  glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
  glBufferData(GL_ARRAY_BUFFER,
               sizeof(model.positions[0]) * model.positions.size(),
               &model.positions[0], GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

  glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXCOORD_VB]);
  glBufferData(GL_ARRAY_BUFFER,
               sizeof(model.texCoords[0]) * model.texCoords.size(),
               &model.texCoords[0], GL_STATIC_DRAW);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

  glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[NORMAL_VB]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(model.normals[0]) * model.normals.size(),
               &model.normals[0], GL_STATIC_DRAW);
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffers[INDEX_VB]);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               sizeof(model.indices[0]) * model.indices.size(),
               &model.indices[0], GL_STATIC_DRAW);

  glBindVertexArray(0);
}

Mesh::Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices,
           unsigned int numIndices) {
  IndexedModel model;

  for (unsigned int i = 0; i < numVertices; i++) {
    model.positions.push_back(*vertices[i].GetPos());
    model.texCoords.push_back(*vertices[i].GetTexCoord());
    model.normals.push_back(*vertices[i].GetNormal());
  }

  for (unsigned int i = 0; i < numIndices; i++)
    model.indices.push_back(indices[i]);

  InitMesh(model);
}

Mesh::~Mesh() {
  glDeleteBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
  glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void Mesh::Draw() {
  glBindVertexArray(m_vertexArrayObject);

  // glDrawElements(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, 0);
  glDrawElementsBaseVertex(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, 0, 0);

  glBindVertexArray(0);
}
double Mesh::GetFlow() {
  if (_type == mesh_type::line_segment && _line_ptr != NULL) {
    return std::abs(_line_ptr->flows.first);
  } else {
    return -1.0f;
  }
}