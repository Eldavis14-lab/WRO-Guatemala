#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h> //DESCARGAR LIBRERÍA:https://github.com/ELECTROALL/Codigos-arduino/blob/master/LiquidCrystal_I2C.zip

LiquidCrystal_I2C lcd(0x27,16,2); // si no te sale con esta direccion  puedes usar (0x3f,16,2) || (0x27,16,2)  ||(0x20,16,2) 

SoftwareSerial bluetoothSerial(2, 3); // RX, TX

void setup() {
  Serial.begin(9600);     
   lcd.init();
  lcd.backlight();
  lcd.clear();// Inicializamos la comunicación serial del Arduino Nano
  bluetoothSerial.begin(9600);  // Inicializamos la comunicación serial del módulo Bluetooth HC-06
  
  // Esperamos un momento para que el módulo Bluetooth se inicie completamente
  delay(1000);
}

void loop() {
  // Verificamos si hay datos disponibles en el módulo Bluetooth
  if (bluetoothSerial.available()) {
   lcd.setCursor(0,0);
  lcd.print(conectado); 
    // Leemos el mensaje completo desde el módulo Bluetooth
    String receivedMessage = bluetoothSerial.readStringUntil('\n');
    
    // Imprimimos el mensaje recibido en el monitor serial
    Serial.print("Mensaje recibido desde Bluetooth: ");
    Serial.println(receivedMessage);
    
    // Puedes agregar aquí la lógica que desees para procesar los datos recibidos desde el Bluetooth
  }

  // Verificamos si hay datos disponibles en la comunicación serial del Arduino Nano
  if (Serial.available()) {
    // Leemos el mensaje completo desde el monitor serial
    String sendMessage = Serial.readStringUntil('\n');
    
    // Enviaremos el mensaje completo al módulo Bluetooth
    bluetoothSerial.println(sendMessage);
  }
}
