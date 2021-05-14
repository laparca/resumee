#ifndef TEMPLATE_WRAPPER_HPP
#define TEMPLATE_WRAPPER_HPP
#include <memory>
#include <resumee.hpp>

namespace resumee
{
    /**
    * The generated template clases use a template function. This is problematic because
    * it cannot be a virtual function. To solve this problem, the class template_wrapper
    * helps us simulating a "virtual render function" using type erasure.
    */
    template<typename StreamType>
    class template_wrapper
    {
        struct internal
        {
            virtual ~internal() {}
            virtual StreamType& render(StreamType&, resumee::v1::resumee const&) = 0;
        };
    
        template<typename T>
        struct internal_type : public internal
        {
            T value_;
    
            explicit internal_type(T const& value) : value_{value} {}
            explicit internal_type(T && value) : value_{std::move(value)} {}

            StreamType& render(StreamType& os, resumee::v1::resumee const& resumee) override
            {
                return value_.render(os, resmuee);
            }
        };
    
        std::shared_ptr<internal> internal_;
    
    public:
    
        template<typename T>
        template_wrapper(T const& t) : internal_{new internal_type<T>{t}}
        {}
        
        template<typename T>
        template_wrapper(T && t) : internal_{new internal_type<T>{std::move(t)}}
        {}

        template_wrapper() = default;
        template_wrapper(template_wrapper<StreamType> const&) = default;
        template_wrapper(template_wrapper<StreamType> &&) = default;
    
        StreamType& render(StreamType& out, resumee::v1::resumee const& resumee)
        {
            return internal_->render(out, resumee);
        }
    };
}
#endif
