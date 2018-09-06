#include "ia.hpp"
#include <Arduino.h>

IA::IA():
  protocols_{},
  protocolCount_{},
  maxFlagIndex{0} {}

IA::IA(Protocol *protocols[], unsigned short int protocolCount):
  protocols_{},
  protocolCount_{protocolCount},
  maxFlagIndex{0} {
  for (unsigned short int i = 0; i < protocolCount; ++i) {
    protocols_[i] = protocols[i];
  }
}

void IA::addProtocol(Protocol *protocol) {
  protocols_[protocolCount_++] = protocol;
}

void IA::autoselectProtocol() {
  selectedProtocolId_=-1;
  unsigned short int maxPriority = 0;
  for (unsigned short int selectedProtocolId = 0; selectedProtocolId < protocolCount_; ++selectedProtocolId) {
    if (!protocols_[selectedProtocolId]->isCompleted()) {
      if (protocols_[selectedProtocolId]->getPriority(this) > maxPriority
            && protocols_[selectedProtocolId]->getPriority(this)>PRIORITY_NULL) {
        maxPriority = protocols_[selectedProtocolId]->getPriority(this);
        selectedProtocolId_ = selectedProtocolId;
      }
    }
  }

}

void IA::setFlag(String flagName, unsigned char value) {
  for (unsigned int i=0;i<=maxFlagIndex;i++) {
    if (dictionnary[i].id == flagName) {
      dictionnary[i].value = value;
      return;
    }
  }
  dictionnary[++maxFlagIndex] = {flagName, value};
}

short int IA::getFlag(String flagName) { //return an unsigned char, or -1 if not found
  for (auto entry : dictionnary) {
    if (entry.id == flagName) {
      return entry.value;
    }
  }
  return -1;
}

void start(){
  if(hasRun){
    return;
  }
  isRunning.store(true);
  hasRun.store(true);
  thread = new thread(this, this);
  thread.detach();
}

void pause(){
  if(!hasRun){
    throw runtime_error("Vous tentez de mettre en pause un thread qui n'a jamais été lançé!");
  }
  isRunning.store(false);
}

void unpause(){
  if(!hasRun){
    throw runtime_error("Vous tentez de sortir de pause un thread qui n'a jamais été lançé!");
  }
  if()
}

void reset();

const bool isRunning(){
  return isRunning;
}

const bool hasRun(){
  return hasRun;
}

void operator()(){ // fonction run
  while(true){
    while(!isRunning){
      std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    if (!mb->isBusy() && !claw->isBusy()) {
      if (selectedProtocolId_==-1||protocols_[selectedProtocolId_]->isCompleted()) {
        autoselectProtocol();
      }
      if(selectedProtocolId_!=-1)protocols_[selectedProtocolId_]->update(this);
    }
  }
}
