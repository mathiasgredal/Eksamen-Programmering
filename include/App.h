#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>
#include <chrono>
#include <stdio.h>

#include <fmt/core.h>

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <bx/bx.h>
#include <bx/math.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include <GLFW/glfw3.h>
#if BX_PLATFORM_LINUX
#define GLFW_EXPOSE_NATIVE_X11
#elif BX_PLATFORM_WINDOWS
#define GLFW_EXPOSE_NATIVE_WIN32
#elif BX_PLATFORM_OSX
#define GLFW_EXPOSE_NATIVE_COCOA
#endif
#include <GLFW/glfw3native.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>

#include <nanovg.h>

class App
{
public:
    App();
    ~App();
    void run();

private:
    static void glfw_errorCallback(int error, const char *description);
    static void glfw_windowResizeCallback(GLFWwindow* window, int width, int height);
    void createWindow();
    void drawGUI();
    void drawVG();

    GLFWwindow* m_window;
    const std::string project_name = "Programmering eksamen";
    int window_height = 600;
    int window_width = 800;

    uint32_t m_frameNumber = 0;
    const bgfx::ViewId m_viewId;
    NVGcontext* m_ctx;
};
