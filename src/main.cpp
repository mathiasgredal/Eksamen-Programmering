#include <cxxopts.hpp>

#include "../include/App.h"

int main(int argc, char* argv[]) {
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
        std::cout << "Available ,backends: " << std::endl;
        bgfx::RendererType::Enum rendererTypes[bgfx::RendererType::Count];
        uint8_t num = bgfx::getSupportedRenderers(bgfx::RendererType::Count, rendererTypes);
        for(int i = 0; i < num; i++) {
            std::cout << fmt::format("    - {}", bgfx::getRendererName(rendererTypes[i])) << std::endl;
        }
        exit(0);
    }


    auto app = App();

    try {
        app.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
