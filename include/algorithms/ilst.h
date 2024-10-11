/* -*- C++ -*- */

#ifndef INCLUDE_ALGORITHMS_ILST_H_INCLUDED
#define INCLUDE_ALGORITHMS_ILST_H_INCLUDED

#include <vector>


bool make_ilst_or_hamil_path(const std::vector<std::vector<unsigned>>& g, std::vector<std::vector<unsigned>>& dfs_tree, unsigned& root);


#endif // INCLUDE_ALGORITHMS_ILST_H_INCLUDED
