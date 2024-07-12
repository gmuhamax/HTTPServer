#include "http.hpp"

namespace http {
    void Headers::add(string key, string value) {
        this->headers[key] = value;
    }

    string Headers::get(string key) {
        return this->get(key, "");
    }

    string Headers::get(string key, string default_) {
        return this->headers.count(key) == 0 ? default_ : this->headers[key];
    }

    Headers::Headers(const char* buf, size_t* offset) {
        string key, value;
        while (buf[(*offset)] != '\r' && buf[((*offset)) + 1] != '\n' && buf[(*offset) + 2] != '\r' && buf[(*offset) + 3] != '\n') {
            while(buf[(*offset)] != ':') {
                key += buf[(*offset)];
                (*offset)++;
            }
            (*offset) += 2;
            while (buf[(*offset)] != '\r' && buf[(*offset) + 1] != '\n') {
                value += buf[(*offset)];
                (*offset)++;
            }
            this->add(key, value);
            key.clear();
            value.clear();
            (*offset) += 2;
        }
    }

    string Headers::str() {
        string res;

        for (pair<string, string> n : this->headers) {
            res += n.first + ": " + n.second + "\r\n";
        }

        return res;
    }
}