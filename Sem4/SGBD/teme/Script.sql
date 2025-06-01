CREATE DATABASE ClinicaMedicala;

CREATE TABLE Specializari
(ID_specializare INT PRIMARY KEY IDENTITY,
Denumire VARCHAR(40) NOT NULL,
Descriere VARCHAR(255) NOT NULL)

CREATE TABLE ServiciiMedicale
(ID_serviciu INT PRIMARY KEY IDENTITY,
Denumire VARCHAR(50) NOT NULL,
Detalii VARCHAR(255) NOT NULL,
Cost DECIMAL(10,2) NOT NULL)

CREATE TABLE Pacienti
(ID_pacient INT PRIMARY KEY IDENTITY,
Nume VARCHAR(40) NOT NULL,
Prenume VARCHAR(40) NOT NULL,
CNP VARCHAR(13) NOT NULL,
Data_nasterii DATE NOT NULL,
Gen VARCHAR(1) NOT NULL,
Adresa VARCHAR(60) NOT NULL,
Telefon VARCHAR(15) NOT NULL,
Email VARCHAR(40) NOT NULL)

CREATE TABLE Medici(
ID_medic INT PRIMARY KEY IDENTITY,
Nume VARCHAR(40) NOT NULL,
Prenume VARCHAR(40) NOT NULL,
ID_specializare INT FOREIGN KEY REFERENCES Specializari(ID_specializare) NOT NULL,
Telefon VARCHAR(15) NOT NULL,
Email VARCHAR(40) NOT NULL,
Data_angajarii DATE NOT NULL,
Grad_profesional VARCHAR(40))

CREATE TABLE OrarMedici
(ID_orar INT PRIMARY KEY IDENTITY,
ID_medic INT FOREIGN KEY REFERENCES Medici(ID_medic) NOT NULL,
Ziua_saptamanii VARCHAR(15) NOT NULL,
Ora_inceput TIME NOT NULL,
Ora_sfarsit TIME NOT NULL)

CREATE TABLE Programari
(ID_programare INT PRIMARY KEY IDENTITY,
ID_pacient INT FOREIGN KEY REFERENCES Pacienti(ID_pacient) NOT NULL,
ID_medic INT FOREIGN KEY REFERENCES Medici(ID_medic) NOT NULL,
Data_programarii DATE NOT NULL,
Ora_programarii TIME NOT NULL,
Motiv VARCHAR(100) NOT NULL)

CREATE TABLE Tratamente
(ID_tratament INT PRIMARY KEY IDENTITY,
ID_pacient INT FOREIGN KEY REFERENCES Pacienti(ID_pacient) NOT NULL,
ID_medic INT FOREIGN KEY REFERENCES Medici(ID_medic) NOT NULL,
Tip VARCHAR(40) NOT NULL,
Descriere VARCHAR(100) NOT NULL, 
Data_tratament DATE NOT NULL,
Cost DECIMAL(10,2) NOT NULL)

CREATE TABLE Facturi
(ID_factura INT PRIMARY KEY IDENTITY,
ID_pacient INT FOREIGN KEY REFERENCES Pacienti(ID_pacient) NOT NULL,
Data_facturare DATE NOT NULL,
Suma DECIMAL(10,2) NOT NULL,
Metoda_plata VARCHAR(30) NOT NULL)

CREATE TABLE Retete
(ID_reteta INT PRIMARY KEY IDENTITY,
ID_pacient INT FOREIGN KEY REFERENCES Pacienti(ID_pacient) NOT NULL,
ID_medic INT FOREIGN KEY REFERENCES Medici(ID_medic) NOT NULL,
Data_emiterii DATE NOT NULL, 
Medicamente VARCHAR(100) NOT NULL,
Dozaj VARCHAR(40) NOT NULL)

CREATE TABLE PacientServiciu
(ID_pacient INT FOREIGN KEY REFERENCES Pacienti(ID_pacient) NOT NULL,
ID_serviciu INT FOREIGN KEY REFERENCES ServiciiMedicale(ID_serviciu) NOT NULL,
Data_serviciu DATE NOT NULL
PRIMARY KEY (ID_pacient, ID_serviciu, Data_serviciu))


SELECT * FROM Specializari;

CREATE TABLE Medici2(
ID_medic INT PRIMARY KEY IDENTITY,
Nume VARCHAR(40) NOT NULL,
Prenume VARCHAR(40) NOT NULL,
ID_specializare INT FOREIGN KEY REFERENCES Specializari(ID_specializare) NOT NULL,
Telefon VARCHAR(15) NOT NULL,
Email VARCHAR(40) NOT NULL,
Grad_profesional VARCHAR(40))

SELECT * FROM Medici2;

CREATE TABLE Angajati(
	id INT PRIMARY KEY IDENTITY,
	nume VARCHAR(40) NOT NULL,
	prenume VARCHAR(40) NOT NULL,
	rol INT FOREIGN KEY REFERENCES Roluri(id) NOT NULL
);

CREATE TABLE Roluri(
	id INT PRIMARY KEY IDENTITY,
	rol VARCHAR(40) NOT NULL,
	salariu INT NOT NULL
);

INSERT INTO Roluri(rol, salariu) VALUES('Medic specialist',20000), ('Medic primar',12000),('Medic rezident',8000),('Asistent',7000),('Infirmier',5000),('Receptioner',5000);
INSERT INTO Angajati(nume, prenume, rol) VALUES('Popa','Ana',1),('Popescu','Radu',1),('Stanciu','Patrick',2),('Petrescu','Cezara',3),('Pasca','Ioan',2),('Lupsa','Sara',4),('Magheru','Simina',4),('Popoviciu','George',3),('Bente','Emanuela',5),('Teodorescu','Marcela',5),('Istrate','Tudor',6);

SELECT * FROM Roluri;
SELECT * FROM Angajati;

CREATE TABLE Producatori(
	id INT PRIMARY KEY IDENTITY,
	denumire VARCHAR(40) NOT NULL,
	oras VARCHAR(40) NOT NULL
);

CREATE TABLE Halate(
	id INT PRIMARY KEY IDENTITY,
	producator INT FOREIGN KEY REFERENCES Producatori(id) NOT NULL
);

INSERT INTO Producatori(denumire, oras) VALUES('MediClothes','Baia Mare'), ('MediStyle','Oradea'),('MediGlam','Tragu Mures');
INSERT INTO Halate(producator) VALUES(1),(1),(1),(2),(2),(3);

SELECT * FROM Producatori;
SELECT * FROM Halate;
