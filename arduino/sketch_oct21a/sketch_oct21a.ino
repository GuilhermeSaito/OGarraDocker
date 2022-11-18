#include <LiquidCrystal.h>
#include <Stepper.h>
#include <Servo.h>


Servo myservo;


int pos = 0;    // variable to store the servo position
int claw = 0;



const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;//Pinos para ligar o display
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);//Define os pinos que serão usados para ligar o display

const int stepsPerRevolution = 200;//Define o No de passos de uma volta completa 
  
//Inicializa a biblioteca para ligacao ao motor 
Stepper myStepper(stepsPerRevolution, 2, 3, 12, 13);

void setup() {

    lcd.begin(16, 2);//Define o número de colunas e linhas do display
    lcd.setCursor(0, 0);//Define o cursor para a coluna 0, linha 0
    lcd.print(" O GARRA DOCKER ");
    myservo.attach(11);
    myStepper.setSpeed(60);
    Serial.begin(9600);
}

void open(){
  lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(" ABRINDO GARRA ");
 for (pos = 0; pos <= 130; pos += 1) { // goes from 0 degrees to 180 degrees

    // in steps of 1 degree

    myservo.write(pos);              // tell servo to go to position in variable 'pos'

    delay(15);                       // waits 15ms for the servo to reach the position

  }
  claw = 1;
}

void close(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" FECHANDO GARRA ");
  for (pos = 130; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees

    myservo.write(pos);              // tell servo to go to position in variable 'pos'

    delay(15);                       // waits 15ms for the servo to reach the position

  }
  claw = 0;
}

//Função para botão select
void select() {
    if(!claw)
      open();
    else
      close();
}

//Função para botão left
void left() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("APERTOU O BOTAO");
    lcd.setCursor(0, 1);
    lcd.print("      LEFT      ");
}

//Função para botão up
void up() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("SUBINDO GARRA");
    Serial.println("counterclockwise");
    for (int s = 0; s < stepsPerRevolution; s++) {
      myStepper.step(1);
    //myStepper2.step(-1);
    }

}

//Função para botão down
void down() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("DESCENDO GARRA");
    Serial.println("clockwise");
    for (int s = 0; s < stepsPerRevolution; s++) {
      myStepper.step(-1);

    }
}
//Função para botão right
void right() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("APERTOU O BOTAO");
    lcd.setCursor(0, 1);
    lcd.print("     RIGHT      ");
}

void loop() {
    Serial.println(analogRead(0));//Exibe a leitura do pino analógico A0 no monitor serial
    delay(100);

    if ((analogRead(0)) < 80) { //Se a leitura for menor que 80 chama a função right
        right();
    }
    else if ((analogRead(0)) < 200) {//Se a leitura for menor que 200 chama a função up
        up();
    }
    else if ((analogRead(0)) < 400) {//Se a leitura for menor que 400 chama a função down
        down();
    }
    else if ((analogRead(0)) < 600) {//Se a leitura for menor que 600 chama a função left
        left();
    }
    else if ((analogRead(0)) < 800) {//Se a leitura for menor que 800 chama a função left
        select();
    }

    //Gira o motor no sentido horario a 90 graus
    /*for (int i = 0; i <= 3; i++)
    {
        myStepper.step(-512);
        delay(2000);
    }

    //Gira o motor no sentido anti-horario a 120 graus
    for (int i = 0; i <= 2; i++)
    {
        myStepper.step(682);
        delay(2000);
    }

    //Gira o motor no sentido horario, aumentando a
    //velocidade gradativamente
    for (int i = 10; i <= 60; i = i + 10)
    {
        myStepper.setSpeed(i);
        myStepper.step(40 * i);
    }
    delay(2000);
*/
}
