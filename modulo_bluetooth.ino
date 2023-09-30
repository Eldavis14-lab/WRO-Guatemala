#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>

// Configuración de la dirección I2C del LCD
LiquidCrystal_I2C lcd(0x27, 16, 2); // Si no funciona con esta dirección, puedes probar con (0x3f, 16, 2) || (0x27, 16, 2) || (0x20, 16, 2)

// Configuración de los pines RX y TX para el módulo Bluetooth
SoftwareSerial bluetoothSerial(2, 3); // RX, TX

void setup() {
  // Inicialización de la comunicación serial del Arduino Nano
  Serial.begin(9600);

  // Inicialización de la pantalla LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();
 bluetoothSerial.begin(9600);
  // Esperamos un momento para que el módulo Bluetooth se inicie completamente
  delay(1000);
}

void loop() {
  // Verificamos si hay datos disponibles en el módulo Bluetooth
  if (bluetoothSerial.available()) {
    lcd.setCursor(0, 0);
    lcd.print("CONECTADO");

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
