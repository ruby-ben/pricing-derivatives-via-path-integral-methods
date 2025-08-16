cmake_minimum_required(VERSION 3.10)
project(OptionPricer) 
set(CMAKE_CXX_STANDARD 17) 

# Common source files 
set(COMMON_SOURCES 
src/path_integral_solver.cpp 
src/black_scholes.cpp 
)

# Main option pricer executable 
add_executable(option_pricer 
src/main.cpp 
${COMMON_SOURCES} 
) 

# Experiment runner executable 
add_executable(run_experiments 
src/run_experiments.cpp 
src/experiment_runner.cpp
${COMMON_SOURCES} 
) 

# Include directories 
target_include_directories(option_pricer PRIVATE include) 
target_include_directories(run_experiments PRIVATE include)


