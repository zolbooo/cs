import re
from datetime import datetime

from telegram import Update
from telegram.ext import ApplicationBuilder, CommandHandler, ContextTypes

from .data import code_lookup
from .flight_duration import get_duration


usage = """Usage: /flight_duration <from code> <time> <destination code> <time>
Example: /flight_duration KZN 14:00 MOW 15:50
"""


request_regex = re.compile(
    "\\s*(?P<from>[A-Z]{3})\\s+(?P<from_time>\\d{1,2}:\\d{1,2})\\s+(?P<dest>[A-Z]{3})\\s+(?P<dest_time>\\d{1,2}:\\d{1,2})\\s*"
)


def _answer_flight_duration(request: str) -> str:
    if len(request) == 0:
        return usage
    match = request_regex.match(request)
    if match is None:
        return "Incorrect request.\n" + usage

    request_data = match.groupdict()
    from_airport = code_lookup(request_data["from"])
    if from_airport is None:
        return "Cannot find an airport with code " + request_data["from"]
    dest_airport = code_lookup(request_data["dest"])
    if dest_airport is None:
        return "Cannot find an airport with code " + request_data["dest"]

    departure_local_time: datetime
    try:
        departure_local_time = datetime.strptime(request_data["from_time"], "%H:%M")
    except:
        return "Incorrect departure time: " + request_data["from_time"]
    arrival_local_time: datetime
    try:
        arrival_local_time = datetime.strptime(request_data["dest_time"], "%H:%M")
    except:
        return "Incorrect arrival time: " + request_data["dest_time"]

    from_name = from_airport.name or from_airport.code
    dest_name = dest_airport.name or dest_airport.code
    flight_duration = get_duration(
        from_airport, dest_airport, departure_local_time, arrival_local_time
    )
    return "\n".join(
        [f"✈️ Flight from {from_name} to {dest_name}", f"🌎 Duration: {flight_duration}"]
    )


async def _flight_duration(update: Update, _: ContextTypes.DEFAULT_TYPE) -> None:
    if update.message is None or update.message.text is None:
        return
    command_payload = update.message.text[len("/flight_duration ") :]
    await update.message.reply_text(_answer_flight_duration(command_payload))


def start_bot(token: str):
    app = ApplicationBuilder().token(token).build()
    app.add_handler(CommandHandler("flight_duration", _flight_duration))
    print("Bot is ready to run!")
    app.run_polling()


__all__ = ["start_bot"]
