#pragma once

#include <unordered_map>
#include <algorithm>
#include <string>
#include <locale>
#include <stdint.h>

#include <bgfx/bgfx.h>
#include <cmrc/cmrc.hpp>

namespace Util {
const std::unordered_map<bgfx::RendererType::Enum, std::string> backend_names = {
    {bgfx::RendererType::Noop,          "Noop"      },
    {bgfx::RendererType::Count,         "Auto"},
    {bgfx::RendererType::Direct3D9,     "DirectX9"  },
    {bgfx::RendererType::Direct3D11,    "DirectX11" },
    {bgfx::RendererType::Direct3D12,    "DirectX12" },
    {bgfx::RendererType::Gnm,           "Gnm"       },
    {bgfx::RendererType::Nvn,           "Nvn"       },
    {bgfx::RendererType::Metal,         "Metal"     },
    {bgfx::RendererType::Vulkan,        "Vulkan"    },
    {bgfx::RendererType::OpenGL,        "OpenGL"    },
    {bgfx::RendererType::OpenGLES,      "OpenGLES"  },
    {bgfx::RendererType::WebGPU,        "WebGPU"    },
};

auto tolower(std::string str) -> std::string;

// Templates can only be implemented in headerfiles
template<class T>
auto vectorContainsElement(const T &elem, const std::vector<T> &list) -> bool
{
    return std::find(list.begin(), list.end(), elem) != list.end();
}

// Backend helper functions
auto getBackendName(bgfx::RendererType::Enum backend) -> std::string;
auto getBackendFromName(std::string backendName) -> bgfx::RendererType::Enum;
auto getValidBackends() -> std::vector<bgfx::RendererType::Enum>;

// File helper functions
auto getFileData(const cmrc::file& file) -> uint8_t*;

// Math helpers
float RadToDeg(float rad);
}

