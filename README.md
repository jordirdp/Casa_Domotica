# Título
🔗Creado por [Jordi Rodriguez](https://github.com/jordirdp) a partir de un proyecto de Manu Sabio

👨🏻‍💻Práctica de **programación básica** en Arduino  

<img src="/Images/Casa.jpg" width="500"/> 

### Software  
- Programado con [Arduino](https://www.arduino.cc/en/software)
- Se han incluido las siguientes librerías:  
-- Wire.h  
-- Keypad.h  
-- DHT.h & DHT_U.h  
-- [Adafruit GFX](https://github.com/adafruit/Adafruit-GFX-Library)  
-- [LiquidCrystal I2C](https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library)  
- Este código realiza las siguientes funciones simples:  
-- Lectura de sensores domésticos   
-- Control de la domótica del hogar (luces, climatización)  
-- Control de seguridad del hogar (intrusión, inundación, incendio)  
-- Información de estados mediante pantalla LCD  

### Hardware  
- Arduino MEGA  
- 8 x leds para habitaciones  
- Led rojo + led azul para climatización
- Led alarma
- Sensor magnético para puerta
- Sensor de llama
- Sensor volumétrico
- Buzzer
- Sensor de agua
- Sensor de temperatura y humedad (DHT11)
- Pantala LCD 20x4
- Keypad
- Pulsador de emergencia

### Montaje  
<img src="/Images/Construccion 1.jpg" height="300"/> <img src="/Images/Construccion 2.jpg" height="300"/>  <img src="/Images/Construccion 3.jpg" height="300"/>  
<img src="/Images/Construccion 4.JPG" height="403"/> <img src="/Images/Construccion 5.JPG" height="403"/>  <img src="/Images/Construccion 6.JPG" height="403"/> 

🔧Conexiones a pines Arduino UNO:  
- A04 = I2C LCD (SDA)  
- A05 = I2C LCD (SCL)  
- D00 = (RX)  
- D01 = (TX)  
- D02 = Led recibidor  
- D03 = Led salon  
- D04 = Led cocina  
- D05 = Led baño  
- D06 = Led habitación 1  
- D07 = Led habitación 2  
- D08 = Led habitación 3  
- D09 = Led habitación 4  
- D10 = Sensor magnético para puerta  
- D11 = DHT11  
- D12 = Sensor de llama  
- D13 = Sensor volumétrico  
- D14 = Zumbador  
- D15 = Led de alarma  
- D16 = Pulsador de emergencia  
- D17 = Led rojo calefacción  
- D18 = Led azul aire acondicionado
- D19 = Sensor de inundación  

### Licencia  
⚖️Todo el contenido distribuido bajo [licencia GPL-3.0](https://www.gnu.org/licenses/gpl-3.0), salvo indicación expresa.  
Las referencias y librerías empleadas, estarán sujetas a sus propia licencia, y no se incluyen en este repositorio.  
