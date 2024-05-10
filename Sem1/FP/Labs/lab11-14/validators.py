from domain import Person, Event, Participation
import re
from datetime import datetime

class Validator:
    def validate_person(self, person):
        if not isinstance(person, Person):
            raise ValueError("Invalid person object.")

        if not isinstance(person.get_person_id(), int) or person.get_person_id() < 0:
            raise ValueError("Invalid person ID.")

        if not isinstance(person.get_name(), str) or not person.get_name():
            raise ValueError("Invalid person name.")

        if not isinstance(person.get_address(), str) or not person.get_address():
            raise ValueError("Invalid person address.")

    def validate_event(self, event):
        if not isinstance(event, Event):
            raise ValueError("Invalid event object.")

        if not isinstance(event.get_event_id(), int) or event.get_event_id() < 0:
            raise ValueError("Invalid event ID.")

        if not self.is_valid_date(event.get_date()):
            raise ValueError("Invalid event date format or value.")

        if not self.is_valid_time(event.get_time()):
            raise ValueError("Invalid event time format or value.")

        if not isinstance(event.get_description(), str) or not event.get_description():
            raise ValueError("Invalid event description.")

    def validate_participation(self, participation):
        if not isinstance(participation, Participation):
            raise ValueError("Invalid participation object.")

        if not isinstance(participation.get_person_id(), int) or participation.get_person_id() < 0:
            raise ValueError("Invalid participation person ID.")

        if not isinstance(participation.get_event_id(), int) or participation.get_event_id() < 0:
            raise ValueError("Invalid participation event ID.")

    def is_valid_date(self, date_str):
        try:
            datetime.strptime(date_str, '%Y-%m-%d')
            return True
        except ValueError:
            return False

    def is_valid_time(self, time_str):
        if len(time_str) != 5:
            return False

        hours, minutes = time_str.split(':')

        if not hours.isdigit() or not minutes.isdigit():
            return False

        hours, minutes = int(hours), int(minutes)

        return 0 <= hours <= 23 and 0 <= minutes <= 59
