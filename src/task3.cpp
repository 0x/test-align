#include "task3.hpp"

#include <algorithm>
#include <cassert>
#include <fstream>

namespace task3 {
std::vector<int> parseFile(std::string_view filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    throw std::runtime_error("Could'n open input file.");
  }
  std::vector<int> chain_fragments;
  unsigned int fragment;
  char comma;
  while (file >> fragment) {
    assert(fragment >= 0);
    chain_fragments.push_back(fragment);
    // Read the symbol ","
    file >> comma;
  }
  file.close();
  return chain_fragments;
}

std::size_t minNumberRings(std::vector<int> &chain_fragments) {
  auto min_fragment =
      std::min_element(chain_fragments.begin(), chain_fragments.end());
  assert(min_fragment != chain_fragments.end());
  if (*min_fragment == 0) {
    chain_fragments.erase(min_fragment);
    min_fragment =
        std::min_element(chain_fragments.begin(), chain_fragments.end());
  } else if (*min_fragment >= chain_fragments.size()) {
    return chain_fragments.size() - 1;
  } else if (*min_fragment == chain_fragments.size() - 2 ||
             *min_fragment == chain_fragments.size() - 1) {
    return *min_fragment;
  } else {
    const auto min = *min_fragment;
    chain_fragments.erase(min_fragment);
    auto sum_max = 0;
    for (auto i = 0u; i <= min; i++) {
      auto max_fragment =
          std::max_element(chain_fragments.begin(), chain_fragments.end());
      sum_max += *max_fragment;
      chain_fragments.erase(max_fragment);
    }
    chain_fragments.push_back(sum_max);
    return min + minNumberRings(chain_fragments);
  }
  return 0;
}
}  // namespace task3
