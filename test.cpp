#include <string>
#include <unordered_map>

using namespace std;

bool hasAddr(string temp, string addr);
unordered_map<string, string> parse(string temp, string addr);

int main(int argc, char const *argv[])
{
    string temp = "/user/<id>/";
    string addr = "/user/12312313/";

    parse(temp, addr);

    return 0;
}

string byTokent(const char token, const char* buf, size_t &pos, size_t offset) {
    string data;

    pos += offset;
    while (buf[pos] != token)
    {
        data += buf[pos];
        pos++;
    }

    return data;
}

bool hasAddr(string temp, string addr) {
    size_t len_k, len_v, len_r, prev_n; 
    size_t pos = 0;
    char next_s;

    while (temp[pos] != '\0') {
        byTokent('<', temp.c_str(), pos, 1);
        if (temp[pos] == '\0') break;
        prev_n = pos - (len_k + (len_r != 0 ? 2 : 0) - len_v);

        len_k = byTokent('>', temp.c_str(), pos, 1).size();
        next_s = temp[++pos];

        size_t q = 0;
        len_v = byTokent(next_s, addr.c_str(), q, prev_n).size();

        
    }

    return temp == addr;
}

unordered_map<string, string> parse(string temp, string addr) {
    unordered_map<string, string> result;
    size_t pos = 0;
    size_t prev_n = 0;
    char next_s;
    string key, value;
    while (temp[pos] != '\0') {
        byTokent('<', temp.c_str(), pos, 1);
        if (temp[pos] == '\0') break;
        prev_n = pos - (key.size() + (result.size() != 0 ? 2 : 0) - value.size());

        key.clear();
        value.clear();
        key = byTokent('>', temp.c_str(), pos, 1);

        next_s = temp[++pos];

        size_t q = 0;
        value = byTokent(next_s, addr.c_str(), q, prev_n);
        result[key] = value;
    }
    return result;
}
