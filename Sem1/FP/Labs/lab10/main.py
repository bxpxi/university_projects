from entities import Specie
from repository import Repository
from controller import Controller
from ui import Console

def main():
    file = "file.txt"
    repo = Repository(file)
    controller = Controller(repo)
    console = Console(controller)
    console.meniu()

if __name__ == "__main__":
    main()


