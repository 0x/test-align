#include <gtest/gtest.h>

#include <fstream>
#include <random>

#include <task1.hpp>
#include <task2.hpp>
#include <task3.hpp>

TEST(TestTask1, NumberPointsInPolygonFromTaskFile) {
  constexpr auto filename = "test_task1_example.txt";
  const auto [polygon_points, test_points] = task1::parseFile(filename);

  EXPECT_EQ(task1::numberPointsInPolygon(polygon_points, test_points), 1)
      << "In the example from the task file, the polygon contains 1 point";
}

TEST(TestTask1, NumberPointsInPolygonUpperBoundaryConditions) {
  constexpr auto n = 1'000;
  constexpr auto m = 10'000;
  const auto fragments_number = 2 * (n - 1);
  std::random_device rd;
  std::default_random_engine random_engine(rd());
  std::uniform_int_distribution<int> uniform_dist(-100'000'000, 100'000'000);
  std::vector<task1::point> polygon_points, test_points;
  polygon_points.reserve(fragments_number);
  test_points.reserve(m - 1);
  for (auto i = 0u; i < fragments_number; i++) {
    polygon_points.emplace_back(uniform_dist(random_engine),
                                uniform_dist(random_engine));
  }
  for (auto i = 0u; i < m - 1; i++) {
    test_points.emplace_back(uniform_dist(random_engine),
                             uniform_dist(random_engine));
  }
  EXPECT_GE(task1::numberPointsInPolygon(polygon_points, test_points), 0)
      << "Number points in the polygon with random upper boundary conditions "
         "data >= 0";
}

TEST(TestTask1, NumberPointsInPolygonLowerBoundaryConditions) {
  constexpr auto n = 2;
  constexpr auto m = 1;
  std::random_device rd;
  std::default_random_engine random_engine(rd());
  std::uniform_int_distribution<int> uniform_dist(-100'000'000, 100'000'000);
  std::vector<task1::point> polygon_points, test_points;
  for (auto i = 0u; i < n * 2; i++) {
    polygon_points.emplace_back(uniform_dist(random_engine),
                                uniform_dist(random_engine));
  }
  test_points.emplace_back(uniform_dist(random_engine),
                           uniform_dist(random_engine));

  EXPECT_GE(task1::numberPointsInPolygon(polygon_points, test_points), 0)
      << "Number points in the polygon with random lower boundary conditions "
         "data >= 0";
}

TEST(TestTask1, NumberPointsInPolygonEmptyData) {
  std::vector<task1::point> polygon_points, test_points;

  EXPECT_GE(task1::numberPointsInPolygon(polygon_points, test_points), 0)
      << "Number points in the polygon with empty data is equal to 0";
}

TEST(TestTask1, NumberPointsInPolygonDuckContour) {
  constexpr auto filename = "test_task1_duck.txt";
  const auto [polygon_points, test_points] = task1::parseFile(filename);

  EXPECT_EQ(task1::numberPointsInPolygon(polygon_points, test_points), 5)
      << "Duck-shaped polygon contains 5 point inside";
}

TEST(TestTask2, ListOfPointsByRangeWithAngleTestRandomData) {
  constexpr auto N = 100u;
  constexpr std::pair<double, double> circle_center(0, 0);
  constexpr auto circle_radius = 80.0;
  constexpr std::pair<double, double> range_x(-100, 100);
  constexpr std::pair<double, double> range_y(-100, 100);
  const auto test_points = task2::makeRandomPointsInRange(N, range_x, range_y);
  constexpr auto max_range = 10.0;
  const auto test_points_in_range = task2::filterPointsByRangeWithAngle(
      circle_radius, circle_center, max_range, test_points);

  EXPECT_GE(test_points_in_range.size(), 0)
      << "List of random points filter by range and sort with angle >= 0";
}

TEST(TestTask2, ListOfPointsByRangeWithAngleTestEmptyData) {
  std::vector<task2::point> test_points;
  constexpr std::pair<double, double> circle_center(0, 0);
  constexpr auto circle_radius = 80.0;
  constexpr auto max_range = 10.0;
  const auto test_points_in_range = task2::filterPointsByRangeWithAngle(
      circle_radius, circle_center, max_range, test_points);

  EXPECT_EQ(test_points_in_range.size(), 0) << "Test with empty data, 0 points";
}

TEST(TestTask2, ListOfPointsByRangeWithAngleOutOfRangeData) {
  constexpr auto N = 100u;
  constexpr std::pair<double, double> circle_center(0, 0);
  constexpr auto circle_radius = 80.0;
  constexpr std::pair<double, double> range_x(-30, 30);
  constexpr std::pair<double, double> range_y(-30, 30);
  const auto test_points = task2::makeRandomPointsInRange(N, range_x, range_y);
  constexpr auto max_range = 10.0;
  auto test_points_in_range = task2::filterPointsByRangeWithAngle(
      circle_radius, circle_center, max_range, test_points);

  EXPECT_EQ(test_points_in_range.size(), 0)
      << "All points out of range, 0 points";
}

TEST(TestTask2, ListOfPointsByRangeWithAngleTestWith19Points) {
  std::ifstream file("test_task2_19points.txt");
  ASSERT_TRUE(file.is_open());
  std::size_t N;
  file >> N;
  std::vector<task2::point> test_points;
  test_points.reserve(N);
  for (auto i = 0u; i < N; i++) {
    double x, y;
    file >> x >> y;
    test_points.emplace_back(x, y);
  }
  std::ifstream file_solution("test_task2_19points_solution.txt");
  ASSERT_TRUE(file_solution.is_open());
  file_solution >> N;
  std::vector<task2::point> test_points_solution;
  test_points.reserve(N);
  for (auto i = 0u; i < N; i++) {
    double x, y;
    file_solution >> x >> y;
    test_points_solution.emplace_back(x, y);
  }
  constexpr task2::point circle_center(0, 0);
  constexpr auto circle_radius = 80.0;
  constexpr auto max_range = 10.0;
  const auto test_points_in_range = task2::filterPointsByRangeWithAngle(
      circle_radius, circle_center, max_range, test_points);

  ASSERT_EQ(test_points_in_range.size(), test_points_solution.size())
      << "Unequal size lists of filterPointsByRangeWithAngle and solution";
  for (auto i = 0u; i < test_points_in_range.size(); i++) {
    EXPECT_EQ(test_points_in_range[i], test_points_solution[i])
        << "Lists of filterPointsByRangeWithAngle and solution differ at index "
        << i;
  }
}

TEST(TestTask3, MinNumberRingsTestExample1FromTask) {
  constexpr auto filename = "test_task3_example1.txt";
  auto chain_fragments = task3::parseFile(filename);

  EXPECT_EQ(task3::minNumberRings(chain_fragments), 3)
      << "Fragments: 10, 32, 45, 4. Number of rings to unbend 3";
}

TEST(TestTask3, MinNumberRingsTestExample2FromTask) {
  constexpr auto filename = "test_task3_example2.txt";
  auto chain_fragments = task3::parseFile(filename);

  EXPECT_EQ(task3::minNumberRings(chain_fragments), 2)
      << "Fragments: 8, 2, 14, 5. Number of rings to unbend 2";
}

TEST(TestTask3, MinNumberRingsTestWith5by3Fragments) {
  constexpr auto filename = "test_task3_3fragments.txt";
  auto chain_fragments = task3::parseFile(filename);

  EXPECT_EQ(task3::minNumberRings(chain_fragments), 3)
      << "Fragments: 3, 3, 3, 3, 3. Number of rings to unbend 3";
}

TEST(TestTask3, MinNumberRingsTestWith0Fragments) {
  std::vector<int> chain_fragments{0};

  EXPECT_EQ(task3::minNumberRings(chain_fragments), 0)
      << "Test with 0 fragments. Number of rings to unbend 0";
}

TEST(TestTask3, MinNumberRingsTestWith5by1Fragments) {
  std::vector<int> chain_fragments{1, 1, 1, 1, 1};

  EXPECT_EQ(task3::minNumberRings(chain_fragments), 2)
      << "Fragments: 1, 1, 1, 1, 1. Number of rings to unbend 2";
}

TEST(TestTask3, MinNumberRingsTestWith1by1Fragments) {
  std::vector<int> chain_fragments{1};

  EXPECT_EQ(task3::minNumberRings(chain_fragments), 0)
      << "Test with 1 fragments with 1 rings. Number of rings to unbend 0";
}

TEST(TestTask3, MinNumberRingsTestWith1by100Fragments) {
  std::vector<int> chain_fragments{100};

  EXPECT_EQ(task3::minNumberRings(chain_fragments), 0)
      << "Test with 1 fragments with 100 rings. Number of rings to unbend 0";
}

TEST(TestTask3, MinNumberRingsTestWith3Fragments) {
  std::vector<int> chain_fragments{2, 2, 1};

  EXPECT_EQ(task3::minNumberRings(chain_fragments), 1)
      << "Fragments: 2, 2, 1. Number of rings to unbend 1";
}
