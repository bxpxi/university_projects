class AddressReportItem:
    """
    Clasa ce este de folos la crearea de rapoarte
    """
    def __init__(self, address, count):
        self.__address = address
        self.__count = count

    def get_address(self):
        return self.__address

    def get_count(self):
        return self.__count

    def incrementare_count(self):
        self.__count += 1