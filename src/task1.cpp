#include "task1.hpp"

#include <fstream>
#include <numeric>

namespace task1 {
std::tuple<std::vector<point>, std::vector<point>> parseFile(
    std::string_view filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    throw std::runtime_error("Could'n open input file.");
  }
  std::size_t n;  // Number of segments.
  std::size_t m;  // Number of test points.
  file >> n >> m;
  // Read the polygon points.
  const auto segments_points_number = 2 * n;
  std::vector<point> polygon_points, test_points;
  polygon_points.reserve(segments_points_number);
  test_points.reserve(m);
  const auto addPoints = [&file](const auto limit, auto &container) {
    for (auto i = 0u; i < limit; ++i) {
      point temp;
      file >> temp.first >> temp.second;
      container.push_back(std::move(temp));
    }
  };
  addPoints(segments_points_number, polygon_points);
  addPoints(m, test_points);
  file.close();
  return {polygon_points, test_points};
}

bool isPointInPolygon(const point &test_point,
                      const std::vector<point> &polygon_points) {
  // Crossing number (count) algorithm.
  auto parity = false;
  for (std::size_t i = 0u, j = polygon_points.size() - 1;
       i < polygon_points.size(); j = i++) {
    const auto between_y = (((polygon_points[i].second <= test_point.second) &&
                             (test_point.second < polygon_points[j].second)) ||
                            ((polygon_points[j].second <= test_point.second) &&
                             (test_point.second < polygon_points[i].second)));

    const auto not_horizontal_y = (polygon_points[j].second - polygon_points[i].second) != 0;

    const auto point_side_relatively_line =
        static_cast<double>(test_point.first) >
        (static_cast<double>(polygon_points[j].first - polygon_points[i].first) *
             static_cast<double>(test_point.second - polygon_points[i].second) /
             static_cast<double>(polygon_points[j].second - polygon_points[i].second) +
         static_cast<double>(polygon_points[i].first));

    if (between_y && not_horizontal_y && point_side_relatively_line) {
      parity = !parity;
    }
  }
  return parity;
}

std::size_t numberPointsInPolygon(const std::vector<point> &polygon_points,
                                  const std::vector<point> &test_points) {
  return std::accumulate(test_points.cbegin(), test_points.cend(), 0u,
                         [&polygon_points](const auto prev, const auto &elem) {
                           return prev + isPointInPolygon(elem, polygon_points);
                         });
}
}  // namespace task1
