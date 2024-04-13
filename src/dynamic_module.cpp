#include <mi/dynamic_module.hpp>

using namespace mi;

void
dynamic_module::load()
{

    dynamic_library::load();
    try_call<void(dynamic_module &)>("on_module_load", {}, *this);
}

void
dynamic_module::unload()
{
    try_call<void(dynamic_module &)>("on_module_unload", {}, *this);
    dynamic_library::unload();
}

std::string
dynamic_module::classname() const
{
    return format::interpolate_string(std::string_view("{}::{}"),
                                      extension::classname(),
                                      info().name);
}

const module_info &
dynamic_module::info() const
{
    return call<const module_info &()>("on_module_info");
}

fs::path_t
dynamic_module::root_path() const
{
    return path().parent_path();
}

fs::path_t
dynamic_module::config_dir() const
{
    return root_path().parent_path() / "config";
}
