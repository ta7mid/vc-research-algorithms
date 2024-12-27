/* -*- C++ -*- */

#ifndef INCLUDE_GRAPH_HELPERS_GRAPH_HELPERS_H_INCLUDED
#define INCLUDE_GRAPH_HELPERS_GRAPH_HELPERS_H_INCLUDED

#include <vector>


bool has_edge(const std::vector<std::vector<unsigned>>& g, const unsigned u, const unsigned v);

unsigned order_vertices(std::vector<std::vector<unsigned>>& g, bool (*ordering_fn)(const std::vector<std::vector<unsigned>>&, const unsigned, const unsigned));

std::vector<std::vector<unsigned>> compress_node_ids(const std::vector<std::vector<unsigned>>& g, std::vector<unsigned>& kept_nodes);


#endif // INCLUDE_GRAPH_HELPERS_GRAPH_HELPERS_H_INCLUDED
