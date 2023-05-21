from os import getenv
from src.bot import start_bot

if __name__ == "__main__":
    token = getenv("BOT_TOKEN")
    if token is None:
        raise Exception(
            "Missing Telegram bot token. Please use BOT_TOKEN environment variable."
        )
    start_bot(token)
