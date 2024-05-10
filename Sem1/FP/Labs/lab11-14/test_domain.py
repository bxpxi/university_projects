import unittest
from domain import Person, Event

class TestDomain(unittest.TestCase):
    def test_person_properties(self):
        person = Person(1, "Ion", "Oradea")

        self.assertEqual(person.get_person_id(), 1)
        self.assertEqual(person.get_name(), "Ion")
        self.assertEqual(person.get_address(), "Oradea")

    def test_event_properties(self):
        event = Event(1, "2022-01-01", "12:00", "Eveniment de test")

        self.assertEqual(event.get_event_id(), 1)
        self.assertEqual(event.get_date(), "2022-01-01")
        self.assertEqual(event.get_time(), "12:00")
        self.assertEqual(event.get_description(), "Eveniment de test")

if __name__ == '__main__':
    unittest.main()
