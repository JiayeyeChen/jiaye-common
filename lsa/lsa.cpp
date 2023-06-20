#include "lsa.hpp"

void LSACalculatorHandle::SelectFile(std::string file_name)
{
    filename = file_name;
}

int LSACalculatorHandle::CalculateLSA(void)
{
    fileStream.open(filename.data());
    int raw_ptr = 0;
    matrix_size_col = 0;
    matrix_size_raw = 0;
    A.conservativeResize(1, 2);
    x.conservativeResize(1, 1);
    b.conservativeResize(1, 1);

    while (fileStream.good())
    {
        std::string line;
        getline(fileStream, line);
        if (!line.length())//Finished loading matrices data
        {
            std::cout<<"Matrices loading finished. Totally "<< matrix_size_raw << " raws and " << matrix_size_col << " columns" << std::endl;
            printf("A is : \n");
            for (int raw = 0; raw <= matrix_size_raw - 1; raw++)
            {
                for (int col = 0; col <= matrix_size_col - 2; col++)
                {
                    std::cout << A(raw, col) << "  ";
                }
                printf("\n");
            }
            printf("b is: \n");
            for (int raw = 0; raw <= matrix_size_raw - 1; raw++)
            {
                std::cout << b(raw) << std::endl;
            }
            fileStream.close();
            const int size = matrix_size_col - 1;
            Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic> inverse;
            inverse.conservativeResize(size, size);
            inverse = A.transpose()*A;
            inverse = inverse.inverse();
            x.conservativeResize(matrix_size_raw);
            x = inverse * A.transpose() * b;
            
            printf("x hat is: \n");
            for (int raw = 0; raw <= matrix_size_col - 2; raw++)
            {
                std::cout << x(raw) << std::endl;
            }
            break;
        }
        else
        {
            matrix_size_raw++;
            int count = 0;
            for (int i = 0; (i = line.find(',', i)) != std::string::npos; i++) {
                count++;
            }
            if (matrix_size_col == 0)
                matrix_size_col = count;
            else if (matrix_size_col != count)
            {
                printf("Error: Column size inconsistent!\n");
                return 1;
            }
            
            A.conservativeResize(matrix_size_raw, matrix_size_col - 1);
            b.conservativeResize(matrix_size_raw);

            printf("The %d raw: ", matrix_size_raw);
            std::cout << line << std::endl;
            std::string tempStr;
            std::stringstream curDataSlotStringStream(line);
            getline(curDataSlotStringStream, tempStr, ',');
            b(raw_ptr) = atof(tempStr.c_str());//Update the b vector
            
            for (int A_col_ptr = 0; A_col_ptr <= matrix_size_col - 2; A_col_ptr++)//Update the A matrix
            {
                getline(curDataSlotStringStream, tempStr, ',');
                A(raw_ptr, A_col_ptr) = atof(tempStr.c_str());
            }
            raw_ptr++;
        }
    }
    return 0;
}

LSACalculatorHandle::LSACalculatorHandle(void):matrix_size_raw(0), matrix_size_col(0)
{
    A.conservativeResize(1, 2);
    x.conservativeResize(1, 1);
    b.conservativeResize(1, 1);
}

LSACalculatorHandle::~LSACalculatorHandle(void)
{

}
