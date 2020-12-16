#include <iostream>

#include "task1.hpp"

namespace {
void usage() {
  std::cout << "Usage: \n"
               "\t <filename>\tPrint number of points inside the contour.\n"
               "\t In <filename>, the first line contains two space-separated "
               "numbers n and m"
               " (2 ≤ n <1e+3, 1 ≤ m < 1e+4).\n"
               "\t n is the number of segments,"
               " m is the number of points to check.\n"
               "\t The next 2*n lines contain coordinates of the segments.\n"
               "\t The next m lines contain the coordinates of the points to "
               "be checked.\n"
               "\n\t Coordinates - integer number separated a space, modulo "
               "not exceeding 1e+8."
            << std::endl;
}
}  // namespace

int main(int argc, const char *argv[]) try {
  if (argc < 2) {
    usage();
    return 0;
  }
  const std::string filename{argv[1]};
  const auto [polygon_points, test_points] = task1::parseFile(filename);
  const auto result_number_points = task1::numberPointsInPolygon(polygon_points, test_points);
  std::cout << "Number of points inside the contour: " << result_number_points << std::endl;
} catch (const std::exception &except) {
  std::cerr << "Error: " << except.what() << std::endl;
  usage();
}
