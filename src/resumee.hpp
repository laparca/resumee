#ifndef RESUMEE_HPP
#define RESUMEE_HPP

#include <yaml_serialization.hpp>

namespace resumee
{
    namespace v1
    {
        struct header
        {
            std::string name_;
            std::string phone_;
            std::string date_birth_;
            std::string jobtitle_;
            std::map<std::string, std::string> links_;
            std::string about_;
        };

        struct link
        {
            std::string name_;
            std::string href_;
        };

        struct education_detail
        {
            std::string start_;
            std::optional<std::string> end_;
            std::string title_;
            std::optional<std::string> calification_;
            std::optional<link> site_;
        };

        using education = std::vector<education_detail>;

        struct experience_detail
        {
            std::string start_;
            std::optional<std::string> end_;
            std::string title_;
            link company_;
            std::vector<std::string> skills_;
            std::vector<std::string> tasks_;
        };

        using experience = std::vector<experience_detail>;

        struct course
        {
            std::string date_;
            std::string title_;
            std::string issuer_;
            std::string href_;
        };

        using courses = std::vector<course>;

        struct other_detail
        {
            std::string title_;
        };

        using other = std::vector<other_detail>;

        struct resumee
        {
            std::string cv_version_;
            header header_;
            education education_;
            other other_;
        };
    }
}

#define EXTRACTOR_FOR(type) \
    namespace resumee { \
        namespace serialization { \
            template<> \
            struct reader_for<type> { \
                static type extract_from(YAML::Node const& node, std::string const& lang); \
                static type read(YAML::Node const& node, std::string const& field_name, std::string const& lang) { \
                    return extract_from(node[field_name], lang); \
                } \
            }; \
        } \
    }

EXTRACTOR_FOR(::resumee::v1::link)

EXTRACTOR_FOR(::resumee::v1::header)

EXTRACTOR_FOR(::resumee::v1::education_detail)

EXTRACTOR_FOR(::resumee::v1::experience_detail)

EXTRACTOR_FOR(::resumee::v1::course)

EXTRACTOR_FOR(::resumee::v1::other_detail)

EXTRACTOR_FOR(::resumee::v1::resumee)

#undef EXTRACTOR_FOR

#endif
