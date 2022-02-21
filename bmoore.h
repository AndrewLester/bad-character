#pragma once

#include <map>
#include <string>
#include <vector>

std::vector<std::vector<int>> prep_bc_array(std::string P,
                                            std::string alphabet);
int bmoore_search(std::string P, std::string T, std::string alpha,
                  std::vector<int> &outList);
