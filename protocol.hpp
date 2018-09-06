#ifndef PROTOCOL_H
#define PROTOCOL_H 1

#define PRIORITY_HIGHEST 6
#define PRIORITY_VERY_HIGH 5
#define PRIORITY_HIGH 4
#define PRIORITY_MEDIUM 3
#define PRIORITY_LOW 2
#define PRIORITY_VERY_LOW 1
#define PRIORITY_NULL 0

class IA;

class Protocol {
  public:
    virtual void doNextMove(IA *ia) = 0; //execute the next action of this protocol
    virtual void reset() = 0; // reset this protocol
    virtual bool isCompleted() = 0; //wether the last action of this protocol have already been executed or not
    virtual unsigned short int getPriority(IA *ia) = 0;
  private:
    enum CommandType {forward, rotate, moveTo, load, unload, stack, buldozer, recalibrateMovingBackward};
    typedef struct {
      CommandType commandType;
      double args[3];
    } Command;
};
#endif
