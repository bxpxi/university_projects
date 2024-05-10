from repository.in_memory import in_memory_repository
from services.person_service import Persoana_service
from ui.console import Console
from domain.validators import Persoana_Validator
from repository.file_repository import persoana_repository_file

rep = persoana_repository_file("test.txt")
val = Persoana_Validator()
ctr = Persoana_service(rep, val)
ui = Console(ctr)

ui.show_ui()
