class Person:
    def __init__(self, person_id, name, address):
        self.person_id = person_id
        self.name = name
        self.address = address
        self.events = []


class Event:
    def __init__(self, event_id, date, time, description):
        self.event_id = event_id
        self.date = date
        self.time = time
        self.description = description
        self.participants = []

    def __str__(self):
        return f"{self.description} - {self.date} {self.time}"