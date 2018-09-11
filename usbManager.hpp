#ifndef USB_MANAGER
#define USB_MANAGER 1

#include <string>

class UsbManager{
  private:
    long int commandId;
    void registerSlave(std::string);
  public:
    UsbManager(std::string username);
    void registerCommand(std:string, bool* callbackFunction);
    void sendCommand(std::string slaveName, std::string command);
};

#endif
