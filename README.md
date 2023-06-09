# EMBEDDED_SYSTEMS-ALARM_PROJECT
Final project for Embedded Systems class. Digital clock with 3 alarms, input using PS/2 Keyboard.

<img width="478" alt="image" src="https://github.com/roxasmanner05/EMBEDDED_SYSTEMS-ALARM_PROJECT/assets/125866443/9246f447-b5bc-43ba-a22e-15b6dc7d0e50">

## Items used for this project:
- Arduino Uno R3
- 8x32 Dot Matrix display with MAX7219 chip
- LM35 Sensor					:	Room temperature sensor.
- LDR Sensor Module		:	Light sensor for auto-brightness.
- 5v Active Buzzer		:	Buzzer for the alarms.
- DS1307 RTC Module		:	Real-time clock.
- DIN 6-pin Connector	:	Port for keyboard.
- PS/2 Keyboard				:	Input.
- 1uF/25v Capacitor		: Stabilize LM35 value readings if your power supply power isn't stable. 

## Connections:

### 8x32 Dot Matrix display with MAX7219 chip:
- Vin		: 5v pin
- GND		: GND pin
- DATA	: pin 11
- CS		: pin 10
- CLK		:	pin 13

### LM35 Sensor:
1uF Capacitor bridge 5v pin with GND.
- Vin		: 5v pin
- GND		: GND pin
-	OUT		: A2 pin

### LDR Sensor Module:
- Vin		: 5v pin
- GND		: GND pin
- D0		: A0 pin

### 5v Active Buzzer:
- Vin		: pin 7
- GND		: GND pin

### DS1307 RTC Module:
- Vin 	: 5v pin
- GND		: GND pin
- SDA		: A4 pin
- SCL		: A5 pin

### DIN 6-pin Connector:
-	Vbus	: 5v pin
-	GND		: GND pin
- DATA	: pin 8
- CLK		: pin 3
