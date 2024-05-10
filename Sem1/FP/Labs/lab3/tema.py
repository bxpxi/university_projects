numere = []
while True:
    numere.append(int(input("Introduceti un numar intreg: ")))
    alegere = input("Doriti sa mai introduceti alt numar intreg? (da/nu) ")
    if alegere.lower() == "nu":
        break
for i in numere:
    print(i)
optiune = ""
while True:
    print("1. Secventa numere egale")
    print("2. Secventa numere din intervalul [0,10]")
    print("3. Secventa de numere a caror suma e egala cu 5")
    print("4. Iesire din aplicatie")

    optiune = input("Selectati o optiune (1/2/3/4) : ")
    optiune = optiune.strip()

    if optiune == '1':
        lungime_curenta = 1
        lungime_maxima = 0
        capat_secventa = numere[0]

        for i in numere[1:]:
            if i == capat_secventa:
                lungime_curenta += 1
            else:
                if lungime_curenta > lungime_maxima:
                    lungime_maxima = lungime_curenta
                    valoare_maxima = capat_secventa
                capat_secventa = i
                lungime_curenta = 1

        if (lungime_maxima >= 2):
            print(f'Secventa de lungime maxima de numere egale are lungimea {lungime_maxima} si este: ')
            for i in range(lungime_maxima):
                print(valoare_maxima)
        else:
            print("Nu exista o secventa de numere egale")

    elif optiune == '2':
        lungime_curenta = 0
        lungime_maxima = 0
        st = 0
        dr = 0
        st_secv = 0
        dr_secv = 0

        for i in range(0, len(numere)):
            if numere[i] >= 0 and numere[i] <= 10 and lungime_curenta == 0:
                lungime_curenta += 1
                dr = i
                st = i
            elif numere[i] >= 0 and numere[i] <= 10:
                lungime_curenta += 1
                dr = i
            else:
                lungime_curenta = 0
            if (lungime_curenta > lungime_maxima):
                lungime_maxima = lungime_curenta
                st_secv = st
                dr_secv = dr

        if lungime_maxima >= 1:
            print(
                f'Secventa de lungime maxima cu numere din intervalul [0,10] are lungimea {lungime_maxima} si porneste de la indexul {st_secv} si se termina la indexul {dr_secv} si este: ')
            for i in range(st_secv, dr_secv + 1):
                print(numere[i])
        else:
            print("Nu exista secventa de numere cuprinse in intervalul [0,10]")

    elif optiune == '3':
        lungime_maxima = 0
        st = 0
        dr = 0
        st_secv = 0
        dr_secv = 0
        suma = 0
        lungime_curenta = 0
        for i in range(0, len(numere)):
            if numere[i] <= 5 and lungime_curenta == 0:
                st = i
                dr = i
                lungime_curenta = 1
                suma = suma + numere[i]
                if suma == 5:
                    if lungime_curenta > lungime_maxima:
                        lungime_maxima = lungime_curenta
                        st_secv = st
                        dr_secv = dr
            elif numere[i] + suma <= 5 and lungime_curenta != 0:
                dr = i
                lungime_curenta += 1
                suma = suma + numere[i]
                if suma == 5:
                    if lungime_curenta > lungime_maxima:
                        lungime_maxima = lungime_curenta
                        st_secv = st
                        dr_secv = dr
            elif numere[i] + suma > 5 and lungime_curenta != 0:
                st = 0
                dr = 0
                lungime_curenta = 0
                suma = 0
        if lungime_maxima > 0:
            print(
                f'Secventa de lungime maxima are lungimea {lungime_maxima}, porneste de la indexul {st_secv} si se termina la indexul {dr_secv} si este')
            for i in range(st_secv, dr_secv + 1):
                print(numere[i])
        else:
            print("Nu exista o secventa de numere care sa aiba suma egala cu 5")

    elif optiune == '4':
        break
    else:
        print("Optiune invalida! Incercati din nou!")
