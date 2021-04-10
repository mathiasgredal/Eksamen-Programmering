 #include "../include/Util.h"

auto Util::tolower(std::string str) -> std::string {
    std::transform(str.begin(), str.end(), str.begin(), static_cast<int(*)(int)>(std::tolower));
    return str;
}

auto Util::getBackendName(bgfx::RendererType::Enum backend) -> std::string
{
    // Since every enum is in the map, this should not be able to fail
    return backend_names.at(backend);
}

auto Util::getBackendFromName(std::string backendName) -> bgfx::RendererType::Enum
{
    for(auto item : backend_names) {
        if(item.second == backendName)
            return item.first;
    }

    // We have not found any backend for this name, throw an error
    throw std::runtime_error("ERROR: Could not find a valid backend for \"" + backendName + "\"");
}

auto Util::getValidBackends() -> std::vector<bgfx::RendererType::Enum>
{
    bgfx::RendererType::Enum rendererTypes[bgfx::RendererType::Count];
    auto numberOfBackends = bgfx::getSupportedRenderers(bgfx::RendererType::Count, rendererTypes);

    auto backendList = std::vector<bgfx::RendererType::Enum>();

    for(auto i = 0; i < numberOfBackends; i++) {
        backendList.push_back(rendererTypes[i]);
    }

    return backendList;
}

auto Util::getFileData(const cmrc::file &file) -> uint8_t*
{
    return (uint8_t*)std::string_view(file.begin(), file.end() - file.begin()).data();
}

float Util::RadToDeg(float rad)
{
    return rad * 180.f / 3.1415926536f;
}
