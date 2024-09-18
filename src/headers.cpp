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

    Headers::Headers(const char* buf, size_t &pos) {
        string key, value;
        while (buf[pos] != '\r' && buf[pos + 1] != '\n' && buf[pos + 2] != '\r' && buf[pos + 3] != '\n') {
            while(buf[pos] != ':') {
                key += buf[pos];
                pos++;
            }
            pos += 2;
            while (buf[pos] != '\r' && buf[pos + 1] != '\n') {
                value += buf[pos];
                pos++;
            }
            this->add(key, value);
            key.clear();
            value.clear();
            pos += 2;
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