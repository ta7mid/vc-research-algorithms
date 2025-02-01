/* -*- C++ -*- */

#ifndef SRC_ALGORITHMS_VERTEX_COVER_H_INCLUDED
#define SRC_ALGORITHMS_VERTEX_COVER_H_INCLUDED

#include <unordered_set>
#include <vector>


[[nodiscard]] unsigned delete_leaf(std::vector<std::vector<unsigned>>& tree, unsigned leaf);

void init_data_structures(
    const std::vector<std::vector<unsigned>>& g,
    const std::vector<std::vector<unsigned>>& tree,
    const unsigned root,

    // out params
    std::vector<unsigned>& parent,
    std::vector<unsigned>& nchildren,
    std::vector<std::unordered_set<unsigned>>& nodes_with_nchildren,
    std::vector<bool>& covers_nontree_edge
);


#endif // SRC_ALGORITHMS_VERTEX_COVER_H_INCLUDED
