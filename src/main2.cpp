#include <iostream>
#include <sstream>

#include "task2.hpp"

namespace {
void usage() {
  std::cout << "Usage: \n"
               "\t task2 <number of points - N>\tPrint an ordered list of "
               "point coordinates."
            << std::endl;
}
}  // namespace

int main(int argc, const char *argv[]) try {
  if (argc < 2) {
    usage();
    return 0;
  }
  std::size_t N;  // Number of points.
  std::stringstream input_points_number;
  input_points_number << argv[1];
  input_points_number >> N;
	
  // Сircle definition.
  constexpr task2::point circle_center(0, 0);
  constexpr auto circle_radius = 80.0;
  // Range of random points.
  constexpr std::pair<double, double> range_x(-100, 100);
  constexpr std::pair<double, double> range_y(-100, 100);
  const auto test_points = task2::makeRandomPointsInRange(N, range_x, range_y);

  // Maximum distance from a point to a circle.
  constexpr auto max_range = 10.0;
  // Filter points by range and sort by angle from 0 to 2pi.
  const auto test_points_in_range = task2::filterPointsByRangeWithAngle(
      circle_radius, circle_center, max_range, test_points);
  std::cout << "An ordered list of point coordinates:\n";
  for (const auto &elem : test_points_in_range) {
    std::cout << "(" << elem.first << ", " << elem.second << ")\n";
  }
} catch (const std::exception &except) {
  std::cerr << "Error: " << except.what() << std::endl;
  usage();
}
