#include <SDL2/SDL.h>
#include <math.h>

#include <algorithm>            // for std::for_each
#include <iostream>
#include <memory>

#include "Graph.hpp"
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
#include "render.hpp"
#define SCREEN_SCALE 1

static const int DISPLAY_WIDTH = 1800/( SCREEN_SCALE);
static const int DISPLAY_HEIGHT = 900/( SCREEN_SCALE);

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
  Display display(DISPLAY_WIDTH, DISPLAY_HEIGHT, "OpenGL");
  Renderer r(g.get_line_order(), model);
  auto meshes = r.render();

  Shader shader("../shaders/basicShader");
  shader._model = &model;
  Texture texture("../res/bricks.jpg");
  Texture texture2;
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


    shader.Bind();

    size_t counter2 = 0;
    for (auto& i : meshes) {
      auto increment = glm::vec3(0.0f, 0.7f * counter * counter2, 0.0f);
      if (i->GetType() == mesh_type::substation) {
        texture.Bind();

      } else {
        texture2.Bind();
      }
      // i->SetRot(increment);
      shader.Update(transform, camera, *i);
      i->Draw();
      counter2++;
    }

    display.SwapBuffers();
    SDL_Delay(1);
    counter += 0.01f;
  }
 
  meshes.clear();
  return 0;
}
