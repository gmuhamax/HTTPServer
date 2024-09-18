#include <string>
#include <vector>
#include <unordered_map>

#include <arpa/inet.h>
#include <sys/socket.h>

using namespace std;

namespace http {
    enum Method {
        GET,
        POST,
        PUT,
        PATCH,
        DELETE
    };

    enum Status {
        OK_200,
        CREATED_201,
        NOT_FOUND_404,
    };

    Method toMethod(string method);
    string fromMethod(Method method);
    string fromStatus(Status status);
    string byTokent(const char token, const char* buf, size_t &pos, size_t offset);
    string byTokent(bool (*alpha)(char symbol), const char* buf, size_t &pos, size_t offset);

    class Headers {
    private:
        unordered_map<string, string> headers;

    public:
        Headers() {};
        Headers(const char* buf, size_t &pos);
    
    public:
        string get(string key);
        string get(string key, string default_);
        void add(string key, string value);
        string str();
    };

    class Request {
    private:
        Method method;
        string addr;
        string addr_q;
        string body;
        const char* buf;
        unordered_map<string, string> query_params;

    public:
        Headers headers;

    public:
        Request() {};
        Request(const char* buf);

    private:
        void parseQuery();

    public:
        string getQuery(string name) { return query_params.count(name) == 0 ? "" : query_params[name]; }
        string getAddr() { return this->addr; }
        string getFullAddr() { return this->addr + this->addr_q; }
        Method getMethod() { return this->method; }
    };

    class Response {
    private:
        Status status;
        string body;
        string result;

    public:
        Headers headers;

    public:
        Response() {};
        Response(string body): body(body), status(status) {}
        Response(string body, Status status);

    private:
        size_t length();

    public:
        size_t size();
        const char* c_str();
    };

    using route_fun = Response (*)(Request req, unordered_map<string, string> args);

    class Route {
    private:
        string temp;
        Method method;
        route_fun fun;
    
    private:
        unordered_map<string, string> parse(string addr);

    public:
        Route(string addr, Method method, route_fun fun): temp(addr), method(method), fun(fun) {};
        bool thisRoute(Request req);
        Response getRes(Request req);
    };

    class Routes {
    private:
        vector<Route> w_addr;

    public:
        Response getResponse(Request req);
        void addRoute(Route route);
    };

    class StaticFile {
    public:
        StaticFile(string addr, string filePath);

    private:
        string addr, filePath;
    };

    class Server {
    public:
        Server(const char* ip, int port): ip(ip), port(port) {};

        void run();
        void stop();

    public:
        Routes route;

    private:
        const char* ip;
        int port;
        bool is_run;

        int s_socket;
        int n_socket;
        sockaddr_in s_addr;
    };
}