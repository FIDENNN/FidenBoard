// so for example this is how you make it

#include "imgui.h" // this is very important

#include "directory/fidenBoard.h"//just include the file

fidenBoard::FidenBoard *keyboard; //create an instance (our keyboard)

void DrawMenu() {
 //your stuff here
  
  ImGui::Begin("Example");
  //Initialize the instance always in a window
  keyboard = new fidenBoard::FidenBoard(ImGui::GetWindowSize(), fidenBoard::flags_noNumbers); //if you want you can use flags, if dont, just write the size
  ImGui::End();
  
}
