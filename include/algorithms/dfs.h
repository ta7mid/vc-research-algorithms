/* -*- C++ -*- */

#ifndef INCLUDE_ALGORITHMS_DFS_H_INCLUDED
#define INCLUDE_ALGORITHMS_DFS_H_INCLUDED

#include <vector>


std::vector<std::vector<unsigned>> dfs(const std::vector<std::vector<unsigned>>& g, unsigned source);

bool is_connected(const std::vector<std::vector<unsigned>>& g);


#endif // INCLUDE_ALGORITHMS_DFS_H_INCLUDED
