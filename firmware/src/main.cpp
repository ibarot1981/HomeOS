#include <Arduino.h>
#include <esp_chip_info.h>
#include <time.h>
#include <WiFi.h>
#include <SPI.h>
#include <GxEPD2_BW.h>
#include <gdey/GxEPD2_420_GDEY042T81.h>
#include <Fonts/FreeMono9pt7b.h>
#include <Fonts/FreeMonoBold18pt7b.h>
#include <Fonts/FreeMonoBold24pt7b.h>

#if __has_include("config.local.h")
#include "config.local.h"
#endif

#ifndef HOMEOS_WIFI_SSID
#define HOMEOS_WIFI_SSID ""
#endif

#ifndef HOMEOS_WIFI_PASSWORD
#define HOMEOS_WIFI_PASSWORD ""
#endif

namespace {
constexpr unsigned long kHeartbeatIntervalMs = 5000;
constexpr unsigned long kClockRefreshIntervalMs = 60UL * 1000UL;
constexpr unsigned long kClockRetryIntervalMs = 5UL * 60UL * 1000UL;
constexpr unsigned long kWiFiConnectTimeoutMs = 20000;
constexpr unsigned long kTimeSyncTimeoutMs = 20000;
unsigned long lastHeartbeatMs = 0;
unsigned long lastClockRefreshMs = 0;
unsigned long lastClockSyncAttemptMs = 0;
int lastRenderedMinute = -1;

constexpr int kEPaperBusyPin = 7;
constexpr int kEPaperDcPin = 8;
constexpr int kEPaperRstPin = 9;
constexpr int kEPaperCsPin = 10;
constexpr int kEPaperMosiPin = 11;
constexpr int kEPaperSckPin = 12;

constexpr const char *kTimeZone = "IST-5:30";
constexpr const char *kNtpServer1 = "pool.ntp.org";
constexpr const char *kNtpServer2 = "time.nist.gov";

enum class ClockStatus {
  kWiFiNotConfigured,
  kWiFiConnectFailed,
  kTimeSyncFailed,
  kTimeSynced,
};

ClockStatus clockStatus = ClockStatus::kWiFiNotConfigured;

GxEPD2_BW<GxEPD2_420_GDEY042T81, GxEPD2_420_GDEY042T81::HEIGHT> display(
    GxEPD2_420_GDEY042T81(kEPaperCsPin, kEPaperDcPin, kEPaperRstPin,
                          kEPaperBusyPin));

bool hasWiFiCredentials() {
  return strlen(HOMEOS_WIFI_SSID) > 0 && strlen(HOMEOS_WIFI_PASSWORD) > 0;
}

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

void printClockInfo() {
  Serial.print("WiFi credentials   : ");
  Serial.println(hasWiFiCredentials() ? "configured locally" : "not configured");
  Serial.println("Timezone           : IST (UTC+05:30)");
  Serial.print("Clock refresh      : full refresh every ");
  Serial.print(kClockRefreshIntervalMs / 1000);
  Serial.println(" seconds");
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

void drawRightText(const char *text, int16_t rightX, int16_t baselineY) {
  int16_t boundsX = 0;
  int16_t boundsY = 0;
  uint16_t boundsWidth = 0;
  uint16_t boundsHeight = 0;
  display.getTextBounds(text, 0, baselineY, &boundsX, &boundsY, &boundsWidth,
                        &boundsHeight);
  const int16_t x = rightX - boundsWidth - boundsX;
  display.setCursor(x, baselineY);
  display.print(text);
}

const char *clockStatusMessage() {
  switch (clockStatus) {
    case ClockStatus::kTimeSynced:
      return "IST via NTP";
    case ClockStatus::kTimeSyncFailed:
      return "Time not synced";
    case ClockStatus::kWiFiConnectFailed:
      return "WiFi not connected";
    case ClockStatus::kWiFiNotConfigured:
    default:
      return "WiFi not configured";
  }
}

void drawClockScreen() {
  struct tm timeInfo;
  const bool hasTime =
      clockStatus == ClockStatus::kTimeSynced && getLocalTime(&timeInfo, 100);

  char timeText[12] = "";
  char dateText[24] = "";
  if (hasTime) {
    strftime(timeText, sizeof(timeText), "%I:%M %p", &timeInfo);
    strftime(dateText, sizeof(dateText), "%a, %d %b %Y", &timeInfo);
    lastRenderedMinute = timeInfo.tm_min;
  } else {
    lastRenderedMinute = -1;
  }

  display.setRotation(0);
  display.setFullWindow();
  display.firstPage();
  do {
    display.fillScreen(GxEPD_WHITE);
    display.setTextColor(GxEPD_BLACK);

    display.setFont(&FreeMono9pt7b);
    display.setCursor(16, 28);
    display.print("HomeOS Clock");
    drawRightText(WiFi.status() == WL_CONNECTED ? "WiFi" : "Offline", 384, 28);
    display.drawFastHLine(16, 42, 368, GxEPD_BLACK);

    if (hasTime) {
      display.setFont(&FreeMonoBold24pt7b);
      drawCenteredText(timeText, 145);

      display.setFont(&FreeMono9pt7b);
      drawCenteredText(dateText, 188);
    } else {
      display.setFont(&FreeMonoBold18pt7b);
      drawCenteredText("Clock setup", 130);

      display.setFont(&FreeMono9pt7b);
      drawCenteredText(clockStatusMessage(), 172);
      drawCenteredText("Check serial logs", 202);
    }

    display.setFont(&FreeMono9pt7b);
    display.drawFastHLine(16, 236, 368, GxEPD_BLACK);
    drawCenteredText(clockStatusMessage(), 264);
    drawCenteredText("Full refresh only", 288);
  } while (display.nextPage());

  lastClockRefreshMs = millis();
}

ClockStatus connectWiFiAndSyncTime() {
  lastClockSyncAttemptMs = millis();

  if (!hasWiFiCredentials()) {
    Serial.println("WiFi credentials are not configured.");
    Serial.println("Create ignored firmware/include/config.local.h to enable NTP.");
    return ClockStatus::kWiFiNotConfigured;
  }

  Serial.println("Connecting WiFi using local credentials.");
  WiFi.mode(WIFI_STA);
  WiFi.begin(HOMEOS_WIFI_SSID, HOMEOS_WIFI_PASSWORD);

  const unsigned long connectStartMs = millis();
  while (WiFi.status() != WL_CONNECTED &&
         millis() - connectStartMs < kWiFiConnectTimeoutMs) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("WiFi connection failed, status code: ");
    Serial.println(WiFi.status());
    return ClockStatus::kWiFiConnectFailed;
  }

  Serial.print("WiFi connected, RSSI: ");
  Serial.print(WiFi.RSSI());
  Serial.println(" dBm");

  configTzTime(kTimeZone, kNtpServer1, kNtpServer2);
  Serial.println("Waiting for NTP time sync.");

  struct tm timeInfo;
  const unsigned long syncStartMs = millis();
  while (!getLocalTime(&timeInfo, 250) &&
         millis() - syncStartMs < kTimeSyncTimeoutMs) {
    delay(250);
    Serial.print(".");
  }
  Serial.println();

  if (!getLocalTime(&timeInfo, 100)) {
    Serial.println("NTP time sync failed.");
    return ClockStatus::kTimeSyncFailed;
  }

  Serial.println("NTP time sync complete.");
  return ClockStatus::kTimeSynced;
}

void runClockScreen() {
  Serial.println();
  Serial.println("Starting ePaper clock screen.");
  Serial.println("If the display is not wired, disconnect USB and wire it before upload.");

  SPI.begin(kEPaperSckPin, -1, kEPaperMosiPin, kEPaperCsPin);

  // Waveshare ePaper boards may need a shortened reset pulse.
  display.init(115200, true, 2, false);
  clockStatus = connectWiFiAndSyncTime();
  drawClockScreen();
  display.hibernate();

  Serial.println("Clock screen refresh command complete. Check the ePaper screen.");
}

void refreshClockIfNeeded(unsigned long now) {
  if (clockStatus != ClockStatus::kTimeSynced) {
    if (hasWiFiCredentials() &&
        now - lastClockSyncAttemptMs >= kClockRetryIntervalMs) {
      Serial.println("Retrying WiFi/NTP clock sync.");
      display.init(115200, true, 2, false);
      clockStatus = connectWiFiAndSyncTime();
      drawClockScreen();
      display.hibernate();
    }
    return;
  }

  struct tm timeInfo;
  if (!getLocalTime(&timeInfo, 50)) {
    Serial.println("Local time became unavailable.");
    clockStatus = ClockStatus::kTimeSyncFailed;
    display.init(115200, true, 2, false);
    drawClockScreen();
    display.hibernate();
    return;
  }

  if (timeInfo.tm_min != lastRenderedMinute &&
      now - lastClockRefreshMs >= kClockRefreshIntervalMs) {
    Serial.println("Refreshing ePaper clock minute.");
    display.init(115200, true, 2, false);
    drawClockScreen();
    display.hibernate();
  }
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
  Serial.println("Display status     : wired for clock screen");
  Serial.println();

  printChipInfo();
  printMemoryInfo();
  printDisplayInfo();
  printClockInfo();

  runClockScreen();
}

void loop() {
  const unsigned long now = millis();
  refreshClockIfNeeded(now);

  if (now - lastHeartbeatMs >= kHeartbeatIntervalMs) {
    lastHeartbeatMs = now;
    Serial.print("HomeOS heartbeat, uptime seconds: ");
    Serial.println(now / 1000);
  }
}
