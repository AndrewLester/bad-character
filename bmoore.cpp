#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <map>

#include "bmoore.h"

std::vector<std::vector<int>> prep_bc_array(std::string P, std::string alpha) {
  std::map<char, std::vector<int>> charLookup;
  std::vector<std::vector<int>> bc_array;

  for (size_t i = 0; i < P.size(); i++) {
    char c = P.at(i);
    if (charLookup.find(c) != charLookup.end()) {
      charLookup.at(c).push_back(i);
      continue;
    }
    charLookup.insert(
        std::pair<char, std::vector<int>>(c, {static_cast<int>(i)}));
  }

  for (const char &alpha_char : alpha) {
    std::vector<int> row = {0};

    if (charLookup.find(alpha_char) == charLookup.end()) {
      for (int i = 1; i < P.size(); i++) {
        row.push_back(i);
      }
      bc_array.push_back(row);
      continue;
    }

    std::vector<int> positions = charLookup.at(alpha_char);
    for (size_t i = 1; i < P.size(); i++) {
      char c = P.at(i);

      int closest_dis = std::numeric_limits<int>::max();
      for (const int &pos : positions) {
        if (pos >= i) {
          break;
        }

        int distance = i - pos - 1;
        if (i - pos - 1 < closest_dis) {
          closest_dis = distance;
        }
      }

      if (closest_dis == std::numeric_limits<int>::max()) {
        closest_dis = i;
      }

      row.push_back(closest_dis);
    }
    bc_array.push_back(row);
  }

  return bc_array;
}

int findChar(std::string alpha, char c) { return alpha.find(c); }

int bmoore_search(std::string P, std::string T, std::string alpha,
                  std::vector<int> &outList) {
  int skip = 0;

  std::vector<std::vector<int>> bc_array = prep_bc_array(P, alpha);
  for (size_t i = 0; i < T.size() - P.size() + 1; i++) {
    int matches = 0;
    for (int j = P.size() - 1; j >= 0; j--) {
      char c = T.at(j + i);

      if (c == P.at(j)) {
        matches++;
        continue;
      }

      int alpha_index = findChar(alpha, c);
      int skips = bc_array.at(alpha_index).at(j);

      if (i == T.size() - P.size()) {
        break;
      }

      if (i + skips >= T.size() - P.size() + 1) {
        skips -= skips - (T.size() - P.size());
      }

      i += skips;
      skip += skips;

      break;
    }

    if (matches == P.size()) {
      outList.push_back(i);
    }
  }

  if (outList.empty()) {
    outList.push_back(-1);
  }

  return skip;
}
