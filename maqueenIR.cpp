#include <map>
#include <vector>

#include "ReceiverIR.h"
#include "pxt.h"
using namespace pxt;
typedef vector<Action> vA;

enum class Pins {
  P0 = 3,
  P1 = 2,
  P2 = 1,
  P3 = 4,
  P4 = 5,
  P5 = 17,
  P6 = 12,
  P7 = 11,
  P8 = 18,
  P9 = 10,
  P10 = 6,
  P11 = 26,
  P12 = 20,
  P13 = 23,
  P14 = 22,
  P15 = 21,
  P16 = 16,
  P19 = 0,
  P20 = 30
};

enum class RemoteButton {
//   Power = 0x00,
//   VolUp = 0x01,
//   FuncStop = 0x02,
//   LeftTwo = 0x04,
//   Suspended = 0x05,
//   RightTwo = 0x06,
//   Down = 0x08,
//   VolDown = 0x09,
//   Up = 0x0a,
//   Zero = 0x0c,
//   EQ = 0x0d,
//   StRept = 0x0e,
//   One = 0x10,
//   Two = 0x11,
//   Three = 0x12,
//   Four = 0x14,
//   Five = 0x15,
//   Six = 0x16,
//   Seven = 0x18,
//   Eight = 0x19,
//   Nine = 0x1a

  // IR HANDLE
  //% block="up"
  UP = 0x11,
  //% block="down"
  DOWN = 0x91,
  //% block="left"
  LEFT = 0x81,
  //% block="right"
  RIGHT = 0xa1,
  //% block="m1"
  M1 = 0xe9,
  //% block="m2"
  M2 = 0x69,
  //% block="a"
  A = 0x21,
  //% block="b"
  B = 0x01,
  //% block="any"
  Any = -1,

  // MINI IR
  //% block="power"
  Power = 0xa2,
  //% block="menu"
  MENU = 0xe2,
  //% block="test"
  TEST = 0x22,
  //% block="+"
  PLUS = 0x02,
  //% block="back"
  Back = 0xc2,
  //% block="<<"
  Back2 = 0xe0,
  //% block="play"
  Play = 0xa8,
  //% block=">>"
  F = 0x90,
  //% block="0"
  Number_0 = 0x68,
  //% block="-"
  Less = 0x98,
  //% block="c"
  C = 0xb0,
  //% block="1"
  Number_1 = 0x30,
  //% block="2"
  Number_2 = 0x18,
  //% block="3"
  Number_3 = 0x7a,
  //% block="4"
  Number_4 = 0x10,
  //% block="5"
  Number_5 = 0x38,
  //% block="6"
  Number_6 = 0x5a,
  //% block="7"
  Number_7 = 0x42,
  //% block="8"
  Number_8 = 0x4a,
  //% block="9"
  Number_9 = 0x52,
};

//% color=50 weight=80
//% icon="\uf1eb"
namespace maqueenIR {
map<RemoteButton, vA> actions;
map<RemoteButton, uint32_t> lastact;
Timer tsb;
uint8_t buf[32];
uint32_t now;
ReceiverIR *rx;
RemoteIR::Format fmt = RemoteIR::UNKNOWN;
int msg;
int IRcallbackNum;

/**
 * button pushed.
 */
//% blockId=ir_received_left_event
//% block="on |%btn| button pressed"
void onPressEvent(RemoteButton btn, Action body) {
  // if(actions.find(btn) == actions.end()) actions[btn] = new vector();
  IRcallbackNum = (int)btn;
  actions[btn].push_back(body);
}

void cA(vA runner) {
  for (int i = 0; i < runner.size(); i++) {
    runAction0(runner[i]);
  }
}

void onReceivable() {
  int x = rx->getData(&fmt, buf, 32 * 8);
  /*
  uBit.serial.send(".");
  uBit.serial.send(buf[0]);
  uBit.serial.send(".");
  uBit.serial.send(buf[1]);
  uBit.serial.send(".");
  uBit.serial.send(buf[2]);
  uBit.serial.send(".");
  uBit.serial.send(buf[3]);
  uBit.serial.send(".");
  uBit.serial.send(buf[4]);
  uBit.serial.send(".");
  uBit.serial.send(buf[5]);
  uBit.serial.send(".");
  uBit.serial.send(buf[6]);
  uBit.serial.send(".");
  uBit.serial.send(buf[7]);
  uBit.serial.send(".");
  uBit.serial.send(buf[8]);
  uBit.serial.send(".");
  uBit.serial.send(buf[9]);
  uBit.serial.send(".");
  uBit.serial.send(buf[10]);
  uBit.serial.send(".");
  uBit.serial.send(buf[11]);
  uBit.serial.send(".");
  uBit.serial.send(buf[12]);
  uBit.serial.send(".");
  uBit.serial.send(buf[13]);
  uBit.serial.send(".");
  uBit.serial.send(buf[14]);
  uBit.serial.send(".");
  uBit.serial.send(buf[15]);
  uBit.serial.send(".");
  uBit.serial.send(buf[16]);
  uBit.serial.send(".");
  uBit.serial.send(buf[17]);
  uBit.serial.send(".");
  uBit.serial.send(buf[18]);
  uBit.serial.send(".");
  uBit.serial.send(buf[19]);
  uBit.serial.send(".");
  uBit.serial.send(buf[20]);
  uBit.serial.send(".");
  uBit.serial.send(buf[21]);
  uBit.serial.send(".");
  uBit.serial.send(buf[22]);
  uBit.serial.send(".");
  uBit.serial.send(buf[23]);
  uBit.serial.send(".");
  uBit.serial.send(buf[24]);
  uBit.serial.send(".");
  uBit.serial.send(buf[25]);
  uBit.serial.send(".");
  uBit.serial.send(buf[26]);
  uBit.serial.send(".");
  uBit.serial.send(buf[27]);
  uBit.serial.send(".");
  uBit.serial.send(buf[28]);
  uBit.serial.send(".");
  uBit.serial.send(buf[29]);
  uBit.serial.send(".");
  uBit.serial.send(buf[30]);
  uBit.serial.send(".");
  uBit.serial.send(buf[31]);
  uBit.serial.send(".");
  uBit.serial.send(buf[32]);
  uBit.serial.send(".");
  uBit.serial.send(buf[33]);
  uBit.serial.send(".");
  uBit.serial.send(buf[34]);
  uBit.serial.send(".");
  uBit.serial.send(buf[35]);
  uBit.serial.send(".end");
  */
  // if(actions.find((RemoteButton)buf[2]) == actions.end()) return;
  now = tsb.read_ms();
  if (now - lastact[(RemoteButton)buf[2]] < 100) return;
  lastact[(RemoteButton)buf[2]] = now;
  msg = (int)buf[2];
  uBit.serial.send(IRcallbackNum);
  if (IRcallbackNum < 1) {
    return;
  }
  for (int i = 1; i <= IRcallbackNum; i++) {
    cA(actions[(RemoteButton)i]);
  }
}

void monitorIR() {
  while (1) {
    while (rx->getState() != ReceiverIR::Received) {
      uBit.sleep(50);
    }
    onReceivable();
  }
}

/**
 * initialises local variablesssss
 */
//% blockId=ir_init
//% block="connect ir receiver to %pin"
void initIR(Pins pin) {
  rx = new ReceiverIR((PinName)pin);
  tsb.start();  // interrupt timer for debounce
  create_fiber(monitorIR);
}
//%
int getParam() { return msg; }

}  // namespace maqueenIR