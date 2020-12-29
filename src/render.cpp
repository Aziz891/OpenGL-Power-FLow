#include "render.hpp"

Renderer::Renderer(l_order &lines, model &model)
    : line_order(lines), _model(model) {}

Renderer::~Renderer() {}

std::vector<std::unique_ptr<Mesh>> Renderer::render() {
  std::vector<std::unique_ptr<Mesh>> meshes;
  std::map<int, int> rendered_busses;
  float scaling_factor = 60.0;
  bool isRendered;
  float rot_angle_y = 0.0f;
  float rot_angle_x = 0.0;
  float rot_angle = 0.0f;
  const double line_wdith = 0.5;
  for (auto &_bus : line_order) {
    if (_bus.first > 5) break;
    isRendered = false;
    if (rendered_busses.find(_bus.first) == rendered_busses.end()) {
      meshes.push_back(std::make_unique<Mesh>(
          "../res/sub.obj", glm::vec3(0.0f, 0.0f, 0.0f),
          glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)));
      rendered_busses[_bus.first] = meshes.size() - 1;
    }
    auto bus_new_coord = meshes[rendered_busses[_bus.first]]->GetCoord();
    float factor = _bus.second.size();
    rot_angle = M_PI_4;
    for (auto &i : _bus.second) {
      if (rendered_busses.find(_model._lines[i]._to_bus + 1) ==
          rendered_busses.end()) {
        // if (_bus.first == 2 && i != 2) continue;
        meshes.push_back(std::make_unique<Mesh>(
            "../res/sub3.obj", glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.5f, scaling_factor, 0.5f)));
        meshes.back()->SetCoord(
            bus_new_coord *

            glm::rotate(rot_angle, glm::vec3(1.0f, 1.0f, 1.0f)));
        auto line_new_coord = meshes.back()->GetCoord();

        meshes.push_back(std::make_unique<Mesh>(
            "../res/sub.obj", glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)));
        meshes.back()->SetCoord(
            line_new_coord *
            glm::translate(glm::vec3(0.0f, scaling_factor, 0.0f)));
        rendered_busses[_model._lines[i]._to_bus + 1] = meshes.size() - 1;
      } else {
        auto sample = glm::vec3(bus_new_coord[3]);
        auto sample2 =
            glm::vec3(meshes[rendered_busses[_model._lines[i]._to_bus + 1]]
                          ->GetCoord()[3]);
        // auto rot_axis = glm::cross(sample, sample2);
        auto rot_direct = sample2 - sample;
        auto rot_axis = glm::vec3(
            glm::normalize(( glm::inverse(bus_new_coord) *  glm::vec4(glm::cross(sample, rot_direct), 0.0))));
        auto angle_rot =
            acos(glm::dot(glm::normalize(sample), glm::normalize(rot_direct)));

        meshes.push_back(std::make_unique<Mesh>(
            "../res/sub3.obj", glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.5f, glm::distance(sample, sample2), 0.5f)));
        // glm::vec3 right = glm::normalize(glm::cross(up, forward));

        // rot_axis = glm::vec3(glm::normalize(glm::rotate((float)0.0f,
        // rot_direct) *
        //                                    glm::vec4(sample, 0.0)));
        // up = glm::normalize(glm::cross(forward, right));
        meshes.back()->SetCoord(bus_new_coord *

                                glm::rotate(1.0f * (float)angle_rot, rot_axis));

        std::cout << "";
      }
      rot_angle += M_PI / 3;
    }
    // if (_bus.first > 5) break;
    std::cout << "";
  }
  return (std::move(meshes));

  //   meshes.push_back(std::make_unique<Mesh>(
  //       "../res/sub.obj", glm::vec3(0.0f, 0.0f, 0.0f),
  //       glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)));

  //   for (size_t i = 0; i < 2; i++) {
  //     /* code */
  //     meshes.push_back(
  //         std::make_unique<Mesh>("../res/sub3.obj", glm::vec3(0.0f, 0.0f,
  //         0.0f),
  //                                glm::vec3(rot_angle_x, rot_angle_y,
  //                                rot_angle), glm::vec3(0.5f, scaling_factor,
  //                                0.5f)));
  //     // rot_angle_x += M_PI_4;
  //     auto test2 = meshes[i]->GetCoord();

  //     meshes.push_back(std::make_unique<Mesh>(
  //         "../res/sub.obj", glm::vec3(0.0f, 0.0f, 0.0f),
  //         glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)));
  //     meshes.back()->SetCoord(
  //         glm::translate(glm::rotate(rot_angle, glm::vec3(0.0f, 0.0f, 1.0f)),
  //                        glm::vec3(0.0f, scaling_factor, 0.0f)));
  //     auto temp = meshes.back()->GetCoord();
  //     meshes.push_back(std::make_unique<Mesh>(
  //         "../res/sub.obj", glm::vec3(0.0f, 0.0f, 0.0f),
  //         glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)));
  //     meshes.back()->SetCoord(
  //         temp *
  //         glm::translate(glm::rotate(rot_angle, glm::vec3(0.0f, 0.0f, 1.0f)),
  //                        glm::vec3(0.0f, scaling_factor, 0.0f)));

  //     rot_angle += M_PI_4;
  //     // rot_angle_y += M_PI_4;
  //   }
}
