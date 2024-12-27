/* -*- C++ -*- */

#ifndef INCLUDE_IO_HELPERS_IO_HELPERS_H_INCLUDED
#define INCLUDE_IO_HELPERS_IO_HELPERS_H_INCLUDED

#include <vector>


std::vector<std::vector<unsigned>> read_simple_graph(const char* graph_representation);

std::vector<std::vector<unsigned>> read_simple_graph_from_file(const char* filepath);

std::vector<std::vector<unsigned>> read_simple_graph_from_stdin();


#endif // INCLUDE_IO_HELPERS_IO_HELPERS_H_INCLUDED
