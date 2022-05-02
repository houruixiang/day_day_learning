cmake_minimum_required(VERSION 3.12)

aux_source_directory(. NN_SRC)
message("NN_SRC: ${NN_SRC}")

add_library(nn STATIC ${NN_SRC})
