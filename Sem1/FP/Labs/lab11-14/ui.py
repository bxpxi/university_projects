# ui.py
from controller import Controller

class UI:
    def __init__(self, controller):
        self.controller = controller

    def print_menu(self):
        print("1. Adăugare persoană")
        print("2. Ștergere persoană")
        print("3. Modificare persoană")
        print("4. Afișare persoane")
        print("5. Adăugare eveniment")
        print("6. Ștergere eveniment")
        print("7. Modificare eveniment")
        print("8. Afișare evenimente")
        print("9. Înscriere persoană la eveniment")
        print("10. Ștergere înscriere persoană de la eveniment")
        print("11. Modificare înscriere persoană la eveniment")
        print("12. Raport: Evenimente pentru o persoană sortate după descriere")
        print("13. Raport: Evenimente pentru o persoană sortate după dată")
        print("14. Raport: Persoane cu cele mai multe evenimente")
        print("15. Raport: Primele p% evenimente cu cei mai mulți participanți")
        print("16. Generare și adăugare date aleatoare")
        print("0. Ieșire")

    def run(self):
        while True:
            self.print_menu()
            option = input("Alegeți o opțiune: ")

            if option == "0":
                self.exit_program()
                print("Iesire din aplicatie")
                break
            elif option == "1":
                self.add_person()
            elif option == "2":
                self.remove_person()
            elif option == "3":
                self.modify_person()
            elif option == "4":
                self.display_people()
            elif option == "5":
                self.add_event()
            elif option == "6":
                self.remove_event()
            elif option == "7":
                self.modify_event()
            elif option == "8":
                self.display_events()
            elif option == "9":
                self.add_participation()
            elif option == "10":
                self.remove_participation()
            elif option == "11":
                self.modify_participation()
            elif option == "12":
                self.report_events_sorted_by_description()
            elif option == "13":
                self.report_events_sorted_by_date()
            elif option == "14":
                self.report_people_with_most_events()
            elif option == "15":
                self.report_top_events_with_most_participants()
            elif option == "16":
                self.generate_and_add_random_data()
            else:
                print("Opțiune invalidă. Încercați din nou.")

    def add_person(self):
        person_id = int(input("ID persoană: "))
        name = input("Nume persoană: ")
        address = input("Adresă persoană: ")
        self.controller.add_person(person_id, name, address)
        print("Persoană adăugată cu succes.")

    def remove_person(self):
        person_id = int(input("ID persoană pentru ștergere: "))
        self.controller.remove_person(person_id)
        print("Persoană ștearsă cu succes.")

    def modify_person(self):
        person_id = int(input("ID persoană pentru modificare: "))
        new_name = input("Nume nou: ")
        new_address = input("Adresă nouă: ")
        self.controller.modify_person(person_id, new_name, new_address)
        print("Persoană modificată cu succes.")

    def display_people(self):
        people = self.controller.get_all_people()
        print("Lista de persoane:")
        for person in people:
            print(f"{person.get_person_id()}. {person.get_name()} - {person.get_address()}")

    def add_event(self):
        event_id = int(input("ID eveniment: "))
        date = input("Dată eveniment (YYYY-MM-DD): ")
        time = input("Timp eveniment (HH:MM): ")
        description = input("Descriere eveniment: ")
        self.controller.add_event(event_id, date, time, description)
        print("Eveniment adăugat cu succes.")

    def remove_event(self):
        event_id = int(input("ID eveniment pentru ștergere: "))
        self.controller.remove_event(event_id)
        print("Eveniment șters cu succes.")

    def modify_event(self):
        event_id = int(input("ID eveniment pentru modificare: "))
        new_date = input("Dată nouă (YYYY-MM-DD): ")
        new_time = input("Timp nou (HH:MM): ")
        new_description = input("Descriere nouă: ")
        self.controller.modify_event(event_id, new_date, new_time, new_description)
        print("Eveniment modificat cu succes.")

    def display_events(self):
        events = self.controller.get_all_events()
        print("Lista de evenimente:")
        for event in events:
            print(f"{event.get_event_id()}. {event.get_date()} {event.get_time()} - {event.get_description()}")

    def add_participation(self):
        person_id = int(input("ID persoană pentru înscriere: "))
        event_id = int(input("ID eveniment pentru înscriere: "))
        self.controller.add_participation(person_id, event_id)
        print("Înscriere realizată cu succes.")

    def remove_participation(self):
        person_id = int(input("ID persoană pentru ștergere înscriere: "))
        event_id = int(input("ID eveniment pentru ștergere înscriere: "))
        self.controller.remove_participation(person_id, event_id)
        print("Înscriere ștearsă cu succes.")

    def modify_participation(self):
        person_id = int(input("ID persoană pentru modificare înscriere: "))
        event_id = int(input("ID eveniment pentru modificare înscriere: "))
        new_person_id = int(input("ID persoană nou pentru înscriere: "))
        new_event_id = int(input("ID eveniment nou pentru înscriere: "))
        self.controller.modify_participation(person_id, event_id, new_person_id, new_event_id)
        print("Înscriere modificată cu succes.")

    def report_events_sorted_by_description(self, sort_algorithm="merge_sort"):
        person_id = int(input("ID persoană pentru raport: "))
        events = self.controller.get_events_for_person_sorted_by_description(person_id, sort_algorithm="merge_sort")
        print("Evenimente pentru persoana dată, sortate după descriere:")
        for event in events:
            print(f"{event.get_date()} {event.get_time()} - {event.get_description()}")

    def report_events_sorted_by_date(self, sort_algorithm="merge_sort"):
        person_id = int(input("ID persoană pentru raport: "))
        events = self.controller.get_events_for_person_sorted_by_date(person_id, sort_algorithm="merge_sort")
        print("Evenimente pentru persoana dată, sortate după dată:")
        for event in events:
            print(f"{event.get_date()} {event.get_time()} - {event.get_description()}")

    def report_people_with_most_events(self):
        people = self.controller.get_people_with_most_events(sort_algorithm="merge_sort")
        if not people:
            print("Nu există persoane cu evenimente.")
            return

        print("Persoane cu cele mai multe evenimente:")
        for person_id in people:
            person = self.controller.get_person_by_id(person_id)
            if person:
                print(f"{person.get_name()} - {person.get_address()}")
            else:
                print(f"Person ID {person_id} nu a fost găsit.")

    def report_top_events_with_most_participants(self,sort_algorithm="merge_sort"):
        percentage = float(input("Introduceți procentul pentru raport (ex. 0.2 pentru 20%): "))
        top_events = self.controller.get_top_events_with_most_participants(percentage,sort_algorithm="merge_sort")
        print(f"Primele {percentage * 100}% evenimente cu cei mai mulți participanți:")
        for event_id, participants_count in top_events:
            event = self.controller.get_event_by_id(event_id)
            print(f"{event.get_date()} {event.get_time()} - {event.get_description()} ({participants_count} participanți)")

    def generate_and_add_random_data(self):
        num_people = int(input("Introduceți numărul de persoane pentru generare aleatoare: "))
        num_events = int(input("Introduceți numărul de evenimente pentru generare aleatoare: "))
        self.controller.generate_and_add_random_data(num_people, num_events)
        print("Date generare aleatoare adăugate cu succes.")

    def exit_program(self):
        print("Salvare date înainte de închidere...")
        self.controller.save_data()
        print("Date salvate. Închidere program.")