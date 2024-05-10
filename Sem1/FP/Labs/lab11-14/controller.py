from file_repository import FileRepository
from domain import Person, Event, Participation
from validators import Validator
from repository import Repository
from sorting import generic_sort
class Controller:
    def __init__(self, repository, validator):
        self.repository = repository
        self.validator = validator

    def add_person(self, person_id, name, address):
        person = Person(person_id, name, address)
        self.validator.validate_person(person)
        self.repository.add_person(person)

    def remove_person(self, person_id):
        self.repository.remove_person(person_id)

    def modify_person(self, person_id, new_name, new_address):
        self.repository.modify_person(person_id, new_name, new_address)

    def get_person_by_id(self, person_id):
        return self.repository.get_person_by_id(person_id)

    def get_all_people(self):
        return self.repository.get_all_people()

    def add_event(self, event_id, date, time, description):
        event = Event(event_id, date, time, description)
        self.validator.validate_event(event)
        self.repository.add_event(event)

    def remove_event(self, event_id):
        self.repository.remove_event(event_id)

    def modify_event(self, event_id, new_date, new_time, new_description):
        self.repository.modify_event(event_id, new_date, new_time, new_description)

    def get_event_by_id(self, event_id):
        return self.repository.get_event_by_id(event_id)

    def get_all_events(self):
        return self.repository.get_all_events()

    def add_participation(self, person_id, event_id):
        participation = Participation(person_id, event_id)
        self.validator.validate_participation(participation)
        self.repository.add_participation(person_id, event_id)

    def remove_participation(self, person_id, event_id):
        self.repository.remove_participation(person_id, event_id)

    def modify_participation(self, person_id, event_id, new_person_id, new_event_id):
        self.repository.modify_participation(person_id, event_id, new_person_id, new_event_id)

    def get_all_participations(self):
        return self.repository.get_all_participations()

    def get_events_for_person_sorted_by_description(self, person_id, sort_algorithm="merge_sort"):
        person = self.repository.get_person_by_id(person_id)
        if not person:
            return []

        participations = [participation for participation in self.repository.get_all_participations()
                          if participation.get_person_id() == person_id]

        events = [self.repository.get_event_by_id(participation.get_event_id()) for participation in participations]

        sorted_events = generic_sort(
            events,
            key=lambda event: event.get_description(),
            algorithm=sort_algorithm
        )

        return sorted_events

    def get_events_for_person_sorted_by_date(self, person_id, sort_algorithm="merge_sort"):
        person = self.repository.get_person_by_id(person_id)
        if not person:
            return []

        participations = [participation for participation in self.repository.get_all_participations()
                          if participation.get_person_id() == person_id]

        events = [self.repository.get_event_by_id(participation.get_event_id()) for participation in participations]

        sorted_events = generic_sort(
            events,
            key=lambda event: event.get_date(),
            algorithm=sort_algorithm
        )

        return sorted_events

    def get_people_with_most_events(self, sort_algorithm="merge_sort"):
        participations_count = {}
        for participation in self.repository.get_all_participations():
            person_id = participation.get_person_id()
            participations_count[person_id] = participations_count.get(person_id, 0) + 1

        sorted_participations = generic_sort(
            participations_count.items(),
            key=lambda x: x[1],
            reverse=True,
            algorithm=sort_algorithm
        )

        max_participations = next(iter(sorted_participations), (None, 0))[1]

        people_with_most_events = [person_id for person_id, count in sorted_participations if
                                   count == max_participations]

        return people_with_most_events

    def get_top_events_with_most_participants(self, percentage, sort_algorithm="merge_sort"):
        total_participations = len(self.repository.get_all_participations())
        top_percentage = int(total_participations * percentage)
        #  complexitate de O(1), deoarece nu depinde de dimensiunea datelor de intrare

        events_participations = {}
        for participation in self.repository.get_all_participations():
            event_id = participation.get_event_id()
            events_participations[event_id] = events_participations.get(event_id, 0) + 1
        '''
        Această bucată de cod parcurge toate participările și calculează numărul de participări pentru fiecare eveniment. 
        Complexitatea este O(N), unde N este numărul total de participări
        '''

        sorted_events = generic_sort(
            events_participations.items(),
            key=lambda x: x[1],
            reverse=True,
            algorithm=sort_algorithm
        )
        top_events = sorted_events[:top_percentage]

        '''
        Sortarea listei events_participations are o complexitate O(N log N), unde N este numărul de evenimente unice. 
        Selectarea primelor top_percentage evenimente are o complexitate O(K), unde K este top_percentage. 
        În general, complexitatea acestei bucati este O(N log N + K).
        '''

        return top_events
        '''
        Astfel, complexitatea totală a funcției este dominată de sortare și este O(N log N + K).
        '''

    def generate_and_add_random_data(self, num_people, num_events):
        self.repository.generate_and_add_random_data(num_people, num_events)

    def save_data(self):
        self.repository.save_data()