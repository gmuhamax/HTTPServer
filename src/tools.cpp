#include "http.hpp"

#include <vector>

vector<string> met {"GET", "POST", "PUT", "PATCH", "DELETE"};
vector<string> stat {
    "200 OK",
    "201 Created",
    "404 Not Found"
};


namespace http {
    Method toMethod(string method) {
        if (method == "GET") return Method::GET;
        else if (method == "POST") return Method::POST;
        else if (method == "PUT") return Method::PUT;
        else if (method == "PATCH") return Method::PATCH;
        else if (method == "DELETE") return Method::DELETE;
        return Method::GET;
    }

    string fromMethod(Method method) {
        return met[method];
    }

    string fromStatus(Status status) {
        return stat[status];
    }

    string byTokent(const char token, const char* buf, size_t &pos, size_t offset) {
        string data;

        pos += offset;
        while (buf[pos] != token)
        {
            data += buf[pos];
            pos++;
        }

        return data;
    }

    string byTokent(bool (*alpha)(char symbol), const char* buf, size_t &pos, size_t offset) {
        string data;

        pos += offset;
        while (alpha(buf[pos]))
        {
            data += buf[pos];
            pos++;
        }

        return data;
    }
}