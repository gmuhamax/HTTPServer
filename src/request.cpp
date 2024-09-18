#include "http.hpp"

namespace http {
    Request::Request(const char* buf): buf(buf) {
        size_t pos = 0;
        this->method = toMethod(byTokent(' ', this->buf, pos, 0));

        this->addr = byTokent([](char symbol) { return symbol != ' ' && symbol != '?'; }, this->buf, pos, 1);
        this->addr_q = byTokent(' ', this->buf, pos, 0);
        parseQuery();
        pos += 11;

        this->headers = Headers(this->buf, pos);
        this->body = byTokent('\0', this->buf, pos, 2);
    }

    void Request::parseQuery() {
        string key, value;
        size_t pos = 0;
        const char* adr = this->addr_q.c_str();

        while (adr[pos] != '\0') {
            key = byTokent([](char symbol) { return symbol != '=' && symbol != '\0'; }, adr, pos, 1);
            value = byTokent([](char symbol) { return symbol != '&' && symbol != '\0'; }, adr, pos, 1);
            this->query_params[key] = value;
            key.clear();
            value.clear();
        }
    }
}