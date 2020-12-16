#pragma once

#include <string>
#include <vector>

namespace task1 {
using point = std::pair<int, int>;
[[nodiscard]] std::tuple<std::vector<point>, std::vector<point>> parseFile(
    std::string_view filename);
[[nodiscard]] bool isPointInPolygon(const point &test_point,
                                    const std::vector<point> &polygon_points);
std::size_t numberPointsInPolygon(const std::vector<point> &polygon_points,
                                  const std::vector<point> &test_points);
}  // namespace task1
