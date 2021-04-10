#include "../include/App.h"

auto App::glfw_errorCallback(int error, const char *description) -> void
{
    throw std::runtime_error(fmt::format("ERROR{}: {}", error, description));
}

auto App::glfw_windowResizeCallback(GLFWwindow *window, int width, int height) -> void
{
    auto app = (App*)glfwGetWindowUserPointer(window);
    app->m_windowWidth = width;
    app->m_windowHeight = height;

    bgfx::reset(app->getWindowWidth(), app->getWindowHeight(), (app->vsync? BGFX_RESET_VSYNC : BGFX_RESET_NONE));
}

auto App::createWindow(bgfx::RendererType::Enum backend) -> void
{
    glfwSetErrorCallback(App::glfw_errorCallback);

    if(!glfwInit())
        throw std::runtime_error("ERROR: Could not initialize glfw");

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    m_window = glfwCreateWindow(m_windowWidth, m_windowHeight, project_name.c_str(), nullptr, nullptr);

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
    init.resolution.width = getWindowWidth();
    init.resolution.height = getWindowHeight();

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

    // Calculate scale
    m_scale = (float)getWindowHeight()/m_windowHeight;

    // Clear view with blue color(#68c4e8)
    bgfx::setViewClear(m_viewId, BGFX_CLEAR_COLOR, 0x68c4e8ff);
    bgfx::setViewRect(m_viewId, 0, 0, bgfx::BackbufferRatio::Equal);

    // Init ImGUI
    imguiCreate(28);
    ImGui_ImplGlfw_InitForOther(m_window, true);
    ImGui::StyleColorsDark();

    // Init NanoVG
    m_ctx = nvgCreate(1, m_viewId);
    auto fs = cmrc::fonts::get_filesystem();
    auto serifFile = fs.open("fonts/FreeSerif.ttf");
    nvgCreateFontMem(m_ctx, "regular", Util::getFileData(serifFile), serifFile.size(), 0);

    auto emojiFile = fs.open("fonts/NotoEmoji-Regular.ttf");
    nvgCreateFontMem(m_ctx, "emoji", Util::getFileData(emojiFile) ,emojiFile.size(), 0);
	
	//create level
    m_level = Scene();
    m_level.Add(std::make_shared<Entity>(Vec2d(400, 50), 0, std::make_shared<Circle>(10)));
    m_level.Add(std::make_shared<Entity>(Vec2d(425, 50), 0, std::make_shared<Circle>(10)));
    m_level.Add(std::make_shared<Entity>(Vec2d(445, 50), 0, std::make_shared<Circle>(10)));

//    m_level.Add(Entity(Vec2d(300, 200), 0, std::make_shared<Circle>(50), SimType::Static));
//    m_level.Add(Entity(Vec2d(600, 300), 0, std::make_shared<Rectangle>(20, 60)));
    m_level.Add(std::make_shared<Entity>(Vec2d(300, 700), 0, std::make_shared<Circle>(200), 1, 10, SimType::Static));
    m_level.Add(std::make_shared<Entity>(Vec2d(550, 700), 0, std::make_shared<Circle>(200), 1, 1, SimType::Static));


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

int mouseState = GLFW_RELEASE;

///
/// \brief App::run Main loop for the game
///
auto App::run() -> void
{
    while (!glfwWindowShouldClose(m_window)) {
        auto t_start = Clock::now();
        glfwPollEvents();


        if(glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_LEFT) !=  mouseState)
        {
            mouseState = glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_LEFT);
            if(mouseState == GLFW_PRESS) {
                double x, y;
                glfwGetCursorPos(m_window, &x, &y);
                m_level.Add(std::make_shared<Entity>(Vec2d(x*m_scale, y*m_scale), 0, std::make_shared<Circle>(15), 5, 2));
            }

        }


        // Run physics
        m_level.Step(ImGui::GetIO().DeltaTime);

        // Clear screen
        bgfx::setViewRect(0, 0, 0, getWindowWidth(), getWindowHeight());
        bgfx::touch(m_viewId);

        // Draw ImGui
        ImGui_ImplGlfw_NewFrame();
        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize = ImVec2( getWindowWidth(), getWindowHeight());
        io.DisplayFramebufferScale = ImVec2(m_scale, m_scale);
        double mx, my;
        glfwGetCursorPos(m_window, &mx, &my);
        io.MousePos = ImVec2(mx*m_scale, my*m_scale);

        ImGuiStyle& style = ImGui::GetStyle();
        ImGuiStyle styleold = style;
        style = ImGuiStyle();
        style.ScaleAllSizes(m_scale);
        memcpy(style.Colors, styleold.Colors, sizeof(style.Colors));

        ImGui::NewFrame();
        drawGUI();
        imguiEndFrame();

        // Draw nanovg
        nvgBeginFrame(m_ctx, getWindowWidth(), getWindowHeight(), 1.0f);
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
    // Draw scene entities
    for(auto entity : m_level.getEntities()) {
        entity->shape->Draw(m_ctx, entity);
    }

//    nvgBeginPath(m_ctx);
//    nvgRect(m_ctx, 40, getWindowHeight()-getWindowHeight()*0.3, 100, 150);
//    nvgStrokeWidth(m_ctx, 15);
//    nvgStrokeColor(m_ctx, nvgRGB(20, 250, 10));
//    nvgLineJoin(m_ctx, NVG_BEVEL);
//    nvgStroke(m_ctx);

    nvgFontSize(m_ctx, 36);
    nvgFontFace(m_ctx, "regular");
    nvgText(m_ctx, 150, getWindowHeight()-getWindowHeight()*0.2, "This is some text", NULL);

//    nvgFontSize(m_ctx, 36*4);
//    nvgFontFace(m_ctx, "emoji");
//    nvgFillColor(m_ctx, nvgRGB(200, 10, 10));
//    nvgText(m_ctx, 30, getWindowHeight()-getWindowHeight()*0.4, "😃🎉🍆", NULL);
}



///
/// \brief App::drawGUI Draws the user interface with ImGui
///
auto App::drawGUI() -> void
{
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::Begin("Stats");
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

    ImGui::SetNextWindowSize(ImVec2(getWindowWidth()*0.251, getWindowHeight()));
    ImGui::SetNextWindowPos(ImVec2(getWindowWidth()*0.75, 0));

    ImGui::PushStyleColor(ImGuiCol_ResizeGrip, 0);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);

    bool show_window = true;
    ImGui::Begin("Inspector", &show_window,  ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoMove);
    ImGui::Text("Hello from main window!");

    ImGui::End();
    ImGui::PopStyleVar();
    ImGui::PopStyleColor();
}

auto App::getWindowHeight() -> int
{
    int height;
    glfwGetFramebufferSize(m_window, nullptr, &height);
    return height;
}

auto App::getWindowWidth() -> int
{
    int width;
    glfwGetFramebufferSize(m_window, &width, nullptr);
    return width;
}
