
/*
  Blink
  The basic Energia example.
  Turns on an LED on for one second, then off for one second, repeatedly.
  Change the LED define to blink other LEDs.
  
  Hardware Required:
  * LaunchPad with an LED
  
  This example code is in the public domain.
*/
//LIBRERIAS
#include <SPI.h>
#include <SD.h>

// most launchpads have a red LED
#define LED GREEN_LED
#define LED1 BLUE_LED
#define LED2 RED_LED
#define boton1 PUSH1

//SPI PINS
#define CSS PA_3 //CHIP SELECT
#define MOSI PA_5
#define MISO PA_4
#define CLOCK PA_2

//Definicion de variables
int recibo = 0;
int start = 1;
char character = 0;//sirve para recibir los archivos de la sd
long long count = 0;

//objeto tipo FILE para leer/escribir archivos
File file;
  
// the setup routine runs once when you press reset:
void setup() {     
  //iniciamos la comunicación serial
  //comunicacion serial
  Serial.begin(115200);
  SPI.setModule(0);//se va a usar el módulo 0
             
  // initialize the digital pin as an output.
  pinMode(LED, OUTPUT);   
  pinMode(boton1, INPUT_PULLUP);
  pinMode(CSS, OUTPUT);
  if (SD.begin(CSS)==0){
    Serial.println("No se pudo iniciar la targeta SD");
  } else {
    Serial.println("Se inició la targeta SD");  
  }
    
  
  
}

// the loop routine runs over and over again forever:
void loop() {
  /*digitalWrite(LED, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);               // wait for a second
  digitalWrite(LED, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);               // wait for a second
  */
  if (start==1){
    start = 0;
    Serial.println("Bienvenido a la interfaz proto-gráfica");
    Serial.println("MENÚ:");
    Serial.println("1. Mostrar Mario");
    Serial.println("2. Mostrar Link");
    Serial.println("3. Mostrar Link2");
    Serial.println("Escriba el número de la opción que desea mostrar: ");
    while (1){
      if (Serial.available()==1){
        recibo = Serial.read();
        break;
      }
      }; //esperamos a que reciba datos    
    Serial.println(recibo);
    //DETERMINAMOS CUÁL OPCIÓN SE SELECCIONÓ
    if (recibo==49){
      file = SD.open("mario.txt", FILE_READ); //LEER EL ARCHIVO mario.txt
      if (file){
        while (1){
          character = file.read();
          count++;
          if (count==528){
            count=0;
            break;
          }
          Serial.print(character);          
        }
      }else{
        Serial.println("No se pudo abrir el archivo (read)");
      }
      file.close(); //cerramos el archivo
      
    }
    if (recibo==50){
      file = SD.open("link.txt", FILE_READ); //LEER EL ARCHIVO link.txt
      if (file){
        while ((character = file.read())!=-1){
          Serial.print(character);
          count++;
          if (count==671){
            count=0;
            break;
          }
        }
      }else{
        Serial.println("No se pudo abrir el archivo (read)");
      }
      file.close(); //cerramos el archivo
      
    }
    if (recibo==51){
      file = SD.open("best.txt", FILE_READ); //LEER EL ARCHIVO MARIO.TXT
      if (file){
        while ((character = file.read())!=-1){ //leemos cada caracter y lo imprimimos en pantalla
          Serial.print(character);
          count++;
          if (count==445){
            break;
          }
        }
      }else{
        Serial.println("No se pudo abrir el archivo (read)");
      }
      file.close(); //cerramos el archivo
      
    }
    
  }
  if (digitalRead(boton1)==0){
    delay(10);
    start=1;
  }

  
 
}
