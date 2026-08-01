#include <Arduino.h>
#include <esp_chip_info.h>

namespace {
constexpr unsigned long kHeartbeatIntervalMs = 5000;
unsigned long lastHeartbeatMs = 0;

void printBytes(const char *label, uint32_t bytes) {
  Serial.print(label);
  Serial.print(bytes);
  Serial.print(" bytes (");
  Serial.print(bytes / (1024.0 * 1024.0), 2);
  Serial.println(" MB)");
}

void printChipInfo() {
  esp_chip_info_t chipInfo;
  esp_chip_info(&chipInfo);

  Serial.print("Chip model         : ESP32-S");
  Serial.println(chipInfo.model == CHIP_ESP32S3 ? "3" : " unknown");
  Serial.print("CPU cores          : ");
  Serial.println(chipInfo.cores);
  Serial.print("Chip revision      : ");
  Serial.println(chipInfo.revision);
}

void printMemoryInfo() {
  printBytes("Flash size         : ", ESP.getFlashChipSize());
  printBytes("Sketch size        : ", ESP.getSketchSize());
  printBytes("Free sketch space  : ", ESP.getFreeSketchSpace());
  printBytes("Heap size          : ", ESP.getHeapSize());
  printBytes("Free heap          : ", ESP.getFreeHeap());
  printBytes("PSRAM size         : ", ESP.getPsramSize());
  printBytes("Free PSRAM         : ", ESP.getFreePsram());

  Serial.print("PSRAM found        : ");
  Serial.println(psramFound() ? "yes" : "no");
}
}  // namespace

void setup() {
  Serial.begin(115200);
  delay(2000);

  Serial.println();
  Serial.println("==============================");
  Serial.println(" HomeOS board diagnostics");
  Serial.println("==============================");
  Serial.println("Target board       : Edgehax S3-PRO");
  Serial.println("Module marking     : ESP32-S3-WROOM-1 MCN16R8");
  Serial.println("USB connector      : UART");
  Serial.println("Serial baud        : 115200");
  Serial.println("Display status     : disconnected for this test");
  Serial.println();

  printChipInfo();
  printMemoryInfo();

  Serial.println();
  Serial.println("Diagnostics complete. Leave the ePaper display disconnected.");
}

void loop() {
  const unsigned long now = millis();
  if (now - lastHeartbeatMs >= kHeartbeatIntervalMs) {
    lastHeartbeatMs = now;
    Serial.print("HomeOS heartbeat, uptime seconds: ");
    Serial.println(now / 1000);
  }
}
