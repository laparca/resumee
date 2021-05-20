#include <template_registry.hpp>
#include <map>

namespace resumee
{
    namespace
    {
        std::map<std::string, wrapper>& registry()
        {
            static std::map<std::string, wrapper> reg{};
            return reg;
        }
    }

    void register_template(std::string const& name, wrapper const& w)
    {
        registry().insert({name, w});
    }

    void register_template(std::string const& name, wrapper && w)
    {
        registry().insert({name, std::move(w)});
    }

    wrapper& registry_get(std::string const& name)
    {
        return registry().at(name);
    }

    void registry_list(std::function<void(std::string const&)> f)
    {
        for (auto const& entry : registry())
        {
            f(entry.first);
        }
    }
}
