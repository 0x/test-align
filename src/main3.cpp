#include <fstream>
#include <iostream>

#include "task3.hpp"

namespace {
void usage() {
  std::cout
      << "Usage: \n"
         "\t task3 <filename>\tPrint minimum number of rings that have to "
         "straighten.\n"
         "\t <filename> contains a string with comma-separated lengths of "
         "chain fragments.\n"
         "\t Lengths - positive integers."
      << std::endl;
}
}  // namespace

int main(int argc, const char *argv[]) try {
  if (argc < 2) {
    usage();
    return 0;
  }
  const std::string filename{argv[1]};
  auto chain_fragments = task3::parseFile(filename);
  // Calculate minimum number rings to make chain.
  const auto min_rings = task3::minNumberRings(chain_fragments);
  std::cout << "The minimum number of rings that have to straighten: "
            << min_rings << std::endl;
} catch (const std::exception &except) {
  std::cerr << "Error: " << except.what() << std::endl;
  usage();
}
