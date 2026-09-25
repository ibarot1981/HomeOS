#include "telegram_service.h"

namespace {
constexpr unsigned long kTelegramPollIntervalMs = 1000;
constexpr unsigned int kTelegramResponseTimeoutMs = 500;
}

TelegramService::TelegramService(const char *botToken, const char *allowedChatIds,
                                 CommandHandler commandHandler)
    : botToken_(botToken),
      allowedChatIds_(allowedChatIds),
      commandHandler_(commandHandler),
      bot_(botToken, client_) {}

void TelegramService::begin() {
  if (!isEnabled()) {
    Serial.println("Telegram             : disabled (local config incomplete)");
    return;
  }

  client_.setCACert(TELEGRAM_CERTIFICATE_ROOT);
  client_.setTimeout(1);
  client_.setHandshakeTimeout(1);
  bot_.longPoll = 0;
  bot_.waitForResponse = kTelegramResponseTimeoutMs;
  Serial.println("Telegram             : enabled with local allowlist");
}

void TelegramService::poll(unsigned long now, bool networkReady) {
  if (!isEnabled() || !networkReady ||
      now - lastPollMs_ < kTelegramPollIntervalMs) {
    return;
  }

  lastPollMs_ = now;
  const int messageCount =
      bot_.getUpdates(bot_.last_message_received + 1);
  if (!initialPollComplete_) {
    initialPollComplete_ = true;
    if (messageCount > 0) {
      lastHandledUpdateId_ = bot_.messages[messageCount - 1].update_id;
      Serial.println("Telegram             : discarded queued updates at startup");
    }
    return;
  }

  for (int index = 0; index < messageCount; ++index) {
    const telegramMessage &message = bot_.messages[index];
    if (message.update_id <= lastHandledUpdateId_) {
      Serial.println("Telegram             : ignored duplicate update");
      continue;
    }
    lastHandledUpdateId_ = message.update_id;

    // A private user message has the sender's ID as its chat ID. Group and
    // supergroup messages use a distinct chat ID, so do not authorize them.
    if (message.type != "message" || message.chat_id != message.from_id ||
        !isAllowedChat(message.chat_id)) {
      Serial.println("Telegram             : ignored unauthorized or unsupported update");
      continue;
    }

    const String response = commandHandler_(message.text);
    if (!response.isEmpty() &&
        !bot_.sendMessage(message.chat_id, response, "")) {
      Serial.println("Telegram             : command response failed");
    }
  }
}

bool TelegramService::sendAlert(const String &message, bool networkReady) {
  if (!isEnabled() || !networkReady) {
    return false;
  }

  const bool sent = sendToAllowedChats(message);
  if (!sent) {
    Serial.println("Telegram             : alert delivery failed");
  }
  return sent;
}

bool TelegramService::isEnabled() const {
  return strlen(botToken_) > 0 && strlen(allowedChatIds_) > 0;
}

bool TelegramService::isAllowedChat(const String &chatId) const {
  String configuredIds(allowedChatIds_);
  int start = 0;
  while (start <= configuredIds.length()) {
    const int separator = configuredIds.indexOf(',', start);
    String allowedId = configuredIds.substring(
        start, separator == -1 ? configuredIds.length() : separator);
    allowedId.trim();
    if (!allowedId.isEmpty() && allowedId == chatId) {
      return true;
    }

    if (separator == -1) {
      break;
    }
    start = separator + 1;
  }

  return false;
}

bool TelegramService::sendToAllowedChats(const String &message) {
  bool allSent = true;
  String configuredIds(allowedChatIds_);
  int start = 0;
  while (start <= configuredIds.length()) {
    const int separator = configuredIds.indexOf(',', start);
    String allowedId = configuredIds.substring(
        start, separator == -1 ? configuredIds.length() : separator);
    allowedId.trim();
    if (!allowedId.isEmpty() && !bot_.sendMessage(allowedId, message, "")) {
      allSent = false;
    }

    if (separator == -1) {
      break;
    }
    start = separator + 1;
  }

  return allSent;
}
