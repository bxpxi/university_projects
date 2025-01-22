CREATE DATABASE CiocolataTorturi
GO
USE CiocolataTorturi

CREATE TABLE TipCiocolata(
	tcid INT PRIMARY KEY IDENTITY(1,1),
	denumire VARCHAR(50),
	descriere VARCHAR(50),
	valoare_nutritionala VARCHAR(50)
);

CREATE TABLE Ciocolata(
	cid INT PRIMARY KEY IDENTITY(1,1),
	denumire VARCHAR(50),
	gramaj INT,
	pret INT,
	cantitate INT,
	tcid INT FOREIGN KEY REFERENCES TipCiocolata(tcid)
);

CREATE TABLE TipTort(
	ttid INT PRIMARY KEY IDENTITY(1,1),
	denumire VARCHAR(50),
	prezentare VARCHAR(50)
);

CREATE TABLE Tort(
	tid INT PRIMARY KEY IDENTITY(1,1),
	denumire VARCHAR(50),
	gramaj INT,
	pret INT,
	ttid INT FOREIGN KEY REFERENCES TipTort(ttid)
);

CREATE TABLE TortCiocolata(
	tid INT,
	cid INT,
	gramaj INT,
	data_realizare DATE,
	CONSTRAINT fk_id_tort FOREIGN KEY(tid) REFERENCES Tort(tid),
	CONSTRAINT fk_id_ciocolata FOREIGN KEY(cid) REFERENCES Ciocolata(cid),
	CONSTRAINT pk_tort_ciocolata PRIMARY KEY(tid,cid)
);

INSERT INTO TipCiocolata(denumire,descriere,valoare_nutritionala) VALUES 
('Ciocolata neagra','Ciocolata neagra 90% cacao','350kcal'),
('Ciocolata cu lapte','Ciocolata cu lapte 60% cacao','400kcal'),
('Ciocolata cu alune','Ciocolata cu alune 50% cacao','450kcal');
SELECT * FROM TipCiocolata;

INSERT INTO Ciocolata(denumire,gramaj,pret,cantitate,tcid) VALUES
('Ciocolata1',200,12,50,1),
('Ciocolata2',300,15,100,2),
('Ciocolata3',250,10,80,3);
SELECT * FROM Ciocolata;

INSERT INTO TipTort(denumire,prezentare) VALUES
('Tort cu frisca si ciocolata', 'Prezentare1'),
('Tort cu fructe si ciocolata', 'Prezentare2'),
('Tort doar cu ciocolata', 'Prezentare3');
SELECT * FROM TipTort;

INSERT INTO Tort(denumire,gramaj,pret,ttid) VALUES
('Tort1',1000,140,1),
('Tort2',2000,300,2),
('Tort3',1500,200,3);
SELECT * FROM Tort;

INSERT INTO TortCiocolata(tid,cid,gramaj,data_realizare) VALUES
(1,1,300,'2025-01-10'),
(2,2,400,'2025-01-11'),
(3,3,450,'2025-01-12');
SELECT * FROM TortCiocolata;

GO
CREATE PROCEDURE Adauga_Ciocolata_Tort @tid INT,@cid INT,@gramaj INT,@data_realizare DATE
AS
BEGIN
	IF(EXISTS(SELECT * FROM TortCiocolata WHERE tid=@tid AND cid=@cid))
	BEGIN
		UPDATE TortCiocolata
		SET gramaj=@gramaj, data_realizare=@data_realizare
		WHERE tid=@tid AND cid=@cid;
	END;
	ELSE
	BEGIN
		INSERT INTO TortCiocolata(tid,cid,gramaj,data_realizare) VALUES
		(@tid,@cid,@gramaj,@data_realizare);
	END;
END;


SELECT * FROM TortCiocolata;
EXEC Adauga_Ciocolata_Tort 1,1,350,'2025-01-13';
EXEC Adauga_Ciocolata_Tort 1,2,200,'2025-01-12';
EXEC Adauga_Ciocolata_Tort 1,3,100,'2025-01-12';

GO

CREATE VIEW Torturi_Toate_Ciocolate
AS
SELECT t.denumire
FROM TortCiocolata tc
INNER JOIN Tort t ON tc.tid=t.tid
GROUP BY t.tid,t.denumire
HAVING COUNT(*) = (SELECT COUNT(*) FROM Ciocolata);

GO

SELECT * FROM Torturi_Toate_Ciocolate;

