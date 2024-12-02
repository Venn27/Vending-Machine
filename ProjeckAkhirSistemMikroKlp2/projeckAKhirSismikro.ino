#include <Servo.h>

// Pin push button
const int buttonBiru = 2;
const int buttonMerah = 4;

int button1State = HIGH;
int button2State = HIGH;
int lastButton1State = HIGH;
int lastButton2State = HIGH;

// Variabel untuk debounce
unsigned long lastDebounceTime1 = 0; // Untuk tombol biru
unsigned long lastDebounceTime2 = 0; // Untuk tombol merah
unsigned long debounceDelay = 50;    // Waktu debounce dalam milidetik

// Servo
Servo servoMotor1;
Servo servoMotor2;

void setup() {
  Serial.begin(9600);

  // Tombol
  pinMode(buttonBiru, INPUT_PULLUP);
  pinMode(buttonMerah, INPUT_PULLUP);

  // Servo
  servoMotor1.attach(3);
  servoMotor2.attach(5);
  servoMotor1.write(0);
  servoMotor2.write(0);

  // Tampilkan pesan awal di serial monitor
  Serial.println("Silahkan pilih tombol...");
}

void loop() {
  // Baca status tombol
  int reading1 = digitalRead(buttonBiru);
  int reading2 = digitalRead(buttonMerah);

  // Debounce tombol pertama
  if (reading1 != lastButton1State) {
    lastDebounceTime1 = millis();
  }

  if ((millis() - lastDebounceTime1) > debounceDelay) {
    if (reading1 != button1State) {
      button1State = reading1;
      if (button1State == LOW) {  // Tombol biru ditekan
        Serial.println("Servo 1 Berputar!");
        servoGerak(servoMotor1);

        Serial.println("Selesai!");
        delay(2000);

        tampilkanPesanAwal();
      }
    }
  }

  // Debounce tombol kedua
  if (reading2 != lastButton2State) {
    lastDebounceTime2 = millis();
  }

  if ((millis() - lastDebounceTime2) > debounceDelay) {
    if (reading2 != button2State) {
      button2State = reading2;
      if (button2State == LOW) {  // Tombol merah ditekan
        Serial.println("Servo 2 Berputar!");
        servoGerak(servoMotor2);

        Serial.println("Selesai!");
        delay(2000);

        tampilkanPesanAwal();
      }
    }
  }

  // Simpan status terakhir tombol
  lastButton1State = reading1;
  lastButton2State = reading2;
}

// Fungsi untuk menggerakkan servo
void servoGerak(Servo &servoMotor) {
  for (int pos = 0; pos <= 180; pos++) {
    servoMotor.write(pos);
    delay(5);
  }
  for (int pos = 180; pos >= 0; pos--) {
    servoMotor.write(pos);
    delay(5);
  }
}

// Fungsi untuk menampilkan pesan awal di serial monitor
void tampilkanPesanAwal() {
  Serial.println("Silahkan pilih tombol...");
}
