void setup() {
  // Initialize serial communication at 9600 baud rate
  Serial.begin(9600);
  
  // Loop from 1 to 10
  for (int i = 1; i <= 10; i++) {
    Serial.println(i); // Print the current number
    delay(2000);       // Wait for 2 seconds (2000 milliseconds)
  }
}

void loop() {
  // The loop is left empty so it only counts to 10 once.
}