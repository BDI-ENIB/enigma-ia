#ifndef IA_H
#define IA_H 1

#include "protocol.hpp"

#include <chrono>
#include <thread>
#include <atomic>
#include <stdexcept>
#include <string>

using std::string;

#define MAX_FLAG_NUMBER 20
#define MAX_PROTOCOL_NUMBER 15

class IA {

  private:
    std::thread *thread_;
    void run();
    Protocol *protocols_[MAX_PROTOCOL_NUMBER];
    unsigned short int protocolCount_;
    short int selectedProtocolId_=-1;
    void autoselectProtocol();
    typedef struct {
      string id;
      unsigned char value;
    } DictionnaryEntry;
    DictionnaryEntry dictionnary_[MAX_FLAG_NUMBER];
    unsigned char maxFlagIndex_;
    std::atomic_bool isRunning_ = false;
    std::atomic_bool hasRun_ = false;
    std::atomic_bool isStopping_ = false;

  public:

    IA(Protocol *protocols[], short unsigned int protocolCount);
    IA();
    void addProtocol(Protocol *protocol);
    void setFlag(string flagName, unsigned char value);
    short int getFlag(string flagName); //return an unsigned char, or -1 if not found

    bool start();
    bool pause();
    bool stop();

    bool isRunning();
    bool hasRun();
};
#endif
