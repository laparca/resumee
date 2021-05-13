#pragma once

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

#define YAML_READ_P(type, field_name, name) reader_for<std::decay_t<decltype(type::name)>>::read(node, field_name, lang)
#define YAML_READ(type, name) YAML_READ_P(type, # name, name ## _)
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
    } \
    type resumee::serialization::reader_for<type>::extract_from(YAML::Node const& node, std::string const& lang)

EXTRACTOR_FOR(::resumee::v1::link)
{
    using link = ::resumee::v1::link;
    return {
        YAML_READ(link, name),
        YAML_READ(link, href)
    };
}

EXTRACTOR_FOR(::resumee::v1::header)
{
    using header = ::resumee::v1::header;
    return {
        YAML_READ(header, name),
        YAML_READ(header, phone),
        YAML_READ_P(header, "dateBirth", date_birth_),
        YAML_READ(header, jobtitle),
        YAML_READ(header, links),
        YAML_READ(header, about)
    };
}

EXTRACTOR_FOR(::resumee::v1::education_detail)
{
    using detail = ::resumee::v1::education_detail;
    return {
        YAML_READ(detail, start),
        YAML_READ(detail, end),
        YAML_READ(detail, title),
        YAML_READ(detail, calification),
        YAML_READ(detail, site)
    };
}

EXTRACTOR_FOR(::resumee::v1::experience_detail)
{
    using detail = ::resumee::v1::experience_detail;
    return {
        YAML_READ(detail, start),
        YAML_READ(detail, end),
        YAML_READ(detail, title),
        YAML_READ(detail, company),
        YAML_READ(detail, skills),
        YAML_READ(detail, tasks)
    };
}

EXTRACTOR_FOR(::resumee::v1::course)
{
    using course = ::resumee::v1::course;
    return {
        YAML_READ(course, date),
        YAML_READ(course, title),
        YAML_READ(course, issuer),
        YAML_READ(course, href)
    };
}

EXTRACTOR_FOR(::resumee::v1::other_detail)
{
    using detail = ::resumee::v1::other_detail;
    return {
        YAML_READ(detail, title)
    };
}

EXTRACTOR_FOR(::resumee::v1::resumee)
{
    using resumee = ::resumee::v1::resumee;
    return {
        YAML_READ_P(resumee, "cvVersion", cv_version_),
        YAML_READ(resumee, header),
        YAML_READ(resumee, education),
        YAML_READ(resumee, other)
    };
}

#undef YAML_READ_P
#undef YAML_READ
#undef EXTRACTOR_FOR
