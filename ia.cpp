#include "ia.hpp"

IA::IA():
  protocols_{},
  protocolCount_{},
  maxFlagIndex_{0} {}

IA::IA(Protocol *protocols[], unsigned short int protocolCount):
  protocols_{},
  protocolCount_{protocolCount},
  maxFlagIndex_{0} {
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

void IA::setFlag(string flagName, unsigned char value) {
  for (unsigned int i=0;i<=maxFlagIndex_;i++) {
    if (dictionnary_[i].id == flagName) {
      dictionnary_[i].value = value;
      return;
    }
  }
  dictionnary_[++maxFlagIndex_] = {flagName, value};
}

short int IA::getFlag(string flagName) { //return an unsigned char, or -1 if not found
  for (auto entry : dictionnary_) {
    if (entry.id == flagName) {
      return entry.value;
    }
  }
  return -1;
}

bool IA::start(){
  if(isStopping_){
    return false;
  }
  if(!hasRun_){
    hasRun_.store(true);
    thread_ = new std::thread(&IA::run, this);
    thread_->detach();
  }
  isRunning_.store(true);
  return true;
}

bool IA::pause(){
  while(isStopping_){
    return false;
  }
  if(!isRunning_){
    return true; // Si il est déja en pause, on ne fait rien mais on return true
  }
  isRunning_.store(false);
  return true;
}

bool IA::stop(){
  if(isStopping_){
    return false;
  }
  isStopping_.store(true);
  isRunning_.store(false);
  thread_->join();
  return true;
}

bool IA::isRunning(){
  return isRunning_;
}

bool IA::hasRun(){
  return hasRun_;
}

void IA::run(){ // fonction run
  while(true){
    while(!isRunning_ &!isStopping_){
      std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    if(isStopping_){
      return;
    }
    /*
    if (!mb->isBusy() && !claw->isBusy()) {
      if (selectedProtocolId_==-1||protocols_[selectedProtocolId_]->isCompleted()) {
        autoselectProtocol();
      }
      if(selectedProtocolId_!=-1)protocols_[selectedProtocolId_]->update(this);
    }*/
  }
}
