from validators import PersonValidator, EventValidator
from repository import PersonRepository, EventRepository
from operator import attrgetter, itemgetter
from sorting import generic_sort
class Controller:
    def __init__(self, person_repo, event_repo, person_generator, event_generator):
        self.person_repo = person_repo
        self.event_repo = event_repo
        self.person_generator = person_generator
        self.event_generator = event_generator

    def add_person(self, person):
        """
        Functie din controller care adauga o persoana
        :param person: o Person
        :return: -
        """
        PersonValidator.validate(person)
        self.person_repo.add_person(person)

    def remove_person(self, person_id):
        '''
        Functie din controller care sterge o persoana
        :param person_id: un person_id al unei Person
        :return: -
        '''
        self.person_repo.remove_person(person_id)

    def get_person_by_id(self, person_id):
        '''
        Functie care gaseste o persoana dupa person_id
        :param person_id: un person_id al unei Person
        :return: Person cu acel person_id
        '''
        return self.person_repo.get_person_by_id(person_id)

    def update_person(self, person_id, new_name, new_address):
        '''
        Functie care modifica o persoana care are un person_id
        :param person_id: un person_id al unei Person
        :param new_name: str nevid
        :param new_address: str nevid
        :return: Person de acel person_id cu noile date
        '''
        return self.person_repo.update_person(person_id, new_name, new_address)

    def add_event(self, event):
        '''
        Functie din controller care adauga un eveniment
        :param event: un event de tip Event
        :return: -
        '''
        EventValidator.validate(event)
        self.event_repo.add_event(event)

    def remove_event(self, event_id):
        '''
        Functie care sterge un eveniment
        :param event_id: un event_id al unui Event
        :return: -
        '''
        self.event_repo.remove_event(event_id)

    def get_event_by_id(self, event_id):
        '''
        Functie care gaseste un event dupa event_id
        :param event_id: event_id al unui Event
        :return: event-ul cautat
        '''
        return self.event_repo.get_event_by_id(event_id)

    def update_event(self, event_id, new_date, new_time, new_description):
        '''
        Functie care modifica un eveniment
        :param event_id: un event_id al unui Event
        :param new_date: date
        :param new_time: time
        :param new_description: str  nevid
        :return: event-ul cu datele modificate
        '''
        return self.event_repo.update_event(event_id, new_date, new_time, new_description)

    def enroll_person_in_event(self, person_id, event_id):
        '''
        Functie care inscrie o persoana la un eveniment
        :param person_id: un person_id al unei Person
        :param event_id: un event_id al unui Event
        :return: -
        '''
        person = self.person_repo.get_person_by_id(person_id)
        event = self.event_repo.get_event_by_id(event_id)

        if person and event:
            event.participants.append(person)
            person.events.append(event)

    def get_person_events_ordered_by_description(self, person_id, sort_type = "merge_sort"):
        '''
        Functie care sorteaza dupa descriere evenimentele la care participa o persoana
        :param person_id: un person_id al unei Person
        :return: evenimentele ordonate dupa descriere
                 [] daca persoana nu participa la niciun eveniment


        Complexitate:
        Căutarea persoanei după ID: O(log n) pentru o căutare binară într-un arbore de căutare binară
        Sortarea evenimentelor după descriere: O(n log n) pentru merge sort
        => complexitatea totală a funcției este O(log n) + O(n log n) = O(n log n)
        '''
        '''person = self.person_repo.get_person_by_id(person_id)
        if person:
            events = person.events
            events.sort(key=attrgetter('description'))
            event_descriptions = []
            for event in events:
                event_descriptions.append(event.description)
            return event_descriptions
        else:
            return []
        '''
        person = self.person_repo.get_person_by_id(person_id)
        if person:
            events = person.events
            sorted_events = generic_sort(events, sort_type, key=lambda event: event.description)
            return sorted_events
        else:
            return []

    def get_person_events_ordered_by_date(self, person_id, sort_type = "merge_sort"):
        '''
            Functie care sorteaza dupa data evenimentele la care participa o persoana
            :param person_id: un person_id al unei Person
            :return: evenimentele ordonate dupa data
                    [] daca persoana nu participa la niciun eveniment
        '''
        person = self.person_repo.get_person_by_id(person_id)
        if person:
            events = person.events
            sorted_events = generic_sort(events, sort_type, key=lambda event: event.date)
            return sorted_events
        else:
            return []

    def get_persons_participating_most_events(self):
        '''
        Functie care returneaza persoanele care participa la cele mai multe evenimente
        :return: lista cu persoane
        '''
        persons_events_count = []
        for person in self.person_repo.persons:
            event_count = len(person.events)
            persons_events_count.append((person, event_count))
        persons_events_count.sort(key=itemgetter(1), reverse=True)
        most_participating_count = persons_events_count[0][1]
        most_participating_persons = []
        for person, count in persons_events_count:
            if count == most_participating_count:
                most_participating_persons.append(person)
            else:
                break
        return most_participating_persons


    def get_top_events_by_participants(self):
        '''
        Functie care returneaza primele 20% evenimente cu cei mai multi participanti
        :return: lista cu evenimnetele
        '''
        events_participants_count = []
        for event in self.event_repo.events:
            participants_count = len(event.participants)
            events_participants_count.append((event, participants_count))
        events_participants_count.sort(key=itemgetter(1), reverse=True)
        top_events_count = int(0.2 * len(events_participants_count))
        top_events = events_participants_count[:top_events_count]
        top_events_info = []
        for event, count in top_events:
            top_events_info.append((event.description, count))
        return top_events_info

    def add_random_person(self):
        '''
        Functie care adauga random o persoana
        :return: -
        '''
        random_person = self.person_generator.generate_random_person()
        self.person_repo.add_person(random_person)

    def add_random_event(self):
        '''
        Functie care adauga random un eveniment
        :return: -
        '''
        random_event = self.event_generator.generate_random_event()
        self.person_repo.add_person(random_event)

    def get_all_participants(self):
        '''
        Functie care afiseaza toti participantii
        :return: lista de persoane
        '''
        return self.person_repo.get_all_persons()

    def get_all_events(self):
        '''
        Functie care afiseaza toate evenimentele
        :return: lista de evenimente
        '''
        return self.event_repo.get_all_events()

    def get_top_participants_by_events(self):
        '''
        Functie care returneaza primele 20% persoane care participa la cele mai multe evenimente
        :return: lista cu persoanele
        '''
        participants_events_count = []
        for person in self.person_repo.persons:
            events_count = len(person.events)
            participants_events_count.append((person, events_count))
        participants_events_count.sort(key=itemgetter(1), reverse=True)
        top_participants_count = int(0.2 * len(participants_events_count))
        top_participants = participants_events_count[:top_participants_count]
        top_participants_info = []
        for person, count in top_participants:
            top_participants_info.append((person.name, count))
        return top_participants_info