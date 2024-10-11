/* -*- C++ -*- */

#ifndef INCLUDE_ALGORITHMS_VC_H_INCLUDED
#define INCLUDE_ALGORITHMS_VC_H_INCLUDED

#include <bitset>
#include <vector>

#include <common/constants.h>


std::bitset<max_order> ilst_to_vc(
    const std::vector<std::vector<unsigned>>& g,
    const std::vector<std::vector<unsigned>>& ilst,
    unsigned root
);


#endif // INCLUDE_ALGORITHMS_VC_H_INCLUDED
