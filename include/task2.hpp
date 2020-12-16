#pragma once

#include <utility>
#include <vector>

namespace task2 {
using point = std::pair<double, double>;
using range = std::pair<double, double>;
[[nodiscard]] std::vector<point> makeRandomPointsInRange(
    const std::size_t points_number, const range &range_x,
    const range &range_y);
[[nodiscard]] std::vector<point> filterPointsByRange(
    const double circle_radius, const point &circle_center,
    const double max_range, const std::vector<point> &unfiltered_points);
[[nodiscard]] std::vector<point> filterPointsByRangeWithAngle(
    const double circle_radius, const point &circle_center,
    const double max_range, const std::vector<point> &unfiltered_points);
[[nodiscard]] double angleFromPointToCenter(const point &circle_center,
                                            const point &input_point);
}  // namespace task2
