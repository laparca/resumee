#ifndef TEMPLATE_REGISTRY_HPP
#define TEMPLATE_REGISTRY_HPP

#include <template_wrapper.hpp>

namespace resumee
{
    using wrapper = resumee::template_wrapper<std::ostream>;

    void register_template(std::string const& name, wrapper const&);
    void register_template(std::string const& name, wrapper &&);

    struct register_template_helper
    {
        register_template_helper(std::string const& name, wrapper const& w)
        {
            register_template(name, w);
        }

        register_template_helper(std::string const& name, wrapper && w)
        {
            register_template(name, std::move(w));
        }
    };
}
#endif
