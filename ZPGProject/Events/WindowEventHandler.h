#pragma once
#include <GLFW/glfw3.h>
#include "CursorPos.h"
#include "ScreenDimensions.h"
class WindowEventHandler
{
public:
    virtual void onWindowSizeChanged(ScreenDimensions& dimensions);
    virtual void onWindowFocusChanged(bool focused);
    virtual void onWindowIconifyChanged(bool iconified);
    virtual void onCursorPositionChanged(CursorPos& cursorPos);
    virtual void onKey(GLFWwindow* window);
    virtual void onMouseButton(GLFWwindow* window);
};

