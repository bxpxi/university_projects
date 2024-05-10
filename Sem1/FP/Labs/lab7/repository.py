class PersonRepository:
    def __init__(self):
        self.persons = []

    def add_person(self, person):
        '''
        Functie prin care se adauga o persoana
        :param person: o persoana din clasa Person
        :return: -
        '''
        self.persons.append(person)

    def remove_person(self, person_id):
        '''
        Functie prin care se sterge o persoana
        :param person_id: un person_id al unei Person
        :return: True - daca s-a gasit persoana cu acel person_id
                 False - daca nu exista o persoana cu acel person_id
        '''
        for person in self.persons:
            if person.person_id == person_id:
                self.persons.remove(person)
                return True
        return False

    def get_person_by_id(self, person_id):
        '''
        Functie care gaseste o persoana Person dupa person_id
        :param person_id: un person_id al unei Person
        :return: person, daca exsita o persoana cu acel id
                 None, in caz contrar
        '''
        for person in self.persons:
            if person.person_id == person_id:
                return person
        return None


    def update_person(self, person_id, new_name, new_address):
        '''
        Functie care modifica datele unei persoane de tip Person
        :param person_id: un person_id al unei Person
        :param new_name: str
        :param new_address: str
        :return: True daca exista o persoana cu acel person_id
                 False in caz contrar
        '''
        for person in self.persons:
            if person.person_id == person_id:
                person.name = new_name
                person.address = new_address
                return True
        return False

    def get_all_persons(self):
        """
        Functie care returneaza toate persoanle din baza de date
        :return: lista de persoane
        """
        return self.persons.copy()

class EventRepository:
    def __init__(self):
        self.events = []

    def add_event(self, event):
        """
        Funtie care adauga un eveniment
        :param event: un event din clasa Event
        :return: -
        """
        self.events.append(event)

    def remove_event(self, event_id):
        '''
        Functie care sterge un eveniment
        :param event_id: un event_id al unui eveniment de clasa Event
        :return: True daca exista un astfel de eveniment
                 False in caz contrar
        '''
        for event in self.events:
            if event.event_id == event_id:
                self.events.remove(event)
                return True
        return False

    def get_event_by_id(self, event_id):
        '''
        Funvctie care gaseste un eveniment dupa event_id
        :param event_id: un event_id al unui eveniment din clasa Event
        :return: event daca exista un Event cu acel event_id
                 None in caz contrar
        '''
        for event in self.events:
            if event.event_id == event_id:
                return event
        return None

    def update_event(self, event_id, new_date, new_time, new_description):
        '''
        Functie care modifica un eveniment
        :param event_id: un event_id al unui eveniment de clasa Event
        :param new_date:  date
        :param new_time: time
        :param new_description: str nevid
        :return: True daca exista un event cu acel event_id
                 None in caz contrar
        '''
        for event in self.events:
            if event.event_id == event_id:
                event.date = new_date
                event.time = new_time
                event.description = new_description
                return True
        return False

    def get_all_events(self):
        '''
        Functie care returneaza toate evenimentele din baza de date
        :return: lista de evenimente
        '''
        return self.events.copy()
