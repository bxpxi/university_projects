import unittest
from validators import Validator

class TestValidators(unittest.TestCase):
    def setUp(self):
        self.validator = Validator()

    def test_validate_person(self):
        self.assertTrue(self.validator.validate_person("Ion", "Oradea"))

    def test_validate_event(self):
        self.assertTrue(self.validator.validate_event("2022-01-01", "12:00", "Eveniment de test"))

if __name__ == '__main__':
    unittest.main()
