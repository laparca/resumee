#include <iostream>
#include <vector>
#include <map>
#include <optional>
#include <resumee.hpp>
#include <template_wrapper.hpp>

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cerr << "Wrong number of arguments" << std::endl;
        exit(1);
    }

    auto resumee_yaml = YAML::LoadFile(argv[1]);
    auto resumee = resumee::serialization::reader_for<resumee::v1::resumee>::extract_from(resumee_yaml, "es");

    return 0;
}
