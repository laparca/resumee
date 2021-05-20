export CPM_SOURCE_CACHE="${HOME}/.cache/CPM"
cmake -H. -Bbuild -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_CLANG_TIDY="clang-tidy;-checks=-*,cppcoreguidelines-*"
cmake --build build -v
