add_executable(align_test align_test.cpp)

target_link_libraries(align_test PUBLIC
	gtest_main
	core
)

file(COPY 
	test_empty.txt 
	test_task1_example.txt
	test_task1_duck.txt
	test_task2_19points.txt
	test_task2_19points_solution.txt
	test_task3_example1.txt
	test_task3_example2.txt
	test_task3_3fragments.txt
	DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
)

add_test(NAME align_test COMMAND align_test)
