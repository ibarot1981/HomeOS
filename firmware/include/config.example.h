#pragma once

// Copy this file to firmware/include/config.local.h and fill in local values.
// config.local.h is ignored by git so credentials stay off the repository.

#define HOMEOS_WIFI_SSID "your-wifi-ssid"
#define HOMEOS_WIFI_PASSWORD "your-wifi-password"

// Create the bot and obtain these values only when ready to test locally.
// Keep the bot token and all chat IDs private. Multiple allowed IDs use commas.
#define HOMEOS_TELEGRAM_BOT_TOKEN "your-telegram-bot-token"
#define HOMEOS_TELEGRAM_ALLOWED_CHAT_IDS "your-telegram-chat-id"
