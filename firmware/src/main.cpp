#include <Arduino.h>
#include <esp_chip_info.h>
#include <SPI.h>
#include <GxEPD2_BW.h>
#include <gdey/GxEPD2_420_GDEY042T81.h>
#include <Fonts/FreeMono9pt7b.h>
#include <Fonts/FreeMonoBold18pt7b.h>

namespace {
constexpr unsigned long kHeartbeatIntervalMs = 5000;
unsigned long lastHeartbeatMs = 0;

constexpr int kEPaperBusyPin = 7;
constexpr int kEPaperDcPin = 8;
constexpr int kEPaperRstPin = 9;
constexpr int kEPaperCsPin = 10;
constexpr int kEPaperMosiPin = 11;
constexpr int kEPaperSckPin = 12;

GxEPD2_BW<GxEPD2_420_GDEY042T81, GxEPD2_420_GDEY042T81::HEIGHT> display(
    GxEPD2_420_GDEY042T81(kEPaperCsPin, kEPaperDcPin, kEPaperRstPin,
                          kEPaperBusyPin));

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

void printDisplayInfo() {
  Serial.println("Display module     : Waveshare 4.2 inch e-Paper Module V2 Rev2.2");
  Serial.println("Display resolution : 400 x 300 black/white");
  Serial.println("GxEPD2 driver      : GxEPD2_420_GDEY042T81 (provisional)");
  Serial.print("EPD BUSY           : GPIO");
  Serial.println(kEPaperBusyPin);
  Serial.print("EPD DC             : GPIO");
  Serial.println(kEPaperDcPin);
  Serial.print("EPD RST            : GPIO");
  Serial.println(kEPaperRstPin);
  Serial.print("EPD CS             : GPIO");
  Serial.println(kEPaperCsPin);
  Serial.print("EPD DIN/MOSI       : GPIO");
  Serial.println(kEPaperMosiPin);
  Serial.print("EPD CLK/SCK        : GPIO");
  Serial.println(kEPaperSckPin);
}

void drawCenteredText(const char *text, int16_t centerY) {
  int16_t boundsX = 0;
  int16_t boundsY = 0;
  uint16_t boundsWidth = 0;
  uint16_t boundsHeight = 0;
  display.getTextBounds(text, 0, centerY, &boundsX, &boundsY, &boundsWidth,
                        &boundsHeight);
  const int16_t x = (display.width() - boundsWidth) / 2 - boundsX;
  display.setCursor(x, centerY);
  display.print(text);
}

void drawHelloWorldScreen() {
  display.setRotation(0);
  display.setFullWindow();
  display.firstPage();
  do {
    display.fillScreen(GxEPD_WHITE);
    display.setTextColor(GxEPD_BLACK);

    display.setFont(&FreeMonoBold18pt7b);
    drawCenteredText("HomeOS", 110);

    display.setFont(&FreeMono9pt7b);
    drawCenteredText("ePaper hello-world", 155);
    drawCenteredText("Waveshare 4.2 V2 Rev2.2", 190);
  } while (display.nextPage());
}

void runDisplayHelloWorld() {
  Serial.println();
  Serial.println("Starting ePaper display hello-world test.");
  Serial.println("If the display is not wired, disconnect USB and wire it before upload.");

  SPI.begin(kEPaperSckPin, -1, kEPaperMosiPin, kEPaperCsPin);

  // Waveshare ePaper boards may need a shortened reset pulse.
  display.init(115200, true, 2, false);
  drawHelloWorldScreen();
  display.hibernate();

  Serial.println("Display refresh command complete. Check the ePaper screen.");
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
  Serial.println("Display status     : wired for hello-world test");
  Serial.println();

  printChipInfo();
  printMemoryInfo();
  printDisplayInfo();

  runDisplayHelloWorld();
}

void loop() {
  const unsigned long now = millis();
  if (now - lastHeartbeatMs >= kHeartbeatIntervalMs) {
    lastHeartbeatMs = now;
    Serial.print("HomeOS heartbeat, uptime seconds: ");
    Serial.println(now / 1000);
  }
}
