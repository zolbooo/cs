import pytz
from datetime import datetime, timedelta

from .data import AirportData


def _format_duration(delta: timedelta) -> str:
    result = []
    total_duration_minutes = delta.total_seconds() // 60
    duration_hours = int(total_duration_minutes // 60)
    duration_minutes = int(total_duration_minutes % 60)
    if duration_hours > 0:
        result.append(f"{duration_hours} hours")
    if duration_minutes > 0:
        result.append(f"{duration_minutes} minutes")
    return " ".join(result)


def get_duration(
    from_airport: AirportData,
    dest_airport: AirportData,
    from_time: datetime,
    dest_time: datetime,
) -> timedelta | str:
    departure_time_utc = from_time.replace(
        tzinfo=pytz.timezone(from_airport.timezone_id)
    ).astimezone(pytz.utc)
    arrival_time_utc = dest_time.replace(
        tzinfo=pytz.timezone(dest_airport.timezone_id)
    ).astimezone(pytz.utc)
    if arrival_time_utc < departure_time_utc:
        arrival_time_utc += timedelta(days=1)

    assert arrival_time_utc >= departure_time_utc
    return _format_duration(arrival_time_utc - departure_time_utc)


__all__ = ["get_duration"]
