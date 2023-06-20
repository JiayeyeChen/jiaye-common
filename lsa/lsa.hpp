#ifndef LSA_HPP
#define LSA_HPP

#include <fstream>
#include <Eigen/Dense>
#include <iostream>
#include <fstream>
#include <sstream>

class LSACalculatorHandle
{
    public:
    std::ifstream fileStream;
    std::string filename;
    Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic> A;
    Eigen::VectorXf                         x{0};
    Eigen::VectorXf                         b{0};
    int                                     matrix_size_raw, matrix_size_col;
    int CalculateLSA(void);
    void SelectFile(std::string file_name);
    LSACalculatorHandle(void);
    ~LSACalculatorHandle(void);
    private:
};
#endif
