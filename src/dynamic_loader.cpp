#include <mi/dynamic_loader.hpp>

using namespace mi;

void
dynamic_loader::load_modules()
{
    filter::iterate(
        begin(),
        end(),
        [](auto &module)
        {
            module->load();
        },
        [](const auto &module)
        {
            return module != nullptr && module->is_unloaded();
        });
}

void
dynamic_loader::unload_modules()
{
    filter::iterate(
        rbegin(),
        rend(),
        [](auto &module)
        {
            module->unload();
        },
        [](const auto &module)
        {
            return module != nullptr && module->is_loaded();
        });
}

void
dynamic_loader::load()
{
    dynamic_module::load();
    load_modules();
}

void
dynamic_loader::unload()
{
    unload_modules();
    dynamic_module::unload();
}