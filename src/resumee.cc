#include <resumee.hpp>

#define YAML_READ_P(type, field_name, name) reader_for<std::decay_t<decltype(type::name)>>::read(node, field_name, lang)
#define YAML_READ(type, name) YAML_READ_P(type, # name, name ## _)
#define EXTRACTOR_IMPL_FOR(type) \
    type resumee::serialization::reader_for<type>::extract_from(YAML::Node const& node, std::string const& lang)

EXTRACTOR_IMPL_FOR(::resumee::v1::link)
{
    using link = ::resumee::v1::link;
    return {
        YAML_READ(link, name),
        YAML_READ(link, href)
    };
}

EXTRACTOR_IMPL_FOR(::resumee::v1::header)
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

EXTRACTOR_IMPL_FOR(::resumee::v1::education_detail)
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

EXTRACTOR_IMPL_FOR(::resumee::v1::experience_detail)
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

EXTRACTOR_IMPL_FOR(::resumee::v1::course)
{
    using course = ::resumee::v1::course;
    return {
        YAML_READ(course, date),
        YAML_READ(course, title),
        YAML_READ(course, issuer),
        YAML_READ(course, href)
    };
}

EXTRACTOR_IMPL_FOR(::resumee::v1::other_detail)
{
    using detail = ::resumee::v1::other_detail;
    return {
        YAML_READ(detail, title)
    };
}

EXTRACTOR_IMPL_FOR(::resumee::v1::resumee)
{
    using resumee = ::resumee::v1::resumee;
    return {
        YAML_READ_P(resumee, "cvVersion", cv_version_),
        YAML_READ(resumee, header),
        YAML_READ(resumee, education),
        YAML_READ(resumee, experience),
        YAML_READ(resumee, other)
    };
}
