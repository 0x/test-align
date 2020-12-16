#pragma once

#include <string>
#include <vector>

namespace task3 {
[[nodiscard]] std::vector<int> parseFile(std::string_view filename);
[[nodiscard]] std::size_t minNumberRings(std::vector<int> &chain_fragments);
}  // namespace task3
