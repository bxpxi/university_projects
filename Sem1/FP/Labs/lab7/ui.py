from entities import Person, Event
from controller import Controller

class ConsoleUI:
    def __init__(self, controller):
        self.controller = controller

    def run(self):
        '''
        Functie care afiseaza meniul
        :return: -
        '''
        while True:
            command = input("Introduceți comanda (help pentru a vedea lista de comenzi): ").lower()

            if command == 'exit':
                break
            elif command == 'help':
                self.print_help()
            elif command == 'adauga_persoana':
                self.add_person()
            elif command == 'sterge_persoana':
                self.remove_person()
            elif command == 'modifica_persoana':
                self.update_person()
            elif command == 'cauta_persoane':
                self.search_persons()
            elif command == 'adauga_eveniment':
                self.add_event()
            elif command == 'sterge_eveniment':
                self.remove_event()
            elif command == 'modifica_eveniment':
                self.update_event()
            elif command == 'cauta_evenimente':
                self.search_events()
            elif command == 'inscrie_persoana':
                self.enroll_person_in_event()
            elif command == 'listeaza_evenimente_dupa_descriere':
                #self.print_person_events_ordered()
                sort_type = input("Introduceți tipul de sortare (merge_sort/bingo_sort): ").lower()
                self.print_person_events_ordered(sort_type)
            elif command == 'listeaza_evenimente_dupa_data':
                #self.print_person_events_ordered_()
                sort_type = input("Introduceți tipul de sortare (merge_sort/bingo_sort): ").lower()
                self.print_person_events_ordered(sort_type)
            elif command == 'participanti_maximi':
                self.print_persons_participating_most()
            elif command == 'evenimente_top':
                self.print_top_events_by_participants()
            elif command == "afisare_persoane":
                self.show_all_participants()
            elif command == "afisare_evenimente":
                self.show_all_events()
            elif command == 'random_person':
                self.controller.add_random_person()
                print("Persoana generată aleatoriu a fost adaugată.")
            elif command == 'random_event':
                print("Eveniment genearat aleatoriu a fost adaugat.")
            elif command == 'persoane_top':
                self.print_top_participants_by_events()
            else:
                print("Comandă invalidă. Introduceți 'help' pentru lista de comenzi.")

    def print_help(self):
        '''
        Functie ce afiseaza optiunea help, cuprinde explicatiile tuturor comenzilor
        :return:
        '''
        print("Lista de comenzi:")
        print("help - Afișează această listă de comenzi")
        print("adauga_persoana - Adaugă o persoană")
        print("sterge_persoana - Șterge o persoană")
        print("modifica_persoana - Modifică o persoană")
        print("cauta_persoane - Caută persoane")
        print("adauga_eveniment - Adaugă un eveniment")
        print("sterge_eveniment - Șterge un eveniment")
        print("modifica_eveniment - Modifică un eveniment")
        print("cauta_evenimente - Caută evenimente")
        print("inscrie_persoana - Înscrie o persoană la un eveniment")
        print("listeaza_evenimente_dupa_descriere - Afișează evenimentele unei persoane ordonate alfabetic după descriere")
        print("listeaza_evenimente_dupa_data - Afișează evenimentele unei persoane ordonate cronologic după data")
        print("participanti_maximi - Afișează persoanele participante la cele mai multe evenimente")
        print("evenimente_top - Afișează primele 20% evenimente cu cei mai mulți participanți")
        print("persoane_top - Afiseaza primele 20% persoane care participa la cele mai multe evenimente")
        print("afisare_persoane - Afișează lista de persoane")
        print("afisare_evenimente - Afișează lista de evenimente")
        print("random_person - Adaugă aleator o persoană")
        print("random_event - Adaugă aleator un eveniment.")
        print("exit - Ieșire din program")

    def add_person(self):
        "Functie de afis pentru a adauga o persoana"
        person_id = int(input("Introduceți ID-ul persoanei: "))
        name = input("Introduceți numele persoanei: ")
        address = input("Introduceți adresa persoanei: ")

        try:
            person = Person(person_id, name, address)
            self.controller.add_person(person)
            print("Persoană adăugată cu succes!")
        except ValueError as ve:
            print(f"Eroare: {ve}")

    def remove_person(self):
        "Functie de afis pentru a sterge o persoana"
        person_id = int(input("Introduceți ID-ul persoanei de șters: "))
        self.controller.remove_person(person_id)
        print("Persoană ștearsă cu succes!")

    def update_person(self):
        "Functie de afis pentru a modifica o persoana"
        person_id = int(input("Introduceți ID-ul persoanei de modificat: "))
        new_name = input("Introduceți noul nume al persoanei: ")
        new_address = input("Introduceți noua adresă a persoanei: ")

        if self.controller.update_person(person_id, new_name, new_address):
            print("Persoană modificată cu succes!")
        else:
            print("Nu s-a găsit persoana cu ID-ul specificat.")

    def search_persons(self):
        "Functie de afis pentru a afisa o persoana dupa person_id"
        try:
            person_id = int(input("Introduceți ID-ul persoanei de căutat: "))
        except ValueError:
            print("ID-ul persoanei trebuie să fie un număr întreg.")
            return
        person = self.controller.get_person_by_id(person_id)
        if person:
            print("Rezultatul căutării pentru persoana cu ID-ul {}: {} - {}".format(person.person_id, person.name, person.address))
        else:
            print("Nu s-a găsit persoana cu ID-ul specificat.")

    def add_event(self):
        "Functie de afis pentru a adauga un eveniment"
        event_id = int(input("Introduceți ID-ul evenimentului: "))
        date = input("Introduceți data evenimentului (YYYY-MM-DD): ")
        time = input("Introduceți ora evenimentului (HH:MM): ")
        description = input("Introduceți descrierea evenimentului: ")
        try:
            event = Event(event_id, date, time, description)
            self.controller.add_event(event)
            print("Eveniment adăugat cu succes!")
        except ValueError as ve:
            print(f"Eroare: {ve}")

    def remove_event(self):
        "Functie de afis pentru a sterge un eveniment"
        event_id = int(input("Introduceți ID-ul evenimentului de șters: "))
        self.controller.remove_event(event_id)
        print("Eveniment șters cu succes!")

    def update_event(self):
        "Functie de afis pentru a modifica un eveniment"
        event_id = int(input("Introduceți ID-ul evenimentului de modificat: "))
        new_date = input("Introduceți noua dată a evenimentului (YYYY-MM-DD): ")
        new_time = input("Introduceți noua oră a evenimentului (HH:MM): ")
        new_description = input("Introduceți noua descriere a evenimentului: ")
        if self.controller.update_event(event_id, new_date, new_time, new_description):
            print("Eveniment modificat cu succes!")
        else:
            print("Nu s-a găsit evenimentul cu ID-ul specificat.")

    def search_events(self):
        "Functie de afis pentru a gasi un eveniment dupa event_id"
        try:
            event_id = int(input("Introduceți ID-ul evenimentului de căutat: "))
        except ValueError:
            print("ID-ul evenimentului trebuie să fie un număr întreg.")
            return
        event = self.controller.get_event_by_id(event_id)
        if event:
            print("Rezultatul căutării pentru evenimentul cu ID-ul {}: {} - {} - {}".format(event.event_id, event.description, event.date, event.time))
        else:
            print("Nu s-a gasit evenimentul.")

    def enroll_person_in_event(self):
        "Functie de afis pentru a inscrie o persaoana la un eveniment"
        person_id = int(input("Introduceți ID-ul persoanei: "))
        event_id = int(input("Introduceți ID-ul evenimentului: "))
        self.controller.enroll_person_in_event(person_id, event_id)
        print("Persoană înscrisă la eveniment cu succes!")

    def print_person_events_ordered(self, sort_type):
        "Functie care afiseaza evenimentele unui participant ordonate alfabetic dupa descriere"
        try:
            person_id = int(input("Introduceți ID-ul persoanei: "))
        except ValueError:
            print("ID-ul persoanei trebuie să fie un număr întreg.")
            return
        events = self.controller.get_person_events_ordered_by_description(person_id, sort_type)
        if events:
            print("Evenimentele persoanei ordonate alfabetic după descriere:")
            for event in events:
                print(event)
        else:
            print("Nu s-au găsit evenimente pentru persoana cu ID-ul specificat.")


    def print_person_events_ordered_(self, sort_type):
        "Functie care afiseaza evenimentele la care participa o persoana ordonate cronologic dupa data"
        try:
            person_id = int(input("Introduceți ID-ul persoanei: "))
        except ValueError:
            print("ID-ul persoanei trebuie să fie un număr întreg.")
            return
        events = self.controller.get_person_events_ordered_by_date(person_id, sort_type)
        if events:
            print("Evenimentele persoanei ordonate cronologic după data:")
            for event in events:
                print(event)
        else:
            print("Nu s-au găsit evenimente pentru persoana cu ID-ul specificat.")

    def print_persons_participating_most(self):
        "Functie care afiseaza persoanele care participa la cele mai multe evenimente"
        persons = self.controller.get_persons_participating_most_events()
        if persons:
            print("Persoanele participante la cele mai multe evenimente:")
            for person in persons:
                print(f"{person.person_id}. {person.name} - {len(person.events)} evenimente")
        else:
            print("Nu există persoane înscrise la niciun eveniment.")

    def print_top_events_by_participants(self):
        "Functie care afiseaza top 20% evenimente cu cei mai multi participanti"
        events_info = self.controller.get_top_events_by_participants()
        if events_info:
            print("Primele 20% evenimente cu cei mai mulți participanți:")
            for event, participants_count in events_info:
                print(f"{event}. Participanți: {participants_count}")
        else:
            print("Nu există suficiente evenimente pentru generarea acestui raport.")


    def show_all_participants(self):
        "Functia care afiseaza toate persoanele"
        participants = self.controller.get_all_participants()
        if participants:
            print("Lista de participanți:")
            for person in participants:
                print(f"{person.name} - {person.address}")
        else:
            print("Nu există participanți.")


    def show_all_events(self):
        "Functie care afiseaza toate evenimentele"
        events = self.controller.get_all_events()
        if events:
            print("Lista de evenimente:")
            for event in events:
                print(f"{event.description} - {event.date} {event.time}")
        else:
            print("Nu există evenimente.")


    def print_top_participants_by_events(self):
        "Functie care afiseaza top 20% persoane care participa la cele mai multe evenimente"
        participants_info = self.controller.get_top_participants_by_events()
        if participants_info:
            print("Primele 20% persoane care participa la cele mai multe evenimente:")
            for person, events_count in participants_info:
                print(f"{person}. Evenimente: {events_count}")
        else:
            print("Nu există suficiente persoane pentru generarea acestui raport.")