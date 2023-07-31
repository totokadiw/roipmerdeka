/*
  Fox Beacon menggunakan Arduino Nano

  14 Pebruari 2022
  Jember, Jawa Timur - INDONESIA
  Oleh: JZ13OUK, Totok Adi Wihanto
  totokadiw@gmail.com
  https://1014rapi.wordpress.com/

  Referensi:
  Arduino Nano
  https://docs.arduino.cc/hardware/nano
  
Klik untuk mengakses ArduinoNanoManual23.pdf



  Modified from: Mike Myers (http://mikemyers.me)  @netnutmike

  This code is in the public domain.
*/

char* letters[] = {
  ".-",     // A
  "-...",   // B
  "-.-.",   // C
  "-..",    // D
  ".",      // E
  "..-.",   // F
  "--.",    // G
  "....",   // H
  "..",     // I
  ".---",   // J
  "-.-",    // K
  ".-..",   // L
  "--",     // M
  "-.",     // N
  "---",    // O
  ".--.",   // P
  "--.-",   // Q
  ".-.",    // R
  "...",    // S
  "-",      // T
  "..-",    // U
  "...-",   // V
  ".--",    // W
  "-..-",   // X
  "-.--",   // Y
  "--.."    // Z
};

char* numbers[] = {
  "-----",   // 0
  ".----",   // 1
  "..---",   // 2
  "...--",   // 3
  "....-",   // 4
  ".....",   // 5
  "-....",   // 6
  "--...",   // 7
  "---..",   // 8
  "----."    // 9   --- end of 1st segment of borrowed code from Mike Myers
};

byte pin_delay1 = 2;
byte pin_delay2 = 3;
byte pin_delay3 = 4;
byte pin_delay4 = 5;
byte pin_delay5 = 6;
byte pin_delay6 = 7;
byte pin_led = 13;
byte pin_ptt = 9;
byte pin_tone = 8;

int jeda_Delay[7] = {0, 5, 10, 15, 20, 25, 30};
byte jeda_dipilih = 1;
byte flag_jeda = 0;

int frequency = 1000;         // frequency of tone
int dotDelay = 100;           // duration of the dot in morse code, this is also the time between the dots and dashes
int charDelay = dotDelay * 2; // duration of the wait between letters for Farsnworth method
int wordDelay = dotDelay * 4; // duration of the wait between words for Farsnworth method
int hitung = 0;

void setup() {
  // initialize the digital pin as an output.
  pinMode(pin_delay1, INPUT_PULLUP);
  pinMode(pin_delay2, INPUT_PULLUP);
  pinMode(pin_delay3, INPUT_PULLUP);
  pinMode(pin_delay4, INPUT_PULLUP);
  pinMode(pin_delay5, INPUT_PULLUP);
  pinMode(pin_delay6, INPUT_PULLUP);

  pinMode(pin_ptt, OUTPUT);
  pinMode(pin_tone, OUTPUT);
  pinMode(pin_led, OUTPUT);
  delay(1000);
}

void loop() {
  static unsigned long timer = millis();
  if (millis() - timer >= 1000) {
    if (digitalRead(pin_delay1) == LOW) {
      if (jeda_dipilih != 1) {
        jeda_dipilih = 1;
        flag_jeda = 1;
      }
    }
    if (digitalRead(pin_delay2) == LOW) {
      if (jeda_dipilih != 2) {
        jeda_dipilih = 2;
        flag_jeda = 1;
      }
    }
    if (digitalRead(pin_delay3) == LOW) {
      if (jeda_dipilih != 3) {
        jeda_dipilih = 3;
        flag_jeda = 1;
      }
    }
    if (digitalRead(pin_delay4) == LOW) {
      if (jeda_dipilih != 4) {
        jeda_dipilih = 4;
        flag_jeda = 1;
      }
    }
    if (digitalRead(pin_delay5) == LOW) {
      if (jeda_dipilih != 5) {
        jeda_dipilih = 5;
        flag_jeda = 1;
      }
    }
    if (digitalRead(pin_delay6) == LOW) {
      if (jeda_dipilih != 6) {
        jeda_dipilih = 6;
        flag_jeda = 1;
      }
    }

    if (flag_jeda == 1) {
      flag_jeda = 0;
      hitung = 0;
    }

    if (jeda_dipilih > 0) {
      hitung++;
      if (hitung == jeda_Delay[jeda_dipilih]) {
        hitung = 0;
        digitalWrite(pin_led, HIGH);
        digitalWrite(pin_ptt, HIGH);
        delay(500);
        tone(pin_tone, frequency); delay(3000); noTone(pin_tone);
        delay(500);
        SendText("FOX1 FOX1 FOX1 DE JZ13OUK");
        delay(500);
        tone(pin_tone, frequency); delay(3000); noTone(pin_tone);
        delay(500);
        digitalWrite(pin_ptt, LOW);
        digitalWrite(pin_led, LOW);
      }
    }
  }
}

void morseCodeSequence(char* sequence) {
  int i = 0;
  while (sequence[i] != NULL)  {
    dotOrDash(sequence[i]);
    i++;
  }
  delay(charDelay);
}

void SendText(char* MorseCodeLetters) {
  int i = 0;
  char ch;
  while (MorseCodeLetters[i] != NULL) {
    ch = MorseCodeLetters[i];
    if (ch >= 'a' && ch <= 'z') {
      morseCodeSequence(letters[ch - 'a']);
    } else if (ch >= 'A' && ch <= 'Z') {
      morseCodeSequence(letters[ch - 'A']);
    } else if (ch >= '0' && ch <= '9')    {
      morseCodeSequence(numbers[ch - '0']);
    } else if (ch == ' ') {
      delay(wordDelay);
    } else {
    }
    i++;
  }
  delay(charDelay);
}

void dotOrDash(char dotOrDash) {
  tone(pin_tone, frequency);
  if (dotOrDash == '.') {
    delay(dotDelay);
  } else {
    delay(dotDelay * 3);
  }
  noTone(pin_tone);
  delay(dotDelay);
}
