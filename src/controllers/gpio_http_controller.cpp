#include "gpio_http_controller.h"

namespace GPIOHttpController {
void handle(WiFiClient client, String url_slices[]) {
  String action = url_slices[2];
  int pin = url_slices[3].toInt();
  int value = url_slices[4].toInt();

  Serial.print("Action: ");
  Serial.print(action);
  Serial.print(" | PIN: ");
  Serial.print(pin);
  Serial.print(" | Value: ");
  Serial.println(value);

  if (action == "button") {
    digitalWrite(pin, HIGH);
    delay(500);
    digitalWrite(pin, LOW);
    Response::ok(client,
                 "{\"pin\": " + String(pin) + ", \"value\": \"pressed\"}");
    return;

  } else if (action == "set") {
    digitalWrite(pin, value);

    Response::ok(client, "{\"pin\": " + String(pin) +
                             ", \"value\": " + String(value) + "}");
    return;
  } else {
    Response::not_found(client);
    return;
  }
}
} // namespace GPIOHttpController
