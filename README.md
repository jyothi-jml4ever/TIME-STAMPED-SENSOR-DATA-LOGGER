Time-Stamped Sensor Data Logger
LPC2148 |Embedded C |Keil |Proteus

*Project Overview*
This project is a real-time temperature monitoring and logging system using the LPC2148 ARM7 microcontroller.
The system reads temperature from the LM35 sensor through the ADC and gets the current date and time from the on-chip RTC. Each reading is tagged with a timestamp, shown on the LCD, and sent to the PC using UART.
A keypad and push button allow the user to edit RTC values and change the temperature set point. If the temperature crosses the limit, the LED and buzzer are activated.

*Objective*
Measure temperature using LM35
Maintain real-time clock using RTC
Attach timestamp to every reading
Display information on LCD
Send log data to PC via UART
Allow user settings through keypad
Generate alert when temperature is high

*Key Features*
Real-time temperature monitoring
RTC-based time stamping
LCD live display
UART serial logging
Keypad menu control
Editable time and set point
Over-temperature alert
Works on hardware and Proteus

*Hardware Requirements*
LPC2148 Microcontroller
LM35 Temperature Sensor
16×2 LCD
4×4 Matrix Keypad

*Software Requirements*
Embedded C
Keil µVision
Flash Magic
Proteus (optional)
Serial Terminal

*Pin Configuration*
LCD (8-bit mode)
RS → P0.10
RW → P0.11
EN → P0.12
D0–D7 → P1.16–P1.23

Keypad
Rows → P1.24–P1.27
Columns → P1.28–P1.31

UART
TXD → P0.0
RXD → P0.1

ADC
LM35 → AD0.1 (P0.28)

Alert Outputs
LED → P0.17
Buzzer → P0.16

*Working Principle*
System initializes UART, RTC, ADC, LCD, and GPIO.
LM35 temperature is read through ADC.
Current time and date are taken from RTC.
Temperature and timestamp are shown on LCD every second.
Data is sent to PC through UART at regular intervals.
If temperature exceeds set point (example: 45°C), alert is activated.
When push button is pressed, system enters Edit Mode.
User can modify time/date and temperature set point using keypad.
After exit, system returns to normal monitoring.

*Serial Output Format*
Normal condition
[INFO] Temp: 32.5°C @ 13:45:20 13/05/2025

Over-temperature
[ALERT] Temp: 47.3°C @ 14:10:55 13/05/2025 - OVER TEMP!

Edit mode
*** Time Editing Mode Activated ***

*LCD Display Format*
Normal display
HH:MM:SS    DAY
DD/MM/YY   T: XX°C

Edit menu
EDIT RTC INFO
SET POINT  EXIT

*Future Improvements*
SD card data storage
IoT cloud monitoring
GSM alert message
Multiple sensor support
Low power mod
