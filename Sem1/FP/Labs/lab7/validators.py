import re

class PersonValidator:
    @staticmethod
    def validate(person):
        '''
        Functie care face validarea pentru fiecare persoana
        :param person: din clasa Person (person_id, name, adress, events)
                        person_id : int > 0
                        name : sir nevid
                        adress : sir nevid
        :return: raise ValueError in caz ca person_id si/sau name si/sau adress nu corespunde
        '''
        if not isinstance(person.person_id, int) or person.person_id <= 0:
            raise ValueError("Invalid person ID")
        if not isinstance(person.name, str) or not person.name.strip():
            raise ValueError("Invalid person name")
        if not isinstance(person.address, str) or not person.address.strip():
            raise ValueError("Invalid person address")

    @staticmethod
    def validate_unique_id(person_id, id_set):
        if person_id in id_set:
            raise ValueError("Person with the same ID already exists.")


class EventValidator:
    DATE_REGEX = r"\d{4}-\d{2}-\d{2}"
    TIME_REGEX = r"\d{2}:\d{2}"

    @staticmethod
    def validate(event):
        '''
        Functie care verifica daca un eveniment e valid
        :param event: un event de clasa Event(event_id, date, time, description, participants)
                                event_id: int>0
                                date : YYYY-MM-DD
                                time: HH:MM
                                description: str nevid
        :return: raise ValueError daca nu se respecta cel putin una din conditii
        '''
        if not isinstance(event.event_id, int) or event.event_id <= 0:
            raise ValueError("Invalid event ID")
        if not re.match(EventValidator.DATE_REGEX, event.date):
            raise ValueError("Invalid event date format (YYYY-MM-DD)")
        if not re.match(EventValidator.TIME_REGEX, event.time):
            raise ValueError("Invalid event time format (HH:MM)")
        if not isinstance(event.description, str) or not event.description.strip():
            raise ValueError("Invalid event description")
    '''
    @staticmethod
    def validate_unique_id(event_id, id_set):
        if event_id in id_set:
            raise ValueError("Event with the same ID already exists.")
    '''