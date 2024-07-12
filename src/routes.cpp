#include "http.hpp"

namespace http {
    bool Routes::hasAddresAndMethod(string addr, Method method) {
        if (this->w_addr.count(addr) == 0) return false;
        if (this->w_addr[addr].count(method) == 0) return false;
        return true;
    }

    void Routes::addRoute(string addr, Method method, route_fun func) {
        this->w_addr[addr][method] = func;
    }

    Response Routes::getResponse(Request req) {
        if (!this->hasAddresAndMethod(req.getAddr(), req.getMethod())) {
            return Response("<h1>404 Found Error</h1>", Status::NOT_FOUND_404);
        }
        return this->w_addr[req.getAddr()][req.getMethod()](req);
    }
}