#include <string>
#include <algorithm>
#include <locale>
#include <cxxopts.hpp>

#include "../include/App.h"

auto tolower(std::string str) -> std::string {
    std::transform(str.begin(), str.end(), str.begin(), static_cast<int(*)(int)>(std::tolower));
    return str;
}

auto main(int argc, char* argv[]) -> int {
    cxxopts::Options options(argv[0], " - This is a demo for a 2D rigidbody physics engine");

    options.add_options()
            ("b,backend", "Set rendering backend(eg. OpenGL, Vulkan, Metal, DirectX9, DirectX11, DirectX12)", cxxopts::value<std::string>())
            ("l,list-backends", "List the availiable backends")
            ("h,help", "Print help");
    auto result = options.parse(argc, argv);

    if (result.count("help"))
    {
        std::cout << options.help() << std::endl;
        exit(0);
    }

    if(result.count("list-backends")) {
        std::cout << "Available backends: " << std::endl;
        bgfx::RendererType::Enum rendererTypes[bgfx::RendererType::Count];
        auto num = bgfx::getSupportedRenderers(bgfx::RendererType::Count, rendererTypes);
        for(auto i = 0; i < num; i++) {
            std::cout << fmt::format("    - {}", bgfx::getRendererName(rendererTypes[i])) << std::endl;
        }
        exit(0);
    }

    auto backend = bgfx::RendererType::Count;
    if(result.count("backend")) {
        auto backend_string = result["backend"].as<std::string>();
        std::cout << "Yeet: " << backend_string << std::endl;

//        if(tolower(backend_string).find("opengl") != std::string::npos)
//            backend =  bgfx::RendererType::OpenGL;
//        else if (tolower(backend_string) == "vulkan")
//            backend =  bgfx::RendererType::Vulkan;
    }


    auto app = App(backend);

    try {
        app.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
