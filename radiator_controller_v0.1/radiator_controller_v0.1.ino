#include <OneWire.h> //Se importan las librerías
#include <DallasTemperature.h>

#define RELAY 2
#define TEMP 3 //Se declara el pin donde se conectará la DATA
#define NUMBER_OF_SAMPLES 1
#define MAX_TEMP_THRESHOLD 22
#define MIN_TEMP_THRESHOLD 18

float acc = 0.0;
int sampleIndex = 0;

OneWire ourWire(TEMP); //Se establece el pin declarado como bus para la comunicación OneWire

DallasTemperature sensors(&ourWire); //Se instancia la librería DallasTemperature


void setup() {
  // Inicializa el pin digital relay (que vale 2)  como salida
  pinMode(RELAY, OUTPUT);
  Serial.begin(9600);
  sensors.begin(); //Se inician los sensores
}

void loop() {
  if(sampleIndex < NUMBER_OF_SAMPLES){
    sensors.requestTemperatures(); //Prepara el sensor para la lectura
    acc += sensors.getTempCByIndex(0); //Se lee la temperatura en grados Celsius
    sampleIndex++;
  } else {
    float averageTemp = acc / NUMBER_OF_SAMPLES;
    Serial.print(averageTemp); //Se lee e imprime la temperatura en grados Celsius
    Serial.println(" grados Centigrados");
    if(averageTemp < MIN_TEMP_THRESHOLD && digitalRead(RELAY) == LOW){
      digitalWrite(RELAY, HIGH);   // Envia el valor HIGH (5V) al pin digital relay
    } else if(averageTemp >= MAX_TEMP_THRESHOLD && digitalRead(RELAY) == HIGH){
       digitalWrite(RELAY, LOW);
    }
    acc = 0;
    sampleIndex = 0;
  }
}
