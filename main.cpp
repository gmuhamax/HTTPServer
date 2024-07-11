#include "http.hpp"

using namespace http;

Response index(Request req) {
    return Response("<h1>Hello, world!</h1>");
}

Response hi(Request req) {
    return Response("<h1>hi</h1>");
}

int main(int argc, char const *argv[])
{
    Server server("127.0.0.1", 7777);

    server.registerHandler("/", Method::GET, index);
    server.registerHandler("/hi", Method::GET, hi);

    server.run();
    return 0;
}
