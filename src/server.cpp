#include "http.hpp"

#include <stdio.h>
#include <unistd.h>

namespace http {
    void Server::run() {
        printf("[I]: Server start...\n");
        this->s_socket = socket(AF_INET, SOCK_STREAM, 0);
        if (this->s_socket == -1) {
            printf("[EX]: Socket can`t create\n");
            return;
        }

        this->s_addr.sin_family = AF_INET;
        this->s_addr.sin_port = htons(this->port);
        this->s_addr.sin_addr.s_addr = inet_addr(this->ip);

        int err = bind(this->s_socket, (const sockaddr*)&this->s_addr, sizeof(s_addr));
        if (err == -1) {
            printf("[EX]: Binded on ip and port: (%s:%d) failed\n", this->ip, this->port);
            return;
        }
        
        err = listen(this->s_socket, 10);
        if (err == -1) {
            printf("[EX]: Listing failed\n");
            return;
        }

        printf("[I]: Listing on ip and port: http://%s:%d\n", this->ip, this->port);

        this->is_run = true;

        char buf[2048] = { 0 };
        Request req;
        Response res;

        while (this->is_run) {
            this->n_socket = accept(this->s_socket, 0, 0);

            recv(this->n_socket, buf, 2048, 0);

            req = Request(buf);
            res = route.getResponse(req);
            printf("%s %s %s\n", fromMethod(req.getMethod()).c_str(), req.getAddr().c_str(), req.headers.get("sec-ch-ua-platform").c_str());
            
            send(this->n_socket, res.c_str(), res.size(), 0);
            close(this->n_socket);
        }

        printf("[I]: Server closed...\n");
    }

    void Server::stop() {
        this->is_run = false;
        close(this->s_socket);
        close(this->n_socket);
    }
}