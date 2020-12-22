#ifndef INPUT_HG
#define INPUT_HG
#include <cstdint>

#include "transform.h"

class InputHandler {
 public:
  InputHandler(Transform &transform, Camera &camera) : _transform(transform), _camera(camera) {}
   ~InputHandler() {}
   void onKeyDown(uint32_t keyCode, bool isRepeat);
   void onKeyUp(uint32_t keyCode, bool isRepeat);
   void onMouseDown(uint32_t mouseButton, uint8_t _tnumClicks);
   void onMouseUp(uint32_t mouseButton, uint8_t _tnumClicks);
   void onMouseMove(int32_t mousePosX, int32_t mousePosY, int32_t deltaX,
                           int32_t deltaY);
  void onWheel(int32_t x, int32_t y);

  // void addKeyControl(uint3_t2_t keyCode, InputControl& inputControl, float
  // weight = 1.0f); void addMouseControl(uint32 mouseButton, InputControl&
  // inputControl, float weight = 1.0f);
 private:
  bool isRotating = false;
  bool isPanning = false;
  Transform &_transform;
  Camera &_camera;
};
#endif