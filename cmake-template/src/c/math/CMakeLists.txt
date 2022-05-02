cmake_minimum_required(VERSION 3.12)

aux_source_directory(. MATH_SRC)
message("MATH_SRC: ${MATH_SRC}")

add_library(math STATIC ${MATH_SRC})
