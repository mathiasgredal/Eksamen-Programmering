#pragma once

#include <iostream>
#include <vector>

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
    App(bgfx::RendererType::Enum backend, bool _vsync = true);
    ~App();
    auto run() -> void;

private:
    static auto glfw_errorCallback(int error, const char *description) -> void ;
    static auto glfw_windowResizeCallback(GLFWwindow* window, int width, int height) -> void;

    auto createWindow(bgfx::RendererType::Enum backend) -> void;
    auto drawGUI() -> void;
    auto drawVG() -> void;

    GLFWwindow* m_window;
    const std::string project_name = "Programmering eksamen";
    int window_height = 600;
    int window_width = 800;

    uint32_t m_frameNumber = 0;
    bool vsync = true;
    const bgfx::ViewId m_viewId;
    NVGcontext* m_ctx;
};
