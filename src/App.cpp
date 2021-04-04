#include "../include/App.h"

auto App::glfw_errorCallback(int error, const char *description) -> void
{
    throw std::runtime_error(fmt::format("ERROR{}: {}", error, description));
}

auto App::glfw_windowResizeCallback(__attribute__((unused)) GLFWwindow *window, int width, int height) -> void
{
    auto app = (App*)glfwGetWindowUserPointer(window);
    bgfx::reset(width, height, app->vsync? BGFX_RESET_VSYNC : BGFX_RESET_NONE);
}

auto App::createWindow(bgfx::RendererType::Enum backend) -> void
{
    glfwSetErrorCallback(App::glfw_errorCallback);

    if(!glfwInit())
        throw std::runtime_error("ERROR: Could not initialize glfw");

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    m_window = glfwCreateWindow(window_width, window_height, project_name.c_str(), nullptr, nullptr);

    if(!m_window)
        throw std::runtime_error("ERROR: Failed to create window");

    // Handle window resize
    glfwSetWindowSizeCallback(m_window, App::glfw_windowResizeCallback);
    glfwSetWindowUserPointer(m_window, (void *)this);

    // Calling renderFrame before init sets main thread to be render thread
    // See: https://bkaradzic.github.io/bgfx/internals.html
    bgfx::renderFrame();

    bgfx::Init init;
    init.type = backend;  // Set vulkan rendering
    init.resolution.reset = vsync? BGFX_RESET_VSYNC : BGFX_RESET_NONE;   // Use vsync
    init.resolution.width = window_width;
    init.resolution.height = window_height;

#if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
    init.platformData.ndt = glfwGetX11Display();
    init.platformData.nwh = (void*)(uintptr_t)glfwGetX11Window(m_window);
#elif BX_PLATFORM_OSX
    init.platformData.nwh = glfwGetCocoaWindow(m_window);
#elif BX_PLATFORM_WINDOWS
    init.platformData.nwh = glfwGetWin32Window(m_window);
#endif

    if (!bgfx::init(init))
        throw std::runtime_error("ERROR: Could not initialize bgfx");

    bgfx::setDebug(BGFX_DEBUG_NONE);
}

App::App(bgfx::RendererType::Enum backend, bool _vsync) : vsync(_vsync), m_viewId(0)
{
    // Create window with GLFW
    createWindow(backend);

    // Clear view with blue color(#68c4e8)
    bgfx::setViewClear(m_viewId, BGFX_CLEAR_COLOR, 0x68c4e8ff);
    bgfx::setViewRect(m_viewId, 0, 0, bgfx::BackbufferRatio::Equal);

    // Init ImGUI
    imguiCreate(22);
    ImGui_ImplGlfw_InitForOther(m_window, true);
    ImGui::StyleColorsDark();

    // Init NanoVG
    m_ctx = nvgCreate(1, m_viewId);
}

App::~App()
{
    nvgDelete(m_ctx);
    ImGui_ImplGlfw_Shutdown();
    imguiDestroy();
    bgfx::shutdown();
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

///
/// \brief App::run Main loop for the game
///
auto App::run() -> void
{
    while (!glfwWindowShouldClose(m_window)) {
        glfwPollEvents();
        glfwGetFramebufferSize(m_window, &window_width, &window_height);
        // Run physics

        // Clear screen
        bgfx::setViewRect(0, 0, 0, window_width, window_height);
        bgfx::touch(m_viewId);

        // Draw ImGui
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        drawGUI();
        imguiEndFrame();

        // Draw nanovg
        nvgBeginFrame(m_ctx, window_width, window_height, 1.0f);
        drawVG();
        nvgEndFrame(m_ctx);

        // Render frame
        bgfx::frame();
    }
}

///
/// \brief App::drawVG Draws vector graphics using nanovg
///
auto App::drawVG() -> void
{
    nvgBeginPath(m_ctx);
    nvgCircle(m_ctx, 30, 30, 5);
    nvgFillColor(m_ctx, nvgRGBA(220,160,0,200));
    nvgFill(m_ctx);
}

///
/// \brief App::drawGUI Draws the user interface with ImGui
///
auto App::drawGUI() -> void
{
    ImGui::Begin("Another Window");
    ImGui::Text("Hello from another window!");
    ImGui::Text(fmt::format("Backend: {}", bgfx::getRendererName( bgfx::getRendererType())).c_str());

    ImGui::Text(fmt::format("FPS: {}", ImGui::GetIO().Framerate).c_str());
    if (ImGui::Button("Close Me")) {
        std::cout << "Hello" << std::endl;
    }
    ImGui::End();
}
