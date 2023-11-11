#include <Wire.h>                                                         //  LIBRERÍA PARA LCD
#include <LiquidCrystal_I2C.h>                                            //  INCLUIMOS LIBRERÍA PARA LCD
#include <Adafruit_GFX.h>                                                 //  INCLUIMOS LIBRERÍA PARA GRÁFICOS DE LCD
LiquidCrystal_I2C lcd (0x27, 20, 4);                                      //  DEFINIMOS TIPO DE LCD

#include <Keypad.h>                                                       //  INCLUIMOS LIBRERÍA PARA KEYPAD

#include <DHT.h>                                                          //  INCLUIMOS LIBRERÍA PARA DHT
#include <DHT_U.h>                                                        //  INCLUIMOS LIBRERÍA ADICIONAL DE DHT
#define DHTPIN 11                                                         //  DEFINIMOS EL PIN DIGITAL PARA EL SENSOR DHT11
#define DHTTYPE DHT11                                                     //  DEFINIMOS EL TIPO DE SENSOR (DTH11)

DHT dht11(DHTPIN, DHTTYPE);                                               //  INICIALIZAMOS EL SENSOR DHT11

int LedRecibidor = 2;                                                     //  LED DE RECIBIDOR
int LedSalon = 3;                                                         //  LED DEL SALÓN
int LedCocina = 4;                                                        //  LED DE LA COCINA
int LedBano = 5;                                                          //  LED DEL BAÑO
int LedHab1 = 6;                                                          //  LED DE HABITACIÓN 1
int LedHab2 = 7;                                                          //  LED DE HABITACIÓN 2
int LedHab3 = 8;                                                          //  LED DE HABITACIÓN 3
int LedHab4 = 9;                                                          //  LED DE HABITACIÓN 4
int SensorPuerta = 10;                                                    //  SENSOR DE PUERTA

int SensorLlama = 12;                                                     //  SENSOR DE LLAMA
int SensorVolumetrico = 13;                                               //  SENSOR VOLUMÉTRICO/MOVIMIENTO
int Buzzer = 14;
int LedRojoAlarma = 15;                                                   //  LED DE ALARMA DE ZUMBADOR
int BotonEmergencia = 16;                                                 //  BOTÓN DE EMERGENCIA - PÁNICO
int LedRojoCalor = 17;                                                    //  LED ROJO INDICA QUE LA CALEFACCIÓN ESRTÁ ENCENDIDA
int LedAzulFrio = 18;                                                     //  LED AZUL INDICA QUE EL AIRE ACONDICIONADO ESTÁ ENCENDIDO
int SensorInundacion = 19;                                                //  SENSOR DE INUNDACIÓN
const byte ROWS = 4;                                                      //  FILAS DEL TECLADO
const byte COLS = 4;                                                      //  COLUMNAS DEL TECLADO

char keys[ROWS][COLS] = {                                                 //  MAPEO DEL TECLADO
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {29, 28, 27, 26};                                    //  DEFINICIÓN DE PINES POR FILA TECLADO
byte colPins[COLS] = {25, 24, 23, 22};                                    //  DEFINICIÓN DE PINES POR COLUMNA TECLADO

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

String entrada;                                                           //  VARIABLE PARA TECLA
String modo = "inicio";                                                   //  VARIABLE PARA EL MODO DE ALARMA
String pass = "1234";                                                     //  PASSWORD POR DEFECTO

void setup() {

  Serial.begin (9600);                                                    //  INICIALIZAMOS COMUNICACIÓN DE SERIE
// DECLARAMOS LOS LEDS COMO SALIDAS
  pinMode (2, OUTPUT);                                                    //  LED RECIBIDOR 
  pinMode (3, OUTPUT);                                                    //  LED SALON
  pinMode (4, OUTPUT);                                                    //  LED COCINA
  pinMode (5, OUTPUT);                                                    //  LED BAÑO
  pinMode (6, OUTPUT);                                                    //  LED HABITACION 1
  pinMode (7, OUTPUT);                                                    //  LED HABITACION 2
  pinMode (8, OUTPUT);                                                    //  LED HABITACION 3
  pinMode (9, OUTPUT);                                                    //  LED HABITACIÓN 4 
  pinMode (10, INPUT);                                                    //  ENTRADA DEL SENSOR DE PUERTA
  pinMode (12, INPUT);                                                    //  ENTRADA DEL SENSOR DE LLAMA
  pinMode (13, INPUT);                                                    //  ENTRADA DEL SENSOR VOLUMÉTRICO/MOVIMIENTO
  pinMode (14, OUTPUT);                                                   //  SALIDA DEL ZUMBADOR 
  pinMode (15, OUTPUT);                                                   //  SALIDA DE LED DE ZUMBADOR
  pinMode (16, INPUT);                                                    //  ENTRADA DEL PULSADOR DE EMERGENCIA/PÁNICO
  pinMode (17, OUTPUT);                                                   //  SALIDA DE LED ROJO DE CALEFACCIÓN
  pinMode (18, OUTPUT);                                                   //  SALIDA DE LED AZUL DE AIRE ACONDICIONADO
  pinMode (19, INPUT);                                                    //  ENTRADA DEL SENSOR DE INUNDACIÓN/NIVEL DE AGUA
  lcd.init();
  lcd.init();
  lcd.begin (16,2);                                                       //  DECLARAMOS LCD
  lcd.setContrast(50);                                                    //  CONTRASTE
  lcd.backlight ();                                                       //  
  lcd.print ("CASA DOMOTICA");                                            //  MENSAJE DE ARRANQUE DEL SISTEMA EN PANTALLA
  lcd.setCursor(0, 0);                                                    //  MENSAJE DE ARRANQUE DEL SISTEMA EN PANTALLA
  delay (2000);                                                           //  2 SEGUNDOS DE ESPERA PARA CAMBIAR MENSAJE
  lcd.clear ();                                                           //  LIMPIAMOS  LCD
  lcd.setCursor(0, 0);
  lcd.print ("BIENVENIDO");                                               //  MODO  ALARMA POR DEFECTO (DESACTIVADO)
  lcd.setCursor(0, 1);                                                    //  MENSAJE DE ARRANQUE DEL SISTEMA EN PANTALLA
  lcd.print("MANUEL SABIO");                                              //  MENSAJE DE ARRANQUE DEL SISTEMA EN PANTALLA
  
  delay(1500);
  dht11.begin();                                                          //  COMENZAMOS EL SENSOR DHT


}

void loop ()
{
  
  char key = keypad.getKey();

    if (key) {
    if (key == 'A');
    tone(14, 4000, 10);
  }

  //  ACTIVAR ALARMA
  if (modo == "armar") {
    if (key) {
      entrada += key;  

      if (key != 'A' and key != 'B' and key != 'C' and key != 'D') {      //  INDICAMOS QUE SI LAS TECLAS PULSADAS NO SON LETRAS, SE OCULTEN
        lcd.print('*');                                                  //  IMPRIMIMOS ASTERÍSCOS PARA OCULTAR LA CLAVE DIGITADA
        tone(14, 4750, 10);
      }
      if (key == 'B') {                                                   //  TECLA CON FUNCIÓN DE BORRAR LO DIGITADO
        tone(14, 3250, 10);
        lcd.setCursor(0, 1);
        lcd.print("                ");
        lcd.setCursor(0, 1);
        entrada = "";
      }
      if (key == 'A') {                                                   //  TECLA CON FUNCIÓN DE ACTIVAR LA ALARMA
        tone(14, 3750, 10);
        entrada = entrada.substring(0, entrada.length() - 1);
        if (entrada == pass) {
          activacion();
          escribir("ACTIVADA", 0, 0);

          digitalWrite(2, HIGH);                              //ACTIVAMOS LUZ PRESENCIA DURANTE UN MINUTO
          delay(2000);                                        //TIEMPO 1 MINUTO
          digitalWrite(2, LOW);                               //APAGAMOS LUZ PRESENCIA PASADO UN MINUTO
          digitalWrite(3, HIGH);                              //ACTIVAMOS LUZ PRESENCIA DURANTE UN MINUTO
          delay(2000);                                        //TIEMPO 1 MINUTO
          digitalWrite(3, LOW);                               //APAGAMOS LUZ PRESENCIA PASADO UN MINUTO
          digitalWrite(4, LOW);                               //APAGAMOS LEDS DEL PISO
          digitalWrite(5, LOW);                               //APAGAMOS LEDS DEL PISO
          digitalWrite(6, LOW);                               //APAGAMOS LEDS DEL PISO
          digitalWrite(7, LOW);                               //APAGAMOS LEDS DEL PISO
          digitalWrite(8, LOW);                               //APAGAMOS LEDS DEL PISO
          digitalWrite(9, LOW);                               //APAGAMOS LEDS DEL PISO
                
          modo = "activa";
          key = '\0';
          entrada = "";
        } 
        else {
          escribir("ERROR!", 5, 0);
          entrada = "";
          digitalWrite(15, HIGH);
          tone(14, 450, 150);
          delay(150);
          tone(14, 250, 300);
          delay(300);
          digitalWrite(15, LOW);
          armar();
        }
      }
      if (key == 'D') {                                                   //
        tone(14, 1750, 10);
        modo = "inicio";
        escribir("DESACTIVADO", 0, 0);
      }
    }
  }

  //  INICIO
  if (modo == "inicio") {

    float RH = dht11.readHumidity();                                         //  LEEMOS LA HUMEDAD RELATIBA
    delay(50);
    float Temp = dht11.readTemperature();                                    //  LEEMOS LA TEMPERATURA EN GRADOS CENTÍGRADOS (POR DEFECTO)
    delay(50);

    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("TEMP: ");
    lcd.setCursor(7, 0);
    lcd.print(Temp);

    lcd.setCursor(0, 1);
    lcd.print("HUME: ");
    lcd.setCursor(7, 1);
    lcd.print(RH);

    if (Temp < 24) {                                                //TEMPERATURA MENOR 24 GRADOS
      digitalWrite(17, HIGH);                                       //ENCENDEMOS CALOR
      digitalWrite(18, LOW);                                        //APAGAMOS FRIO
    }
    if (Temp > 25) {                                                //TEMPERATURA MAYOR 25 GRADOS
      digitalWrite(17, LOW);                                        // APAGAMOS CALOR
      digitalWrite(18, HIGH);                                       // ENCENDEMOS FRIO
    }
    if (Temp > 24 && Temp < 25) {                                   //TEMPERATURA ENTRE 24 Y 25 GRADOS
      digitalWrite(17, LOW);                                        //APAGAMOS CALOR
      digitalWrite(18, LOW);                                        //APAGAMOS FRIO
    }

    if (digitalRead(12) == LOW) {                     //  ACTIVAMOS SENSOR DE LLAMA
      lcd.clear();
      lcd.setCursor(6,0);
      lcd.print("ALERTA");                            //IMPRIMIMOS EN PANTALLA ALERTA FUEGO !!
      lcd.setCursor(6, 1);
      lcd.print("FUEGO!");                            //IMPRIMIMOS EN PANTALLA ALERTA FUEGO !!
      tone(14, 1108, 50);
      delay(15);
      delay(15);
      tone(14, 1174, 50);
      delay(15);
      tone(14, 1318, 50);
      delay(15);
      tone(14, 1396, 50);
      delay(15);
      delay(15);
      tone(14, 1479, 50);
      delay(15);
      delay(15);
      digitalWrite(15, HIGH);                         //ENCENDEMOS LED ROJO DE ALARMA PARPADEANDO
      delay(200);
      digitalWrite(15, LOW);                          //APAGAMOS LED ROJO DE ALARMA HACIENDO PARPADEO
      delay(200);
    }
    else {
      digitalWrite(14, LOW);                          //DESACTIVAMOSBUZZER MIENTRAS SUENA LA ALARMA
    }

    if (digitalRead(16) == HIGH) {                  //  PULSADOR
      lcd.clear();
      lcd.setCursor(3,0);
      lcd.print("EMERGENCIA");                      //ALERTA DE FUEGO EN PANTALLA 
      tone(14, 1000, 500);
      delay(100);
      tone(14, 1750, 500);
      delay(100);
      tone(14, 1500, 500);
      delay(100);
      tone(14, 1000, 500);
      delay(100);
      digitalWrite(15, HIGH);                     //ENCENDEMOS LED ROJO DE ALARMA PARPADEANDO
      delay(200);
      digitalWrite(15, LOW);                      //APAGAMOS LED ROJO DE ALARMA HACIENDO PARPADEO
      delay(200);
    }
    else {
      digitalWrite(14, LOW);                      //DESACTIVAMOSBUZZER MIENTRAS SUENA LA ALARMA
    }

    if (digitalRead(19) == LOW) {                  //  INUNDACIÓN
      lcd.clear();
      lcd.setCursor(6,0);
      lcd.print("ALERTA");
      lcd.setCursor(3, 1);
      lcd.print("INUNDACION");
      tone(14, 1108, 50);
      delay(15);
      delay(15);
      tone(14, 1174, 50);
      delay(15);
      tone(14, 1318, 50);
      delay(15);
      tone(14, 1396, 50);
      delay(15);
      delay(15);
      tone(14, 1479, 50);
      delay(15);
      delay(15);
      digitalWrite(15, HIGH);
      delay(200);
      digitalWrite(15, LOW);
      delay(200);
    }
    else {
      digitalWrite(14, LOW);
    }

    if (key) {
      if (key == '1') {
        digitalWrite(6, HIGH);
      }
      if (key == '2') {
        digitalWrite(6, LOW);
      }
      if (key == '4') {
        digitalWrite(7, HIGH);
      }
      if (key == '5') {
        digitalWrite(7, LOW);
      }
      if (key == '7') {
        digitalWrite(8, HIGH);
      }
      if (key == '8') {
        digitalWrite(8, LOW);
      }
      if (key == '*') {
        digitalWrite(9, HIGH);
      }
      if (key == '0') {
        digitalWrite(9, LOW);
      }
      if (key == '3') {
        digitalWrite(2, HIGH);
      }
      if (key == '6') {
        digitalWrite(3, HIGH);
      }
      if (key == 'B') {
        digitalWrite(2, LOW);
        digitalWrite(3, LOW);
      }
      if (key == '9') {
        digitalWrite(4, HIGH);
      }
      if (key == '#') {
        digitalWrite(5, HIGH);
      }
      if (key == 'D') {
        digitalWrite(4, LOW);
        digitalWrite(5, LOW);
      }
      if (key == 'A') {
        tone(14, 4000, 10);
        modo = "armar";
        armar();
      }
      if (key == 'C') {
        tone(14, 2500, 10);
        modo = "cambiarpass";
        key = '\0';
        cambiarPass();
      }
    }
  }

  // ALARMA ACTIVA
  if (modo == "activa") {

    float RH = dht11.readHumidity();                                         //  LEEMOS LA HUMEDAD RELATIBA
    delay(50);
    float Temp = dht11.readTemperature();                                    //  LEEMOS LA TEMPERATURA EN GRADOS CENTÍGRADOS (POR DEFECTO)
    delay(50);

    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("TEMP: ");
    lcd.setCursor(7, 0);
    lcd.print(Temp);
    delay(50);

    lcd.setCursor(0, 1);
    lcd.print("HUME: ");
    delay(50);
    lcd.setCursor(7, 1);
    lcd.print(RH);
    delay(50);

    if (Temp < 24) {
      digitalWrite(17, HIGH);
      digitalWrite(18, LOW);
    }
    if (Temp > 25) {
      digitalWrite(17, LOW);
      digitalWrite(18, HIGH);
    }
    if (Temp > 24 && Temp < 25) {
      delay(500);
      digitalWrite(17, LOW);
      digitalWrite(18, LOW);
    }
    
    if (digitalRead(10) == HIGH) {                    //  ACTIVAMOS SENSOR DE PUERTA
      lcd.clear();
      lcd.setCursor(6,0);
      lcd.print("ALERTA");
      lcd.setCursor(2, 1);
      lcd.print("PUERTA ABIERTA");
      tone(14, 1108, 50);
      delay(15);
      delay(15);
      tone(14, 1174, 50);
      delay(15);
      tone(14, 1318, 50);
      delay(15);
      tone(14, 1396, 50);
      delay(15);
      delay(15);
      tone(14, 1479, 50);
      delay(15);
      delay(15);
      digitalWrite(15, HIGH);     //ACTIVAMOS LED ALARMA PARPADEO
      delay(200);
      digitalWrite(15, LOW);      //DESACTIVAMOS LED ALARMA
      delay(200);
    }
    else {
      digitalWrite(14, LOW);      //PARAMOS ALARMA BUZZER
    }
    


    if (digitalRead(12) == LOW) {                         //  ACTIVAMOS SENSOR DE LLAMA
      lcd.clear();
      lcd.setCursor(6,0);
      lcd.print("ALERTA");
      lcd.setCursor(6, 1);
      lcd.print("FUEGO!");
      tone(14, 1108, 50);
      delay(15);
      delay(15);
      tone(14, 1174, 50);
      delay(15);
      tone(14, 1318, 50);
      delay(15);
      tone(14, 1396, 50);
      delay(15);
      delay(15);
      tone(14, 1479, 50);
      delay(15);
      delay(15);
      digitalWrite(15, HIGH);
      delay(200);
      digitalWrite(15, LOW);
      delay(200);
    }
    else {
      digitalWrite(14, LOW);
    }

    if (digitalRead(13) == HIGH) {                              //  ACTIVAMOS SENSOR VOLUMÉTRICO
      lcd.clear();
      lcd.setCursor(6,0);
      lcd.print("ALERTA");
      lcd.setCursor(4,1);
      lcd.print("INTRUSO!");
      tone(14, 1108, 50);
      delay(15);
      delay(15);
      tone(14, 1174, 50);
      delay(15);
      tone(14, 1318, 50);
      delay(15);
      tone(14, 1396, 50);
      delay(15);
      delay(15);
      tone(14, 1479, 50);
      delay(15);
      delay(15);
      digitalWrite(15, HIGH);
      delay(200);
      digitalWrite(15, LOW);
      delay(200);
    }
    else {
      digitalWrite(14, LOW);
    }

    if (digitalRead(19) == LOW) {                  //  INUNDACIÓN
      lcd.clear();
      lcd.setCursor(6,0);
      lcd.print("ALERTA");
      lcd.setCursor(3,1);
      lcd.print("INUNDACION");
      tone(14, 1108, 50);
      delay(15);
      delay(15);
      tone(14, 1174, 50);
      delay(15);
      tone(14, 1318, 50);
      delay(15);
      tone(14, 1396, 50);
      delay(15);
      delay(15);
      tone(14, 1479, 50);
      delay(15);
      delay(15);
      digitalWrite(15, HIGH);
      delay(200);
      digitalWrite(15, LOW);
      delay(200);
    }
    else {
      digitalWrite(14, LOW);
    }

    if (digitalRead(30) == HIGH) {
      lcd.clear();
      lcd.setCursor(3,0);
      lcd.print("LUZ NOCTURNA");
      lcd.setCursor(4,1);
      lcd.print("ENCENDIDA");
      delay(500);
      digitalWrite(3, HIGH);
      digitalWrite(8, HIGH);
      digitalWrite(6, HIGH);
    }
    else {
      digitalWrite(3, LOW);
      delay(100);
      digitalWrite(8, LOW);
      delay(100);
      digitalWrite(6, LOW);
      delay(100);
    }
    
    if (key) {

      if (key == 'A') {
        tone(14, 4000, 10);
        modo = "desarmar";
        key = '\0';
        desarmar();
      }
    }
  }

  // DESCONECTAR ALARMA
  if (modo == "desarmar") {
    if (key) {
      entrada += key;
      Serial.println(entrada);

      if (key != 'A' and key != 'B' and key != 'C' and key != 'D') {
        //lcd.print(key);
        lcd.print('*');
        tone(14, 4750, 10);
      }
      if (key == 'B') {
        tone(14, 3250, 10);
        lcd.setCursor(0, 1);
        lcd.print("                ");
        lcd.setCursor(0, 1);
        entrada = "";
      }
      if (key == 'A') {
        entrada = entrada.substring(0, entrada.length() - 1);
        tone(14, 4000, 10);
        if (entrada == pass) {
          escribir("DESACTIVADO", 0, 0);
          modo = "inicio";
          key = '\0';
          entrada = "";
          tone(14, 300, 500);
          delay(100);
          tone(14, 500, 500);
        } 
        else {
          escribir("ERROR!", 5, 0);
          entrada = "";
          digitalWrite(15, HIGH);
          tone(14, 450, 150);
          delay(150);
          tone(14, 250, 300);
          delay(300);
          digitalWrite(15, LOW);
          desarmar();
        }
      }
    }
  }

  //  CAMBIAR PASSWORD
  if (modo == "cambiarpass") {
    if (key) {
      entrada += key;
      Serial.println(entrada);

      if (key != 'A' and key != 'B' and key != 'C' and key != 'D') {
        //lcd.print(key);
        lcd.print('*');
        tone(14, 4000, 10);
      }
      if (key == 'B') {
        tone(14, 3250, 10);
        lcd.setCursor(0, 1);
        lcd.print("                ");
        lcd.setCursor(0, 1);
        entrada = "";
      }
      if (key == 'A') {
        entrada = entrada.substring(0, entrada.length() - 1);
        tone(14, 4000, 10);
        if (entrada == pass) {
          repetirPass();
          modo = "repetirPass";
          key = '\0';
          entrada = "";
        } 
        else {
          escribir("ERROR!", 5, 0);
          entrada = "";
          digitalWrite(15, HIGH);
          tone(14, 450, 150);
          delay(150);
          tone(14, 250, 300);
          delay(300);
          digitalWrite(15, LOW);
          cambiarPass();
        }
      }
      if (key == 'D') {
        tone(14, 1750, 10);
        modo = "inicio";
        lcd.clear();
        lcd.print("DESACTIVADO");
      }
    }
  }

  //  REPETIR PASSWORD
  if (modo == "repetirPass") {
    if (key) {
      entrada += key;
      Serial.println(entrada);

      if (key != 'A' and key != 'B' and key != 'C' and key != 'D') {
        //lcd.print(key);
        lcd.print('*');
        tone(14, 4750, 10);
      }
      if (key == 'B') {
        tone(14, 3250, 10);
        lcd.setCursor(0, 1);
        lcd.print("                ");
        lcd.setCursor(0, 1);
        entrada = "";
      }
      if (key == 'A') {
        entrada = entrada.substring(0, entrada.length() - 1);
        tone(14, 4000, 10);
        pass = entrada;
        escribir("MODIFICADO", 3, 0);
        tone(14, 2000, 500);
        delay(100);
        tone(14, 2250, 500);
        delay(2000);
        escribir("DESACTIVADO", 0, 0);
        modo = "inicio";
      }
      if (key == 'D') {
        tone(14, 1750, 10);
        modo = "inicio";
        escribir("DESACTIVADO", 0, 0);
      }
    }
  }
}

void armar() {
  escribir("PASSWORD", 4, 0);
  lcd.setCursor(0, 1);
}
void desarmar() {
  escribir("PASSWORD", 4, 0);
  lcd.setCursor(0, 1);
}
void cambiarPass() {
  escribir("OLD PASSWORD", 2, 0);
  lcd.setCursor(0, 1);
}
void repetirPass() {
  escribir("NEW PASSWORD", 2, 0);
  lcd.setCursor(0, 1);
}
void activacion() {
  tone(14, 2000, 1000);
  escribir("Activado en 3", 0, 0);
  delay(1500);
  tone(14, 2000, 1000);
  escribir("Activado en 2", 0, 0);
  delay(1500);
  tone(14, 2000, 1000);
  escribir("Activado en 1", 0, 0);
  delay(1500);
  tone(14, 2500, 1000);
  delay(1000);
}
void escribir(String text, int col, int fila) {
  lcd.clear();
  lcd.setCursor(col, fila);
  lcd.print(text);
}