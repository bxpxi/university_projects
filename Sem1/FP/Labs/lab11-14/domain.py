class Person:
    def __init__(self, person_id, name, address):
        self._person_id = person_id
        self._name = name
        self._address = address

    def get_person_id(self):
        return self._person_id

    def set_person_id(self, person_id):
        self._person_id = person_id

    def get_name(self):
        return self._name

    def set_name(self, name):
        self._name = name

    def get_address(self):
        return self._address

    def set_address(self, address):
        self._address = address


class Event:
    def __init__(self, event_id, date, time, description):
        self._event_id = event_id
        self._date = date
        self._time = time
        self._description = description

    def get_event_id(self):
        return self._event_id

    def set_event_id(self, event_id):
        self._event_id = event_id

    def get_date(self):
        return self._date

    def set_date(self, date):
        self._date = date

    def get_time(self):
        return self._time

    def set_time(self, time):
        self._time = time

    def get_description(self):
        return self._description

    def set_description(self, description):
        self._description = description


class Participation:
    def __init__(self, person_id, event_id):
        self._person_id = person_id
        self._event_id = event_id

    def get_person_id(self):
        return self._person_id

    def set_person_id(self, person_id):
        self._person_id = person_id

    def get_event_id(self):
        return self._event_id

    def set_event_id(self, event_id):
        self._event_id = event_id
