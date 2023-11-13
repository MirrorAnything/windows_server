//
// Created by meepojia on 2023/11/13.
//

#include "event.h"
#include <windows.h>

#include "windows.h"

static int screenWidth = GetSystemMetrics(SM_CXSCREEN);
static int screenHeight = GetSystemMetrics(SM_CYSCREEN);
void Event::MouseMove() {
    SetCursorPos(screenWidth * mouse_x, screenHeight * mouse_y);
}