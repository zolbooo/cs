import os
import csv
from dataclasses import dataclass


@dataclass
class AirportData:
    code: str
    name: str
    timezone_id: str
    country_id: str


data: dict[str, AirportData] | None = None


def _parse_data():
    global data
    reader = csv.DictReader(
        open(os.path.join(os.getcwd(), "airport-codes", "airports.csv"), "r")
    )
    data = dict(
        map(
            lambda entry: (
                entry["code"],
                AirportData(
                    code=entry["code"],
                    name=entry["name"],
                    timezone_id=entry["time_zone_id"],
                    country_id=entry["country_id"],
                ),
            ),
            reader,
        )
    )


def code_lookup(code: str) -> AirportData | None:
    if data is None:
        _parse_data()
    assert data is not None
    return data[code]


__all__ = ["AirportData", "code_lookup"]
