# Black-Scholes Path Integral Method - Usage Instructions
## Setup
```bash
mkdir build && cd build
```

## Building the Project
From the build directory:
```bash
cmake ..
make
```
/
## Available Executables

### 1. Option Pricer (Single Run)
Run a single Black-Scholes simulation with specified parameters:
```bash
# Save paths to CSV (default)
./option_pricer

# Or explicitly specify whether to save (1) or not (0)
./option_pricer 1  # saves to ../data/paths.csv
./option_pricer 0  # doesn't save to CSV
```

## Analyzing Results
Use the Jupyter notebooks in the examples directory:
1. `blackscholes_path_integral_error.ipynb` - For single simulation analysis

Note: The CSV files will be saved in the 'data' directory at the project root level, 
not in the build directory.


next steps
-------------
- Apply the engine to different SDE
- Experiment the relationship between standard error (and this error) of the average path and the analytical solution (if it exists) vs the number of simulations averaged.
    - The best approach would be subtracting cummulative sums and ensembling to understand the error
