import unittest
from controller import Controller
from file_repository import FileRepository
from validators import Validator
from domain import Person, Event

class TestController(unittest.TestCase):
    def setUp(self):
        self.repository = FileRepository("test_people.txt", "test_events.txt")
        self.validator = Validator()
        self.controller = Controller(self.repository, self.validator)

    def test_add_person(self):
        # Blackbox testing
        person_id = 1
        name = "Patricia"
        address = "Oradea"

        result = self.controller.add_person(person_id, name, address)

        people = self.controller.get_all_people()
        self.assertEqual(len(people), 1)
        self.assertEqual(people[0].get_person_id(), person_id)
        self.assertEqual(people[0].get_name(), name)
        self.assertEqual(people[0].get_address(), address)

        self.assertTrue(result)

    def test_add_event(self):
        self.controller.add_event(1, "2022-01-01", "12:00", "Eveniment de test")
        event = self.repository.get_all_events()[0]
        self.assertEqual(event.get_event_id(), 1)
        self.assertEqual(event.get_date(), "2022-01-01")
        self.assertEqual(event.get_time(), "12:00")
        self.assertEqual(event.get_description(), "Eveniment de test")

    def test_get_all_people(self):
        self.controller.add_person(1, "Patricia", "Oradea")
        self.controller.add_person(2, "Ion", "Oradea")
        people = self.controller.get_all_people()
        self.assertEqual(len(people), 2)
        self.assertEqual(people[0].get_name(), "Patricia")
        self.assertEqual(people[1].get_name(), "Ion")

    def test_get_all_events(self):
        self.controller.add_event(1, "2022-01-01", "12:00", "Eveniment de test")
        self.controller.add_event(2, "2022-01-02", "14:00", "Alt eveniment")
        events = self.controller.get_all_events()
        self.assertEqual(len(events), 2)
        self.assertEqual(events[0].get_description(), "Eveniment de test")
        self.assertEqual(events[1].get_description(), "Alt eveniment")

    def test_update_person(self):
        self.controller.add_person(1, "Patricia", "Oradea")
        updated_person = Person(1, "Patricia Updated", "Oradea Updated")
        self.controller.update_person(updated_person)
        person = self.repository.get_all_people()[0]
        self.assertEqual(person.get_name(), "Patricia Updated")
        self.assertEqual(person.get_address(), "Oradea Updated")

    def test_update_event(self):
        self.controller.add_event(1, "2022-01-01", "12:00", "Eveniment de test")
        updated_event = Event(1, "2022-01-02", "14:00", "Eveniment actualizat")
        self.controller.update_event(updated_event)
        event = self.repository.get_all_events()[0]
        self.assertEqual(event.get_date(), "2022-01-02")
        self.assertEqual(event.get_description(), "Eveniment actualizat")

    def test_delete_person(self):
        self.controller.add_person(1, "Patricia", "Oradea")
        self.controller.delete_person(1)
        people = self.repository.get_all_people()
        self.assertEqual(len(people), 0)

    def test_delete_event(self):
        self.controller.add_event(1, "2022-01-01", "12:00", "Eveniment de test")
        self.controller.delete_event(1)
        events = self.repository.get_all_events()
        self.assertEqual(len(events), 0)

    def test_participate_person(self):
        self.controller.add_person(1, "Patricia", "Oradea")
        self.controller.add_event(1, "2022-01-01", "12:00", "Eveniment de test")
        self.controller.participate_person(1, 1)
        person = self.repository.get_all_people()[0]
        self.assertEqual(person.get_person_id(), 1)
        self.assertEqual(person.get_name(), "Patricia")
        self.assertEqual(person.get_address(), "Oradea")
        self.assertEqual(person.get_events_participated(), [1])

    def test_get_events_participated(self):
        self.controller.add_person(1, "Patricia", "Oradea")
        self.controller.add_event(1, "2022-01-01", "12:00", "Eveniment de test")
        self.controller.participate_person(1, 1)
        events_participated = self.controller.get_events_participated(1)
        self.assertEqual(events_participated, [(1, "2022-01-01", "12:00", "Eveniment de test")])

    def test_get_persons_ordered_alphabetically(self):
        self.controller.add_person(2, "Ion", "Oradea")
        self.controller.add_person(1, "Patricia", "Oradea")
        persons_ordered = self.controller.get_persons_ordered_alphabetically()
        self.assertEqual(len(persons_ordered), 2)
        self.assertEqual(persons_ordered[0].get_name(), "Ion")
        self.assertEqual(persons_ordered[1].get_name(), "Patricia")

    def test_get_persons_ordered_by_events_participated(self):
        self.controller.add_person(1, "Patricia", "Oradea")
        self.controller.add_person(2, "Ion", "Oradea")
        self.controller.add_person(3, "Maria", "Oradea")
        self.controller.add_event(1, "2022-01-01", "12:00", "Eveniment 1")
        self.controller.add_event(2, "2022-01-02", "14:00", "Eveniment 2")
        self.controller.participate_person(1, 1)
        self.controller.participate_person(1, 2)
        self.controller.participate_person(2, 1)
        persons_ordered = self.controller.get_persons_ordered_by_events_participated()
        self.assertEqual(len(persons_ordered), 3)
        self.assertEqual(persons_ordered[0].get_name(), "Patricia")
        self.assertEqual(persons_ordered[1].get_name(), "Ion")
        self.assertEqual(persons_ordered[2].get_name(), "Maria")

    def test_get_top_events_percentage(self):
        self.controller.add_person(1, "Patricia", "Oradea")
        self.controller.add_person(2, "Ion", "Oradea")
        self.controller.add_person(3, "Maria", "Oradea")
        self.controller.add_event(1, "2022-01-01", "12:00", "Eveniment 1")
        self.controller.add_event(2, "2022-01-02", "14:00", "Eveniment 2")
        self.controller.participate_person(1, 1)
        self.controller.participate_person(1, 2)
        self.controller.participate_person(2, 1)
        self.controller.participate_person(3, 1)
        self.controller.participate_person(3, 2)
        top_events_percentage = self.controller.get_top_events_percentage()
        self.assertEqual(len(top_events_percentage), 1)
        self.assertEqual(top_events_percentage[0].get_description(), "Eveniment 1")


if __name__ == '__main__':
    unittest.main()
