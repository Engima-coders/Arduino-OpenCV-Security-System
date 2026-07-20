#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Fingerprint Sensor
SoftwareSerial mySerial(2, 3);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

// Servo
Servo doorServo;

const int servoPin = 10;
const int lockPos = 0;
const int unlockPos = 50;

// Keypad
const byte numRows = 4;
const byte numCols = 4;

char keymap[numRows][numCols] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[numRows] = {9,8,7,6};
byte colPins[numCols] = {5,4,A0,A1};

Keypad myKeypad = Keypad(
  makeKeymap(keymap),
  rowPins,
  colPins,
  numRows,
  numCols
);

// Password
String correctPassword = "1144";
String enteredPassword = "";
bool faceVerified = false;

// Function Prototypes
int getFingerprintIDez();
void askPassword();
void handleAccessGranted();
void handleAccessDenied();

void setup()
{
  Serial.begin(9600);

  // Servo
  doorServo.attach(servoPin);
  doorServo.write(lockPos);

  // LCD
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Fingerprint");
  lcd.setCursor(0, 1);
  lcd.print("Initializing");

  delay(2000);

  // Fingerprint
  finger.begin(57600);
  delay(5);

  if (finger.verifyPassword())
  {
    Serial.println("Fingerprint Sensor Found");

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Sensor Found");

    delay(2000);
  }
  else
  {
    Serial.println("Fingerprint Sensor Error");

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Sensor Error");

    lcd.setCursor(0,1);
    lcd.print("Check Wiring");

    while(1);
  }

  finger.getTemplateCount();

  lcd.clear();

  if (finger.templateCount == 0)
  {
    lcd.setCursor(0,0);
    lcd.print("No Templates");

    lcd.setCursor(0,1);
    lcd.print("Enroll Finger");
  }
  else
  {
    lcd.setCursor(0,0);
lcd.print("Waiting Face");

lcd.setCursor(0,1);
lcd.print("Recognition");
  }
}

void loop()
{
  // Wait for command from Python
  if (Serial.available())
  {
    char cmd = Serial.read();

    if (cmd == 'F' )
    {
      faceVerified = true;

      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Face Verified");

      lcd.setCursor(0,1);
      lcd.print("Place Finger");

      delay(1500);
    }
    
  }

  // Start fingerprint verification only after face is verified
  if(faceVerified)
  {
    getFingerprintIDez();
    delay(50);
  }
}

// Fingerprint Verification
int getFingerprintIDez()
{
  uint8_t p = finger.getImage();

  if (p == FINGERPRINT_NOFINGER)
    return -1;

  if (p != FINGERPRINT_OK)
    return -1;

  p = finger.image2Tz();

  if (p != FINGERPRINT_OK)
    return -1;

  p = finger.fingerFastSearch();

  if (p == FINGERPRINT_NOTFOUND)
  {
    Serial.println("Fingerprint Not Recognized");

    lcd.clear();

    lcd.setCursor(0,0);
    lcd.print("Access Denied");

    lcd.setCursor(0,1);
    lcd.print("Unknown User");

    delay(2000);

    lcd.clear();
lcd.setCursor(0,0);
lcd.print("Unknown Finger");

lcd.setCursor(0,1);
lcd.print("Try Again");

delay(2000);

// Wait until finger removed
while(finger.getImage() != FINGERPRINT_NOFINGER)
{
    delay(100);
}

faceVerified = false;

lcd.clear();
lcd.setCursor(0,0);
lcd.print("Waiting Face");

lcd.setCursor(0,1);
lcd.print("Recognition");

return -1;
  }

  if (p != FINGERPRINT_OK)
    return -1;

  Serial.print("Fingerprint ID: ");
  Serial.println(finger.fingerID);

  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Finger Verified");

  lcd.setCursor(0,1);
  lcd.print("Enter PIN");

  delay(1500);

  askPassword();

  return finger.fingerID;
}

// PIN Verification
void askPassword()
{
  enteredPassword = "";

  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Enter PIN:");

  lcd.setCursor(0,1);

  while(true)
  {
    char key = myKeypad.getKey();

    if(key)
    {
      if(key == 'B')
      {
        if(enteredPassword == correctPassword)
        {
          handleAccessGranted();
        }
        else
        {
          handleAccessDenied();
        }
        return;
      }

      else if(key == '*')
      {
        enteredPassword = "";

        lcd.setCursor(0,1);
        lcd.print("                ");

        lcd.setCursor(0,1);
      }

      else
      {
        if(enteredPassword.length() < 4)
        {
          enteredPassword += key;

          lcd.print("*");
        }
      }
    }
  }
}

// Access Granted
void handleAccessGranted()
{
  Serial.println("PIN Correct");
  Serial.println("Door Unlocked");

  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("PIN Correct");

  lcd.setCursor(0,1);
  lcd.print("Door Open");

  // Unlock Door
  doorServo.write(unlockPos);

  delay(5000);

  // Lock Again
  doorServo.write(lockPos);

  // Wait until finger removed
while(finger.getImage() != FINGERPRINT_NOFINGER)
{
    delay(100);
}

faceVerified = false;

lcd.clear();

lcd.setCursor(0,0);
lcd.print("Door Locked");

delay(2000);

lcd.clear();

lcd.setCursor(0,0);
lcd.print("Waiting Face");

lcd.setCursor(0,1);
lcd.print("Recognition");
}

// Access Denied
void handleAccessDenied()
{
  Serial.println("Wrong PIN");

  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Wrong PIN");

  lcd.setCursor(0,1);
  lcd.print("Access Denied");

  delay(3000);

  // Wait until finger removed
while(finger.getImage() != FINGERPRINT_NOFINGER)
{
    delay(100);
}

faceVerified = false;

lcd.clear();

lcd.setCursor(0,0);
lcd.print("Waiting Face");

lcd.setCursor(0,1);
lcd.print("Recognition");
}