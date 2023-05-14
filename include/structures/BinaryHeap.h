#pragma once
#include "structures/Iterable.h"
#include "structures/DynamicArray.h"

using SDIZO::DynamicArray;

namespace SDIZO {
    template <typename T>
    class BinaryHeap : public Iterable {
        private:
            DynamicArray<T>* heap = new DynamicArray<T>;
        public:
            BinaryHeap() {}
            
            ~BinaryHeap() {}

            /**
             * @brief Push value at the end of heap
             * 
             * @param value 
             */
            void push(T value) {
                this->heap->pushBack(value);
                this->bubbleUp(this->heap->getLength() - 1);
            }

            /**
             * @brief Pop value out of heap top
             * 
             * @return T
             */
            T pop() {
                if(this->getLength() == 0) {
                    throw new Exception((char*)"Tried to pop() out of empty heap!");
                }
                this->heap->first();
                T value = this->heap->getActual();
                if(this->getLength() != 1) {
                    this->heap->set(0, this->heap->popBack());
                } else {
                    return this->heap->popBack();
                }
                this->bubbleDown(0);

                return value;
            }

            /**
             * @brief Find index of an element
             * 
             * @param value 
             * @return T 
             */
            int find(T value) {
                return this->heap->find(value);
            }

            /**
             * @brief Get element under index
             * 
             * @param index 
             * @return T 
             */
            T get(int index) {
                return this->heap->get(index);
            }

            /**
             * @brief Get the length of heap
             * 
             * @return int 
             */
            int getLength() {
                return this->heap->getLength();
            }

            /**
             * @brief Checks whether actual item is not null
             * 
             * @return true 
             * @return false 
             */
            bool isItem()  {
                return this->heap->isItem();
            }

            /**
             * @brief Changes actual pointer to next member.
             * 
             */
            void next() {
                this->heap->next();
            }

            /**
             * @brief Changes actual pointer to previous member.
             * 
             */
            void prev() {
                this->heap->prev();
            }

            /**
             * @brief Gets the actual list item
             * 
             * @return T
             */
            T getActual() {
                return this->heap->getActual();
            }

            /**
             * @brief Sets iterator to start of an data structure
             */
            void first() {
                this->heap->first();
            }

            /**
             * @brief Sets iterator to end of an data structure
             * 
             */
            void last() {
                this->heap->last();
            }

        private:
            /**
             * @brief 
             * 
             */
            void bubbleDown(int actualIndex) {
                int leftChildIndex = this->leftChildIndex(actualIndex);
                while(leftChildIndex != -1) {
                    int biggerChildIndex = leftChildIndex;
                    int rightChildIndex = this->rightChildIndex(actualIndex);
                    if(
                        rightChildIndex != -1 && 
                        this->heap->get(leftChildIndex) > this->heap->get(rightChildIndex) 
                    ) {
                        biggerChildIndex = rightChildIndex;
                    }
                    T smallerChildValue = this->heap->get(biggerChildIndex);
                    T actualValue = this->heap->get(actualIndex);
                    if(smallerChildValue > actualValue) {
                        break;
                    }
                    this->heap->set(biggerChildIndex, actualValue);
                    this->heap->set(actualIndex, smallerChildValue);
                    actualIndex = biggerChildIndex;
                    leftChildIndex = this->leftChildIndex(biggerChildIndex);
                }
            }

            /**
             * @brief 
             * 
             */
            void bubbleUp(int index) {
                int parent = this->parentIndex(index);
                while(parent != -1 && this->heap->get(parent) > this->heap->get(index)) {
                    T buff = this->heap->get(parent);
                    this->heap->set(parent, this->heap->get(index));
                    this->heap->set(index, buff);
                    index = parent;
                    parent = this->parentIndex(parent);
                }
            }

            /**
             * @brief Get the index of left child -1 if don't exist
             * 
             * @param nodeIndex 
             * @return int 
             */
            int leftChildIndex(int nodeIndex) {
                int leftChildIndex = nodeIndex * 2 + 1;
                if(leftChildIndex > this->getLength() - 1) {
                    return -1;
                }

                return leftChildIndex;
            }

            /**
             * @brief Get the index of right child -1 if don't exist
             * 
             * @param nodeIndex 
             * @return int 
             */
            int rightChildIndex(int nodeIndex) {
                int rightChildIndex = nodeIndex * 2 + 2;
                if(rightChildIndex > this->getLength() - 1) {
                    return -1;
                }

                return rightChildIndex;
            }

            /**
             * @brief Get the index of node parent -1 if don't exist
             * 
             * @return int 
             */
            int parentIndex(int nodeIndex) {
                if(nodeIndex == 0) {
                    return -1;
                }

                return (nodeIndex - 1) / 2;
            }
    };
}