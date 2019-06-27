# DIY-Modelfinder
This is a Little Modellfinder like an Hellgate Buzzer  https://buzzer.hellgatefpv.com/ </br>

Parts you need:</br>
-2x 10K Resistor</br>
-little 1s lipo from scratch 50mAh to 200mAh</br>
-Attiny85</br>
-5V active Buzzer</br>
-5V PowerSupply from FC or Reciver</br>
-TP4056 Lipo Charger module like this with undervoltage Protection. https://www.ebay.de/itm/5-5V-1A-Micro-USB-18650-Battery-Charging-Lademodul-Schutzschaltung-TP4056/123286323604?epid=14019161893&hash=item1cb4700194:g:0EwAAOSwyCNbYZML</br>

One tricky thing is to modify the Charger that it doesn´t charge with 1A current. </br>
for this please look inside the Datasheet. </br>
You have to Replace the Resistor, next to gnd input, with a 10k Resistor for 140mAh charging current. That is completly enough.</br>


Connection Diagramm </br>

<img src="http://peschi.info/wp-content/uploads/2019/06/Connection.png" alt="Connection" /></br>
