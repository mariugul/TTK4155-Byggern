/**
\mainpage Atmega2560 - Node 2



\section Intro Introduction
This is the code for "Node 2", the Atmega2560, which runs on an Arduino Mega board. The Chip however, is programmed <br>
with Jtag in embedded C and not with Arduino. Follow the instructions under <b>Get started</b>.


Atmega2560 has these specifications:
<ul>
    <li> Something
    <li> 
    <li> 
    <li> 
    <li> 5V logic.
    <li> 
</ul> 

The <b>pinout</b> can be found <a href="https://www.pjrc.com/teensy/pinout.html" target="_blank">here</a>. <br>
The <b>schematic</b> can be found <a href="https://www.pjrc.com/teensy/schematic.html" target="_blank">here</a>. <br>
The <b>datasheets</b> can be found <a href="https://www.pjrc.com/teensy/datasheets.html" target="_blank">here</a>. <br>

\section Install Get started
To be able to run Arduino on the Teensy 3.6 you need to install the <a href="https://www.arduino.cc/en/Main/Software" target="_blank">Arduino IDE</a> and the extension <a href="https://www.pjrc.com/teensy/teensyduino.html" target="_blank">Teensyduino</a>. <br>
The Teensyduino extension will upload your Arduino code so that the Teensy can understand it.<br>
Most functions of Arduino will work on Teensy, and with the Teensyduino installer there are several libraries included that can be useful, they are documented <a href="https://www.pjrc.com/teensy/td_libs.html" target="_blank">here</a>. <br>
To be able to program the Teensy it needs power. Because it is powered by an external power source (LiPo battery), the VUSB underneath was cut <a href="https://www.pjrc.com/teensy/external_power.html" target="_blank">shown here</a>, and it can no longer be powered with the USB cable. <br>
If power should be needed through the USB cable the VUSB pad can be soldered. However be careful if external power is connected because it will flow into the computer. Use of a diode should be considered in this case.<br>

\section libraries Used libraries
The libraries that have been used in this program are listed below.

<ul>
    <li> FastCRC <a href="https://github.com/FrankBoesing/FastCRC" target="_blank">gitHub</a>. (<i>CRC16-CCITT with tables and hardware calculation.</i>)
    <li> Delay..
    <li> Interrupt..
    <li> 
</ul> 


\section files Source files
Node 2 has several source files that provides different functionality to the application. <br>

Communication:
<ul> 
	<li> CAN          </i>
	<li> MCP2515      </i>
	<li> SPI          </i>
	<li> USART        </i>
	<li> TWI_Master   </i>
</ul>

Analog/Digital Converters:
<ul>
	<li> ADC          </i>
	<li> DAC          </i>
</ul>

Motor/Servo Control:
<ul>
	<li> PID          </i>
	<li> PWM          </i>
	<li> Motor        </i>
	<li> Servo        </i>
	<li> Solenoid	  </i>
</ul>

Timers and Interrupts:
<ul>
	<li> Timers		  </i>
	<li> IRQ_Handlers </i>
	
</ul>

\section functions Global Functions

<ul>
    <li> lowBattery() returns true if battery is low.       </i>
    <li> ledOn() turns the onboard LED on.                  </i>
    <li> ledOff() turns the onboard LED off.                </i>
    <li> ledBlink() blinks the onboard LED.                 </i>
    <li> batteryVoltage() returns battery voltage in float. </i>
    <li> sendBattToApp() sends the battery voltage to app.  </i>
   
</ul>





<CENTER>Copyright 2019 by Marius C.K. Gulbrandsen and Daniel Rahme</CENTER>

*/
//END OF MAINPAGE