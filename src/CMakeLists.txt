find_program(BASH bash HINTS /bin /usr/bin)
function(prepare_template out_var)
    set(result)
    foreach(in_f ${ARGN})
        set(out_f "${CMAKE_CURRENT_BINARY_DIR}/${in_f}.cpp")
        add_custom_command(
            OUTPUT ${out_f}
            COMMAND
                ${CMAKE_COMMAND} -E env ${BASH} -c "${cpptemplater_BINARY_DIR}/cpptemplater --class web_test -i resumee.hpp -i template_registry.hpp -i utils.hpp -e 'resumee::v1::resumee const& resumee' < ${in_f} > ${out_f}"
            DEPENDS ${in_f}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            COMMENT "Creating preprocessed template file ${out_f}"
            VERBATIM
        )
        list(APPEND result ${out_f})
    endforeach()
    set(${out_var} "${result}" PARENT_SCOPE)
endfunction()

prepare_template(template_files web_test.tmpl)

add_executable(
    resumee
    main.cc
    resumee.cc
    template_registry.cpp
    ${template_files})

target_include_directories(resumee
    PRIVATE
        ${resumee_SOURCE_DIR}/src
)
target_link_libraries(resumee PRIVATE yaml-cpp Boost::program_options)
