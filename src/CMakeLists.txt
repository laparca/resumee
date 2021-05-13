find_program(BASH bash HINTS /bin /usr/bin)
add_custom_command(
    OUTPUT web_test.cc
    COMMAND
        ${CMAKE_COMMAND} -E env ${BASH} -c "${cpptemplater_BINARY_DIR}/cpptemplater --class web_test -i template_base.hpp -i template_registry.hpp --parent-class resumee::template_base < ${resumee_SOURCE_DIR}/src/web_test.tmpl | tee web_test.cc"
    DEPENDS ${resumee_SOURCE_DIR}/src/web_test.tmpl
    VERBATIM
)

add_executable(
    resumee
    main.cc
    resumee.cc
    template_registry.cpp
    web_test.cc)

target_include_directories(resumee
    PRIVATE
        ${resumee_SOURCE_DIR}/src
)
target_link_libraries(resumee yaml-cpp)
