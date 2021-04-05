#include <cxxopts.hpp>

#include "../include/App.h"
#include "../include/Util.h"

#include <fstream>


auto main(int argc, char* argv[]) -> int {
    cxxopts::Options options(argv[0], " - This is a demo for a 2D rigidbody physics engine");
    options.allow_unrecognised_options();

    options.add_options()
        ("b,backend", "Set rendering backend(eg. OpenGL, Vulkan, Metal, DirectX9, DirectX11, DirectX12)", cxxopts::value<std::string>())
        ("l,list-backends", "List the availiable backends")
        ("v,disable-vsync", "Disable V-Sync to uncap FPS")
        ("h,help", "Print help");

    auto result = options.parse(argc, argv);

    if (result.count("help"))
    {
        std::cout << options.help() << std::endl;
        return 0;
    }

    if(result.count("list-backends")) {
        std::cout << "Available backends: " << std::endl;
        for(auto backend : Util::getValidBackends())
            std::cout << "    - " << Util::getBackendName(backend) << std::endl;;
        return 0;
    }

    auto backend = bgfx::RendererType::Count;
    if(result.count("backend")) {
        auto backend_string = result["backend"].as<std::string>();
        backend = Util::getBackendFromName(backend_string);

        if(!Util::vectorContainsElement<bgfx::RendererType::Enum>(backend, Util::getValidBackends()))
            throw std::runtime_error("ERROR: Selected backend not available");

        std::cout << "Using backend: " << Util::getBackendName(backend) << std::endl;
    }

    auto vsync = true;
    if(result.count("disable-vsync"))
        vsync = false;


    auto *app = new App(backend, vsync);

    try {
        app->run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    delete app;


    std::cout << "Hello" << std::endl;

    return 0;
}
