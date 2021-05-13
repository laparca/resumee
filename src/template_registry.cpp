#include <template_registry.hpp>
#include <map>

namespace resumee
{
    namespace 
    {
        std::map<std::string, wrapper> template_registry;
    }

    void register_template(std::string const& name, wrapper const& w)
    {
        template_registry.insert(std::pair<std::string, wrapper>{name, w});
    }
    void register_template(std::string const& name, wrapper && w)
    {
        template_registry.insert(std::pair<std::string, wrapper>{name, std::move(w)});
    }
}
