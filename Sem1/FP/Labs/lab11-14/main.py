from controller import Controller
from repository import Repository
from validators import Validator
from ui import UI
from file_repository import FileRepository

def main():
    #repository = Repository()
    repository = FileRepository("people.txt", "events.txt")
    validator = Validator()
    controller = Controller(repository, validator)
    ui = UI(controller)
    ui.run()
    controller.save_data()

if __name__ == "__main__":
    main()
