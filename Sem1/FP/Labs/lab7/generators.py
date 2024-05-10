import random
from entities import Person, Event

class PersonGenerator:
    def __init__(self):
        self.names = ["Ion", "Maria", "Ana", "Mihai", "Elena", "George", "Larisa", "Adrian", "Andreea", "Alexandra", "Patricia"]
        self.cities = ["București", "Cluj-Napoca", "Iași", "Timișoara", "Iasi", "Constanța", "Oradea", "Brașov", "Galați", "Sibiu"]

    def generate_random_person(self):
        person_id = random.randint(1, 1000)
        name = random.choice(self.names)
        city = random.choice(self.cities)
        address = f"{random.randint(1, 100)} {city} Strada"
        return Person(person_id, name, address)

class EventGenerator:
    def __init__(self):
        self.descriptions = ["Concert", "Expoziție", "Spectacol", "Lansare de carte", "Conferință", "Teatru", "Festival", "Curs", "Prezentare"]

    def generate_random_event(self):
        event_id = random.randint(1, 1000)
        date = f"2023-{random.randint(1, 12):02d}-{random.randint(1, 28):02d}"
        time = f"{random.randint(0, 23):02d}:{random.randint(0, 59):02d}"
        description = random.choice(self.descriptions)
        return Event(event_id, date, time, description)