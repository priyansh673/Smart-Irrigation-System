float model_coef[2] = {0.31252223, -0.18626435};  //Coeeficients calculated 
float model_intercept = -160.56781552;      

void setup() {
  Serial.begin(9600);

  pinMode(A1, INPUT);  // Analog input for TMP36 temperature sensor
  pinMode(A0, INPUT);  // Analog input for soil moisture sensor
  pinMode(13, OUTPUT);  // Single-color LED 
}

void loop() {
  // Read sensor values
  int moistureValue = analogRead(A0);  // Soil moisture sensor
  float tempValue = analogRead(A1);  // TMP36 temperature sensor

  // Apply the logistic regression model
   float linear_combination = model_coef[0] * moistureValue + model_coef[1] * tempValue + model_intercept;
  float prediction = 1 / (1 + exp(-linear_combination));
  // Display results with single-color LED
  if (prediction < 0.5) {
    // Irrigation needed (Display HIGH)
    digitalWrite(13, HIGH);
  } else {
    // No irrigation needed (Display LOW)
    digitalWrite(13, LOW);
  }
  Serial.print("Moisture: ");
  Serial.print(moistureValue);
  Serial.print(", Temp: ");
  Serial.print(tempValue);
  Serial.print(", Prediction: ");
  Serial.println(prediction);

  delay(1000);
}
