#include "task2.hpp"

#include <cassert>
#include <cmath>
#include <iostream>
#include <random>

namespace task2 {
std::vector<point> makeRandomPointsInRange(const std::size_t points_number,
                                           const range &range_x,
                                           const range &range_y) {
  // Number of points must be positive.
  assert(points_number >= 0);
  // Seed with a real random value, if available.
  std::random_device rd;
  std::default_random_engine random_engine(rd());
  std::uniform_real_distribution<double> uniform_dist_x(range_x.first,
                                                        range_x.second);
  std::uniform_real_distribution<double> uniform_dist_y(range_y.first,
                                                        range_y.second);
  std::vector<point> random_points;
  random_points.reserve(points_number);
  for (auto number = 0; number < points_number; number++) {
    random_points.emplace_back(uniform_dist_x(random_engine),
                               uniform_dist_y(random_engine));
  }
  return random_points;
}

std::vector<point> filterPointsByRange(
    const double circle_radius, const point &circle_center,
    const double max_range, const std::vector<point> &unfiltered_points) {
  std::vector<point> filtered_points;
  std::copy_if(unfiltered_points.begin(), unfiltered_points.end(),
               std::back_inserter(filtered_points), [&](const auto &elem) {
                 const auto distance =
                     std::sqrt((elem.first - circle_center.first) *
                                   (elem.first - circle_center.first) +
                               (elem.second - circle_center.second) *
                                   (elem.second - circle_center.second));
                 return std::abs(circle_radius - distance) < max_range;
               });

  return filtered_points;
}

double angleFromPointToCenter(const point &circle_center,
                              const point &input_point) {
  constexpr auto pi = 3.14159265358979323846;
  // Calculate angle of the segment from the point to the center, [0, 2pi].
  auto angle = std::atan2(input_point.second - circle_center.second,
                          input_point.first - circle_center.first);
  return (angle < 0.0) ? (angle + 2.0 * pi) : angle;
}

std::vector<point> filterPointsByRangeWithAngle(
    const double circle_radius, const point &circle_center,
    const double max_range, const std::vector<point> &unfiltered_points) {
  // Filter point by range.
  auto points_in_range = task2::filterPointsByRange(
      circle_radius, circle_center, max_range, unfiltered_points);
  // Sort points by angle from 0 to 2pi.
  std::sort(points_in_range.begin(), points_in_range.end(),
            [&circle_center](const auto &point1, const auto &point2) -> bool {
              return task2::angleFromPointToCenter(circle_center, point1) <
                     task2::angleFromPointToCenter(circle_center, point2);
            });
  return points_in_range;
}
}  // namespace task2
