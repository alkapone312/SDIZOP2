#pragma once
#include "structures/Iterable.h"

namespace SDIZO {
    template <typename T>
    class DynamicArray : public SDIZO::Iterable {
        private:
            T* dynamicArray = new T[0];
            int length = 0;
            int actualIndex = 0;
        public:
            DynamicArray() {}

            ~DynamicArray() {
                delete[] this->dynamicArray;
            }

            /**
             * @brief Push to the back of array
             * 
             * @param value 
             */
            void pushBack(T value) {
                this->add(this->length, value);
            }

            /**
             * @brief Push to the front of array
             * 
             * @param value 
             */
            void pushFront(T value) {
                this->add(0, value);
            }

            /**
             * @brief Add value at specific index
             * 
             * @param index 
             */
            void add(int index, T value) {
                if(index != this->length) {
                    this->checkIndex(index);
                }
                //new array
                T* buff = new T[this->length + 1];
                buff[index] = value;
                //copy array
                for(int i = 0 ; i < index; i++) {
                    buff[i] = this->dynamicArray[i];
                }
                for(int i = index; i < this->length; i++) {
                    buff[i+1] = this->dynamicArray[i];
                }
                //replace buffer with actual array
                delete this->dynamicArray;
                this->dynamicArray = buff;
                this->length++;
            }

            /**
             * @brief Remove value from last position
             * 
             * @return T 
             */
            T popBack() {
                return this->remove(this->length - 1);
            }

            /**
             * @brief Remove value from the first position
             * 
             * @return T 
             */
            T popFront() {
                return this->remove(0);
            }

            /**
             * @brief Remove value at specific index
             * 
             * @param index 
             * @return T 
             */
            T remove(int index) {
                this->checkIndex(index);
                //new smaller aray
                this->length--;
                T value = this->dynamicArray[index];
                T* buff = new T[this->length];
                //copy array
                for(int i = 0; i < index; i++) {
                    buff[i] = this->dynamicArray[i];
                }
                for(int i = index; i < this->length; i++) {
                    buff[i] = this->dynamicArray[i+1];
                }
                //replace actual with buffer
                delete[] this->dynamicArray;
                this->dynamicArray = buff;
                if(!this->length) {
                    this->dynamicArray = nullptr;
                }

                return value;
            }


            /**
             * @brief Find value index at specific index
             * 
             * @param value
             * @return int | -1 if no value found
             */
            int find(T value) {
                for(int i = 0 ; i < this->length; i++) {
                    if(this->dynamicArray[i] == value) {
                        return i;
                    }
                }

                return -1;
            }

            /**
             * @brief Get value from specific index
             * 
             * @param index
             * @return T
             */
            T get(int index) {
                this->checkIndex(index);
                
                return this->dynamicArray[index];
            }

            /**
             * @brief Set value at specified index.
             * 
             * @param index 
             * @param value 
             */
            void set(int index, T value) {
                this->checkIndex(index);
                this->dynamicArray[index] = value;
            }

            /**
             * @brief Get the Length of array
             * 
             * @return int 
             */
            int getLength() {
                return this->length;
            }

            /**
             * @brief Checks whether actual item is not null
             * 
             * @return true 
             * @return false 
             */
            bool isItem() {
                return this->actualIndex >= 0 && this->actualIndex < this->length;
            }

            /**
             * @brief Changes actual pointer to next member.
             * 
             */
            void next() {
                this->actualIndex++;
            }

            /**
             * @brief Changes actual pointer to previous member.
             * 
             */
            void prev() {
                this->actualIndex--;
            }

            /**
             * @brief Sets iterator to start of an data structure
             */
            void first() {
                this->actualIndex = 0;
            }

            /**
             * @brief Sets iterator to end of an data structure
             * 
             */
            void last() {
                this->actualIndex = this->length - 1;
            }

            T getActual() {
                return this->dynamicArray[this->actualIndex];
            }

        private:

            /**
             * @brief Checks if index is not out of bounds
             * 
             * @param index 
             */
            void checkIndex(int index) {
                if(index != 0 && index >= this->length || index < 0) {
                    throw new Exception((char*)"Index out of bounds!"); 
                }
            }

    };
}