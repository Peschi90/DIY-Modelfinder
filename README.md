# DIY-Modelfinder
This is a Little Modellfinder like an Hellgate Buzzer  https://buzzer.hellgatefpv.com/

Parts you need:
-2x 10K Resistor
-little 1s lipo from scratch 50mAh to 200mAh
-Attiny85
-5V active Buzzer
-5V PowerSupply from FC or Reciver
-TP4056 Lipo Charger module like this with undervoltage Protection. https://www.ebay.de/itm/5-5V-1A-Micro-USB-18650-Battery-Charging-Lademodul-Schutzschaltung-TP4056/123286323604?epid=14019161893&hash=item1cb4700194:g:0EwAAOSwyCNbYZML

One tricky thing is to modify the Charger that it doesn´t charge with 1A current. 
for this please look inside the Datasheet. 
You have to Replace the Resistor, next to gnd input, with a 10k Resistor for 140mAh charging current. That is completly enough.


Connection Diagramm
                                                        FC +      Buz +
                                       |---------|       ^         ^
                __________________     |         |       |         |          |
  Lipo +-------| Charger        + |----|     |----------------------------------|
               | Lipo    | Lipo   |          |   8       7         6          5 |
               | Input   | Output |          |             ATtiny85             |
  Lipo --------|         |      - |-->Pin4   |O 1       2         3          4  |
               | 5V Power input   |          |----------------------------------|
               |__________________|             |       |         |          |
                   |         |                                           |--GND----> Buz -
                   |         |------>Pin7              Charger Out -<----|
                   |         |  
                FC Gnd /    FC + 

