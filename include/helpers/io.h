/* -*- C++ -*- */

#ifndef INCLUDE_HELPERS_IO_H_INCLUDED
#define INCLUDE_HELPERS_IO_H_INCLUDED

#include <vector>


std::vector<std::vector<unsigned>> read_simple_graph(const char* graph_repr);

std::vector<std::vector<unsigned>> read_simple_graph_from_file(const char* filepath);


#endif // INCLUDE_HELPERS_IO_H_INCLUDED
