import json
from entities import Person, Event

class PersonFileRepository:
    def __init__(self, file_path):
        self.file_path = file_path
        self.persons = self.load()
        self.id_set = {person.person_id for person in self.persons}

    def save(self):
        with open(self.file_path, 'w') as file:
            data = [{'person_id': person.person_id, 'name': person.name, 'address': person.address} for person in self.persons]
            json.dump(data, file)

    def load(self):
        try:
            with open(self.file_path, 'r') as file:
                data = json.load(file)
                return [Person(person['person_id'], person['name'], person['address']) for person in data]
        except FileNotFoundError:
            return []

    def add_person(self, person):
        if person.person_id in self.id_set:
            raise ValueError("Person with the same ID already exists.")
        self.persons.append(person)
        self.id_set.add(person.person_id)
        self.save()

    def remove_person(self, person_id):
        for person in self.persons:
            if person.person_id == person_id:
                self.persons.remove(person)
                self.save()
                return True
        return False

    def update_person(self, person_id, new_name=None, new_address=None):
        for person in self.persons:
            if person.person_id == person_id:
                person.name = new_name
                person.address = new_address
                return True
        return False

        self.save()

    def get_person_by_id(self, person_id):
        for person in self.persons:
            if person.person_id == person_id:
                return person
        return None


    def get_all_persons(self):
        return self.persons

    def clear_all_persons(self):
        self.persons = []
        self.save()

class EventFileRepository:
    def __init__(self, file_path):
        self.file_path = file_path
        self.events = self.load()
        self.id_set = {event.event_id for event in self.events}

    def save(self):
        with open(self.file_path, 'w') as file:
            data = [
                {'event_id': event.event_id, 'date': event.date, 'time': event.time, 'description': event.description,
                 'participants': event.participants} for event in self.events]
            json.dump(data, file)

    def load(self):
        try:
            with open(self.file_path, 'r') as file:
                data = json.load(file)
                return [Event(event['event_id'], event['date'], event['time'], event['description']
                              ) for event in data]
        except FileNotFoundError:
            return []

    def add_event(self, event):
        if event.event_id in self.id_set:
            raise ValueError("Event with the same ID already exists.")
        self.events.append(event)
        self.id_set.add(event.event_id)
        self.save()

    def remove_event(self, event_id):
        for event in self.events:
            if event.event_id == event_id:
                self.events.remove(event)
                self.save()
                return True
        return False

    def update_event(self, event_id, new_date=None, new_time=None, new_description=None):
        for event in self.events:
            if event.event_id == event_id:
                if new_date:
                    event.date = new_date
                if new_time:
                    event.time = new_time
                if new_description:
                    event.description = new_description
        self.save()

    def get_event_by_id(self, event_id):
        for event in self.events:
            if event.event_id == event_id:
                return event
        return None

    def get_all_events(self):
        return self.events

    def clear_all_events(self):
        self.events = []
        self.save()


