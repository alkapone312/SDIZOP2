#pragma once

#include <functional>
#include "exception/Exception.h"

namespace SDIZO {
    template <typename T>
    class Matrix {
        private:
            T **matrix;
            int rows;
            int cols;

        public:
            /**
             * @brief Construct a new Matrix object
             * 
             * @param r 
             * @param c 
             */
            Matrix(int r, int c): rows(r), cols(c) {
                matrix = new T*[rows];
                for(int i = 0; i < rows; i++) {
                    matrix[i] = new T[cols];
                }
            }
            
            /**
             * @brief Destroy the Matrix object
             * 
             */
            ~Matrix() {
                for(int i = 0; i < rows; i++) {
                    delete[] matrix[i];
                }
                delete[] matrix;
            }

            /**
             * @brief 
             * 
             * @param row 
             * @param col 
             * @param value 
             */
            void set(int row, int col, T value) {
                checkIndex(row, col);
                matrix[row][col] = value;
            }

            /**
             * @brief 
             * 
             * @param row 
             * @param col 
             * @return & T 
             */
            T& get(int row, int col) {
                checkIndex(row, col);
                return matrix[row][col];
            }

            /**
             * @brief 
             * 
             * @param func 
             */
            void forEach(std::function<void(T&)> func) {
                for (int i = 0; i < rows; ++i) {
                    for (int j = 0; j < cols; ++j) {
                        func(matrix[i][j]);
                    }
                } 
            }

            /**
             * @brief 
             * 
             * @param func 
             * @return Matrix<T> 
             */
            Matrix<T> map(std::function<T(T)> func) {
                Matrix<T> result(rows, cols);
                for (int i = 0; i < rows; ++i) {
                    for (int j = 0; j < cols; ++j) {
                        result(i, j) = func(matrix[i][j]);
                    }
                }

                return result;
            }

            /**
             * @brief 
             * 
             * @tparam Func 
             * @param rows 
             * @param cols 
             * @param f 
             * @return Matrix<T> 
             */
            static Matrix<T> create(int rows, int cols, T (*createFunc)(int, int)) {
                Matrix<T> matrix(rows, cols);

                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < cols; j++) {
                        matrix(i, j) = createFunc(i, j);
                    }
                }

                return matrix;
            }

            /**
             * @brief Get the Rows object
             * 
             * @return int 
             */
            int getRows() {
                return rows;
            }

            /**
             * @brief Get the Cols object
             * 
             * @return int 
             */
            int getCols() {
                return cols;
            }

            /**
             * @brief 
             * 
             * @param i 
             * @param j 
             * @return T& 
             */
            T& operator()(int i, int j) {
                checkIndex(i, j);
                return matrix[i][j];
            }

        private:
            bool checkIndex(int col, int row) {
                if(row >= getRows() || col >= getCols() || row < 0 || col < 0) {
                    throw new SDIZO::Exception("Index out of bounds");
                }

                return true;
            }
    };
};