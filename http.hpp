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

    class Headers {
    private:
        unordered_map<string, string> headers;

    public:
        Headers() {};
        Headers(const char* buf, size_t* offset);
    
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
        string body;

    public:
        Headers headers;

    public:
        Request() {};
        Request(const char* buf);

    public:
        string getAddr() { return this->addr; }
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

    using route_fun = Response (*)(Request req);
    using route_map = unordered_map<string, std::unordered_map<Method, route_fun>>;

    struct Routes {
    private:
        route_map w_addr;

    private:
        bool hasAddresAndMethod(string addr, Method method);

    public:
        Response getResponse(Request req);
        void addRoute(string addr, Method method, route_fun func);
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