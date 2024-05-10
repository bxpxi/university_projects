from controller.controller import EventController
from repository.repository import EventRepository
from ui.ui import ConsoleUI

def main():
    # Inițializare repository și controller
    event_repository = EventRepository()
    event_controller = EventController(event_repository)

    # Inițializare interfață utilizator
    console_ui = ConsoleUI(event_controller)

    # Rulează interfața utilizatorului
    console_ui.run()


main()

