import unittest
from entities import Person, Event
from repository import PersonRepository, EventRepository
from controller import Controller
from generators import PersonGenerator, EventGenerator
from file_repository import PersonFileRepository, EventFileRepository
class TestPersonRepository(unittest.TestCase):
    def setUp(self):
        self.person_repo = PersonFileRepository("test_persons.json")

    def test_add_person(self):
        person1 = Person(1, "Ion", "Cluj")
        self.person_repo.add_person(person1)
        self.assertEqual(len(self.person_repo.get_all_persons()), 1)

        # Try adding a person with the same ID
        person2 = Person(1, "Ana", "Arad")
        self.person_repo.add_person(person2)

    def test_remove_person(self):
        person1 = Person(1, "Ion", "Cluj")
        self.person_repo.add_person(person1)
        self.person_repo.remove_person(1)
        self.assertEqual(len(self.person_repo.get_all_persons()), 0)

    def test_update_person(self):
        person1 = Person(1, "Ion", "Cluj")
        self.person_repo.add_person(person1)
        self.person_repo.update_person(1, "Patricia", "Oradea")
        updated_person = self.person_repo.get_person_by_id(1)
        self.assertEqual(updated_person.name, "Patricia")
        self.assertEqual(updated_person.address, "Oradea")

    def test_get_person_by_id(self):
        person1 = Person(1, "Ion", "Cluj")
        self.person_repo.add_person(person1)
        result = self.person_repo.get_person_by_id(1)
        self.assertEqual(result.name, "Ion")
        self.assertEqual(result.address, "Cluj")


class TestEventRepository(unittest.TestCase):
    def setUp(self):
        self.event_repo = EventFileRepository("test_events.json")

    def test_add_event(self):
        event1 = Event(1, "2023-12-01", "12:30", "Concert")
        self.event_repo.add_event(event1)
        self.assertEqual(len(self.event_repo.get_all_events()), 1)

        # Try adding an event with the same ID
        event2 = Event(1, "2023-12-15", "18:00", "Film")
        self.event_repo.add_event(event2)

    def test_remove_event(self):
        event1 = Event(1, "2023-12-01", "12:30", "Concert")
        self.event_repo.add_event(event1)
        self.event_repo.remove_event(1)
        self.assertEqual(len(self.event_repo.get_all_events()), 0)

    def test_update_event(self):
        event1 = Event(1, "2023-12-01", "12:30", "Concert")
        self.event_repo.add_event(event1)
        self.event_repo.update_event(1, "2023-12-20", "20:00", "Picnic")
        updated_event = self.event_repo.get_event_by_id(1)
        self.assertEqual(updated_event.date, "2023-12-20")
        self.assertEqual(updated_event.time, "20:00")
        self.assertEqual(updated_event.description, "Picnic")

    def test_get_event_by_id(self):
        event1 = Event(1, "2023-12-01", "12:30", "Concert")
        self.event_repo.add_event(event1)
        result = self.event_repo.get_event_by_id(1)
        self.assertEqual(result.date, "2023-12-01")
        self.assertEqual(result.time, "12:30")
        self.assertEqual(result.description, "Concert")


class TestController(unittest.TestCase):
    def setUp(self):
        self.person_repo = PersonFileRepository("test_persons.json")
        self.event_repo = EventFileRepository("test_events.json")
        person_generator = PersonGenerator()
        event_generator = EventGenerator()
        self.controller = Controller(self.person_repo, self.event_repo, person_generator, event_generator)

    def test_add_person(self):
        person1 = Person(1, "Ion", "Cluj")
        self.controller.add_person(person1)
        self.assertEqual(len(self.person_repo.get_all_persons()), 1)

        # Try adding a person with the same ID
        person2 = Person(1, "Ana", "Arad")
        self.controller.add_person(person2)

    def test_remove_person(self):
        person1 = Person(1, "Ion", "Cluj")
        self.controller.add_person(person1)
        self.controller.remove_person(1)
        self.assertEqual(len(self.person_repo.get_all_persons()), 0)

    def test_update_person(self):
        person1 = Person(1, "Ion", "Cluj")
        self.controller.add_person(person1)
        self.controller.update_person(1, "Patricia", "Oradea")
        updated_person = self.person_repo.get_person_by_id(1)
        self.assertEqual(updated_person.name, "Patricia")
        self.assertEqual(updated_person.address, "Oradea")

    def test_add_event(self):
        event1 = Event(1, "2023-12-01", "12:30", "Concert")
        self.controller.add_event(event1)
        self.assertEqual(len(self.event_repo.get_all_events()), 1)

        # Try adding an event with the same ID
        event2 = Event(1, "2023-12-15", "18:00", "Film")
        self.controller.add_event(event2)

    def test_remove_event(self):
        event1 = Event(1, "2023-12-01", "12:30", "Concert")
        self.controller.add_event(event1)
        self.controller.remove_event(1)
        self.assertEqual(len(self.event_repo.get_all_events()), 0)

    def test_update_event(self):
        event1 = Event(1, "2023-12-01", "12:30", "Concert")
        self.controller.add_event(event1)
        self.controller.update_event(1, "2023-12-20", "20:00", "Picnic")
        updated_event = self.event_repo.get_event_by_id(1)
        self.assertEqual(updated_event.date, "2023-12-20")
        self.assertEqual(updated_event.time, "20:00")
        self.assertEqual(updated_event.description, "Picnic")

    def test_enroll_person_in_event(self):
        person1 = Person(1, "Ion", "Cluj")
        self.controller.add_person(person1)
        event1 = Event(1, "2023-12-01", "12:30", "Concert")
        self.controller.add_event(event1)
        self.controller.enroll_person_in_event(1, 1)
        self.assertEqual(len(person1.events), 1)

    def test_get_person_events_ordered_by_description(self):
        person1 = Person(1, "Ion", "Cluj")
        self.controller.add_person(person1)
        event1 = Event(1, "2023-12-01", "12:30", "Concert")
        self.controller.add_event(event1)
        self.controller.enroll_person_in_event(1, 1)
        events_ordered = self.controller.get_person_events_ordered_by_description(1)
        self.assertEqual(len(events_ordered), 1)
        self.assertEqual(events_ordered[0].description, "Concert")

    def test_get_persons_participating_most_events(self):
        person1 = Person(1, "Ion", "Cluj")
        person2 = Person(2, "Ana", "Arad")
        self.controller.add_person(person1)
        self.controller.add_person(person2)
        event1 = Event(1, "2023-12-01", "12:30", "Concert")
        event2 = Event(2, "2023-12-15", "18:00", "Film")
        self.controller.add_event(event1)
        self.controller.add_event(event2)
        self.controller.enroll_person_in_event(1, 1)
        self.controller.enroll_person_in_event(2, 1)
        self.controller.enroll_person_in_event(1, 2)
        persons_most_participating = self.controller.get_persons_participating_most_events()
        self.assertEqual(len(persons_most_participating), 1)
        self.assertEqual(persons_most_participating[0].name, "Ion")

    def test_get_top_events_by_participants(self):
        person1 = Person(1, "Ion", "Cluj")
        person2 = Person(2, "Ana", "Arad")
        self.controller.add_person(person1)
        self.controller.add_person(person2)
        event1 = Event(1, "2023-12-01", "12:30", "Concert")
        event2 = Event(2, "2023-12-15", "18:00", "Film")
        self.controller.add_event(event1)
        self.controller.add_event(event2)
        self.controller.enroll_person_in_event(1, 1)
        self.controller.enroll_person_in_event(2, 1)
        self.controller.enroll_person_in_event(1, 2)
        top_events = self.controller.get_top_events_by_participants()
        self.assertEqual(len(top_events), 1)
        self.assertEqual(top_events[0][0].description, "Concert")

    def test_get_all_participants(self):
        person1 = Person(1, "Ion", "Cluj")
        person2 = Person(2, "Ana", "Arad")
        self.controller.add_person(person1)
        self.controller.add_person(person2)
        initial_persons = [person1, person2]
        participants = self.controller.get_all_participants()
        self.assertEqual(participants, initial_persons)

    def test_get_all_events(self):
        event1 = Event(1, "2023-12-01", "12:30", "Concert")
        event2 = Event(2, "2023-12-15", "18:00", "Film")
        self.controller.add_event(event1)
        self.controller.add_event(event2)
        initial_events = [event1, event2]
        events = self.controller.get_all_events()
        self.assertEqual(events, initial_events)

    def tearDown(self):
        self.person_repo.clear_all_persons()
        self.event_repo.clear_all_events()

if __name__ == '__main__':
    unittest.main()