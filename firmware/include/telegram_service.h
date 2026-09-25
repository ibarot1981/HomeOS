#pragma once

#include <Arduino.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

class TelegramService {
 public:
  using CommandHandler = String (*)(const String &command);

  TelegramService(const char *botToken, const char *allowedChatIds,
                  CommandHandler commandHandler);

  void begin();
  void poll(unsigned long now, bool networkReady);
  bool sendAlert(const String &message, bool networkReady);
  bool isEnabled() const;

 private:
  bool isAllowedChat(const String &chatId) const;
  bool sendToAllowedChats(const String &message);

  const char *botToken_;
  const char *allowedChatIds_;
  CommandHandler commandHandler_;
  WiFiClientSecure client_;
  UniversalTelegramBot bot_;
  unsigned long lastPollMs_ = 0;
  bool initialPollComplete_ = false;
};
