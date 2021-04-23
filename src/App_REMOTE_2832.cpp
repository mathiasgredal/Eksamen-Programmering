#include "../include/App.h"

auto App::glfw_errorCallback(int error, const char *description) -> void
{
    throw std::runtime_error(fmt::format("ERROR{}: {}", error, description));
}

auto App::glfw_windowResizeCallback(__attribute__((unused)) GLFWwindow *window, int width, int height) -> void
{
    auto app = (App*)glfwGetWindowUserPointer(window);
    app->windowWidth = width;
    app->windowHeight = height;

    bgfx::reset(app->scaledWidth(), app->scaledHeight(), (app->vsync? BGFX_RESET_VSYNC : BGFX_RESET_NONE));
}

auto App::createWindow(bgfx::RendererType::Enum backend) -> void
{
    glfwSetErrorCallback(App::glfw_errorCallback);

    if(!glfwInit())
        throw std::runtime_error("ERROR: Could not initialize glfw");

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    m_window = glfwCreateWindow(windowWidth, windowHeight, project_name.c_str(), nullptr, nullptr);

    if(!m_window)
        throw std::runtime_error("ERROR: Failed to create window");

    // Handle window resize
    glfwSetWindowSizeCallback(m_window, App::glfw_windowResizeCallback);
    glfwSetWindowUserPointer(m_window, (void *)this);

    // Calling renderFrame before init sets main thread to be render thread
    // See: https://bkaradzic.github.io/bgfx/internals.html
    bgfx::renderFrame();

    bgfx::Init init;
    init.type = backend;
    init.resolution.reset = (vsync? BGFX_RESET_VSYNC : BGFX_RESET_NONE);   // Use vsync
    init.resolution.width = scaledWidth();
    init.resolution.height = scaledHeight();

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

    int framebufWidth, framebufHeight;
    glfwGetFramebufferSize(m_window, &framebufWidth, &framebufHeight);
    scale = framebufHeight/(float)windowHeight;

    scale = 2.f;
    std::cout << "Scale: " << scale << std::endl;

    // Clear view with blue color(#68c4e8)
    bgfx::setViewClear(m_viewId, BGFX_CLEAR_COLOR, 0x68c4e8ff);
    bgfx::setViewRect(m_viewId, 0, 0, bgfx::BackbufferRatio::Equal);

    // Init ImGUI
    imguiCreate(14*scale);
    ImGui_ImplGlfw_InitForOther(m_window, true);
    ImGui::StyleColorsDark();

    // Init NanoVG
    m_ctx = nvgCreate(1, m_viewId);
    auto fs = cmrc::fonts::get_filesystem();
    auto serifFile = fs.open("fonts/FreeSerif.ttf");
    nvgCreateFontMem(m_ctx, "regular", Util::getFileData(serifFile), serifFile.size(), 0);

    auto emojiFile = fs.open("fonts/NotoEmoji-Regular.ttf");
    nvgCreateFontMem(m_ctx, "emoji", Util::getFileData(emojiFile) ,emojiFile.size(), 0);
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
        auto t_start = Clock::now();
        glfwPollEvents();
        // Run physics

        // Clear screen
        bgfx::setViewRect(0, 0, 0, scaledWidth(), scaledHeight());
        bgfx::touch(m_viewId);

        // Draw ImGui
        ImGui_ImplGlfw_NewFrame();
        ImGui::GetStyle().ScaleAllSizes(2.f);
        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize = ImVec2( (float)scaledWidth(), (float)scaledHeight());
        io.DisplayFramebufferScale = ImVec2(scale, scale);
        double mx, my;
        glfwGetCursorPos(m_window, &mx, &my);
        io.MousePos = ImVec2(mx*scale, my*scale);
        ImGui::NewFrame();
        drawGUI();
        imguiEndFrame();

        // Draw nanovg
        nvgBeginFrame(m_ctx, scaledWidth(), scaledHeight(), 1.0f);
        drawVG();
        nvgEndFrame(m_ctx);

        t_begin=t_start;
        t_end = Clock::now();
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
    nvgRect(m_ctx, 40, scaledHeight()-scaledHeight()*0.3, 100, 150);
    nvgStrokeWidth(m_ctx, 15);
    nvgStrokeColor(m_ctx, nvgRGB(20, 250, 10));
    nvgLineJoin(m_ctx, NVG_BEVEL);
    nvgStroke(m_ctx);

    nvgFontSize(m_ctx, 36);
    nvgFontFace(m_ctx, "regular");
    nvgText(m_ctx, 150, scaledHeight()-scaledHeight()*0.2, "This is some text", NULL);

    nvgFontSize(m_ctx, 36*4);
    nvgFontFace(m_ctx, "emoji");
    nvgFillColor(m_ctx, nvgRGB(200, 10, 10));
    nvgText(m_ctx, 30, scaledHeight()-scaledHeight()*0.4, "😃🎉🍆", NULL);

}

///
/// \brief App::drawGUI Draws the user interface with ImGui
///
auto App::drawGUI() -> void
{
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::Begin("Stats");
    ImGui::Text(fmt::format("Scale: {}", scale).c_str());
    ImGui::Text(fmt::format("Backend: {}", bgfx::getRendererName( bgfx::getRendererType())).c_str());
    ImGui::Text(fmt::format("FPS: {:.1f}", ImGui::GetIO().Framerate).c_str());

    float cpuTime = std::chrono::duration_cast<std::chrono::nanoseconds>(t_end-t_begin).count()/1000000.f;

#if BX_PLATFORM_OSX
    float gpuTime = (bgfx::getStats()->gpuTimeEnd-bgfx::getStats()->gpuTimeBegin)/1000.f;
#else
    float gpuTime = (bgfx::getStats()->gpuTimeEnd-bgfx::getStats()->gpuTimeBegin)/1000000.f;
#endif
    ImGui::Text(fmt::format("CPU Time: {:.3f}ms", cpuTime).c_str());
    ImGui::Text(fmt::format("GPU Time: {:.3f}ms", gpuTime).c_str());
    ImGui::End();

    ImGui::SetNextWindowSize(ImVec2(scaledWidth()*0.251, scaledHeight()));
    ImGui::SetNextWindowPos(ImVec2(scaledWidth()*0.75, 0));

    ImGui::PushStyleColor(ImGuiCol_ResizeGrip, 0);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);

    bool show_window = true;
    ImGui::Begin("Inspector", &show_window,  ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoMove);
    ImGui::Text("Hello from main window!");

    ImGui::End();
    ImGui::PopStyleVar();
    ImGui::PopStyleColor();
}


int App::scaledHeight()
{
    return windowHeight*scale;
}

int App::scaledWidth()
{
    return windowWidth*scale;
}