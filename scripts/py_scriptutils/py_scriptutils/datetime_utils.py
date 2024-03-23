from datetime import datetime

def format_iso8601(time: datetime):
    return time.strftime("%Y-%m-%dT%H:%M:%S")

def format_iso8601_date(time: datetime):
    return time.strftime("%Y-%m-%d")
