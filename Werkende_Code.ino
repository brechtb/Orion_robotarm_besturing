#include <EEPROM.h>
#include <BMSerial.h>
#include <BMPS2.h>
#include <SPI.h>
#include <Orion.h>

#define DEBUG 1

#define SIMPLEWRIST
//#define CUSTOMPINS


  #define BASE 5
  #define SHOULDER 4
  #define ELBOW 3
  #define WRIST 2
  #define WRISTROT 1
  #define GRIP 0

#define DEADZONE 20

#define GREENLED A1
#define REDLED A0

#define KEY 0x4321

//Maximum body offset
#define MAXX 1100
#define MAXY 1800
#define MAXZ 800
#define MAXR 350

#define DEGREE 178

//leg servo pin assignments
const int IKPins[6] = {BASE,SHOULDER,ELBOW,WRIST,WRISTROT,GRIP};
#ifdef SIMPLEWRIST
  //leg dimensions
  const int IKLengths[6] = {0,1535,1330,0,0,0};
  //Start position
  const int StartPos[6] = {0,800,0,0,0,100};
#else
  //leg dimensions
  const int IKLengths[6] = {0,1535,1330,1680,0,0};
  //Start position
  const int StartPos[6] = {1680,800,0,0,0,100};
#endif
//Servo angle offsets
const int ServoAOffsets[6] = {0,500,750,200,0,0};
//Servo normal/reverse flags
const unsigned char reverse[6] = {0,1,1,1,0,1};

unsigned int Rate;

boolean onoff;
boolean heartbeat;
long lastbeat;

boolean wristmode;


void setup() {  
  Serial.begin(115200);
  
  // initialize Orion
  Orion.begin();
  Orion.green(true);
  Orion.red(false);
  
  //Set Body Dimensions and initial Leg positions
  unsigned long flags=0;
  for(int i=0;i<6;i++){
    Orion.stopPulse(IKPins[i]);  //stops servo if running and starts reading feedback data if not
    Orion.setSpeed(50);  //limit maximum servo speed
  }

  //Set initial rate and leg lift
  Rate = 8;
  
  //Init other system variables
  lastbeat = millis();
  onoff = false;

  Orion.tone(NOTE_C6,100);
  Orion.tone(NOTE_B5,100);
  Orion.tone(NOTE_A5,100);

  wristmode = false;
}
 
void loop(){
  
  Orion.setAngle(BASE,156);
  Orion.setAngle(GRIP,90);
  Orion.execute();
  delay(1000);
}


  
