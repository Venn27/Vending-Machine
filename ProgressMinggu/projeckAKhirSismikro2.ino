#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#include <Servo.h>

Servo servoMotor1;

// Pin push button
const int buttonBiru = 2; 
const int buttonMerah = 4;

int button1State = HIGH;
int button2State = HIGH;
int lastButton1State = HIGH;
int lastButton2State = HIGH;

// Variabel untuk debounce
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50; // Waktu debounce dalam milidetik

void setup() {
  Serial.begin(9600);
  lcd.backlight(); // Menyalakan lampu belakang LCD
  lcd.init(); // Inisialisasi LCD
  lcd.setCursor(0, 0);
  lcd.print("Silahkan pilih");
  lcd.setCursor(0, 1);
  lcd.print("tombol...");
  servoMotor1.attach(5); 

  pinMode(buttonBiru, INPUT_PULLUP);
  pinMode(buttonMerah, INPUT_PULLUP);
}

void loop() {
  int reading1 = digitalRead(buttonBiru);
  int reading2 = digitalRead(buttonMerah);

  // Jika tombol pertama telah berubah status
  if (reading1 != lastButton1State) {
    lastDebounceTime = millis(); // Update waktu debounce
  }

  // Jika tombol pertama sudah stabil selama debounceDelay
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading1 != button1State) {
      button1State = reading1;
      if (button1State == LOW) { // Tombol pertama ditekan (LOW berarti aktif)
        // Hapus layar LCD
        lcd.clear();
        lcd.setCursor(0, 0);

        //   for (int pos = 0; pos <= 360; pos++) {
        //   servoMotor1.write(pos); 
        //   delay(5);
        // }

        // for (int pos = 180; pos >= 0; pos--) {
        //   servoMotor1.write(pos);
        //   delay(5); 
        // }

        lcd.print("Tombol Biru Ditekan!");
        delay(2000); // Simulasi operasi
        lcd.clear();
         servoMotor1.write(180); // Mulai putar searah jarum jam
        delay(2000); // Tunggu 2 detik (sesuaikan waktu agar sesuai dengan kecepatan servo)

        // Berhenti setelah putaran selesai
        servoMotor1.write(90); // Berhenti
        delay(1000); // Tunggu 1 detik sebelum memulai ulang
        lcd.setCursor(0, 0);

        lcd.print("Silahkan pilih");
        lcd.setCursor(0, 1);
        lcd.print("tombol...");
      }
    }
  }

  // Jika tombol kedua telah berubah status
  if (reading2 != lastButton2State) {
    lastDebounceTime = millis(); // Update waktu debounce
  }

  // Jika tombol kedua sudah stabil selama debounceDelay
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading2 != button2State) {
      button2State = reading2;
      if (button2State == LOW) { 
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Tombol Merah Ditekan!");
        delay(2000); // Simulasi operasi
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Silahkan pilih");
        lcd.setCursor(0, 1);
        lcd.print("tombol...");
      }
    }
  }

  // Simpan status tombol terakhir
  lastButton1State = reading1;
  lastButton2State = reading2;
}
