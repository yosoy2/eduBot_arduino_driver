#include <Arduino.h>

// Motor A
int ENA = 11;
int IN1 = 10;
int IN2 = 12;

// Motor B
int ENB = 5;
int IN3 = 7;
int IN4 = 6;

// Grove buzzer
int buzzer = 4;

// Hall encoder right, motor A
volatile unsigned int temp_right, counter_right = 0; //This variable will increase or decrease depending on the rotation of encoder

// Hall encoder left, motor B
volatile unsigned int temp_left, counter_left = 0;

void Adelante ()
{
 //Direccion motor A
 digitalWrite (IN1, HIGH);
 digitalWrite (IN2, LOW);
 analogWrite (ENA, 255); //Velocidad motor A
 //Direccion motor B
 digitalWrite (IN3, HIGH);
 digitalWrite (IN4, LOW);
 analogWrite (ENB, 255); //Velocidad motor B
}

void Atras ()
{
 //Direccion motor A
 digitalWrite (IN1, LOW);
 digitalWrite (IN2, HIGH);
 analogWrite (ENA, 255*1); //Velocidad motor A
 //Direccion motor B
 digitalWrite (IN3, LOW);
 digitalWrite (IN4, HIGH);
 analogWrite (ENB, 255*1); //Velocidad motor B
}

void Derecha ()
{
 //Direccion motor A
 digitalWrite (IN1, HIGH);
 digitalWrite (IN2, LOW);
 analogWrite (ENA, 255); //Velocidad motor A
 //Direccion motor B
 digitalWrite (IN3, LOW);
 digitalWrite (IN4, HIGH);
 analogWrite (ENB, 0); //Velocidad motor A
}

void Izquierda ()
{
 //Direccion motor A
 digitalWrite (IN1, LOW);
 digitalWrite (IN2, HIGH);
 analogWrite (ENA, 0); //Velocidad motor A
 //Direccion motor B
 digitalWrite (IN3, HIGH);
 digitalWrite (IN4, LOW);
 analogWrite (ENB, 255); //Velocidad motor A
}

void Parar ()
{
 //Direccion motor A
 digitalWrite (IN1, LOW);
 digitalWrite (IN2, LOW);
 analogWrite (ENA, 0); //Velocidad motor A
 //Direccion motor B
 digitalWrite (IN3, LOW);
 digitalWrite (IN4, LOW);
 analogWrite (ENB, 0); //Velocidad motor A
}

void linear_speed(float x)
{
  if(x>0){
    // Sentido positivo, hacia adelante
    //Direccion motor A
    digitalWrite (IN1, HIGH);
    digitalWrite (IN2, LOW);
    analogWrite (ENA, 255*x); //Velocidad motor A
    //Direccion motor B
    digitalWrite (IN3, HIGH);
    digitalWrite (IN4, LOW);
    analogWrite (ENB, 255*x); //Velocidad motor B
  }
  else if(x<0){
    // Sentido negativo, hacia atras
    digitalWrite (IN1, LOW);
    digitalWrite (IN2, HIGH);
    analogWrite (ENA, 255*x); //Velocidad motor A
    //Direccion motor B
    digitalWrite (IN3, LOW);
    digitalWrite (IN4, HIGH);
    analogWrite (ENB, 255*x); //Velocidad motor B
  }
  else{
    // Se detiene
    Parar();
  }
}

void angular_speed(float w){
  // Sentido positivo, en contra del reloj
  if(w>0){
  }
  // Sentido negativo, a favor del reloj
  else if(w<0){
  }
  else{
  Parar();
  }
}

  void ai2() {
  if(digitalRead(3)==LOW){
  counter_left++;
  }else{
  counter_left--;
  }
  }

  void ai3() {
  if(digitalRead(2)==LOW){
  counter_left--;
  }else{
  counter_left++;
  }
  }

  void ai8() {
  // ai8 is activated if DigitalPin nr 2 is going from LOW to HIGH
  // Check pin 3 to determine the direction
  if(digitalRead(9)==LOW) {
  counter_right--;
  }else{
  counter_right++;
  }
  }

  void ai9() {
  // ai8 is activated if DigitalPin nr 3 is going from LOW to HIGH
  // Check with pin 2 to determine the direction
  if(digitalRead(8)==LOW) {
  counter_right++;
  }else{
  counter_right--;
  }
  }

  void leftEncoder_read() {
    if( counter_left != temp_left ){
    SerialUSB.print ("counter_left: ");
    SerialUSB.println (counter_left);
    //digitalWrite(LED_BUILTIN, HIGH);
    temp_left = counter_left;
    }
    //digitalWrite(LED_BUILTIN, LOW);
  }

  void rightEncoder_read() {
    if( counter_right != temp_right ){
    SerialUSB.print ("counter_right: ");
    SerialUSB.println (counter_right);
    //digitalWrite(LED_BUILTIN, HIGH);
    temp_right = counter_right;
    }
    //digitalWrite(LED_BUILTIN, LOW);
  }

  void setup() {

     // Declarar la velocidad del puerto serial
   SerialUSB.begin(250000);

   // RIGHT ENCODER
      // Declarar las resistencias internas de los pines 9 y 8
   pinMode(8, INPUT_PULLUP);
   pinMode(9, INPUT_PULLUP);
      // Interruptores
  attachInterrupt(8, ai8, RISING);
  attachInterrupt(9, ai9, RISING);

   // LEFT ENCODER
      // Declarar las resistencias internas de los pines 2 y 3
   pinMode(2, INPUT_PULLUP);
   pinMode(3, INPUT_PULLUP);
      // Interruptores
  attachInterrupt(2, ai2, RISING);
  attachInterrupt(3, ai3, RISING);

     // Declaramos todos los pines como salidas
   pinMode (ENA, OUTPUT);
   pinMode (ENB, OUTPUT);
   pinMode (IN1, OUTPUT);
   pinMode (IN2, OUTPUT);
   pinMode (IN3, OUTPUT);
   pinMode (IN4, OUTPUT);

   // Iniciar pin del buzzer como salida
   pinMode(buzzer,OUTPUT);

   digitalWrite(buzzer, HIGH);
   delay(100);
   digitalWrite(buzzer, LOW);
   delay(100);
   analogWrite(buzzer, 120);
   delay(100);
   analogWrite(buzzer,0);
   delay(100);
   analogWrite(buzzer, 255);
   delay(100);
   analogWrite(buzzer,0);
   delay(100);

   // Inicio
   SerialUSB.println("---START---");
   delay(50);
   SerialUSB.println("---START---");
   delay(50);
   SerialUSB.println("---START---");
   delay(50);
   SerialUSB.println("---START---");
   delay(50);
   SerialUSB.println("---START---");
   delay(50);
   SerialUSB.println("---START---");
   delay(50);
   SerialUSB.println("---START---");
   delay(50);
   SerialUSB.println("---START---");
   delay(50);

   while(!SerialUSB){
      ;
   }
  }

  void loop() {
    // Send the value of counter
   //leftEncoder_read();
   //rightEncoder_read();

   if(SerialUSB.available()>0){
     char option = SerialUSB.read();
     if (option >= '1' && option <= '2'){
       linear_speed(1);
     }
     else if (option >= '3' && option <= '4'){
       Atras();
     }
     else if (option >= '5' && option <= '6'){
       Derecha();
     }
     else if (option >= '7' && option <= '8'){
       Izquierda();
     }
     else{
       Parar();
     }
   }
   }
