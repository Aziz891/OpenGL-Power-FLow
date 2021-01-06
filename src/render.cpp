#include "render.hpp"

Renderer::Renderer(l_order &lines, model &model)
    : line_order(lines), _model(model) {}

Renderer::~Renderer() {}
/*
 x : -90 to 90
 z: 0 to 360

 increment : f(factor) = 180 / factor;
*/

std::vector<std::unique_ptr<Mesh>> Renderer::render() {
  std::vector<std::unique_ptr<Mesh>> meshes;
  std::map<int, int> rendered_busses;
  float scaling_factor = 60.0;
  float rot_angle_x = 0.0f;
  float rot_angle_z = 0.0f;
  const float line_wdith = 0.5;
  for (auto &_bus : line_order) {
    // if (_bus.first > 3) break;
    if (rendered_busses.find(_bus.first) == rendered_busses.end()) {
      meshes.push_back(std::make_unique<Mesh>(
          "../res/sub.obj", glm::vec3(0.0f, 0.0f, 0.0f),
          glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)));
      rendered_busses[_bus.first] = meshes.size() - 1;
    }
    auto bus_new_coord = meshes[rendered_busses[_bus.first]]->GetCoord();
    float factor = _bus.second.size()  ;
    rot_angle_x = (float)0.0f;
    rot_angle_z = (float)0.0f;
    for (auto &i : _bus.second) {
      if (rendered_busses.find(_model._lines[i]._to_bus + 1) ==
          rendered_busses.end()) {
        // if (_bus.first == 2 && i != 2) continue;
        meshes.push_back(std::make_unique<Mesh>(
            "../res/line.obj", glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(line_wdith, scaling_factor, line_wdith), mesh_type::line_segment));
        meshes.back()->SetCoord(
            bus_new_coord *

            glm::rotate(rot_angle_z, glm::vec3(0.0f, 0.0f, 1.0f))  * 
            glm::rotate(rot_angle_x , glm::vec3(1.0f, 0.0f, 0.0f)) 

            );
        meshes.back()->_line_ptr = &(_model._lines[i]);
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
        auto local_up = glm::vec3(bus_new_coord *
                                  glm::vec4(glm::vec3(0.0f, 1.0f, 0.0f), 0.0f));
        auto sample2 =
            glm::vec3(meshes[rendered_busses[_model._lines[i]._to_bus + 1]]
                          ->GetCoord()[3]);
        auto rot_direct = sample2 - sample;
        auto rot_axis = glm::vec3(
            glm::normalize((
              glm::inverse(bus_new_coord) *
                            glm::vec4(glm::cross(local_up, rot_direct), 0.0))));
        auto angle_rot =
            acos(glm::dot(glm::normalize(local_up), glm::normalize(rot_direct)));

        meshes.push_back(std::make_unique<Mesh>(
            "../res/line.obj", glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(line_wdith, glm::distance(sample, sample2), line_wdith) , mesh_type::line_segment));
        meshes.back()->_line_ptr = &(_model._lines[i]);
        meshes.back()->SetCoord(bus_new_coord *

                                glm::rotate(1.0f * (float)angle_rot, rot_axis));

        std::cout << "";
      }
      rot_angle_x +=      M_PI / factor;
      rot_angle_z +=   2.0f  * M_PI / factor;
    }
  }
  return (std::move(meshes));

 
}
