#include "http.hpp"

using namespace http;

Response index(Request req) {
    return Response("<h1>Hello, world!</h1>", Status::OK_200);
}

Response hi(Request req) {
    return Response("<h1>hi</h1>", Status::OK_200);
}

int main(int argc, char const *argv[])
{
    Server server("127.0.0.1", 8888);

    server.route.addRoute("/", Method::GET, index);
    server.route.addRoute("/hi", Method::GET, hi);

    server.run();
    return 0;
}
