#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#define DHTPIN 2        
#define DHTTYPE DHT11    
#define VIBRATION_PIN 5  
#define BUZZER_PIN 6     

DHT dht(DHTPIN, DHTTYPE);  
LiquidCrystal_I2C lcd(0x27, 16, 2); 

void setup() {
  Serial.begin(9600);           
  dht.begin();                  
  pinMode(VIBRATION_PIN, INPUT); 
  pinMode(BUZZER_PIN, OUTPUT);  // Initialize buzzer pin as output

  Serial.println("System Initialized");
  lcd.init(); 
  lcd.backlight();
}

void loop() {
  // Read data from DHT11
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Check if DHT data is valid
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print("°C,  Humidity: ");
    Serial.print(humidity);
    Serial.println("%");

    delay(1000);  
    lcd.clear();                 
    lcd.setCursor(0, 0);         
    lcd.print("Temperature: ");        
    lcd.setCursor(2, 1);         
    lcd.print(temperature); 
    delay(1000);                 

    lcd.clear();                  
    lcd.setCursor(0, 0);         
    lcd.print("Vibration Detected!");
    delay(2000);

    lcd.clear();                  
    lcd.setCursor(0, 0);         
    lcd.print("GLOF Predicted!! ");

    // Activate buzzer for alert
    digitalWrite(BUZZER_PIN, HIGH);
    delay(500);                 // Buzzer on for 1 second
    digitalWrite(BUZZER_PIN, LOW);
    delay(1000);                 // Buzzer off for 1 second
  }

  int vibrationState = digitalRead(VIBRATION_PIN);
  if (vibrationState == HIGH) {
    Serial.println("Vibration detected");
  } 

  Serial.println("---------------------------------");
  delay(1000);    
}





