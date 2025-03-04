#include <LiquidCrystal.h>
#include <Servo.h>

int estadoActual1=0;
int estadoActual2=0;
int estadoUltimo=0;
int contador=0;
float radioEnCm=5.0;   //ingresar radio de la rueda en cm
float pi=3.1416;
float perimetroRueda=2*pi*(radioEnCm/100);  //Calcula Perimetro en metros
float distRecorrida=0;
float distKM=0;
int tiempo1=0;
int tiempo2=0;
int tiempo3=0;
float tiempo4=0;
float velocidad=0;
float velocidad2=0;

LiquidCrystal lcd(7, 8, 9, 10, 11 , 12);
unsigned long time = 0;


Servo myservo;  //creamos un objeto servo 
int angulo;

void setup(){
        myservo.attach(4); 
        pinMode(3,INPUT);
        Serial.begin(9600);
        lcd.begin(16,2);

        time = millis();
}

void loop(){

      angulo= 90;
        myservo.write(angulo);
        Serial.print("ángulo:  ");
        Serial.println(angulo);
        delay(2000); 

      lcd.clear();
      lcd.write("V=");
        if (velocidad > 0) {
          lcd.print(velocidad);
        }else{
          lcd.write("0");
        }
      lcd.write("Km/h");
      lcd.setCursor(0,1);
      if(distRecorrida<=999){
        lcd.write("D=");
        lcd.print(distRecorrida);
        lcd.write("m");
      }else{
        lcd.write("D=");
        lcd.print(distKM);
        lcd.write("Km");
                      }

        estadoActual1=digitalRead(3);
        delay(10);
        estadoActual2=digitalRead(3);
//Si los estados no son iguales, el sketch no hace gran cosa
        if (estadoActual1 == estadoActual2) {
              if (estadoActual1 != estadoUltimo){
                    if (estadoActual1 == HIGH) {
                        contador = contador + 1;
                        Serial.print ("Vueltas ");
                        Serial.println(contador);
                        distancia();
                        VEL();
                    }
              }
        }
        estadoUltimo= estadoActual1;
              

        if (millis()-time > 1500){  // aca la reseteas cada 10 seg
          if (velocidad == velocidad2){
            velocidad=0;
            distRecorrida=0;
            contador = -1;
          }
          velocidad2 = velocidad;
		      time = millis();
	      }
}


void distancia(){
                        distRecorrida=perimetroRueda*contador;
                        distKM=distRecorrida/1000;
                        if(distRecorrida<=999){
                                Serial.print("Distancia recorrida en m= ");
                                Serial.println(distRecorrida);
                        }
                        else{
                                Serial.print("Distancia recorrida en Km= ");
                                Serial.println(distKM);
                        }
                        }

void VEL(){
        if (contador%2 == 0 ) {
              tiempo1=millis();
        }
        else {
              tiempo2=millis();
        }
        tiempo3=abs(tiempo2-tiempo1); //hay que pasar el tiempo a hrs
        tiempo4=(((tiempo3/1000.0)/60.0)/60.0);
        velocidad=((perimetroRueda/1000)/tiempo4);
        Serial.print(" tiempo1= ");
        Serial.print(tiempo1);
        Serial.print("tiempo2= ");
        Serial.print(tiempo2);
        Serial.print(" tiempo3= ");
        Serial.print(tiempo3);
        Serial.print(" tiempo4= ");
        Serial.println(tiempo4);
        Serial.print("velocidad= ");
        Serial.println(velocidad);        
}

void PantallaLCD(){
            lcd.clear();
            lcd.write("V=");
            if (velocidad > 0) {
              lcd.print(velocidad);
            }else{
              lcd.write("0");
            }
            lcd.write("Km/h");
            lcd.setCursor(0,1);
                        if(distRecorrida<=999){
                                lcd.write("D=");
                                lcd.print(distRecorrida);
                                lcd.write("m");
                        }
                        else{
                                lcd.write("D=");
                                lcd.print(distKM);
                                lcd.write("Km");
                        }
            return;
}