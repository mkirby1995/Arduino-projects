const int sensorPin = A0;
const float baselineTemp = 16.0;

void setup() {
    // put your setup code here, to run once:
    
    // variables:
    int sensorValue = 0;         // the sensor value
    int sensorMin = 1023;        // minimum sensor value
    int sensorMax = 0;    
      
    Serial.begin(9600);
    for (int pinNumber = 2; pinNumber < 5; pinNumber++) {
        pinMode(pinNumber, OUTPUT);
        digitalWrite(pinNumber, LOW);
    }
    
    // calibrate during the first 10 seconds
    while (millis() < 10000) {
    sensorValue = analogRead(sensorPin);

    // record the maximum sensor value
    if (sensorValue > sensorMax) {
      sensorMax = sensorValue;
    }

    // record the minimum sensor value
    if (sensorValue < sensorMin) {
      sensorMin = sensorValue;
    }
  }
}

void loop() {
    // put your main code here, to run repeatedly:
    int sensorVal = analogRead(sensorPin);
    Serial.print("Sensor Value: ");
    Serial.print(sensorVal);

    // Convert the ADC reading to voltage
    float voltage = (sensorVal / 1024.0) * 5.0;

    Serial.print(", dgrees C; ");
    // Convert the voltage to temperature in degrees
    float temperature = ((voltage - .5) * 100);
    Serial.println(temperature);

    if (temperature < baselineTemp - 2) {
        digitalWrite(2, LOW);
        digitalWrite(3, LOW);
        digitalWrite(4, LOW);
    } else if (temperature >= baselineTemp + 2 && temperature < baselineTemp + 4) {
        digitalWrite(2, HIGH);
        digitalWrite(3, LOW);
        digitalWrite(4, LOW);
    } else if (temperature >= baselineTemp + 4 && temperature < baselineTemp + 6) {
        digitalWrite(2, HIGH);
        digitalWrite(3, HIGH);
        digitalWrite(4, LOW);
    } else if (temperature >= baselineTemp + 6) {
        digitalWrite(2, HIGH);
        digitalWrite(3, HIGH);
        digitalWrite(4, HIGH);
    }
    delay(1000);

}
