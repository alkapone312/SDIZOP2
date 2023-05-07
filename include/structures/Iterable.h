#pragma once

namespace SDIZO {
    class Iterable {
        public:
            /**
             * @brief Checks whether actual item is not null
             * 
             * @return true 
             * @return false 
             */
            virtual bool isItem() = 0;

            /**
             * @brief Changes actual pointer to next member.
             * 
             */
            virtual void next() = 0;

            /**
             * @brief Changes actual pointer to previous member.
             * 
             */
            virtual void prev() = 0;

            /**
             * @brief Gets the actual list item
             * 
             * @return int
             */
            virtual int getActual() = 0;

            /**
             * @brief Sets iterator to start of an data structure
             */
            virtual void first() = 0;

            /**
             * @brief Sets iterator to end of an data structure
             * 
             */
            virtual void last() = 0;
    };
}