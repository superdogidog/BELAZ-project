
//      Код  для платы MakeBlock MegaPi PRO
//      на микроконтроллере ATMEGA2560-16AU


// не пытайтесь повторить или понять в здравом уме
// суперпупермегасложный код

#include <MePS2.h> // библиотека для Джойстика
#include <Arduino.h> // библиотека ардуино стандарт
#include <Wire.h> // библиотека для управления модулями через интерфейс IC2
#include <SoftwareSerial.h>// последовательная связь с цифровыми портами
#include <MeMegaPiPro.h>  //библиотека платы

MeUltrasonicSensor ultrasonic_8(8); // ултразвуковой датчик порт 8
MeEncoderNew superMotor_7_1(0x09 + 7, 1); // выставляю порты моторов
MeEncoderNew superMotor_7_2(0x09 + 7, 2); // выставляю порты моторов
MeLEDMatrix ledMtx_9(9); // лед панель порт 9
unsigned char drawBuffer[16];//Задает число пикселей, выделяемых для памяти вне экрана при отрисовке фрейма
unsigned char *drawTemp;//Объект, реализующий этот интерфейс, может рисовать сам себя, используя информацию из CoordinateRect
double currentTime = 0;// значение числа двойной точности
double lastTime = 0;// значение числа двойной точности
Me7SegmentDisplay seg7_7(7);
MeLEDMatrix ledMtx_10(10);
double angle_rad = PI / 180.0; // значение числа двойной точности
double angle_deg = 180.0 / PI; // значение числа двойной точности
MeEncoderOnBoard Encoder_1(SLOT1);
MeEncoderOnBoard Encoder_2(SLOT2);
MeEncoderOnBoard Encoder_3(SLOT3);
MeEncoderOnBoard Encoder_4(SLOT4);

float dvig1 = 0;//значение переменных
float dvig2 = 0;//значение переменных
float time = 0;//значение переменных
float time_y = 0;//значение переменных
float timer_1 = 0;//значение переменных
float timer_time = 0;//значение переменных
float rejimi = 0;//значение переменных
float cargo = 0;//значение переменных
float password = 0;//значение переменных

MePS2 MePS2(PORT_15);//порт контроллера
void passwords () { // функция пароля
  while (!(MePS2.ButtonPressed(9))) //на джойстике кнопка 1
  {
    _loop();
  }
  while (!(MePS2.ButtonPressed(9))) //на джойстике кнопка 1
  {
    _loop();
  }
  while (!(MePS2.ButtonPressed(10))) //на джойстике кнопка 3
  {
    _loop();
  }
  while (!(MePS2.ButtonPressed(1))) //на джойстике кнопка R1
  {
    _loop();
  }

}

void modes () { // функция переключения режимов езды
  if (MePS2.ButtonPressed(18)) { //при нажатой кнопке режим увеличивается на 1
    rejimi = (rejimi + 1);
    _delay(0.3);

  }
  if (rejimi > 2) { //если значения режима больше 2х то оно обнуляется
    rejimi = 0;

  }

  /*    Всего режимов езды 3

         Standrat - обычная езда но при видимости препядствия за метр мощность моторов понижается,
         а при подьезде к препядствию почти вплотную для избежания удара включается механизм
         тормозящий и отталкивающий Белаз от стены

         LOW - Режим не имеющий никаких систем торможения, но ограничивающий постянно
         мощность моторов.

         PRO - Режим для професианалов своего дела, не имеет не каких ограничений и систем торможения

  */




}
void dvijenie () { //метод движения
  if (rejimi == 0.000000) { // какой режим стоит тут (тут Standart)
    if (ultrasonic_8.distanceCm() > 13) {
      dvig2 = ((MePS2.MeAnalog(4) / 2.5 - MePS2.MeAnalog(2) / 2.5));//переменная отвечающая за движение задаю ее значение
      dvig1 = (MePS2.MeAnalog(4) / 2.5 + MePS2.MeAnalog(2) / 2.5); //переменная отвечающая за движение задаю ее значение
      if (dvig1 > 100) { // тут я ограничиваю значение мощности подаваемое на моторы
        dvig1 = 100;

      }
      if (dvig2 > 100) { // тут я ограничиваю значение мощности подаваемое на моторы
        dvig2 = 100;

      }
      if (dvig1 < -100) { // тут я ограничиваю значение мощности подаваемое на моторы
        dvig1 = -100;

      }
      if (dvig2 < -100) { // тут я ограничиваю значение мощности подаваемое на моторы
        dvig2 = -100;

      }
      if (ultrasonic_8.distanceCm() < 100) { //тут я понимаю что до препядствия расстояние меньше метра
        if (dvig1 > 35) { // тут я ограничиваю значение мощности подаваемое на моторы
          dvig1 = 35;

        }
        if (dvig2 > 35) { // тут я ограничиваю значение мощности подаваемое на моторы
          dvig2 = 35;

        }
        if (dvig1 < -35) { // тут я ограничиваю значение мощности подаваемое на моторы
          dvig1 = -35;

        }
        if (dvig2 < -35) { // тут я ограничиваю значение мощности подаваемое на моторы
          dvig2 = -35;

        }

      }

      superMotor_7_1.setPWM(dvig1 * -1 / 100.0 * 255); // задаю значение моторам

      superMotor_7_2.setPWM(dvig2 * 1 / 100.0 * 255); // задаю значение моторам


    }

  }
  if (rejimi == 1.000000) { //если режим PRO
    dvig2 = ((MePS2.MeAnalog(4) / 2.5 - MePS2.MeAnalog(2) / 2.5));
    dvig1 = (MePS2.MeAnalog(4) / 2.5 + MePS2.MeAnalog(2) / 2.5);
    if (dvig1 > 100) {
      dvig1 = 100;

    }
    if (dvig2 > 100) {
      dvig2 = 100;

    }
    if (dvig1 < -100) {
      dvig1 = -100;

    }
    if (dvig2 < -100) {
      dvig2 = -100;

    }

    superMotor_7_1.setPWM(dvig1 * -1 / 100.0 * 255);

    superMotor_7_2.setPWM(dvig2 * 1 / 100.0 * 255);

  }
  if (rejimi == 2.000000) { //если режим LOW
    dvig2 = ((MePS2.MeAnalog(4) / 7.28 - MePS2.MeAnalog(2) / 7.28));
    dvig1 = (MePS2.MeAnalog(4) / 7.28 + MePS2.MeAnalog(2) / 7.28);
    if (dvig1 > 35) {
      dvig1 = 35;

    }
    if (dvig2 > 35) {
      dvig2 = 35;

    }
    if (dvig1 < -35) {
      dvig1 = -35;

    }
    if (dvig2 < -35) {
      dvig2 = -35;

    }

    superMotor_7_1.setPWM(dvig1 * -1 / 100.0 * 255);

    superMotor_7_2.setPWM(dvig2 * 1 / 100.0 * 255);

  }

}
void prepatstvie () { // метод препядствие
  if (rejimi == 0.000000) { //проверка режима
    if (ultrasonic_8.distanceCm() < 13) {

      superMotor_7_1.move(360, abs(60));
      // тут я кручу моторы назад на 1 оборот со скорость 60rpm
      superMotor_7_2.move(-360, abs(60));

    }

  }

}
void face () { //меняет лица на одном из экранов и делает это по таймеру
  if (timer_1 == 0.000000) {

    drawTemp = new unsigned char[16] {0, 0, 60, 126, 126, 60, 0, 0, 0, 0, 60, 126, 126, 60, 0, 0};
    memcpy(drawBuffer, drawTemp, 16);//библиотеки добавленные для экранов
    free(drawTemp);
    ledMtx_9.drawBitmap(0, 0, 16, drawBuffer);

  }
  if (timer_1 == 1.000000) {

    drawTemp = new unsigned char[16] {0, 16, 48, 48, 48, 48, 16, 0, 0, 16, 48, 48, 48, 48, 16, 0};
    memcpy(drawBuffer, drawTemp, 16);
    free(drawTemp);
    ledMtx_9.drawBitmap(0, 0, 16, drawBuffer);

  }
  if (timer_1 == 2.000000) {

    drawTemp = new unsigned char[16] {0, 2, 7, 7, 15, 14, 8, 0, 0, 8, 14, 15, 7, 7, 2, 0};
    memcpy(drawBuffer, drawTemp, 16);
    free(drawTemp);
    ledMtx_9.drawBitmap(0, 0, 16, drawBuffer);

  }
  if (timer_1 == 3.000000) {

    drawTemp = new unsigned char[16] {12, 14, 14, 6, 6, 2, 2, 0, 0, 2, 2, 6, 6, 14, 14, 12};
    memcpy(drawBuffer, drawTemp, 16);
    free(drawTemp);
    ledMtx_9.drawBitmap(0, 0, 16, drawBuffer);

  }
  if (timer_1 == 4.000000) {

    drawTemp = new unsigned char[16] {0, 12, 24, 24, 28, 12, 0, 0, 0, 0, 12, 28, 24, 24, 12, 0};
    memcpy(drawBuffer, drawTemp, 16);
    free(drawTemp);
    ledMtx_9.drawBitmap(0, 0, 16, drawBuffer);

  }
  if (timer_1 == 5.000000) {

    drawTemp = new unsigned char[16] {0, 0, 24, 28, 28, 24, 0, 0, 0, 0, 24, 28, 28, 24, 0, 0};
    memcpy(drawBuffer, drawTemp, 16);
    free(drawTemp);
    ledMtx_9.drawBitmap(0, 0, 16, drawBuffer);

  }
  if (timer_1 == 6.000000) {

    drawTemp = new unsigned char[16] {0, 0, 60, 30, 14, 4, 0, 0, 0, 0, 4, 14, 30, 60, 0, 0};
    memcpy(drawBuffer, drawTemp, 16);
    free(drawTemp);
    ledMtx_9.drawBitmap(0, 0, 16, drawBuffer);

  }
  if (timer_1 == 7.000000) {

    drawTemp = new unsigned char[16] {0, 0, 54, 62, 28, 62, 54, 0, 0, 54, 62, 28, 62, 54, 0, 0};
    memcpy(drawBuffer, drawTemp, 16);
    free(drawTemp);
    ledMtx_9.drawBitmap(0, 0, 16, drawBuffer);

  }
  if (timer_1 == 8.000000) {

    drawTemp = new unsigned char[16] {16, 60, 62, 62, 62, 62, 60, 16, 16, 60, 62, 62, 62, 62, 60, 16};
    memcpy(drawBuffer, drawTemp, 16);
    free(drawTemp);
    ledMtx_9.drawBitmap(0, 0, 16, drawBuffer);

  }
  if (timer_1 == 9.000000) {

    drawTemp = new unsigned char[16] {0, 12, 24, 24, 28, 12, 0, 0, 0, 0, 12, 28, 24, 24, 12, 0};
    memcpy(drawBuffer, drawTemp, 16);
    free(drawTemp);
    ledMtx_9.drawBitmap(0, 0, 16, drawBuffer);

  }

}
double getLastTime() {
  return currentTime = millis() / 1000.0 - lastTime;
}
void panelki () {
  if (getLastTime() > timer_time) {
    timer_1 += 1;
    lastTime = millis() / 1000.0;
    face();//применяю функцию панелек

  }
  if (timer_1 > 10) {
    timer_1 = 0;
    // обнуляю таймер когда он больше 10
  }

}
void gruz_otdel () {
  if (cargo == 0.000000) {
    if (MePS2.ButtonPressed(14)) {

      Encoder_1.move(180, abs(35));

      Encoder_2.move(180, abs(35));
      _delay(0.2);
      cargo = 1;

    }//метод движения груз отдела

  }
  if (cargo == 1.000000) { //проверка если груз уже опущен то опустить еще раз нельзя
    if (MePS2.ButtonPressed(15)) {

      Encoder_1.move(-180, abs(35));

      Encoder_2.move(-180, abs(35));
      _delay(0.2);
      cargo = 0;

    }

  }

}
void isr_process_encoder1(void) { //функция для энкодеров обязательна для работы именно с нашей платой
  if (digitalRead(Encoder_1.getPortB()) == 0) {
    Encoder_1.pulsePosMinus();
  } else {
    Encoder_1.pulsePosPlus();
  }
}
void isr_process_encoder2(void) {
  {//функция для энкодеров обязательна для работы именно с нашей платой
    if (digitalRead(Encoder_2.getPortB()) == 0) {
      Encoder_2.pulsePosMinus();
    } else {
      Encoder_2.pulsePosPlus();
    }
  }
  void isr_process_encoder3(void) {
    {//функция для энкодеров обязательна для работы именно с нашей платой
      if (digitalRead(Encoder_3.getPortB()) == 0) {
        Encoder_3.pulsePosMinus();
      } else {
        Encoder_3.pulsePosPlus();
      }
    }
    void isr_process_encoder4(void) {
      {//функция для энкодеров обязательна для работы именно с нашей платой
        if (digitalRead(Encoder_4.getPortB()) == 0) {
          Encoder_4.pulsePosMinus();
        } else {
          Encoder_4.pulsePosPlus();
        }
      }

      void _delay(float seconds) {// функция задержки
        long endTime = millis() + seconds * 1000;
        while (millis() < endTime) _loop();
      }

      void setup() {// тут задаются пины
        MePS2.begin(115200);
        superMotor_7_1.begin();
        superMotor_7_2.begin();
        ledMtx_9.setColorIndex(1);
        ledMtx_9.setBrightness(6);
        attachInterrupt(Encoder_1.getIntNum(), isr_process_encoder1, RISING);
        Encoder_1.setPulse(8);
        Encoder_1.setRatio(46.67);
        Encoder_1.setPosPid(1.8, 0, 1.2);
        Encoder_1.setSpeedPid(0.18, 0, 0);
        attachInterrupt(Encoder_2.getIntNum(), isr_process_encoder2, RISING);
        Encoder_2.setPulse(8);
        Encoder_2.setRatio(46.67);
        Encoder_2.setPosPid(1.8, 0, 1.2);
        Encoder_2.setSpeedPid(0.18, 0, 0);
        ledMtx_10.setColorIndex(1);
        ledMtx_10.setBrightness(6);
        TCCR1A = _BV(WGM10);
        TCCR1B = _BV(CS11) | _BV(CS10) | _BV(WGM12);
        TCCR2A = _BV(WGM21) | _BV(WGM20);
        TCCR2B = _BV(CS22);
        TCCR3A = _BV(WGM30);
        TCCR3B = _BV(CS31) | _BV(CS30) | _BV(WGM32);
        TCCR4A = _BV(WGM40);
        TCCR4B = _BV(CS41) | _BV(CS40) | _BV(WGM42);

        passwords();
        timer_time = 1;

      }

      void _loop() {
        MePS2.loop();// постоянно читаю значения с джойстика
        Encoder_1.loop();// постоянно читаю значения с энкодеров
        Encoder_2.loop();// постоянно читаю значения с энкодеров
      }

      void loop() {// функция которая всегда повторяется
        // тут я использую ранее сделанные функции
        prepatstvie();// функция препядствие
        dvijenie();// функция движение
        panelki();// функция передних панелей
        modes();// функция переключения режимов
        gruz_otdel();// функция грузового отдела

        seg7_7.display((float)round(ultrasonic_8.distanceCm()));//  тут отображение режимов управления
        if (rejimi == 0.000000) {
          ledMtx_10.drawStr(0, 0 + 7, String("STD").c_str());// STD - Standart

        }
        if (rejimi == 1.000000) {
          ledMtx_10.drawStr(0, 0 + 7, String("PRO").c_str());// PRO - Pro mode

        }
        if (rejimi == 2.000000) {
          ledMtx_10.drawStr(0, 0 + 7, String("LOW").c_str());// LOW - Low power ome

        }

        _loop();
      }
