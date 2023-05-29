#pragma once

#include <functional>
#include "exception/Exception.h"
#include "structures/DynamicArray.h"

namespace SDIZO {
    template <typename T>
    class Matrix {
        private:
            DynamicArray<DynamicArray<int>*>* matrix;
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
                matrix = new DynamicArray<DynamicArray<int>*>();
                for(int i = 0; i < rows; i++) {
                    DynamicArray<int>* row = new DynamicArray<int>;
                    for(int j = 0 ; j < cols; j++) {
                        row->pushBack(0);
                    }
                    matrix->pushBack(row);
                }
            }
            
            /**
             * @brief Destroy the Matrix object
             * 
             */
            ~Matrix() {
                delete matrix;
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
                matrix->get(row)->set(col, value);
            }

            /**
             * @brief 
             * 
             * @param row 
             * @param col 
             * @return & T 
             */
            T get(int row, int col) {
                checkIndex(row, col);
                return matrix->get(row)->get(col);
            }

            /**
             * @brief 
             * 
             * @param func 
             */
            void forEach(std::function<void(int col, int row, T)> func) {
                for (int i = 0; i < rows; ++i) {
                    for (int j = 0; j < cols; ++j) {
                        func(i, j, matrix->get(i)->get(j));
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
                        result->set(i, j, func(matrix->get(i)->get(j)));
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
                        matrix.set(i, j, createFunc(i, j));
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
                return matrix->getLength();
            }

            /**
             * @brief Get the Cols object
             * 
             * @return int 
             */
            int getCols() {
                return matrix->get(0)->getLength();
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