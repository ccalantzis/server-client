#include <iostream>
#include "cpp_client.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <chrono>

using namespace std;

int main()
{
    std::string str = "127.0.0.1";
    const char *cstr = str.c_str();
    cpp_client client = cpp_client(cstr, 8000);
    auto start = std::chrono::high_resolution_clock::now();
    client.read_data();
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Time taken: " << elapsed.count() << " s\n";
}
