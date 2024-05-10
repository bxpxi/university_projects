def clear_file_content(file_name):
    """
    Se sterge continutul din fisier
    Preconditii: file_name - fisier
    Postconditii: continutul fisierului se goleste
    """
    f = open(file_name, "w")
    f.close()