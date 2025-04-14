# CMakeList.txt : CMake project for praktika_9_1, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("praktika_9_1")

# utf8 on windows
if(MSVC)
    add_compile_options(/utf-8)
endif()

# Add source to this project's executable.
add_executable (praktika_9_1 "src/main.cpp" "src/calculators/matrix.cpp" "src/calculators/matrix.h" "src/calculators/common_fractions.cpp" "src/calculators/common_fractions.h" "src/calculators/combinatorics.cpp" "src/calculators/combinatorics.h" "src/calculators/polynomial.cpp" "src/calculators/polynomial.h" "src/calculators/probability_and_stats.cpp" "src/calculators/probability_and_stats.h" "src/calculators/functions.cpp" "src/calculators/functions.h" "src/common/menu.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET praktika_9_1 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
