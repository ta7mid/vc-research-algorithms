/* -*- C++ -*- */

#ifndef SRC_ALGORITHMS_VC_H_INCLUDED
#define SRC_ALGORITHMS_VC_H_INCLUDED

#include <bitset>
#include <vector>

#include <common/constants.h>


std::bitset<max_n> ilst_to_vc(
    const std::vector<std::vector<unsigned>>& g,
    const std::vector<std::vector<unsigned>>& ilst,
    unsigned root
);


#endif // SRC_ALGORITHMS_VC_H_INCLUDED
