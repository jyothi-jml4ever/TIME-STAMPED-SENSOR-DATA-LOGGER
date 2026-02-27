**OVERVIEW**

	This project is a real-time temperature monitoring and logging system using the LPC2148 ARM7 microcontroller.

	The system reads temperature from the LM35 sensor through the ADC and gets the current date and time from the on-chip RTC. Each temperature reading is tagged with a 			timestamp, displayed on a 16×2 LCD, and sent to a PC through UART.

	A keypad and push switch allow the user to edit the RTC time and temperature set point. If the temperature exceeds the limit, the LED and buzzer turn ON as an alert.


**OBJECTIVE**

	To continuously monitor temperature and maintain a reliable, time-stamped log of readings for analysis, fault detection, and historical tracking in embedded and industrial environments.


**BLOCK DIAGRAM**


![TIME-STAMPED SENSOR DATA LOGGER](https://github.com/user-attachments/assets/0fe15f43-5463-483b-a9fa-9d3c4b2fd42e)



**HARDWARE REQUIREMENTS**

	•LPC2148 microcontroller 

	•LM35 temperature sensor  

	•16×2 LCD display  

	•matrix keypad 

	•push button switch 

	•LED or buzzer 

	•MAX232 level converter 

	•regulated power supply 

	•connecting circuitry.


**SOFTWARE REQUIREMENTS**

	•Embedded C programming 

	•Keil µVision compiler  

	•Flash Magic for programming the controller  

	•A serial terminal application such as Hyper Terminal for viewing logs.

	•Proteus 8 Professional software is used for virtual circuit simulation.


**WORKING PRINCIPLE**

	•After power-up, the LPC2148 initializes UART, RTC, ADC, LCD, keypad, and GPIO. 

	•During normal operation, the controller periodically reads temperature from the LM35, fetches the current time from the RTC, and formats the data. 

	•The information is displayed on the LCD every second and transmitted to the PC at defined intervals.

	•If the temperature exceeds the user-defined threshold, the system activates the LED/Buzzer and sends an alert message.

	•When the push button is pressed, the system enters edit mode, allowing the user to modify RTC time/date or the temperature set point using the keypad, after which normal monitoring resumes.


**SERIAL DATA OUTPUT**

	Normal condition messages are transmitted in a formatted log showing temperature and timestamp. When the temperature crosses the set limit, the message includes an alert indication. During RTC editing, the terminal displays a dedicated edit-mode notification for user awareness.


**FEATURES**

	•Real-time temperature sensing

	•Accurate RTC time stamping

	•Continuous LCD monitoring

	•Periodic UART data logging

	•Over-temperature alert mechanism

	•Keypad-based RTC and set-point editing

	•Reliable embedded operation


**APPLICATIONS**

	•Industrial temperature monitoring systems

	•environmental data loggers

	•laboratory experiments

	•equipment safety monitoring

	•academic embedded system projects


**AUTHOR**

Jyothi Priya
