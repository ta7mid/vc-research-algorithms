/* -*- C++ -*- */

#ifndef SRC_HELPERS_IO_H_INCLUDED
#define SRC_HELPERS_IO_H_INCLUDED

#include <istream>
#include <string>
#include <vector>


std::vector<std::vector<unsigned>> read(std::istream& iss, const std::string& additional_ctx = "");


#endif // SRC_HELPERS_IO_H_INCLUDED
