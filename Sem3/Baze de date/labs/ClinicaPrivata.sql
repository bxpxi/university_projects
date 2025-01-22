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

-- LAB 2

go
use ClinicaMedicala
go

INSERT INTO Specializari(Denumire, Descriere) VALUES 
('Cardiologie', 'Specializare in diagnosticul si tratamentul bolilor de inima'),
('Dermatologie', 'Specializare in tratarea afectiunilor pielii'),
('Pediatrie', 'Specializare in ingrijirea copiilor si adolescentilor'),
('Oftalmologie', 'Specializare in diagnosticarea si tratarea bolilor ochilor'),
('Ortopedie', 'Specializare in tratamentul afectiunilor sistemului osos');

INSERT INTO ServiciiMedicale(Denumire,Detalii,Cost) VALUES
('Consultatie generala', 'Examinare medicala generala pentru pacienti', 150.00),
('Analize de sange', 'Testare pentru diferite afectiuni', 200.00),
('Ecografie abdominala', 'Examinare ecografica a abdomenului', 300.00),
('Radiografie', 'Examinare radiologica a oaselor', 250.00),
('Consultatie dermatologica', 'Examinare a afectiunilor pielii', 180.00);

INSERT INTO Pacienti(Nume, Prenume, CNP, Data_nasterii, Gen, Adresa, Telefon, Email) VALUES
('Popescu', 'Ion', '1234567890123', '1980-05-15', 'M', 'Str. Mare, nr. 10', '0712345678', 'ion.popescu@example.com'),
('Ionescu', 'Maria', '2345678901234', '1992-11-25', 'F', 'Str. Mica, nr. 20', '0723456789', 'maria.ionescu@example.com'),
('Georgescu', 'Andrei', '3456789012345', '1975-03-10', 'M', 'Str. Verde, nr. 5', '0734567890', 'andrei.georgescu@example.com'),
('Dumitrescu', 'Elena', '4567890123456', '1985-09-05', 'F', 'Str. Albastra, nr. 15', '0745678901', 'elena.dumitrescu@example.com'),
('Marin', 'Vasile', '5678901234567', '1968-07-20', 'M', 'Str. Roza, nr. 30', '0756789012', 'vasile.marin@example.com');

INSERT INTO Medici(Nume, Prenume, ID_specializare, Telefon, Email, Data_angajarii, Grad_profesional) VALUES
('Popescu', 'Andrei', 1, '0712345678', 'andrei.popescu@clinica.com', '2010-01-15', 'Medic Specialist'),
('Ionescu', 'Elena', 2, '0723456789', 'elena.ionescu@clinica.com', '2012-03-22', 'Medic Primar'),
('Georgescu', 'Maria', 3, '0734567890', 'maria.georgescu@clinica.com', '2015-06-30', 'Medic Rezident'),
('Dumitrescu', 'Ion', 4, '0745678901', 'ion.dumitrescu@clinica.com', '2018-09-10', 'Medic Specialist'),
('Marin', 'Alex', 5, '0756789012', 'alex.marin@clinica.com', '2020-11-05', 'Medic Specialist');

INSERT INTO OrarMedici(ID_medic, Ziua_saptamanii, Ora_inceput, Ora_sfarsit) VALUES
(1, 'Luni', '08:00', '16:00'),
(1, 'Marti', '08:00', '16:00'),
(2, 'Miercuri', '09:00', '17:00'),
(3, 'Joi', '08:00', '12:00'),
(4, 'Vineri', '10:00', '14:00');

INSERT INTO Programari(ID_pacient,ID_medic,Data_programarii,Ora_programarii,Motiv) VALUES
(1, 1, '2024-10-20', '10:00', 'Consultatie cardiaca'),
(2, 2, '2024-10-21', '11:00', 'Dermatita'),
(3, 3, '2024-10-22', '14:00', 'Consultatie pediatrica'),
(4, 4, '2024-10-23', '09:00', 'Probleme de vedere'),
(5, 5, '2024-10-24', '13:00', 'Durere de spate');

INSERT INTO Tratamente(ID_pacient,ID_medic,Tip,Descriere,Data_tratament,Cost) VALUES
(1, 1, 'Stent Coronarian', 'Implantare stent pentru arterele coronariene', '2024-10-25', 5000.00),
(2, 2, 'Crema dermatologica', 'Prescriere de crema pentru eczema', '2024-10-26', 150.00),
(3, 3, 'Vaccin', 'Vaccinare de rutina pentru copii', '2024-10-27', 100.00),
(4, 4, 'Chirurgie oculara', 'Interventie pentru cataracta', '2024-10-28', 2000.00),
(5, 5, 'Fizioterapie', 'Sedinte de fizioterapie pentru spate', '2024-10-29', 300.00);

INSERT INTO Facturi(ID_pacient,Data_facturare,Suma,Metoda_plata) VALUES
(1, '2024-10-25', 5100.00, 'Card de credit'),
(2, '2024-10-26', 150.00, 'Numerar'),
(3, '2024-10-27', 100.00, 'Card de debit'),
(4, '2024-10-28', 2000.00, 'Numerar'),
(5, '2024-10-29', 300.00, 'Transfer bancar');

INSERT INTO Retete(ID_pacient,ID_medic,Data_emiterii,Medicamente,Dozaj) VALUES
(1, 1, '2024-10-25', 'Aspirina 100mg', '1 comprimat pe zi'),
(2, 2, '2024-10-26', 'Crema cortizonica', 'Aplicare local pe zona afectata'),
(3, 3, '2024-10-27', 'Vaccin ROR', '1 doza'),
(4, 4, '2024-10-28', 'Picaturi pentru ochi', '2 picaturi de 3 ori pe zi'),
(5, 5, '2024-10-29', 'Medicamente pentru dureri', '1 comprimat la nevoie');

INSERT INTO PacientServiciu(ID_pacient,ID_serviciu,Data_serviciu) VALUES
(1, 1, '2024-10-20'),
(2, 2, '2024-10-21'),
(3, 3, '2024-10-22'),
(4, 4, '2024-10-23'),
(5, 5, '2024-10-24');

INSERT INTO Tratamente(ID_pacient,ID_medic,Tip,Descriere,Data_tratament,Cost) VALUES
(1, 1, 'Stent Coronarian2', 'Implantare stent pentru arterele coronariene', '2024-12-10', 3000.00)

--LAB2

-- 1. Pacientii (+ medicul si motivul programarii) care au programare la un medic cu specializarea dermatologie
SELECT p.Nume as Nume_Pacient, p.Prenume as Prenume_Pacient, pr.Motiv, m.Nume as Nume_Medic, m.Prenume as Prenume_Medic
FROM Pacienti p 
INNER JOIN Programari pr on p.ID_pacient=pr.ID_pacient 
INNER JOIN Medici m on pr.ID_medic=m.ID_medic
WHERE m.ID_medic = 2;

-- 2. Pacientii (+medicul) care au tratament peste 1000 lei
SELECT p.Nume as Nume_Pacient, p.Prenume as Prenume_Pacient, t.Tip, m.Nume as Nume_Medic, m.Prenume as Prenume_Medic, t.Cost 
FROM Pacienti p 
INNER JOIN Tratamente t on p.ID_pacient=t.ID_pacient 
INNER JOIN Medici m on t.ID_medic=m.ID_medic 
WHERE t.Cost > 1000;

-- 3. Pacientii grupati dupa gen + numar pacienti care au primit tratamente, cu informații despre medici
SELECT p.Gen, COUNT(t.ID_tratament) AS Numar_tratamente
FROM Pacienti p 
INNER JOIN Tratamente t ON p.ID_pacient = t.ID_pacient
INNER JOIN Medici m on t.ID_medic=m.ID_medic 
GROUP BY p.Gen;

-- 4. Medicii + numar de tratamente pentru medicii care au administrat 2 tratamente + pacientii
SELECT m.Nume as Nume_Medic, m.Prenume AS Prenume_Medic, p.Nume as Nume_Pacient, p.Prenume AS Prenume_Pacient, COUNT(t.ID_tratament) as Numar_tratamente
FROM Medici m
INNER JOIN Tratamente t on m.ID_medic=t.ID_medic 
INNER JOIN Pacienti p ON t.ID_pacient = p.ID_pacient
GROUP BY m.Nume, m.Prenume, m.ID_medic, p.Nume, p.Prenume
HAVING COUNT(t.ID_tratament)=2;

-- 5. Pacientii, serviciile medicale pe care le-au primit si data serviciului, fara a repeta aceleasi combinatii
SELECT DISTINCT p.Nume, p.Prenume, s.Denumire as Denumire_Serviciu, ps.Data_serviciu 
FROM Pacienti p 
INNER JOIN PacientServiciu ps on p.ID_pacient=ps.ID_pacient
INNER JOIN ServiciiMedicale s on ps.ID_serviciu = s.ID_serviciu;

-- 6. Medicii care au specializarea cardiologie si au programari intre orele 10:00 și 12:00
SELECT m.Nume, m.Prenume, pr.Ora_programarii 
FROM Medici m
INNER JOIN Programari pr on m.ID_medic=pr.ID_medic
INNER JOIN Specializari s ON m.ID_specializare = s.ID_specializare
WHERE s.Denumire='Cardiologie' AND pr.Ora_programarii BETWEEN '10:00' AND '12:00';

-- 7. Metodele de plata distincte utilizate in facturile pacientilor care au fost tratati in cadrul serviciilor de "Ecografie abdominala"
SELECT DISTINCT f.Metoda_plata 
FROM PacientServiciu ps
INNER JOIN Facturi f on ps.ID_pacient=f.ID_pacient
INNER JOIN ServiciiMedicale sm ON ps.ID_serviciu = sm.ID_serviciu
WHERE sm.Denumire='Ecografie abdominala';

-- 8. Grupeaza serviciile medicale si afiseaza costul mediu pentru fiecare serviciu, dar numai serviciile care au un cost mediu mai mare de 200 lei
SELECT Denumire, AVG(Cost) as Cost_mediu 
FROM ServiciiMedicale
GROUP BY Denumire
HAVING AVG(Cost) > 200;

-- 9. Tratamentele si numele medicilor care le-au administrat pacientilor cu nume care incepe cu P
SELECT t.Descriere, m.Nume as Nume_Medic, m.Prenume as Prenume_Medic 
FROM Medici m
INNER JOIN Tratamente t on m.ID_medic=t.ID_medic
INNER JOIN Pacienti p on t.ID_pacient=p.ID_pacient
WHERE p.Nume LIKE 'P%';

-- 10. Pacientii si medicii lor, impreuna cu serviciile medicale pe care le-au primit, grupate dupa medic
SELECT m.Nume AS Nume_Medic, m.Prenume AS Prenume_Medic, 
p.Nume AS Nume_Pacient, p.Prenume AS Prenume_Pacient, 
s.Denumire AS Serviciu_Medical
FROM Medici m
INNER JOIN Programari pr ON m.ID_medic = pr.ID_medic
INNER JOIN Pacienti p ON pr.ID_pacient = p.ID_pacient
INNER JOIN PacientServiciu ps ON p.ID_pacient = ps.ID_pacient
INNER JOIN ServiciiMedicale s ON ps.ID_serviciu = s.ID_serviciu
GROUP BY m.Nume, m.Prenume, p.Nume, p.Prenume, s.Denumire;

--LAB3
CREATE TABLE Versiuni(
	Id INT IDENTITY PRIMARY KEY,
	Versiune INT,
	DataModificare DATETIME DEFAULT GETDATE()
);

INSERT INTO Versiuni(Versiune) VALUES(0);

SELECT * FROM Versiuni;

GO

CREATE PROCEDURE ModificaTipTelefonPacienti 
AS
BEGIN
ALTER TABLE Pacienti 
ALTER COLUMN Telefon VARCHAR(20);
PRINT 'Tipul coloanei [Telefon] din tabela [Pacienti] a fost modificat.';
END

GO

CREATE PROCEDURE RevertTipTelefonPacienti
AS
BEGIN
	ALTER TABLE Pacienti ALTER COLUMN Telefon VARCHAR(15);
	PRINT 'Tipul coloanei [Telefon] din tabela [Pacienti] a fost restaurat.';
END

GO

CREATE PROCEDURE AdaugaValoareImplicitaCost AS
BEGIN
	ALTER TABLE ServiciiMedicale ADD CONSTRAINT Df_Cost DEFAULT 100 FOR Cost;
	PRINT 'Valoarea implicita a fost adaugata pentru [Cost] in tabela [ServiciiMedicale].';
END

GO

CREATE PROCEDURE RevertValoareImplicitaCost AS
BEGIN
	ALTER TABLE ServiciiMedicale DROP CONSTRAINT Df_Cost;
	PRINT 'Valoarea implicita a fost stearsa pentru [Cost] in tabela [ServiciiMedicale].';
END

GO

CREATE PROCEDURE CreeazaTabelaIstoricModificari AS
BEGIN
	CREATE TABLE IstoricModificari(
		ID INT PRIMARY KEY IDENTITY,
		Descriere VARCHAR(255),
		DataModificare DATETIME DEFAULT GETDATE()
	);
	PRINT 'Tabelul [IstoricModificari] a fost creat.';
END

GO

CREATE PROCEDURE StergeTabelaIstoricModificari AS
BEGIN
	DROP TABLE IstoricModificari;
	PRINT 'Tabelul IstoricModificari a fost sters.';
END

GO

CREATE PROCEDURE AdaugaCampNumarSedinte AS
BEGIN
	ALTER TABLE Tratamente ADD NumarSedinte INT;
	PRINT 'Campul [NumarSedinte] a fost adaugat in tabela [Tratamente].';
END

GO

CREATE PROCEDURE StergeCampNumarSedinte AS
BEGIN
	ALTER TABLE Tratamente DROP COLUMN NumarSedinte;
	PRINT 'Campul [NumarSedinte] a fost sters din tabela [Tratamente].'
END

GO

CREATE PROCEDURE AdaugaCheieStrainaFacturiMedici AS
BEGIN
    ALTER TABLE Facturi ADD ID_medic INT;
	ALTER TABLE Facturi ADD CONSTRAINT FK_Facturi_Medici FOREIGN KEY (ID_medic) REFERENCES Medici(ID_medic);
	PRINT 'Cheia straina a fost adaugata in tabela [Facturi].';
END

GO

CREATE PROCEDURE StergeCheieStrainaFacturiMedici AS
BEGIN
	ALTER TABLE Facturi DROP CONSTRAINT FK_Facturi_Medici;
	ALTER TABLE Facturi DROP COLUMN ID_medic;
	PRINT 'Cheia straina a fost stearsa din tabela [Facturi].';
END

GO

CREATE PROCEDURE Main (@VersiuneNoua INT) AS
BEGIN
	DECLARE @VersiuneCurenta INT;
	SELECT TOP 1 @VersiuneCurenta = Versiune FROM Versiuni ORDER BY DataModificare DESC;

	IF @VersiuneNoua < 0 OR @VersiuneNoua > 5
	BEGIN
		PRINT 'Versiune invalida. Introduceti o versiune intre 0 si 5.';
		RETURN;
	END

	IF @VersiuneCurenta = @VersiuneNoua
	BEGIN
		PRINT 'Baza de date este deja la versiunea specificata.';
		RETURN;
	END

	WHILE @VersiuneCurenta < @VersiuneNoua
	BEGIN
		SET @VersiuneCurenta = @VersiuneCurenta + 1;
		IF @VersiuneCurenta = 1 EXEC ModificaTipTelefonPacienti;
		ELSE IF @VersiuneCurenta = 2 EXEC AdaugaValoareImplicitaCost;
		ELSE IF @VersiuneCurenta = 3 EXEC CreeazaTabelaIstoricModificari;
		ELSE IF @VersiuneCurenta = 4 EXEC AdaugaCampNumarSedinte;
		ELSE IF @VersiuneCurenta = 5 EXEC AdaugaCheieStrainaFacturiMedici;

		INSERT INTO Versiuni(Versiune) VALUES(@VersiuneCurenta);
	END

	WHILE @VersiuneCurenta > @VersiuneNoua
	BEGIN
		SET @VersiuneCurenta = @VersiuneCurenta - 1;
		IF @VersiuneCurenta = 4 EXEC StergeCheieStrainaFacturiMedici;
		ELSE IF @VersiuneCurenta = 3 EXEC StergeCampNumarSedinte;
		ELSE IF @VersiuneCurenta = 2 EXEC StergeTabelaIstoricModificari;
		ELSE IF @VersiuneCurenta = 1 EXEC RevertValoareImplicitaCost;
		ELSE IF @VersiuneCurenta= 0 EXEC RevertTipTelefonPacienti;

		INSERT INTO Versiuni(Versiune) VALUES(@VersiuneCurenta);
	END

	PRINT 'Baza de date a fost actualizata la versiunea ' + CAST(@VersiuneCurenta AS VARCHAR(10));
END
	
GO

EXEC ModificaTipTelefonPacienti
EXEC RevertTipTelefonPacienti
EXEC AdaugaValoareImplicitaCost
EXEC RevertValoareImplicitaCost
EXEC CreeazaTabelaIstoricModificari
EXEC StergeTabelaIstoricModificari
EXEC AdaugaCampNumarSedinte
EXEC StergeCampNumarSedinte
EXEC AdaugaCheieStrainaFacturiMedici
EXEC StergeCheieStrainaFacturiMedici

EXEC Main 1
EXEC Main 2
EXEC Main 3
EXEC Main 4
EXEC Main 5
EXEC Main 6
EXEC Main 0

--lab4
---- if tables exist drop any foreign constraints ----
if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestRunTables_Tables]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)
ALTER TABLE [TestRunTables] DROP CONSTRAINT FK_TestRunTables_Tables
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestTables_Tables]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)
ALTER TABLE [TestTables] DROP CONSTRAINT FK_TestTables_Tables
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestRunTables_TestRuns]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)
ALTER TABLE [TestRunTables] DROP CONSTRAINT FK_TestRunTables_TestRuns
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestRunViews_TestRuns]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)
ALTER TABLE [TestRunViews] DROP CONSTRAINT FK_TestRunViews_TestRuns
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestTables_Tests]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)
ALTER TABLE [TestTables] DROP CONSTRAINT FK_TestTables_Tests
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestViews_Tests]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)
ALTER TABLE [TestViews] DROP CONSTRAINT FK_TestViews_Tests
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestRunViews_Views]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)
ALTER TABLE [TestRunViews] DROP CONSTRAINT FK_TestRunViews_Views
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestViews_Views]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)
ALTER TABLE [TestViews] DROP CONSTRAINT FK_TestViews_Views
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[Tables]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [Tables]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[TestRunTables]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [TestRunTables]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[TestRunViews]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [TestRunViews]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[TestRuns]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [TestRuns]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[TestTables]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [TestTables]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[TestViews]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [TestViews]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[Tests]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [Tests]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[Views]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [Views]
GO

---- create the tables ----
CREATE TABLE [Tables] (
	[TableID] [int] IDENTITY (1, 1) NOT NULL ,
	[Name] [nvarchar] (50) COLLATE SQL_Latin1_General_CP1_CI_AS NOT NULL 
) ON [PRIMARY]
GO

CREATE TABLE [TestRunTables] (
	[TestRunID] [int] NOT NULL ,
	[TableID] [int] NOT NULL ,
	[StartAt] [datetime] NOT NULL ,
	[EndAt] [datetime] NOT NULL 
) ON [PRIMARY]
GO

CREATE TABLE [TestRunViews] (
	[TestRunID] [int] NOT NULL ,
	[ViewID] [int] NOT NULL ,
	[StartAt] [datetime] NOT NULL ,
	[EndAt] [datetime] NOT NULL 
) ON [PRIMARY]
GO

CREATE TABLE [TestRuns] (
	[TestRunID] [int] IDENTITY (1, 1) NOT NULL ,
	[Description] [nvarchar] (2000) COLLATE SQL_Latin1_General_CP1_CI_AS NULL ,
	[StartAt] [datetime] NULL ,
	[EndAt] [datetime] NULL 
) ON [PRIMARY]
GO

CREATE TABLE [TestTables] (
	[TestID] [int] NOT NULL ,
	[TableID] [int] NOT NULL ,
	[NoOfRows] [int] NOT NULL ,
	[Position] [int] NOT NULL 
) ON [PRIMARY]
GO

CREATE TABLE [TestViews] (
	[TestID] [int] NOT NULL ,
	[ViewID] [int] NOT NULL 
) ON [PRIMARY]
GO

CREATE TABLE [Tests] (
	[TestID] [int] IDENTITY (1, 1) NOT NULL ,
	[Name] [nvarchar] (50) COLLATE SQL_Latin1_General_CP1_CI_AS NOT NULL 
) ON [PRIMARY]
GO

CREATE TABLE [Views] (
	[ViewID] [int] IDENTITY (1, 1) NOT NULL ,
	[Name] [nvarchar] (50) COLLATE SQL_Latin1_General_CP1_CI_AS NOT NULL 
) ON [PRIMARY]
GO

ALTER TABLE [Tables] WITH NOCHECK ADD 
	CONSTRAINT [PK_Tables] PRIMARY KEY  CLUSTERED 
	(
		[TableID]
	)  ON [PRIMARY] 
GO

ALTER TABLE [TestRunTables] WITH NOCHECK ADD 
	CONSTRAINT [PK_TestRunTables] PRIMARY KEY  CLUSTERED 
	(
		[TestRunID],
		[TableID]
	)  ON [PRIMARY] 
GO

ALTER TABLE [TestRunViews] WITH NOCHECK ADD 
	CONSTRAINT [PK_TestRunViews] PRIMARY KEY  CLUSTERED 
	(
		[TestRunID],
		[ViewID]
	)  ON [PRIMARY] 
GO

ALTER TABLE [TestRuns] WITH NOCHECK ADD 
	CONSTRAINT [PK_TestRuns] PRIMARY KEY  CLUSTERED 
	(
		[TestRunID]
	)  ON [PRIMARY] 

GO

ALTER TABLE [TestTables] WITH NOCHECK ADD 
	CONSTRAINT [PK_TestTables] PRIMARY KEY  CLUSTERED 
	(
		[TestID],
		[TableID]
	)  ON [PRIMARY] 
GO

ALTER TABLE [TestViews] WITH NOCHECK ADD 
	CONSTRAINT [PK_TestViews] PRIMARY KEY  CLUSTERED 
	(
		[TestID],
		[ViewID]
	)  ON [PRIMARY] 
GO

ALTER TABLE [Tests] WITH NOCHECK ADD 
	CONSTRAINT [PK_Tests] PRIMARY KEY  CLUSTERED 
	(
		[TestID]
	)  ON [PRIMARY] 
GO

ALTER TABLE [Views] WITH NOCHECK ADD 
	CONSTRAINT [PK_Views] PRIMARY KEY  CLUSTERED 
	(
		[ViewID]
	)  ON [PRIMARY] 
GO

ALTER TABLE [TestRunTables] ADD 
	CONSTRAINT [FK_TestRunTables_Tables] FOREIGN KEY 
	(
		[TableID]
	) REFERENCES [Tables] (
		[TableID]
	) ON DELETE CASCADE  ON UPDATE CASCADE ,
	CONSTRAINT [FK_TestRunTables_TestRuns] FOREIGN KEY 
	(
		[TestRunID]
	) REFERENCES [TestRuns] (
		[TestRunID]
	) ON DELETE CASCADE  ON UPDATE CASCADE 
GO

ALTER TABLE [TestRunViews] ADD 
	CONSTRAINT [FK_TestRunViews_TestRuns] FOREIGN KEY 
	(
		[TestRunID]
	) REFERENCES [TestRuns] (
		[TestRunID]
	) ON DELETE CASCADE  ON UPDATE CASCADE ,
	CONSTRAINT [FK_TestRunViews_Views] FOREIGN KEY 
	(
		[ViewID]
	) REFERENCES [Views] (
		[ViewID]
	) ON DELETE CASCADE  ON UPDATE CASCADE 
GO

ALTER TABLE [TestTables] ADD 
	CONSTRAINT [FK_TestTables_Tables] FOREIGN KEY 
	(
		[TableID]
	) REFERENCES [Tables] (
		[TableID]
	) ON DELETE CASCADE  ON UPDATE CASCADE ,
	CONSTRAINT [FK_TestTables_Tests] FOREIGN KEY 
	(
		[TestID]
	) REFERENCES [Tests] (
		[TestID]
	) ON DELETE CASCADE  ON UPDATE CASCADE 
GO

ALTER TABLE [TestViews] ADD 
	CONSTRAINT [FK_TestViews_Tests] FOREIGN KEY 
	(
		[TestID]
	) REFERENCES [Tests] (
		[TestID]
	),
	CONSTRAINT [FK_TestViews_Views] FOREIGN KEY 
	(
		[ViewID]
	) REFERENCES [Views] (
		[ViewID]
	)
GO



-------------------------------CREARE TABELE-------------------------------

DROP TABLE Calificare
DROP TABLE Laboranti
DROP TABLE Instrumente

--  o tabelă având un câmp ca şi cheie primară şi nici o cheie străină
CREATE TABLE Instrumente(
	id INT PRIMARY KEY IDENTITY(1,1),
	denumire NVARCHAR(100),
)

-- o tabelă având un câmp ca şi cheie primară şi cel puţin o cheie străină
CREATE TABLE Laboranti(
     id INT PRIMARY KEY IDENTITY(1,1),
	 nume NVARCHAR(100),
	 instrument INT FOREIGN KEY REFERENCES Instrumente(id)
)

-- o tabelă având două câmpuri ca şi cheie primară

CREATE TABLE Calificare(
	laborant INT FOREIGN KEY REFERENCES Laboranti(id),
	instrument INT FOREIGN KEY REFERENCES Instrumente(id),
	CONSTRAINT PK_LabInstrument PRIMARY KEY (laborant, instrument),
	experienta INT
)



--------------------------------------- VIEW ---------------------------------------------------

-- primul View: un view ce conţine o comandă SELECT pe o tabelă
-- Afisam instrumentele 
GO
CREATE OR ALTER VIEW viewInstrumente AS
	SELECT * FROM Instrumente
GO

-- al doilea View: un view ce conţine o comandă SELECT aplicată pe cel puţin două tabele
-- Experienta laborantilor pentru instumentele folosite
CREATE OR ALTER VIEW viewLaboranti AS
	SELECT Laboranti.nume, Instrumente.denumire, Calificare.experienta
	FROM Laboranti, Instrumente, Calificare
	WHERE Calificare.laborant = Laboranti.id AND Laboranti.instrument = Instrumente.id
GO

-- al treilea View: un view ce conţine o comandă SELECT aplicată pe cel puţin două tabele şi având o clauză GROUP BY.
-- Afiseaza instrumentele folosite de cel putin 1 laborant
CREATE OR ALTER VIEW viewCalificare AS 
	SELECT I.denumire, COUNT(*) AS nr_laboranti
	FROM Laboranti L, Instrumente I
	WHERE L.instrument = I.id
	GROUP BY I.denumire
GO




-- Tables – conţine listele tabelelor ce ar putea face parte din testare
DELETE FROM Tables
INSERT INTO Tables VALUES ('Instrumente'), ('Laboranti'),('Calificare')

-- Views – o muţime de view-uri existente în baza de date şi care sunt utilizate în testarea performanţei unor interogări particulare
DELETE FROM Views
INSERT INTO Views VALUES ('viewInstrumente'),('viewLaboranti'),('viewCalificare')

-- Tests – conţine informaţii despre diferite configuraţii de testare
DELETE FROM Tests
INSERT INTO Tests VALUES ('selectView'),('insertInstrumente'),('deleteInstrumente'),('insertLaboranti'),('deleteLaboranti'),('insertCalificare'),('deleteCalificare')

SELECT * FROM Tests
SELECT * FROM Tables
SELECT * FROM Views

-- TestViews – este  tabela  de legătură dintre Tests şi Views şi conţine lista view-urilor implicate în fiecare test
DELETE FROM TestViews
INSERT INTO TestViews VALUES (1,1)
INSERT INTO TestViews VALUES (1,2)
INSERT INTO TestViews VALUES (1,3)

SELECT * FROM TestViews

-- TestTables – este  tabela  de  legătură dintre Tests şi Tables şi conţine lista tabelelor implicate în fiecare test
DELETE FROM TestTables
INSERT INTO TestTables VALUES (2,1,100,1),(4,2,100,2),(6,3,100,3)

SELECT * FROM TestTables
GO



---------------------- PROCEDURI DE INSERARE SI STERGERE --------------------

CREATE OR ALTER PROC insertInstrumente
AS
	DECLARE @crt INT = 1
	DECLARE @rows INT
	SELECT @rows = NoOfRows FROM TestTables WHERE TestID = 2
	PRINT @rows
	WHILE @crt <= @rows
	BEGIN
		INSERT INTO Instrumente VALUES (CAST(@crt as nvarchar(20)))
		SET @crt = @crt + 1
	END
GO
CREATE OR ALTER PROC deleteInstrumente
AS
	DELETE FROM Instrumente WHERE id > 0
	
GO


CREATE OR ALTER PROC insertLaboranti
AS
	DECLARE @crt INT = 1
	DECLARE @rows INT
	SELECT @rows = NoOfRows FROM TestTables WHERE TestID = 4
	PRINT @rows
	WHILE @crt <= @rows
	BEGIN
		INSERT INTO Laboranti VALUES (CAST(@crt as nvarchar(20)),@crt)
		SET @crt = @crt + 1
	END

GO
CREATE OR ALTER PROC deleteLaboranti
AS
	DELETE FROM Laboranti WHERE id > 0

GO


CREATE OR ALTER PROC insertCalificare
AS
	DECLARE @crt INT = 1
	DECLARE @rows INT
	SELECT @rows = NoOfRows FROM TestTables WHERE TestID = 6
	PRINT @rows
	WHILE @crt <= @rows
	BEGIN
		INSERT INTO Calificare VALUES (@crt,@crt,@crt)
		SET @crt = @crt + 1
	END
GO
CREATE OR ALTER PROC deleteCalificare
AS
	DELETE FROM Calificare
GO



CREATE OR ALTER PROC TestRunTablesProc
AS 
	DECLARE @start DATETIME;
	DECLARE @start1 DATETIME;
	DECLARE @start2 DATETIME;
	DECLARE @start3 DATETIME;
	DECLARE @start4 DATETIME;
	DECLARE @start5 DATETIME;
	DECLARE @start6 DATETIME;
	DECLARE @end1 DATETIME;
	DECLARE @end2 DATETIME;
	DECLARE @end3 DATETIME;
	DECLARE @end4 DATETIME;
	DECLARE @end5 DATETIME;
	DECLARE @end6 DATETIME;
	DECLARE @end DATETIME;
	DECLARE @description VARCHAR(100);
	SET @description = '';
	SET @start = GETDATE();
	-- 1) ştergerea datelor din tabelele asociate testului (în ordinea dată de câmpul Position) 
	EXEC deleteCalificare;
	SET @description = @description +  'deleteCalificare ';
	EXEC deleteLaboranti;
	SET @description = @description +  'deleteLaboranti ';
	EXEC deleteInstrumente;
	SET @description = @description +  'deleteInstrumente ';
	
	-- 2) inserareaînregistrărilor în tabele în ordinea inversă dată de Position (numărul de înregistrări inserate este dat de câmpul NoOfRows) 
	SET @start4 = GETDATE();
	EXEC insertInstrumente;
	SET @description = @description +  'insertInstrumente ';
	SET @end4 = GETDATE();
	SET @start5 = GETDATE();
	EXEC insertLaboranti;
	SET @description = @description +  'insertLaboranti ';
	SET @end5 = GETDATE();
	SET @start6 = GETDATE();
	EXEC insertCalificare;
	SET @description = @description +  'insertCalificare ';
	SET @end6 = GETDATE();
	
	DECLARE @start1view DATETIME;
	DECLARE @start2view DATETIME;
	DECLARE @start3view DATETIME;
	DECLARE @end1view DATETIME;
	DECLARE @end2view DATETIME;
	DECLARE @end3view DATETIME;
	
	-- 3) Evaluarea timpului de execuţie a view-urilor
	SET @start1view = GETDATE();
	EXEC ('SELECT * FROM viewInstrumente');
	SET @description = @description +  'viewInstrumente ';
	SET @end1view = GETDATE();

	SET @start2view = GETDATE();
	EXEC ('SELECT * FROM viewLaboranti');
	SET @description = @description +  'viewLaboranti ';
	SET @end2view = GETDATE();

	SET @start3view = GETDATE();
	EXEC ('SELECT * FROM viewCalificare');
	SET @description = @description +  'viewCalificare ';
	SET @end3view = GETDATE();

	SET @end = GETDATE();
	
	-- TestRuns – conţine rezultatele execuţiei diferitelor teste
	INSERT INTO TestRuns VALUES (@description,@start,@end)
	DECLARE @ID INT = @@IDENTITY
	INSERT INTO TestRunTables VALUES(@ID,1,@start4,@end4);
	INSERT INTO TestRunTables VALUES(@ID,2,@start5,@end5);
	INSERT INTO TestRunTables VALUES(@ID,3,@start6,@end6);
	INSERT INTO TestRunViews VALUES (@ID, 1, @start1view, @end1view);
	INSERT INTO TestRunViews VALUES (@ID, 2, @start2view, @end2view);
	INSERT INTO TestRunViews VALUES (@ID, 3, @start3view, @end3view);
GO 

EXEC TestRunTablesProc


SELECT * FROM TestRuns
SELECT * FROM TestRunTables
SELECT * FROM TestRunViews

DELETE FROM TestRuns
DELETE FROM TestRunTables
DELETE FROM TestRunViews


-- Lab 5
CREATE FUNCTION dbo.ValidareCNP (@CNP VARCHAR(13))
RETURNS BIT
AS
BEGIN
    DECLARE @isValid BIT;

    IF LEN(@CNP) <> 13
    BEGIN
        SET @isValid = 0;
        RETURN @isValid;
    END

    IF @CNP LIKE '%[^0-9]%'
    BEGIN
        SET @isValid = 0;
        RETURN @isValid;
    END

    SET @isValid = 1;
    RETURN @isValid;
END;

CREATE FUNCTION dbo.ValidareEmail (@Email VARCHAR(40))
RETURNS BIT
AS
BEGIN
    DECLARE @isValid BIT;

    IF @Email LIKE '%@%.%' AND LEN(@Email) BETWEEN 5 AND 40
    BEGIN
        SET @isValid = 1;
    END
    ELSE
    BEGIN
        SET @isValid = 0;
    END

    RETURN @isValid;
END;

CREATE PROCEDURE dbo.CreatePacient
    @Nume VARCHAR(40),
    @Prenume VARCHAR(40),
    @CNP VARCHAR(13),
    @Data_nasterii DATE,
    @Gen VARCHAR(1),
    @Adresa VARCHAR(60),
    @Telefon VARCHAR(15),
    @Email VARCHAR(40)
AS
BEGIN
    IF dbo.ValidareCNP(@CNP) = 0
    BEGIN
        RAISERROR('CNP invalid!', 16, 1);
        RETURN;
    END

    IF dbo.ValidareEmail(@Email) = 0
    BEGIN
        RAISERROR('Email invalid!', 16, 1);
        RETURN;
    END

    INSERT INTO Pacienti (Nume, Prenume, CNP, Data_nasterii, Gen, Adresa, Telefon, Email)
    VALUES (@Nume, @Prenume, @CNP, @Data_nasterii, @Gen, @Adresa, @Telefon, @Email);
END;

CREATE PROCEDURE dbo.ReadPacient
    @ID_pacient INT
AS
BEGIN
    SELECT * FROM Pacienti WHERE ID_pacient = @ID_pacient;
END;

CREATE PROCEDURE dbo.UpdatePacient
    @ID_pacient INT,
    @Nume VARCHAR(40),
    @Prenume VARCHAR(40),
    @CNP VARCHAR(13),
    @Data_nasterii DATE,
    @Gen VARCHAR(1),
    @Adresa VARCHAR(60),
    @Telefon VARCHAR(15),
    @Email VARCHAR(40)
AS
BEGIN
    IF dbo.ValidareCNP(@CNP) = 0
    BEGIN
        RAISERROR('CNP invalid!', 16, 1);
        RETURN;
    END

    IF dbo.ValidareEmail(@Email) = 0
    BEGIN
        RAISERROR('Email invalid!', 16, 1);
        RETURN;
    END

    UPDATE Pacienti
    SET Nume = @Nume,
        Prenume = @Prenume,
        CNP = @CNP,
        Data_nasterii = @Data_nasterii,
        Gen = @Gen,
        Adresa = @Adresa,
        Telefon = @Telefon,
        Email = @Email
    WHERE ID_pacient = @ID_pacient;
END;

CREATE PROCEDURE dbo.DeletePacient
    @ID_pacient INT
AS
BEGIN
    DELETE FROM Pacienti WHERE ID_pacient = @ID_pacient;
END;

CREATE PROCEDURE dbo.CreateMedici
    @Nume VARCHAR(40),
    @Prenume VARCHAR(40),
    @ID_specializare INT,
    @Telefon VARCHAR(15),
    @Email VARCHAR(40),
    @Data_angajarii DATE,
    @Grad_profesional VARCHAR(40)
AS
BEGIN
    IF dbo.ValidareEmail(@Email) = 0
    BEGIN
        RAISERROR('Email invalid!', 16, 1);
        RETURN;
    END

    INSERT INTO Medici (Nume, Prenume, ID_specializare, Telefon, Email, Data_angajarii, Grad_profesional)
    VALUES (@Nume, @Prenume, @ID_specializare, @Telefon, @Email, @Data_angajarii, @Grad_profesional);
END;

CREATE PROCEDURE dbo.ReadMedici
    @ID_medic INT
AS
BEGIN
    SELECT * FROM Medici WHERE ID_medic = @ID_medic;
END;

CREATE PROCEDURE dbo.UpdateMedici
    @ID_medic INT,
    @Nume VARCHAR(40),
    @Prenume VARCHAR(40),
    @ID_specializare INT,
    @Telefon VARCHAR(15),
    @Email VARCHAR(40),
    @Data_angajarii DATE,
    @Grad_profesional VARCHAR(40)
AS
BEGIN
    IF dbo.ValidareEmail(@Email) = 0
    BEGIN
        RAISERROR('Email invalid!', 16, 1);
        RETURN;
    END

    UPDATE Medici
    SET Nume = @Nume,
        Prenume = @Prenume,
        ID_specializare = @ID_specializare,
        Telefon = @Telefon,
        Email = @Email,
        Data_angajarii = @Data_angajarii,
        Grad_profesional = @Grad_profesional
    WHERE ID_medic = @ID_medic;
END;

CREATE PROCEDURE dbo.DeleteMedici
    @ID_medic INT
AS
BEGIN
    DELETE FROM Medici WHERE ID_medic = @ID_medic;
END;

CREATE PROCEDURE dbo.CreateServiciu
    @Denumire VARCHAR(50),
    @Detalii VARCHAR(255),
    @Cost DECIMAL(10,2)
AS
BEGIN
    INSERT INTO ServiciiMedicale (Denumire, Detalii, Cost)
    VALUES (@Denumire, @Detalii, @Cost);
END;

CREATE PROCEDURE dbo.ReadServiciu
    @ID_serviciu INT
AS
BEGIN
    SELECT * FROM ServiciiMedicale WHERE ID_serviciu = @ID_serviciu;
END;

CREATE PROCEDURE dbo.UpdateServiciu
    @ID_serviciu INT,
    @Denumire VARCHAR(50),
    @Detalii VARCHAR(255),
    @Cost DECIMAL(10,2)
AS
BEGIN
    UPDATE ServiciiMedicale
    SET Denumire = @Denumire,
        Detalii = @Detalii,
        Cost = @Cost
    WHERE ID_serviciu = @ID_serviciu;
END;

CREATE PROCEDURE dbo.DeleteServiciu
    @ID_serviciu INT
AS
BEGIN
    DELETE FROM ServiciiMedicale WHERE ID_serviciu = @ID_serviciu;
END;

CREATE PROCEDURE dbo.CreateProgramare
    @ID_pacient INT,
    @ID_medic INT,
    @Data_programarii DATE,
    @Ora_programarii TIME,
    @Motiv VARCHAR(100)
AS
BEGIN
    INSERT INTO Programari (ID_pacient, ID_medic, Data_programarii, Ora_programarii, Motiv)
    VALUES (@ID_pacient, @ID_medic, @Data_programarii, @Ora_programarii, @Motiv);
END;

CREATE PROCEDURE dbo.ReadProgramare
    @ID_programare INT
AS
BEGIN
    SELECT * FROM Programari WHERE ID_programare = @ID_programare;
END;

CREATE PROCEDURE dbo.UpdateProgramare
    @ID_programare INT,
    @ID_pacient INT,
    @ID_medic INT,
    @Data_programarii DATE,
    @Ora_programarii TIME,
    @Motiv VARCHAR(100)
AS
BEGIN
    UPDATE Programari
    SET ID_pacient = @ID_pacient,
        ID_medic = @ID_medic,
        Data_programarii = @Data_programarii,
        Ora_programarii = @Ora_programarii,
        Motiv = @Motiv
    WHERE ID_programare = @ID_programare;
END;

CREATE PROCEDURE dbo.DeleteProgramare
    @ID_programare INT
AS
BEGIN
    DELETE FROM Programari WHERE ID_programare = @ID_programare;
END;

CREATE PROCEDURE InsertPacientServiciu
    @ID_pacient INT,
    @ID_serviciu INT,
    @Data_serviciu DATE
AS
BEGIN
    IF NOT EXISTS (SELECT 1 FROM Pacienti WHERE ID_pacient = @ID_pacient)
    BEGIN
        PRINT 'Pacientul nu exista';
        RETURN;
    END

    IF NOT EXISTS (SELECT 1 FROM ServiciiMedicale WHERE ID_serviciu = @ID_serviciu)
    BEGIN
        PRINT 'Serviciul nu exista';
        RETURN;
    END

    INSERT INTO PacientServiciu (ID_pacient, ID_serviciu, Data_serviciu)
    VALUES (@ID_pacient, @ID_serviciu, @Data_serviciu);
    
    PRINT 'Serviciu adaugat pacientului cu succes';
END

CREATE PROCEDURE SelectPacientServiciu
    @ID_pacient INT = NULL,
    @ID_serviciu INT = NULL
AS
BEGIN
    SELECT PS.ID_pacient, P.Nume + ' ' + P.Prenume AS NumePacient, 
           PS.ID_serviciu, S.Denumire AS Serviciu, 
           PS.Data_serviciu
    FROM PacientServiciu PS
    JOIN Pacienti P ON PS.ID_pacient = P.ID_pacient
    JOIN ServiciiMedicale S ON PS.ID_serviciu = S.ID_serviciu
    WHERE (@ID_pacient IS NULL OR PS.ID_pacient = @ID_pacient)
      AND (@ID_serviciu IS NULL OR PS.ID_serviciu = @ID_serviciu)
    ORDER BY PS.Data_serviciu;
END

CREATE PROCEDURE UpdatePacientServiciu
    @ID_pacient INT,
    @ID_serviciu INT,
    @Data_serviciu DATE
AS
BEGIN
    IF NOT EXISTS (SELECT 1 FROM Pacienti WHERE ID_pacient = @ID_pacient)
    BEGIN
        PRINT 'Pacientul nu exista';
        RETURN;
    END

    IF NOT EXISTS (SELECT 1 FROM ServiciiMedicale WHERE ID_serviciu = @ID_serviciu)
    BEGIN
        PRINT 'Serviciul nu exista';
        RETURN;
    END

    UPDATE PacientServiciu
    SET Data_serviciu = @Data_serviciu
    WHERE ID_pacient = @ID_pacient AND ID_serviciu = @ID_serviciu;
    
    PRINT 'Datele pentru pacientul ' + CAST(@ID_pacient AS VARCHAR) + ' si serviciul ' + CAST(@ID_serviciu AS VARCHAR) + ' au fost actualizate cu succes';
END

CREATE PROCEDURE DeletePacientServiciu
    @ID_pacient INT,
    @ID_serviciu INT
AS
BEGIN
    IF NOT EXISTS (SELECT 1 FROM PacientServiciu WHERE ID_pacient = @ID_pacient AND ID_serviciu = @ID_serviciu)
    BEGIN
        PRINT 'Inregistrarea nu exista';
        RETURN;
    END

    DELETE FROM PacientServiciu 
    WHERE ID_pacient = @ID_pacient AND ID_serviciu = @ID_serviciu;

    PRINT 'Serviciu sters cu succes pentru pacientul ' + CAST(@ID_pacient AS VARCHAR);
END

CREATE VIEW dbo.VW_PacientiTratamente AS
SELECT Pacienti.ID_pacient, Pacienti.Nume, Pacienti.Prenume, Tratamente.Tip, Tratamente.Descriere, Tratamente.Data_tratament
FROM Pacienti
JOIN Tratamente ON Pacienti.ID_pacient = Tratamente.ID_pacient;

SELECT * FROM dbo.VW_PacientiTratamente;

CREATE VIEW dbo.VW_ProgramariMedici AS
SELECT Programari.ID_programare, Programari.Data_programarii, Programari.Ora_programarii, Medici.Nume AS MedicNume, Medici.Prenume AS MedicPrenume
FROM Programari
JOIN Medici ON Programari.ID_medic = Medici.ID_medic;

SELECT * FROM dbo.VW_ProgramariMedici;

CREATE NONCLUSTERED INDEX idx_pacienti_email ON Pacienti (Email);
CREATE NONCLUSTERED INDEX idx_tratamente_pacient ON Tratamente (ID_pacient);
CREATE NONCLUSTERED INDEX idx_programari_data ON Programari (Data_programarii);

ALTER TABLE Pacienti
ADD CONSTRAINT CHK_Gen CHECK (Gen IN ('M', 'F'));

ALTER TABLE ServiciiMedicale
ADD CONSTRAINT CHK_Cost CHECK (Cost >= 0);

--executarea operatiilor CRUD
EXEC dbo.CreatePacient 
    @Nume = 'Popescu',
    @Prenume = 'Ion',
    @CNP = '1980101123456',
    @Data_nasterii = '1980-01-01',
    @Gen = 'M',
    @Adresa = 'Strada Victoriei, nr. 10',
    @Telefon = '0722123456',
    @Email = 'popescu.ion@gmail.com';

SELECT * FROM Pacienti WHERE CNP = '1980101123456';

EXEC dbo.ReadPacient @ID_pacient = 7;

EXEC dbo.UpdatePacient 
    @ID_pacient = 6,
    @Nume = 'Ionescu',
    @Prenume = 'Maria',
    @CNP = '2900201123456',
    @Data_nasterii = '1990-02-01',
    @Gen = 'F',
    @Adresa = 'Strada Libertății, nr. 25',
    @Telefon = '0733123456',
    @Email = 'ionescu.maria@gmail.com';

SELECT * FROM Pacienti WHERE ID_pacient = 6;

EXEC dbo.DeletePacient @ID_pacient = 6;

SELECT * FROM Pacienti WHERE ID_pacient = 6;

EXEC dbo.CreateMedici 
    @Nume = 'Marin',
    @Prenume = 'Ana',
    @ID_specializare = 1,
    @Telefon = '0744123456',
    @Email = 'ana.marin@gmail.com',
    @Data_angajarii = '2020-05-15',
    @Grad_profesional = 'Specialist';

SELECT * FROM Medici WHERE Email = 'ana.marin@gmail.com';

EXEC dbo.ReadMedici @ID_medic = 6;

EXEC dbo.UpdateMedici 
    @ID_medic = 6,
    @Nume = 'Popa',
    @Prenume = 'George',
    @ID_specializare = 2,
    @Telefon = '0755123456',
    @Email = 'george.popa@gmail.com',
    @Data_angajarii = '2021-08-10',
    @Grad_profesional = 'Primar';

SELECT * FROM Medici WHERE ID_medic = 6;

EXEC dbo.DeleteMedici @ID_medic = 6;

SELECT * FROM Medici WHERE ID_medic = 6;

EXEC dbo.CreateServiciu 
    @Denumire = 'Consult dermatologic',
    @Detalii = 'Consultatie generala pentru afectiuni dermatologice',
    @Cost = 200.00;

SELECT * FROM ServiciiMedicale WHERE Denumire = 'Consult dermatologic';

EXEC dbo.ReadServiciu @ID_serviciu = 6;

EXEC dbo.UpdateServiciu 
    @ID_serviciu = 6,
    @Denumire = 'Consult dermatologic detaliat',
    @Detalii = 'Consultatie completa si diagnostic detaliat',
    @Cost = 300.00;

SELECT * FROM ServiciiMedicale WHERE ID_serviciu = 6;

EXEC dbo.DeleteServiciu @ID_serviciu = 6;

SELECT * FROM ServiciiMedicale WHERE ID_serviciu = 6;

EXEC dbo.CreateProgramare 
    @ID_pacient = 1,
    @ID_medic = 4,
    @Data_programarii = '2024-12-15',
    @Ora_programarii = '10:30:00',
    @Motiv = 'Consultatie de rutina';

SELECT * FROM Programari WHERE ID_pacient = 1 AND ID_medic = 4;

EXEC dbo.ReadProgramare @ID_programare = 6;

EXEC dbo.UpdateProgramare 
    @ID_programare = 6,       
    @ID_pacient = 1,          
    @ID_medic = 1,            
    @Data_programarii = '2024-12-20',
    @Ora_programarii = '11:00:00',   
    @Motiv = 'Consultatie de control';

SELECT * FROM Programari WHERE ID_programare = 6;

EXEC dbo.DeleteProgramare @ID_programare = 6;

SELECT * FROM Programari WHERE ID_programare = 6;

SELECT * FROM sys.dm_db_index_usage_stats;

--
CREATE DATABASE Trenuri;
GO
USE Trenuri;
 
CREATE TABLE TipTren(
tid INT PRIMARY KEY IDENTITY(1,1),
descriere VARCHAR(50)
);
 
CREATE TABLE Tren(
id INT PRIMARY KEY IDENTITY,
tid INT FOREIGN KEY REFERENCES TipTren(tid),
nume VARCHAR(50)
);
 
CREATE TABLE Rute(
rid INT PRIMARY KEY IDENTITY,
nume_ruta VARCHAR(50),
trenid INT FOREIGN KEY REFERENCES Tren(id)
);
 
CREATE TABLE Statie(
sid INT PRIMARY KEY IDENTITY,
nume_statie VARCHAR(50)
);
 
CREATE TABLE RuteStatii(
rid INT,
sid INT,
ora_plecare TIME,
ora_sosire TIME,
CONSTRAINT fk_id_rute FOREIGN KEY(rid) REFERENCES Rute(rid),
CONSTRAINT fk_id_statie FOREIGN KEY(sid) REFERENCES Statie(sid),
CONSTRAINT pk_rute_statie PRIMARY KEY(rid,sid)
);

INSERT INTO TipTren (descriere) VALUES ('Tip1'), ('Tip2'), ('Tip3');
SELECT * FROM TipTren;
 
INSERT INTO Tren (tid, nume) VALUES (1,'Tren1'), (2, 'Tren2'), (3, 'Tren3');
SELECT * FROM Tren;
 
INSERT INTO Rute (nume_ruta, trenid) VALUES ('Ruta1', 1), ('Ruta2', 2), ('Ruta3', 3);
SELECT * FROM Rute;
 
INSERT INTO Statie(nume_statie) VALUES ('Statie1'), ('Statie2'), ('Statie3');
SELECT * FROM Statie;
 
INSERT INTO RuteStatii(rid, sid, ora_plecare, ora_sosire) VALUES (1,1,'12:00','16:00'),
(1,2,'13:45','18:00'), (2,2,'18:20','21:45');
SELECT * FROM RuteStatii;

go;
CREATE PROCEDURE Adauga_Statie @sid INT,@rid INT,@plecare TIME,@sosire TIME
AS
BEGIN
	IF(EXISTS(SELECT * FROM RuteStatii WHERE sid=@sid AND rid=@rid))
	BEGIN
		UPDATE RuteStatii
		SET ora_plecare=@plecare, ora_sosire=@sosire
		WHERE sid=@sid AND rid=@rid;
	END;
	ELSE
	BEGIN
		INSERT INTO RuteStatii(sid,rid,ora_sosire,ora_plecare) VALUES
		(@sid,@rid,@sosire,@plecare);
	END;
END;
 
SELECT * FROM RuteStatii;
 
EXEC Adauga_Statie 1,1,'13:00','15:00';
EXEC Adauga_Statie 3,3,'13:00','15:00';

GO
 
CREATE VIEW Rute_Valide
AS
SELECT r.nume_ruta
FROM RuteStatii rs
INNER JOIN Rute r on rs.rid=r.rid
GROUP BY r.rid,r.nume_ruta
HAVING count(*) = (SELECT COUNT(*) FROM Statie);
 
exec Adauga_Statie 3,1,'10:00','15:00';
 
SELECT * FROM Rute_Valide

--

-- Crearea tabelei pentru tipurile de restaurante
CREATE TABLE TipRestaurant (
    id INT PRIMARY KEY AUTO_INCREMENT,
    nume VARCHAR(255) NOT NULL,
    descriere TEXT
);

-- Crearea tabelei pentru orase
CREATE TABLE Oras (
    id INT PRIMARY KEY AUTO_INCREMENT,
    nume VARCHAR(255) NOT NULL
);

-- Crearea tabelei pentru restaurante
CREATE TABLE Restaurant (
    id INT PRIMARY KEY AUTO_INCREMENT,
    nume VARCHAR(255) NOT NULL,
    adresa VARCHAR(255),
    numar_telefon VARCHAR(20),
    oras_id INT,
    tip_restaurant_id INT,
    FOREIGN KEY (oras_id) REFERENCES Oras(id),
    FOREIGN KEY (tip_restaurant_id) REFERENCES TipRestaurant(id)
);

-- Crearea tabelei pentru utilizatori
CREATE TABLE Utilizator (
    id INT PRIMARY KEY AUTO_INCREMENT,
    nume_utilizator VARCHAR(255) NOT NULL,
    email VARCHAR(255) UNIQUE NOT NULL,
    parola VARCHAR(255) NOT NULL
);

-- Crearea tabelei pentru evaluari (notele date de utilizatori)
CREATE TABLE Evaluare (
    id INT PRIMARY KEY AUTO_INCREMENT,
    utilizator_id INT,
    restaurant_id INT,
    nota DECIMAL(3, 2), -- Nota va fi un numar real cu 2 zecimale
    FOREIGN KEY (utilizator_id) REFERENCES Utilizator(id),
    FOREIGN KEY (restaurant_id) REFERENCES Restaurant(id),
    CONSTRAINT unique_evaluare UNIQUE (utilizator_id, restaurant_id)
);

DELIMITER $$

CREATE PROCEDURE AdaugaNota(
    IN p_restaurant_id INT,
    IN p_utilizator_id INT,
    IN p_nota DECIMAL(3, 2)
)
BEGIN
    -- Verificăm dacă utilizatorul a dat deja o notă pentru restaurantul respectiv
    IF EXISTS (SELECT 1 FROM Evaluare WHERE utilizator_id = p_utilizator_id AND restaurant_id = p_restaurant_id) THEN
        -- Dacă există, actualizăm nota
        UPDATE Evaluare
        SET nota = p_nota
        WHERE utilizator_id = p_utilizator_id AND restaurant_id = p_restaurant_id;
    ELSE
        -- Dacă nu există, inserăm un nou rând în tabelul de evaluări
        INSERT INTO Evaluare (utilizator_id, restaurant_id, nota)
        VALUES (p_utilizator_id, p_restaurant_id, p_nota);
    END IF;
END $$

DELIMITER ;

DELIMITER $$

CREATE FUNCTION AfiseazaEvaluari(p_email VARCHAR(255))
RETURNS TABLE
BEGIN
    RETURN
    SELECT
        tr.nume AS tip_restaurant,
        r.nume AS nume_restaurant,
        r.numar_telefon AS numar_telefon,
        o.nume AS oras,
        e.nota AS nota,
        u.nume_utilizator AS nume_utilizator,
        u.email AS email_utilizator
    FROM Evaluare e
    JOIN Utilizator u ON e.utilizator_id = u.id
    JOIN Restaurant r ON e.restaurant_id = r.id
    JOIN TipRestaurant tr ON r.tip_restaurant_id = tr.id
    JOIN Oras o ON r.oras_id = o.id
    WHERE u.email = p_email;
END $$

DELIMITER ;

--

CREATE DATABASE MagazineDB;
USE MagazineDB;
------------------------------------- creare tabele ----------------------------------------------

CREATE TABLE Clienti(
	Id_Clienti int identity primary key,
	nume varchar(30) not null,
	prenume varchar(30) not null,
	gen varchar(30) not null,
	data_nastere DATE not null
);

CREATE TABLE Produse_Favorite(
	Id_Produse_Favorite int identity primary key,
	denumire varchar(30) not null,
	pret float,
	reducere float,
	Id_Clienti int foreign key references Clienti(Id_Clienti)
);

CREATE TABLE Locatii(
	Id_Locatii int identity primary key,
	localitate varchar(30) not null,
	strada varchar(30) not null,
	numar int default 1,
	cod_postal varchar(10) not null
);

CREATE TABLE Magazine(
	Id_Magazine int identity primary key,
	denumire varchar(30) not null,
	an int default 2022,
	Id_Locatie int foreign key references Locatii(Id_Locatii)
);

CREATE TABLE Magazine_Clienti(
	Id_Magazine int foreign key references Magazine(Id_Magazine),
	Id_Clienti int foreign key references Clienti(Id_Clienti),
	data_cumparaturilor DATE not null,
	pretul_achitat float
	CONSTRAINT pk_Magazine_Clienti PRIMARY KEY (Id_Magazine, Id_Clienti)
);

---------------------------- insert values -----------------------------------


INSERT INTO  Locatii
values ('Targu Neamt', 'Corbului', 17, '645432'),
('Targu Neamt', 'Umbrei', 44, '645432'),
('Piatra Neamt', 'aefstrdy', 2, '645432');

INSERT INTO Magazine
values ('Soridor', '2001', 1),
('Geneza', '2005', 2),
('Kaufland', '2018', 3);

INSERT INTO  Clienti
values ('Varvara', 'Andrei', 'm', '2004'),
('State', 'Alexandru', 'm', '2002'),
('Murariu', 'Emlia', 'f', '5/14/2007');

INSERT INTO Produse_Favorite
values ('Paine', 2, 0, 1),
('Produs2', 17, 0, 1),
('Produs3', 2, 0, 1),
('Produs4', 2, 0, 1),
('Produs5', 2, 0, 2),
('Produs6', 2, 0, 3);

INSERT INTO Magazine_Clienti
values (1, 3, '2022', 37);

SELECT * FROM Magazine;
SELECT * FROM Clienti;
SELECT * FROM Magazine_Clienti;

GO
------------------------------------ Procedura --------------------------------------------------

CREATE OR ALTER PROCEDURE Add_Client_Magazin
	@Id_Magazin int,
	@Id_Client int,

	@data_cumparaturi DATE,
	@pret_achitat float
AS
	if EXISTS(SELECT MC.Id_Clienti from Magazine_Clienti as MC where MC.Id_Clienti = @Id_Client and MC.Id_Magazine = @Id_Magazin)
	BEGIN
		UPDATE Magazine_Clienti
		SET data_cumparaturilor = @data_cumparaturi, pretul_achitat = @pret_achitat
		where Id_Clienti = @Id_Client and Id_Magazine = @Id_Magazin;
	END
	else
	BEGIN
		INSERT INTO Magazine_Clienti
		values (@Id_Magazin, @Id_Client, @data_cumparaturi, @pret_achitat);
	END
GO

EXEC Add_Client_Magazin 1, 3, '2023', 55;

EXEC Add_Client_Magazin 3, 2, '2014', 8;
SELECT * FROM Magazine_Clienti;

GO
--------------------------------------- VIEW -----------------------------------------------

CREATE OR ALTER VIEW Afiseaza_Clienti
as
	select C.nume from Clienti as C
	INNER JOIN Produse_Favorite as P
	on C.Id_Clienti = P.Id_Clienti
	group by C.nume
	having COUNT(*) <= 3;
go

SELECT * FROM Afiseaza_Clienti;


























