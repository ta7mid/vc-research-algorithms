/* -*- C++ -*- */

#ifndef INCLUDE_ALGORITHMS_VERTEX_COVER_H_INCLUDED
#define INCLUDE_ALGORITHMS_VERTEX_COVER_H_INCLUDED

#include <unordered_set>
#include <vector>

#include <common/constants.h>


[[nodiscard]] std::unordered_set<unsigned> ilst_output_to_cvc(
    const std::vector<std::vector<unsigned>>& g,
    bool is_ilst,
    std::vector<std::vector<unsigned>>& ilst,
    unsigned& root
);

[[nodiscard]] std::unordered_set<unsigned> cvc_tree_to_vc(
    const std::vector<std::vector<unsigned>>& g,
    std::vector<std::vector<unsigned>> cvc_tree,
    unsigned root
);

bool is_vc(const std::vector<std::vector<unsigned>>& g, const std::unordered_set<unsigned>& node_set);

bool is_vc(const std::vector<std::vector<unsigned>>& g, const std::vector<unsigned>& node_list);


#endif // INCLUDE_ALGORITHMS_VERTEX_COVER_H_INCLUDED
