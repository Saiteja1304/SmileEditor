#include <Core/Input.hpp>
#include <Graphics/GL/Graphics.hpp>
#include <Window/Window.hpp>

#include <iostream>
// Set Singleton class's instance to 0
Window *Window::WInstance = 0;
Graphics *Graphics::GInstance = 0;
Input *Input::IInstance = 0;

int main() {
  // Get window and graphics instances
  Window *window = window->WGetInstance();
  Graphics *graphics = graphics->GGetInstance();
  Input *input = input->IGetInstance();

  // glfw init
  window->WInitGLFW();
  // create window
  window->WCreateWindow();
  // set created window to current context
  window->WSetContext();

  // Init Input
  input->IInit();

  // load gl lib
  graphics->GInit();
  // set viewport size
  graphics->GSetViewPort(0, 0, 800, 800);

  // main loop
  while (window->WIsRunning) {
    if(input->IGetKeyDown(INPUT_KEY_W)){
      std::cout << "Key W pressed\n";
    }
    window->WPollEvents();
    // set BG color
    graphics->GBackGroundColor(0.35, 0.45, 0.55, 1.0);
    // update window
    window->WUpdate();
    window->WSwapBuffers();
  }

  // destroy window
  window->WDestroyWindow();
  // terminate glfw
  window->WExitGLFW();
}