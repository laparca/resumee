#ifndef YAML_SERIALIZATION_HPP
#define YAML_SERIALIZATION_HPP

#include <yaml-cpp/yaml.h>
#include <optional>
#include <vector>
#include <map>

namespace resumee
{
    namespace serialization
    {
        template<typename T>
        struct reader_for;

        template<typename T>
        struct reader_for<std::optional<T>>
        {
            static std::optional<T> extract_from(YAML::Node const& node, std::string const& lang)
            {
                if (node)
                {
                    return reader_for<T>::extract_from(node, lang);
                }

                return {};
            }

            static std::optional<T> read(YAML::Node const& node, std::string const& field_name, std::string const& lang)
            {
                return extract_from(node[field_name], lang);
            }
        };
        
        template<>
        struct reader_for<std::string>
        {
            static std::string extract_from(YAML::Node const& node, std::string const& lang)
            {
                switch(node.Type())
                {
                    case YAML::NodeType::Scalar:
                        return node.as<std::string>();
                    case YAML::NodeType::Map:
                        return reader_for<std::string>::read(node, lang, lang);
                    case YAML::NodeType::Undefined:
                    case YAML::NodeType::Null:
                        return {};
                    default:
                        throw "";
                }
            }

            static std::string read(YAML::Node const& node, std::string const& field_name, std::string const& lang)
            {
                auto const& value = node[field_name];
                return extract_from(value, lang);
            }
        };

        template<typename T>
        struct reader_for<std::map<std::string, T>>
        {
            static std::map<std::string, T> extract_from(YAML::Node const& node, std::string const& lang)
            {
                std::map<std::string, T> result;
                
                if (node.Type() != YAML::NodeType::Map)
                {
                    throw "";
                }

                for (auto const& value : node)
                {
                    std::string key = value.first.as<std::string>();

                    result[key] = reader_for<T>::extract_from(value.second, lang);
                }

                return result;
            }

            static std::map<std::string, T> read(YAML::Node const& node, std::string const& field_name, std::string const& lang)
            {
                std::map<std::string, T> result;

                auto const& value = node[field_name];

                return extract_from(value, lang);
            }
        };

        template<typename T>
        struct reader_for<std::vector<T>>
        {
            static std::vector<T> extract_from(YAML::Node const& node, std::string const& lang)
            {
                if (node.Type() == YAML::NodeType::Undefined)
                {
                    return {};
                }
                if (node.Type() != YAML::NodeType::Sequence)
                {
                    throw "";
                }

                std::vector<T> result;

                for (auto const& value : node)
                {
                    result.push_back(reader_for<T>::extract_from(value, lang));
                }

                return result;
            }

            static std::vector<T> read(YAML::Node const& node, std::string const& field_name, std::string const& lang)
            {
                return extract_from(node[field_name], lang);
            }
        };

    }
}

#endif
