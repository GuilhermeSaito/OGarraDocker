#include <Servo.h>

int pos = 1;
const int but_horario = 11;
const int but_anti_horario = 10;

Servo servo_9;

void setup()
{
    servo_9.attach(9, 500, 2500);

    servo_9.write(1);

    pinMode(but_horario, INPUT);
    pinMode(but_anti_horario, INPUT);
}

void loop()
{
    if (pos > 0 && pos < 180) {
        int move = 0;

        int horario_state = digitalRead(but_horario);
        int anti_horario_state = digitalRead(but_anti_horario);

        if (horario_state == HIGH)
            move = 1;
        else if (anti_horario_state == HIGH)
            move = -1;
        pos += move;
    }
    else if (pos <= 0) {
        pos += 1;
    }
    else {
        pos += -1;
    }
    servo_9.write(pos);
}