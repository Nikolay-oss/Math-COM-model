cmake_minimum_required(VERSION 3.16)
project(coursework)

set(CMAKE_CXX_STANDARD 17)

find_package(./sciplot)

include_directories(./includes ./matrix_lib ./srcs ./sciplot/sciplot ./sciplot)

add_executable(coursework
        includes/mathFunc.hpp
        includes/MathModel.hpp
        includes/RungeKutta.hpp
        includes/matrix.hpp
		includes/linearInterpolation.hpp
		includes/launchCalculations.hpp
		includes/parser.hpp
		includes/drawGraph.hpp

        sciplot/sciplot/sciplot.hpp

		matrix_lib/matrix.cpp

        srcs/integrator/MathModel.cpp
        srcs/integrator/RungeKutta.cpp
		srcs/linearInterpolation.cpp
        srcs/mathFunc.cpp
        srcs/main.cpp
		srcs/launchCalculations.cpp
		srcs/parser/parser.cpp
		srcs/parser/readInitValues.cpp
		srcs/drawGraph.cpp
        )
