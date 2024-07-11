#include "../http.hpp"

namespace http {
    size_t Response::length() {
        return sizeof(this->body);
    }

    size_t Response::size() {
        return this->result.size();
    }

    const char* Response::c_str() {
        return this->result.c_str();
    }

    Response::Response(string body, Status status) {
        this->status = status;
        this->body = body;

        this->result = "HTTP/1.1 ";
        this->result += fromStatus(this->status);
        this->result += "\r\n";
        
        this->headers.add("Content-Type", "text/html");
        this->headers.add("Content-Length", to_string(this->length()));

        this->result += this->headers.str();
        this->result += "\r\n" + this->body;
    }
}