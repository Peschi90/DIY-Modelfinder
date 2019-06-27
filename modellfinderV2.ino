/* Modelfinde V2 (C) I3uLL3t www.peschi.info
 * A simple Buzzer to find your model after a crash.
 * The Buzzer has an integratet Lipo to beep for a long time if you Model Lipo is flown away.
 * The code is developed for an Attiny85
 * 
 * Only things you need:
 * - small Lipo from scratch 50mAh to 200mAh
 * - Lipo charger module like the TP4056 with integrated low Voltage Cutoff
 * - Attiny85
 * - 5V active Buzzer
 * - 1x 10Kohm Resistor
 * - 5V Power Supply from Flightcontroller or reciver
 *                                                        FC +      Buz +
 *                                       |---------|       ^         ^
 *                __________________     |         |       |         |          |
 *  Lipo +-------| Charger        + |----|     |----------------------------------|
 *               | Lipo    | Lipo   |          |   8       7         6          5 |
 *               | Input   | Output |          |             ATtiny85             |
 *  Lipo --------|         |      - |-->Pin4   |O 1       2         3          4  |
 *               | 5V Power input   |          |----------------------------------|
 *               |__________________|             |       |         |          |
 *                   |         |                                           |--GND----> Buz -
 *                   |         |------>Pin7              Charger Out -<----|
 *                   |         |
 *                FC Gnd /    FC + 
 */

const int bitInputVol = 2;
const int bitBuzzer = 1;
int modeStatus = 0;               //0 = off ; 1 = Active; 2 = warning active; 3 = Deactivation Beeps; 4 = Activation Beeps;

bool inputReadFirstHIGH = true;
bool inputReadFirstLOW = true;
unsigned long inputFirstTime;
bool oneTimeLOW = false;
bool inputStatus = false;

const int activationTime = 10000;
const int deactivationTime = 2000;

bool buzzer = false;
const int buzzerON = 2000;
const int buzzerOFF = 10000;
unsigned long buzzerTime;

void setup() {
 pinMode(bitInputVol,INPUT);
 pinMode(bitBuzzer,OUTPUT);
 digitalWrite(bitBuzzer, LOW);
}

void loop() {
  unsigned long milliSeconds = millis();

  switch(modeStatus){
    case 0:
      //INAVTIVE STATE
      digitalWrite(bitBuzzer, LOW);
    break;
    case 1:
      // Its possible to Programm some activation Sequenzes if you want.
      // for example: Beep every 60 seconds to show that the mode is active
    break;
    case 2:
      if((milliSeconds - buzzerTime) >= buzzerOFF && buzzer == false){
        digitalWrite(bitBuzzer,HIGH);
        buzzer = true;
        buzzerTime = milliSeconds;
      }else if((milliSeconds - buzzerTime) >= buzzerON && buzzer == true){
        digitalWrite(bitBuzzer,LOW);
        buzzer = false;
        buzzerTime = milliSeconds;
      }
    break;
    case 3:
      digitalWrite(bitBuzzer, HIGH);
      delay(200);
      digitalWrite(bitBuzzer, LOW);
      delay(50);
      digitalWrite(bitBuzzer, HIGH);
      delay(200);
      digitalWrite(bitBuzzer, LOW);
      delay(50);
      digitalWrite(bitBuzzer, HIGH);
      delay(200);
      digitalWrite(bitBuzzer, LOW);
      delay(50);
      digitalWrite(bitBuzzer, HIGH);
      delay(200);
      digitalWrite(bitBuzzer, LOW);
      delay(50);
      digitalWrite(bitBuzzer, HIGH);
      delay(500);
      digitalWrite(bitBuzzer, LOW);
      delay(50);
      modeStatus = 0;
    break;
    case 4:
      digitalWrite(bitBuzzer, HIGH);
      delay(1000);
      digitalWrite(bitBuzzer, LOW);
      delay(150);
      digitalWrite(bitBuzzer, HIGH);
      delay(1000);
      digitalWrite(bitBuzzer, LOW);
      delay(150);
      modeStatus = 1;
    break;
  }
  if(digitalRead(bitInputVol) == HIGH){
    if(inputReadFirstHIGH == true){
      inputFirstTime = milliSeconds;
      inputReadFirstHIGH = false;
    }
    if(inputReadFirstHIGH == false && (milliSeconds - inputFirstTime) >= activationTime && modeStatus == 0){
      modeStatus = 4;
      inputReadFirstHIGH = true;
      oneTimeLOW = false;
      inputReadFirstLOW = true;
    }else if(inputReadFirstHIGH == false && (milliSeconds - inputFirstTime) <= activationTime && (milliSeconds - inputFirstTime) >= deactivationTime && modeStatus == 2 && oneTimeLOW == true){
      modeStatus = 3;
      inputReadFirstHIGH = true;
      inputReadFirstLOW = true;
      oneTimeLOW = false;
    }
    
  }else if(digitalRead(bitInputVol) == LOW){
    if(inputReadFirstLOW == true){
      oneTimeLOW = true;
      inputReadFirstLOW = false;
      inputReadFirstHIGH = true;
    }
    if(modeStatus == 1){
      modeStatus = 2;
      inputReadFirstHIGH = true;
      inputReadFirstLOW = true;
      oneTimeLOW = false;
    }
  }

}// LOOP

