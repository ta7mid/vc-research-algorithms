/* -*- C++ -*- */

#ifndef SRC_ALGORITHMS_VERTEX_COVER_H_INCLUDED
#define SRC_ALGORITHMS_VERTEX_COVER_H_INCLUDED

#include <vector>


[[nodiscard]] unsigned delete_leaf(std::vector<std::vector<unsigned>>& tree, unsigned leaf);

void init_data_structures(
    const std::vector<std::vector<unsigned>>& g,
    const std::vector<std::vector<unsigned>>& tree,
    const unsigned root,

    // out params
    std::vector<unsigned>& node_parent,
    std::vector<unsigned>& level,
    std::vector<std::vector<unsigned>>& nodes_with_nchildren_todo,
    std::vector<bool>& covers_nontree_edge
);


#endif // SRC_ALGORITHMS_VERTEX_COVER_H_INCLUDED
