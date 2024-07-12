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
}