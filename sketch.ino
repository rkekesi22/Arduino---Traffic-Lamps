const int red = 10;
const int orange = 9;
const int green = 8;

const int walk_red = 2;
const int walk_green = 4;

const int button = 7;

const int buzzer = 12;

bool pressButton = false;

unsigned long lastPressTime = 0;
unsigned long debounceTime = 50; 

bool lastState = HIGH;
bool actualState;

void setup() {
  pinMode(red, OUTPUT);
  pinMode(orange, OUTPUT);
  pinMode(green, OUTPUT);

  pinMode(walk_red, OUTPUT);
  pinMode(walk_green, OUTPUT);

  pinMode(button, INPUT_PULLUP);

  pinMode(buzzer, OUTPUT);

  digitalWrite(green, HIGH);
  digitalWrite(walk_red, HIGH);

  Serial.begin(9600);

}

void loop() {
  actualState = digitalRead(button);

  //Serial.println("Aktuális állapot:");
  //Serial.println(actualState);
  //Serial.println("Utolsó állapot:");
  //Serial.println(lastState);

  if( actualState != lastState)
  {
    lastPressTime = millis();
  }

  //Serial.println(lastPressTime);

  //Serial.println("Kivonás");
  //Serial.println((millis() -  lastPressTime));
  //delay(2000);

  if ( (millis() -  lastPressTime) > debounceTime) 
  {
    if( lastState == HIGH  && actualState == LOW)
    {
      Serial.println("Érvényes gombnyomás");
      
      digitalWrite(green, LOW);
      digitalWrite(orange, HIGH);

      delay(2000);

      digitalWrite(orange, LOW);
      digitalWrite(red, HIGH);

      digitalWrite(walk_red, LOW);
      digitalWrite(walk_green, HIGH);

      for( int i = 0; i <= 6; i++)
      {
        tone(buzzer, 1000);
        delay(300);
        noTone(buzzer);
        delay(300);
      }

      for (int i = 0; i <= 6; i++)
      {
        digitalWrite(walk_green, LOW);
        tone(buzzer, 1500);
      
        delay(250);

        digitalWrite(walk_green, HIGH);
        delay(250);
      }

      noTone(buzzer);
      digitalWrite(walk_green, LOW);
      digitalWrite(walk_red, HIGH);

      delay(1000);
    
      digitalWrite(red, LOW);
      digitalWrite(green, HIGH);

    }
  }

  lastState = actualState;
}

