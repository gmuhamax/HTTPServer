#include "http.hpp"

namespace http {
    Request::Request(const char* buf) {
        string data;
        size_t ptr = 0;

        while (buf[ptr] != ' ')
        {
            data += buf[ptr];
            ptr++;
        }

        ptr++;
        this->method = toMethod(data);
        data.clear();

        while (buf[ptr] != ' ')
        {
            data += buf[ptr];
            ptr++;
        }

        ptr++;
        this->addr = data;
        data.clear();

        ptr += 10;

        this->headers = Headers(buf, &ptr);

        ptr += 2;

        while (buf[ptr] != '\0') {
            data += buf[ptr];
            ptr++;
        }

        this->body = data;
        data.clear();
    }
}