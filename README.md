# MATH-4320 Mathematical Modeling
This repository contains source code for the MATH 4320 Mathematical Modeling homework taken at Tarleton State University during the Fall semester of 2024, taught by Dr. Bryant Wyatt. This course focused on developing techniques to model physical phenomenon in a coding environment. An overview of topics covered can be found below.

### Topics Covered
 - Building "Digital Twins" of Real World Phenomenon
 - Particle Modeling
 - Numerical Methods for 2nd order ODEs (Leap Frog Formulas)
 - Unit Conversion and Simulation Units (Stable Numerical Calculations)
 - Asteroid Formation and Collision
 - Force Function Derivation
 - Self Assembly of Particles
 - Latice Tower Construction (Adjacency Matrices for Bodies)

### Compiling and Executing Code
This repository contains mostly CUDA files, with some suplimentary bash scripts, text files, PDF files, and C files. Paper homework assignments have been recreated as PDF files. To execute the CUDA files, please use the nvcc compiler provided by NVIDIA in the following way:
```bash
# Compile the CUDA source file
nvcc source_file.cu -o executable_name -lglut -lm -lGLU -lGL

# Execute the compiled program
./executable_name
```

When a bash script is provided in a folder, this excecution in implimented in that file. First, ensure that the script has executable permissions, and then execute the script to compile and run that CUDA or C file.
```bash
# Give bash script executable permissions
chmod 755 compileRun.sh

# Execute the bash script
./compileRun.sh
```
You need to give executable permission only once. Afterwards you need only to execute the file.
