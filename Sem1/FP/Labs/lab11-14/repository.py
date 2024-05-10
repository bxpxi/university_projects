import random
from domain import Person, Event, Participation
from validators import Validator

class Repository:
    def __init__(self):
        self.people = []
        self.events = []
        self.participations = []

    def add_person(self, person):
        if not isinstance(person, Person):
            raise ValueError("Invalid person object")
        Validator().validate_person(person)
        self.people.append(person)

    def remove_person(self, person_id):
        self.people = [person for person in self.people if person.get_person_id() != person_id]

    def modify_person(self, person_id, new_name, new_address):
        for person in self.people:
            if person.get_person_id() == person_id:
                person.set_name(new_name)
                person.set_address(new_address)
                break

    def get_person_by_id(self, person_id):
        for person in self.people:
            if person.get_person_id() == person_id:
                return person
        return None

    def get_all_people(self):
        return self.people

    def add_event(self, event):
        if not isinstance(event, Event):
            raise ValueError("Invalid event object.")
        Validator().validate_event(event)
        self.events.append(event)

    def remove_event(self, event_id):
        self.events = [event for event in self.events if event.get_event_id() != event_id]

    def modify_event(self, event_id, new_date, new_time, new_description):
        for event in self.events:
            if event.get_event_id() == event_id:
                event.set_date(new_date)
                event.set_time(new_time)
                event.set_description(new_description)
                break

    def get_event_by_id(self, event_id):
        for event in self.events:
            if event.get_event_id() == event_id:
                return event
        return None

    def get_all_events(self):
        return self.events

    def add_participation(self, person_id, event_id):
        participation = Participation(person_id, event_id)
        Validator().validate_participation(participation)
        self.participations.append(participation)

    def remove_participation(self, person_id, event_id):
        self.participations = [participation for participation in self.participations
                               if participation.get_person_id() != person_id or participation.get_event_id() != event_id]

    def modify_participation(self, person_id, event_id, new_person_id, new_event_id):
        for participation in self.participations:
            if participation.get_person_id() == person_id and participation.get_event_id() == event_id:
                participation.set_person_id(new_person_id)
                participation.set_event_id(new_event_id)
                break

    def get_all_participations(self):
        return self.participations

    # lab 10 - functionalitate in plus - adaugare random
    def generate_random_person(self):
        person_id = len(self.people) + 1

        names = ["Ion", "Maria", "Andrei", "Elena", "Alex", "Ana", "Patricia", "Carla", "Iulia"]
        cities = ["Oradea", "Cluj-Napoca", "Timișoara", "Iași", "București", "Arad", "Suceava", "Constanta"]

        name = random.choice(names)
        city = random.choice(cities)

        return Person(person_id, name, city)

    def generate_random_event(self):
        event_id = len(self.events) + 1

        year = random.randint(2024, 2025)
        month = random.randint(1, 12)
        day = random.randint(1, 28)

        date = f"{year:04d}-{month:02d}-{day:02d}"

        hour = random.randint(0, 23)
        minute = random.randint(0, 59)

        time = f"{hour:02d}:{minute:02d}"

        descriptions = ["Concert", "Conferință", "Petrecere", "Spectacol", "Expoziție", "Film", "Prezentare"]

        description = random.choice(descriptions)

        return Event(event_id, date, time, f"{description}")

    def generate_and_add_random_data(self, num_people, num_events):
        for _ in range(num_people):
            person = self.generate_random_person()
            self.add_person(person)

        for _ in range(num_events):
            event = self.generate_random_event()
            self.add_event(event)
