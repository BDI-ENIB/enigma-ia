#ifndef IA_H
#define IA_H 1

#include "src/summerbot-motionbase/MotionBase.h"
#include "src/summerbot-claw/claw.hpp"
#include "src/summerbot-screen/Screen.h"
#include "src/summerbot-bee/Bee.h"
#include "protocol.hpp"

#include <chrono>
#include <thread>
#include <atomic>
#include <stdexcept>

#define MAX_FLAG_NUMBER 20
#define MAX_PROTOCOL_NUMBER 15

class IA {
  private:
    std::thread *thread;
    void operator()();
    Protocol *protocols_[MAX_PROTOCOL_NUMBER];
    unsigned short int protocolCount_;
    short int selectedProtocolId_=-1;
    void autoselectProtocol();
    typedef struct {
      String id;
      unsigned char value;
    } DictionnaryEntry;
    DictionnaryEntry dictionnary[MAX_FLAG_NUMBER];
    unsigned char maxFlagIndex;
    std::atomic_bool isRunning = false;
    std::atomic_bool hasRun = false;
    std::atomic_bool isReseting = false;

  public:

    IA(Protocol *protocols[], short unsigned int protocolCount);
    IA();
    void addProtocol(Protocol *protocol);
    void setFlag(String flagName, unsigned char value);
    short int getFlag(String flagName); //return an unsigned char, or -1 if not found
    void start();
    void pause();
    void reset();
    bool isRunning();
    bool hasRun();
};
#endif
