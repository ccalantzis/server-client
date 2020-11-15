import python_client_interface as interface
import os

dllfile = os.path.abspath('cpp_client/libinterface.so')
print("about to create")
ci = interface.ClientInterface(dllfile)
print("created")
ci.initClientInterface("127.0.0.1", 8000)
ci.readData()
