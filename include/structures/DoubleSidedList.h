#pragma once
#include "structures/Iterable.h"

namespace SDIZO {
    template <typename T>
    struct DoubleSidedListNode {
        DoubleSidedListNode* prev = nullptr;
        DoubleSidedListNode* next = nullptr;
        T value;
    };

    template <typename T>
    class DoubleSidedList : public SDIZO::Iterable {
        private:
            DoubleSidedListNode* head = nullptr;
            DoubleSidedListNode* tail = nullptr;
            DoubleSidedListNode* actual = head;
            int length = 0;
        public:
            DoubleSidedList() {}

            ~DoubleSidedList() {
                while(this->head) {
                    DoubleSidedListNode* buff = this->head;
                    this->head = this->head->next;
                    delete buff;
                }
            }

            /**
             * @brief Pushes value at the end of the list
             * 
             * @param value 
             */
            void pushBack(T value) {
                DoubleSidedListNode* newNode = new DoubleSidedListNode;
                newNode->value = value;
                if(this->setIfEmpty(newNode)) {
                    return;
                }
                this->tail->next = newNode;
                this->tail->next->prev = this->tail;
                this->tail = newNode;
                this->length++;
            }

            /**
             * @brief Pushes value at the front of the list.
             * 
             * @param value 
             */
            void pushFront(T value)  {
                DoubleSidedListNode* newNode = new DoubleSidedListNode;
                newNode->value = value;
                if(this->setIfEmpty(newNode)) {
                    return;
                }
                this->head->prev = newNode;
                this->head->prev->next = this->head;
                this->head = newNode;
                this->length++;
            }

            /**
             * @brief Pops value out of back of the list.
             * 
             * @throw SDIZO::Exception
             * @return T 
             */
            T popBack() {
                if(!this->length) {
                    throw new Exception((char*)"Tried to popBack() out of empty array!");
                }

                DoubleSidedListNode* oldTail = this->tail;
                this->tail = this->tail->prev;
                this->deleteConnection(this->tail, oldTail);
                this->length--;

                if(!this->length) {
                    this->head = nullptr;
                    this->tail = nullptr;
                }

                return this->getValueAndDelete(oldTail);
            }

            /**
             * @brief Pops value out of front of the list.
             * 
             * @throw SDIZO::Exception
             * @return T 
             */
            T popFront() {
                if(!this->length) {
                    throw new Exception((char*)"Tried to popFront() out of empty array!");
                }

                DoubleSidedListNode* oldHead = this->head;
                this->head = this->head->next;
                this->deleteConnection(oldHead, this->head);
                this->length--;

                if(!this->length) {
                    this->head = nullptr;
                    this->tail = nullptr;
                }
                
                return this->getValueAndDelete(oldHead);
            }

            /**
             * @brief Gets value of list item at specified index
             * 
             * @throw SDIZO::Exception
             * @param index 
             * @return T 
             */
            T get(int index) {
                this->checkIndex(index);
                DoubleSidedListNode* actual = this->head;
                for(int i = 0 ; i < index; i++) {
                    actual = actual->next;
                }

                return actual->value;
            }

            /**
             * @brief Removes item with specified index
             * 
             * @throw SDIZO::Exception
             * @param index 
             * @return T 
             */
            T remove(int index) {
                this->checkIndex(index);
                DoubleSidedListNode* actual = this->head;
                if(index == 0) {
                    this->head = this->head->next;
                }
                if(index == this->length - 1) {
                    this->tail = this->tail->prev;
                }
                for(int i = 0 ; i < index; i++) {
                    actual = actual->next;
                }
                if(actual->next) {
                    actual->next->prev = actual->prev ? actual->prev : nullptr;
                }
                if(actual->prev) {
                    actual->prev->next = actual->next ? actual->next : nullptr;
                }
                this->length--;

                return this->getValueAndDelete(actual);
            }
            
            /**
             * @brief Adds an item to the specific index
             * 
             * @param index 
             * @param value 
             */
            void add(int index, T value) {
                this->checkIndex(index);
                DoubleSidedListNode* newNode = new DoubleSidedListNode;
                newNode->value = value;
                if(this->setIfEmpty(newNode)) {
                    return;
                }
                DoubleSidedListNode* actual = this->head;
                for(int i = 0 ; i < index; i++) {
                    actual = actual->next;
                }
                if(actual->next) {
                    newNode->prev = actual;
                    newNode->next = actual->next;
                    actual->next->prev = newNode;
                    actual->next = newNode;

                    return;
                }

                newNode->prev = actual;
                actual->next = newNode;
            }


            /**
             * @brief Get the length list.
             * 
             * @return int 
             */
            int getLength() {
                return length;
            }

            /**
             * @brief Finds an index of a value.
             * 
             * @param value 
             * @return int 
             */
            int find(T value) {
                DoubleSidedListNode* actual = this->head;
                for(int i = 0 ; i < this->length; i++) {
                    if(actual->value == value) {
                        return i;
                    }
                    actual = actual->next;
                }
                
                return -1;
            }

            /**
             * @brief Checks whether actual item is not null
             * 
             * @return true 
             * @return false 
             */
            bool isItem() {
                return this->actual != nullptr;
            }

            /**
             * @brief Changes actual pointer to next member.
             * 
             */
            void next() {
                this->actual = this->actual->next;
            }

            /**
             * @brief Changes actual pointer to previous member.
             * 
             */
            void prev() {
                this->actual = this->actual->prev;
            }

            /**
             * @brief Gets the actual list item
             * 
             * @return T
             */
            T getActual() {
                return this->actual->value;
            }

            /**
             * @brief Sets iterator to start of an data structure
             */
            void first() {
                this->actual = this->head;
            }

            /**
             * @brief Sets iterator to end of an data structure
             * 
             */
            void last() {
                this->actual = this->tail;
            }
            
        private:
    
            /**
             * @brief Deletes connection between two nodes in given order.
             * 
             * @param item1 
             * @param item2 
             */
            void deleteConnection(DoubleSidedListNode* item1, DoubleSidedListNode* item2) {
                if(item1 != nullptr) {
                    item1->next = nullptr;
                }

                if(item2 != nullptr) {
                    item2->prev = nullptr;
                }
            }

            
            /**
             * @brief Set the head and tail if list is empty. 
             * 
             * @param node 
             * @return true 
             * @return false 
             */
            bool setIfEmpty(DoubleSidedListNode* node) {
                if(!this->length) {
                    this->head = node; 
                    this->tail = node;
                    this->length++;

                    return true;
                }

                return false;
            }

            /**
             * @brief Get the value and free object memory.
             * 
             * @param node 
             * @return int 
             */
            T getValueAndDelete(DoubleSidedListNode* node) {
                T value = node->value;
                delete node;

                return value;
            }

            /**
             * @brief Throws SDIZO::Exception if index is out of bounds.
             * 
             * @throw SDIZO::Exception
             * @param index 
             */
            void checkIndex(int index) {
                if(index != 0 && index >= this->length || index < 0) {
                    throw new Exception((char*)"Index out of bounds!"); 
                }
            }
    };
}