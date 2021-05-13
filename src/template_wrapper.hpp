#ifndef TEMPLATE_WRAPPER_HPP
#define TEMPLATE_WRAPPER_HPP
#include <memory>

namespace resumee
{
    template<typename StreamType>
    class template_wrapper
    {
        struct internal
        {
            virtual ~internal() {}
            virtual StreamType& render(StreamType&) = 0;
        };
    
        template<typename T>
        struct internal_type : public internal
        {
            T value_;
    
            explicit internal_type(T const& value) : value_{value} {}
            explicit internal_type(T && value) : value_{std::move(value)} {}

            StreamType& render(StreamType& os) override
            {
                return value_.render(os);
            }
        };
    
        std::shared_ptr<internal> internal_;
    
    public:
    
        template<typename T>
        template_wrapper(T const& t) : internal_{new internal_type<T>{t}}
        {
        }
        
        template<typename T>
        template_wrapper(T && t) : internal_{new internal_type<T>{std::move(t)}}
        {
        }

        template_wrapper() = default;
        template_wrapper(template_wrapper<StreamType> const&) = default;
        template_wrapper(template_wrapper<StreamType> &&) = default;
    
        StreamType& render(StreamType& out)
        {
            return internal_->render(out);
        }
    };
}
#endif
