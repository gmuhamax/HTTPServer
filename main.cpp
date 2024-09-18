#include "http.hpp"

using namespace http;

Response index(Request req, unordered_map<string, string> arg) {
    printf(arg["id"].c_str());
    return Response("<h1>Hello, World</h1>");
}

Response hi(Request req, unordered_map<string, string> arg) {
    return Response("<h1>hi</h1>");
}

int main(int argc, char const *argv[])
{
    Server server("127.0.0.1", 8888);

    server.route.addRoute(Route("/<id>/", Method::GET, index));
    server.route.addRoute(Route("/hi/", Method::GET, hi));

    server.run();
    return 0;
}
