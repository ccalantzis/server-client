import ctypes

class ClientInterface:
    def __init__(self, dllpath):
        print(dllpath)
        self._interface_lib = ctypes.cdll.LoadLibrary(dllpath)
        print("interface lib created")
        self._c_interface = ctypes.c_void_p(0)

    def __del__(self):
        del self._interface_lib

    def initClientInterface(self, host_name, port):
        host_name = host_name.encode('utf-8')
        self._interface_lib.allocate_interface(ctypes.byref(self._c_interface), ctypes.c_char_p(host_name), ctypes.c_int(port))

    def deallocateClientInterface(self):
        self._interface_lib.deallocate_interface(self._c_interface)

    def readData(self):
        self._interface_lib.read_data(self._c_interface)
