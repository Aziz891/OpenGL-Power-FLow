#include <SDL2/SDL.h>
#include <assimp/postprocess.h>  // Post processing flags
#include <assimp/scene.h>        // Output data structure

#include <algorithm>            // for std::for_each
#include <assimp/Importer.hpp>  // C++ importer interface
#include<iostream>
#include "InputHandler.hpp"
#include "Parser.hpp"
#include "camera.h"
#include "display.h"
#include "mesh.h"
#include "model.hpp"
#include "shader.h"
#include "solver.hpp"
#include "texture.h"
#include "transform.h"
#include "Graph.hpp"

static const int DISPLAY_WIDTH = 800;
static const int DISPLAY_HEIGHT = 600;

int main(int argc, char** argv) {
  // create a typedef for the Graph type
  // typedef adjacency_list<vecS, vecS, bidirectionalS> Graph;


  // Assimp::Importer importer;
  model model;
  Parser parser(model);
  parser.read();
  model.generate_admit();

  solver solver(model);
  solver.solve();
  Power_Graph g(model);

  // And have it read the given file with some example postprocessing
  // Usually - if speed is not the most important aspect for you - you'll
  // probably to request more postprocessing than we do in this example.
  //   const aiScene* scene = importer.ReadFile(
  //       "../res/monkey3.obj", aiProcess_CalcTangentSpace |
  //       aiProcess_Triangulate |
  //                     aiProcess_JoinIdenticalVertices |
  //                     aiProcess_SortByPType);

  //   // If the import failed, report it
  //   if (!scene) {
  //     // DoTheErrorLogging( importer.GetErrorString());
  //     std::cout << importer.GetErrorString();
  //     std::cout << importer.GetErrorString();
  //   }
  //   Mesh::Mesh(Vertex* vertices, unsigned int numVertices, unsigned int*
  //   indices, unsigned int numIndices)
  // Mesh test()
  Display display(DISPLAY_WIDTH, DISPLAY_HEIGHT, "OpenGL");

  Vertex vertices[] = {
      Vertex(glm::vec3(-20, -1, -1), glm::vec2(1, 0), glm::vec3(0, 0, -1)),
      Vertex(glm::vec3(-1, 1, -1), glm::vec2(0, 0), glm::vec3(0, 0, -1)),
      Vertex(glm::vec3(1, 1, -1), glm::vec2(0, 1), glm::vec3(0, 0, -1)),
      Vertex(glm::vec3(1, -1, -1), glm::vec2(1, 1), glm::vec3(0, 0, -1)),

      Vertex(glm::vec3(-1, -1, 1), glm::vec2(1, 0), glm::vec3(0, 0, 1)),
      Vertex(glm::vec3(-1, 1, 1), glm::vec2(0, 0), glm::vec3(0, 0, 1)),
      Vertex(glm::vec3(1, 1, 1), glm::vec2(0, 1), glm::vec3(0, 0, 1)),
      Vertex(glm::vec3(1, -1, 1), glm::vec2(1, 1), glm::vec3(0, 0, 1)),

      Vertex(glm::vec3(-1, -1, -1), glm::vec2(0, 1), glm::vec3(0, -1, 0)),
      Vertex(glm::vec3(-1, -1, 1), glm::vec2(1, 1), glm::vec3(0, -1, 0)),
      Vertex(glm::vec3(1, -1, 1), glm::vec2(1, 0), glm::vec3(0, -1, 0)),
      Vertex(glm::vec3(1, -1, -1), glm::vec2(0, 0), glm::vec3(0, -1, 0)),

      Vertex(glm::vec3(-1, 1, -1), glm::vec2(0, 1), glm::vec3(0, 1, 0)),
      Vertex(glm::vec3(-1, 1, 1), glm::vec2(1, 1), glm::vec3(0, 1, 0)),
      Vertex(glm::vec3(1, 1, 1), glm::vec2(1, 0), glm::vec3(0, 1, 0)),
      Vertex(glm::vec3(1, 1, -1), glm::vec2(0, 0), glm::vec3(0, 1, 0)),

      Vertex(glm::vec3(-1, -1, -1), glm::vec2(1, 1), glm::vec3(-1, 0, 0)),
      Vertex(glm::vec3(-1, -1, 1), glm::vec2(1, 0), glm::vec3(-1, 0, 0)),
      Vertex(glm::vec3(-1, 1, 1), glm::vec2(0, 0), glm::vec3(-1, 0, 0)),
      Vertex(glm::vec3(-1, 1, -1), glm::vec2(0, 1), glm::vec3(-1, 0, 0)),

      Vertex(glm::vec3(1, -1, -1), glm::vec2(1, 1), glm::vec3(1, 0, 0)),
      Vertex(glm::vec3(1, -1, 1), glm::vec2(1, 0), glm::vec3(1, 0, 0)),
      Vertex(glm::vec3(1, 1, 1), glm::vec2(0, 0), glm::vec3(1, 0, 0)),
      Vertex(glm::vec3(1, 1, -1), glm::vec2(0, 1), glm::vec3(1, 0, 0)),
  };

  unsigned int indices[] = {0,  1,  2,  0,  2,  3,

                            6,  5,  4,  7,  6,  4,

                            10, 9,  8,  11, 10, 8,

                            12, 13, 14, 12, 14, 15,

                            16, 17, 18, 16, 18, 19,

                            22, 21, 20, 23, 22, 20};

  Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices,
            sizeof(indices) / sizeof(indices[0]));

  Mesh monkey("../res/sub.obj");
  Mesh monkey2("../res/sub.obj");
  std::vector<Mesh*> meshes;
  for (size_t i = 0; i < 15; i++) {
    /* code */
    Mesh* temp;
    if (i == 0) {
      temp = new Mesh("../res/sub2.obj", glm::vec3(80.0f * i, 0.0f, 0.0f));
      temp->SetScale(glm::vec3(2.0f, 50.0f, 2.0f));

    } else {
      temp = new Mesh("../res/sub.obj", glm::vec3(80.0f * i, 0.0f, 0.0f));
      temp->SetScale(glm::vec3(5.0f, 5.0f, 5.0f));
    }
    meshes.push_back(temp);
  }

  Shader shader("../shaders/basicShader");
  Texture texture("../res/bricks.jpg");
  Transform transform;
  Transform transform2;
  Camera camera(glm::vec3(0.0f, 0.0f, -150.0f), 70.0f,
                (float)DISPLAY_WIDTH / (float)DISPLAY_HEIGHT, 0.1f, 5000.0f);

  SDL_Event e;
  // *transform.GetPos() = glm::vec3(100.0f, 100.0f, 1.0f);
  InputHandler eventHandler(transform, camera);
  bool isRunning = true;
  float counter = 0.0f;
  while (isRunning) {
    while (SDL_PollEvent(&e)) {
      switch (e.type) {
        case SDL_KEYDOWN:
          eventHandler.onKeyDown(e.key.keysym.scancode, e.key.repeat != 0);
          break;
        case SDL_KEYUP:
          eventHandler.onKeyUp(e.key.keysym.scancode, e.key.repeat != 0);
          break;
        case SDL_MOUSEBUTTONDOWN:
          eventHandler.onMouseDown(e.button.button, e.button.clicks);
          break;
        case SDL_MOUSEBUTTONUP:
          eventHandler.onMouseUp(e.button.button, e.button.clicks);
          break;
        case SDL_MOUSEMOTION:
          eventHandler.onMouseMove(e.motion.x, e.motion.y, e.motion.xrel,
                                   e.motion.yrel);
          break;
        case SDL_MOUSEWHEEL:
          eventHandler.onWheel(e.wheel.x, e.wheel.y);
          break;
        case SDL_QUIT:
          isRunning = false;
          break;
        default:
          break;
      };

      // ...
    }

    display.Clear(1.0f, 1.0f, 1.0f, 1.0f);

    float sinCounter = sinf(counter);
    float absSinCounter = abs(sinCounter);

    // transform.GetRot()->y = counter * 100;
    // transform.GetPos()->x = sinCounter;
    // transform.GetRot()->z = counter * 100;
    // transform.GetScale()->x = absSinCounter;
    // transform.GetScale()->y = absSinCounter;

    shader.Bind();
    texture.Bind();
    // shader.Update(transform, camera, monkey);

    // shader.Update(transform, camera, monkey2);
    //   monkey2.Draw();
    size_t counter2 = 0;
    for (auto i : meshes) {
      auto increment = glm::vec3(0.0f, 0.7f * counter * counter2, 0.0f);
      i->SetRot(increment);
      shader.Update(transform, camera, *i);
      i->Draw();
      counter2++;
    }

    display.SwapBuffers();
    SDL_Delay(1);
    counter += 0.01f;
  }
  for (auto p : meshes) {
    delete p;
  }
  meshes.clear();
  return 0;
}
