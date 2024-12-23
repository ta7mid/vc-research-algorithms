/* -*- C++ -*- */

#ifndef INCLUDE_ALGORITHMS_VC_H_INCLUDED
#define INCLUDE_ALGORITHMS_VC_H_INCLUDED

#include <bitset>
#include <vector>

#include <common/constants.h>


[[nodiscard]] std::bitset<max_order> ilst_output_to_cvc(
    const std::vector<std::vector<unsigned>>& g,
    bool is_ilst,
    std::vector<std::vector<unsigned>>& ilst,
    unsigned& root
);

[[nodiscard]] std::bitset<max_order> cvc_tree_to_vc(
    const std::vector<std::vector<unsigned>>& g,
    const std::vector<std::vector<unsigned>>& cvc_tree,
    unsigned root
);

/**
 * @pre g is a connected non-ring graph
 * @pre ilst is an independent-leaves spanning tree of g
 * @param g the base graph
 * @param ilst an ILST of g
 * @param root the root of the ILST
 * @return a vertex cover of g
 */
[[nodiscard]] std::bitset<max_order> ilst_to_vc(
    const std::vector<std::vector<unsigned>>& g,
    std::vector<std::vector<unsigned>>& ilst,
    unsigned root
);

bool is_vc(const std::vector<std::vector<unsigned>>& g, const std::bitset<max_order>& is_included);


#endif // INCLUDE_ALGORITHMS_VC_H_INCLUDED
