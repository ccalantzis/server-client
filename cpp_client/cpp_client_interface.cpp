#include "cpp_client_interface.h"
#include "cpp_client.h"
#include <iostream>

void allocate_interface(void **interface, const char* host_name, int port)
{
    std::cout << "trry deallocating\n";
    deallocate_interface(*interface);
    std::cout << "deallocated\n";
    (*interface) = reinterpret_cast<cpp_client*>(new cpp_client(host_name, port));
}

void deallocate_interface(void *interface)
{
    if(interface == nullptr)
        return;
    cpp_client* ci = reinterpret_cast<cpp_client*>(interface);
    delete ci;
}

void read_data(void* interface)
{
    if(interface == nullptr)
        return;
    cpp_client* ci = reinterpret_cast<cpp_client*>(interface);
    ci->read_data();
}
