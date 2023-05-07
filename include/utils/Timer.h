#pragma once

#include <chrono>

namespace SDIZO {
    class Timer {
        private:
            std::chrono::high_resolution_clock::time_point startTime;
            std::chrono::high_resolution_clock::time_point stopTime;
        public:
            Timer();
            ~Timer();

            /**
             * @brief Start timer measurement.
             * 
             */
            void start();

            /**
             * @brief Stop timer measurement.
             * 
             */
            void stop();

            /**
             * @brief Get the measured time in nanoseconds
             * 
             * @return int 
             */
            int getResult();
    };   
}
