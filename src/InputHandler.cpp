#include "InputHandler.hpp"
#include<iostream>

#define MOUSE_OFFSET 0;

void InputHandler::onKeyDown( uint32_t keyCode, bool isRepeat)
{
}

void InputHandler::onKeyUp(uint32_t keyCode, bool isRepeat)
{
	// updateInput(keyCode, -1.0f, isRepeat);
}

void InputHandler::onMouseDown(uint32_t mouseButton, uint8_t numClicks)
{
	isRotating = true;
}

void InputHandler::onMouseUp(uint32_t mouseButton, uint8_t numClicks)
{
	isRotating = false;
}

void InputHandler::onMouseMove(int32_t mousePosX, int32_t mousePosY, 
		int32_t deltaX, int32_t deltaY) {
			if (isRotating) {

			// std::cout << deltaX << " , " << deltaY <<  " , " << " , " << mousePosX << " , "  << mousePosY << std::endl ;
			// std::cout << _transform.GetRot()->x << " >> ";
	          _transform.GetRot()->y += 0.01 * deltaX ;
	          _transform.GetRot()->x -= 0.01 * deltaY ;

			// std::cout << _transform.GetRot()->x << std::endl;

			}
		}
 void InputHandler::onWheel(int32_t x, int32_t y){

	 _camera.MoveForward(10 * y);
 };


// void GameEventHandler::addKeyControl(uint32_t keyCode, InputControl& inputControl, float weight)
// {
// }
// void GameEventHandler::addMouseControl(uint32_t mouseButton, InputControl& inputControl, float weight)
// {
// }

// void GameEventHandler::updateInput(uint32_t inputCode, float dir, bool isRepeat)
// {
// 	if(isRepeat) {
// 		return;
// 	}

// 	// for(uint32 i = 0; i < inputs[inputCode].size(); i++) {
// 	// 	inputs[inputCode][i].second.addAmt(inputs[inputCode][i].first * dir);
// 	// }
// }
