import unittest
from file_repository import FileRepository
from domain import Person, Event
from validators import Validator

class TestRepository(unittest.TestCase):
    def setUp(self):
        self.repository = FileRepository("test_people.txt", "test_events.txt")
        self.validator = Validator()

    def test_add_person(self):
        self.repository.add_person(Person(1, "Patricia", "Oradea"))
        person = self.repository.get_all_people()[0]
        self.assertEqual(person.get_person_id(), 1)
        self.assertEqual(person.get_name(), "Patricia")
        self.assertEqual(person.get_address(), "Oradea")

    def test_add_event(self):
        self.repository.add_event(Event(1, "2022-01-01", "12:00", "Eveniment de test"))
        event = self.repository.get_all_events()[0]
        self.assertEqual(event.get_event_id(), 1)
        self.assertEqual(event.get_date(), "2022-01-01")
        self.assertEqual(event.get_time(), "12:00")
        self.assertEqual(event.get_description(), "Eveniment de test")

    def test_get_all_people(self):
        self.repository.add_person(Person(1, "Patricia", "Oradea"))
        self.repository.add_person(Person(2, "Ion", "Oradea"))
        people = self.repository.get_all_people()
        self.assertEqual(len(people), 2)
        self.assertEqual(people[0].get_name(), "Patricia")
        self.assertEqual(people[1].get_name(), "Ion")

    def test_get_all_events(self):
        self.repository.add_event(Event(1, "2022-01-01", "12:00", "Eveniment de test"))
        self.repository.add_event(Event(2, "2022-01-02", "14:00", "Alt eveniment"))
        events = self.repository.get_all_events()
        self.assertEqual(len(events), 2)
        self.assertEqual(events[0].get_description(), "Eveniment de test")
        self.assertEqual(events[1].get_description(), "Alt eveniment")

    def test_update_person(self):
        self.repository.add_person(Person(1, "Patricia", "Oradea"))
        updated_person = Person(1, "Patricia Updated", "Oradea Updated")
        self.repository.update_person(updated_person)
        person = self.repository.get_all_people()[0]
        self.assertEqual(person.get_name(), "Patricia Updated")
        self.assertEqual(person.get_address(), "Oradea Updated")

    def test_update_event(self):
        self.repository.add_event(Event(1, "2022-01-01", "12:00", "Eveniment de test"))
        updated_event = Event(1, "2022-01-02", "14:00", "Eveniment actualizat")
        self.repository.update_event(updated_event)
        event = self.repository.get_all_events()[0]
        self.assertEqual(event.get_date(), "2022-01-02")
        self.assertEqual(event.get_description(), "Eveniment actualizat")

    def test_delete_person(self):
        self.repository.add_person(Person(1, "Patricia", "Oradea"))
        self.repository.delete_person(1)
        people = self.repository.get_all_people()
        self.assertEqual(len(people), 0)

    def test_delete_event(self):
        self.repository.add_event(Event(1, "2022-01-01", "12:00", "Eveniment de test"))
        self.repository.delete_event(1)
        events = self.repository.get_all_events()
        self.assertEqual(len(events), 0)

    def test_modify_person(self):
        self.repository.add_person(Person(1, "Patricia", "Oradea"))
        modified_person = Person(1, "Patricia Updated", "Oradea Updated")
        self.repository.modify_person(modified_person)
        person = self.repository.get_all_people()[0]
        self.assertEqual(person.get_name(), "Patricia Updated")
        self.assertEqual(person.get_address(), "Oradea Updated")

    def test_modify_event(self):
        self.repository.add_event(Event(1, "2022-01-01", "12:00", "Eveniment de test"))
        modified_event = Event(1, "2022-01-02", "14:00", "Eveniment actualizat")
        self.repository.modify_event(modified_event)
        event = self.repository.get_all_events()[0]
        self.assertEqual(event.get_date(), "2022-01-02")
        self.assertEqual(event.get_description(), "Eveniment actualizat")


if __name__ == '__main__':
    unittest.main()
