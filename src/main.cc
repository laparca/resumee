#include <iostream>
#include <vector>
#include <map>
#include <optional>
#include <resumee.hpp>
#include <template_registry.hpp>
#include <boost/program_options.hpp>

int main(int argc, char** argv)
{
    namespace po = boost::program_options;
    po::options_description desc("Allowed options");
    std::string lang;
    std::string input_file;
    std::string resumee_template;

    desc.add_options()
        ("help,h", "This help message")
        ("lang,l", po::value<std::string>(&lang)->default_value("es"), "Language to use")
        ("input-file,i", po::value<std::string>(&input_file), "Yaml with the resumee")
        ("template,t", po::value<std::string>(&resumee_template)->default_value("web_test"), "Template to render the resumee")
        ("list-templates", "List all the templates you can use for your resumee")
        ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if(vm.count("help"))
    {
        std::cout << desc << std::endl;
        return 1;
    }

    if (vm.count("list-templates"))
    {
        resumee::registry_list([](std::string const& template_name)
        {
            std::cout << template_name << std::endl;
        });
        return 0;
    }

    if (vm.count("input-file") == 0)
    {
        std::cerr << "Parameter input-file is mandatory" << std::endl;
        return 1;
    }

    auto const resumee_yaml = YAML::LoadFile(input_file);
    auto const resumee = resumee::serialization::reader_for<resumee::v1::resumee>::extract_from(resumee_yaml, lang);

    try
    {
        resumee::registry_get(resumee_template).render(std::cout, resumee);
    }
    catch(std::out_of_range const& e)
    {
        std::cerr << "The template " << resumee_template << " is invalid." << std::endl;
        std::cerr << "Please, use --list-templates to check the valid ones" << std::endl;
        return 1;
    }

    return 0;
}
