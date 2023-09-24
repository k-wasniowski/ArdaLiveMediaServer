#pragma once

#include <memory>
#include <string>

namespace Media
{
    namespace Sdp
    {
        class Time;
        using TimeSharedPtr_t = std::shared_ptr<Time>;

        class Time
        {
        public:
            Time() = default;

            Time(int start, int stop)
            {
                this->start = start;
                this->stop = stop;
            }

            virtual TimeSharedPtr_t clone()
            {
                return std::make_shared<Time>(start, stop);
            }

            virtual std::string toString()
            {
                return "t=" + std::to_string(start) + " " + std::to_string(stop) + "\r\n";
            }

            int getStart()
            {
                return start;
            }

            void setStart(int start)
            {
                this->start = start;
            }

            int getStop()
            {
                return stop;
            }

            void setStop(int stop)
            {
                this->stop = stop;
            }

        private:
            int start;
            int stop;
        };
    }
}
