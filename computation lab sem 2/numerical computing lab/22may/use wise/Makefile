# Compiler
CXX = g++
# Compiler flags
CXXFLAGS = -std=c++11 -Wall
# Target executable
TARGET = numericalmethods
# Source files
SRCS = main.cpp \
	LinearSystemSolvers/LinearSystemSolvers.cpp \
	MatrixDecompositions/MatrixDecompositions.cpp \
	IterativeMethodsforSolvingLinearSystems/IterativeSolvers.cpp \
	Root-FindingMethods/RootFindingMethods.cpp \
	Fixed-PointIteration/FixedPointIteration.cpp
# Object files
OBJS = $(SRCS:.cpp=.o)
# Header files
HDRS = LinearSystemSolvers/LinearSystemSolvers.hpp \
       MatrixDecompositions/MatrixDecompositions.hpp \
       IterativeMethodsforSolvingLinearSystems/IterativeSolvers.hpp \
       Root-FindingMethods/RootFindingMethods.hpp \
       Fixed-PointIteration/FixedPointIteration.hpp
# Default target
all: $(TARGET)
# Link the object files to create the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files into object files
%.o: %.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(TARGET) $(OBJS)

# Phony targets
.PHONY: all Clean