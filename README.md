# submarine
this is an attempt to build the electronic circuit for a submarine with an Arduino nano 33 IoT.
In this Project I make use of the bmp280 to meassure the temperature and air pressure,
The DHT11 to meassure the humidity and also the temperature for redundancy.
An IRF510 transistor as a switch to turn on a ventilator.
there is also a use for an MPU6050 gyroscope to indicate with some leds in wich position the submarine is floating

# arduino
in the file submarinePinOut.txt you will find the pins that I used and to what they are connectedpin	
A4=SDA	SDA
A5=SCL	SCL
Vin	
GND	
2	led under
3	led mid
4	led left
5	led up
6	led right
7	DHT data
8	onled
9	ventilator
10	alarmled

# gyro
the gyro indacates the floating position in most cases its centered
![alt text](https://raw.githubusercontent.com/kiwiton/submarine/blob/master/submarine.jpg)
