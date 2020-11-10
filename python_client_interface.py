import ctypes

class ClientInterface:
    def __init__(self, dllpath):
        print(dllpath)
        self._interface_lib = ctypes.cdll.LoadLibrary(dllpath)
        print("interface lib created")
        self._c_interface = ctypes.c_void_p(0)

    def __del__(self):
        del self._interface_lib

    def initClientInterface(self):
        tcp_addr = self.tcp_addr.encode('utf-8')
        self._interface_lib.allocate_interface(ctypes.byref(self._c_interface)) #, ctypes.c_char_p(tcp_addr), ctypes.c_int(self.tcp_port))

    def deallocateClientInterface(self):
        self._interface_lib.deallocateClientInterface(self._c_interface)

    def readData(self):
        self._interface_lib.readData(self._c_interface)
