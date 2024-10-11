/* -*- C++ -*- */

#ifndef INCLUDE_HELPERS_GRAPH_H_INCLUDED
#define INCLUDE_HELPERS_GRAPH_H_INCLUDED

#include <vector>


bool has_edge(const std::vector<std::vector<unsigned>>& g, const unsigned u, const unsigned v);

unsigned order_vertices(std::vector<std::vector<unsigned>>& g, bool (*ordering_fn)(const std::vector<std::vector<unsigned>>&, const unsigned, const unsigned));


#endif // INCLUDE_HELPERS_GRAPH_H_INCLUDED
