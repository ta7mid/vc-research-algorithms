/* -*- C++ -*- */

#ifndef INCLUDE_ALGORITHMS_CONNECTIVITY_H_INCLUDED
#define INCLUDE_ALGORITHMS_CONNECTIVITY_H_INCLUDED

#include <vector>


std::vector<unsigned> next_connected_component(const std::vector<std::vector<unsigned>>& g, std::vector<bool>& visited);

bool is_connected(const std::vector<std::vector<unsigned>>& g);


#endif // INCLUDE_ALGORITHMS_CONNECTIVITY_H_INCLUDED
