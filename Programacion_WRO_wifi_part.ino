#include "CTBot.h"
CTBot myBot;
String mensaje;
int IDchat = 1814038179;

void setup() {
  Serial.begin(115200);
  myBot.wifiConnect("ASUS_E2.4", "7270ff3442");
  myBot.setTelegramToken("5607254707:AAHdCHGtorJX1fNkKutJYzYESyiONbCAXVk");
  while (!Serial);
  Serial.println("LoRa Receiver");
 

  {
    Serial.println(".");
    delay(500);
  }
}

void loop() {
  if (Serial.available()) {
    while (Serial.available()) {
      char c = Serial.read();
      mensaje += c;
      delay(10);  // Espera un breve momento para recibir el mensaje completo
    }
    myBot.sendMessage(IDchat, mensaje);
    mensaje = "";  // Limpia el mensaje después de enviarlo
  }

  TBMessage msg;
  if (myBot.getNewMessage(msg)) {
    Serial.print("Received message from: ");
    Serial.println(msg.sender.username);
    if (msg.messageType == CTBotMessageText) {
      Serial.print("Text: ");
      Serial.println(msg.text);
    }
  }
}
