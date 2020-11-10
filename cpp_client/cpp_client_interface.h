#ifndef CPP_CLIENT_INTERFACE_H
#define CPP_CLIENT_INTERFACE_H

#ifdef __cplusplus
extern "C" {
#endif


void allocate_interface(void **interface, const char* host_name, int port);
void deallocate_interface(void *interface);
void read_data(void* interface);



#ifdef __cplusplus
}
#endif

#endif // CPP_CLIENT_INTERFACE_H
