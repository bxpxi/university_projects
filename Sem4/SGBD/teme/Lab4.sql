CREATE TABLE IstoricTranzactii(
	ID INT PRIMARY KEY IDENTITY(1,1),
	actiune VARCHAR(50),
	data_executiei DATETIME,
	mesaj VARCHAR(50)
)

SELECT * FROM IstoricTranzactii;
SELECT * FROM Roluri;

-- Dirty reads
-- T1
BEGIN TRANSACTION
UPDATE Roluri SET salariu=7200 WHERE rol='Asistent'
WAITFOR DELAY '00:00:05'
ROLLBACK TRANSACTION
INSERT INTO IstoricTranzactii(actiune, data_executiei, mesaj) VALUES('Dirty reads ROLLBACK', CURRENT_TIMESTAMP, 'Rollback successfully')

-- T2 gresit
SET TRANSACTION ISOLATION LEVEL READ UNCOMMITTED
BEGIN TRANSACTION
SELECT * FROM Roluri
INSERT INTO IstoricTranzactii(actiune, data_executiei, mesaj) VALUES('SELECT Roluri', CURRENT_TIMESTAMP, 'SELECT * FROM Roluri (dupa update)')
WAITFOR DELAY '00:00:10'
SELECT * FROM Roluri
INSERT INTO IstoricTranzactii(actiune, data_executiei, mesaj) VALUES('SELECT Roluri', CURRENT_TIMESTAMP, 'SELECT * FROM Roluri (dupa rollback)')
COMMIT TRANSACTION

-- T2 solutie - setez nivelul de izolare la READ COMMITTED
SET TRANSACTION ISOLATION LEVEL READ COMMITTED
BEGIN TRANSACTION
SELECT * FROM Roluri
INSERT INTO IstoricTranzactii(actiune, data_executiei, mesaj) VALUES('SELECT Roluri', CURRENT_TIMESTAMP, 'SELECT * FROM Roluri (dupa update)')
WAITFOR DELAY '00:00:10'
SELECT * FROM Roluri
INSERT INTO IstoricTranzactii(actiune, data_executiei, mesaj) VALUES('SELECT Roluri', CURRENT_TIMESTAMP, 'SELECT * FROM Roluri (dupa rollback)')
COMMIT TRANSACTION

-- Unrepeadable reads
-- T1 gresit
SET TRANSACTION ISOLATION LEVEL READ COMMITTED
BEGIN TRANSACTION
SELECT * FROM Roluri
WAITFOR DELAY '00:00:06'
SELECT * FROM Roluri
COMMIT TRANSACTION

-- T1 solutie - schimb nivelul de izolare la REPEATABLE READ
SET TRANSACTION ISOLATION LEVEL REPEATABLE READ
BEGIN TRANSACTION
SELECT * FROM Roluri
WAITFOR DELAY '00:00:06'
SELECT * FROM Roluri
COMMIT TRANSACTION

-- T2
BEGIN TRANSACTION
WAITFOR DELAY '00:00:03'
UPDATE Roluri SET salariu=7000 WHERE rol='Asistent'
INSERT INTO IstoricTranzactii(actiune, data_executiei, mesaj) VALUES('Asistent updated', CURRENT_TIMESTAMP, 'Delay for Asistent update')
COMMIT TRANSACTION
INSERT INTO IstoricTranzactii(actiune, data_executiei, mesaj) VALUES('Asistent updated', CURRENT_TIMESTAMP, 'Update rollback ended')

-- Phantom reads
-- T1 gresit
SET TRANSACTION ISOLATION LEVEL REPEATABLE READ
BEGIN TRANSACTION
SELECT * FROM Angajati WHERE id BETWEEN 1 AND 100
WAITFOR DELAY '00:00:07'
SELECT * FROM Angajati WHERE id BETWEEN 1 AND 100
COMMIT TRANSACTION

-- T1 solutie - schimb nivelul de izolare la SERIALIZABLE
SET TRANSACTION ISOLATION LEVEL SERIALIZABLE
BEGIN TRANSACTION
SELECT * FROM Angajati WHERE id BETWEEN 1 AND 100;
WAITFOR DELAY '00:00:07'
SELECT * FROM Angajati WHERE id BETWEEN 1 AND 100;
COMMIT TRANSACTION
INSERT INTO IstoricTranzactii(actiune, data_executiei, mesaj) VALUES('Phantom reads', CURRENT_TIMESTAMP, 'PR succeded')

-- T2
BEGIN TRANSACTION
INSERT INTO IstoricTranzactii(actiune, data_executiei, mesaj) VALUES('PR Insert', CURRENT_TIMESTAMP, 'Delay for insert started')
WAITFOR DELAY '00:00:05'
INSERT INTO Angajati(nume, prenume, rol) VALUES ('A', 'A', 1);
INSERT INTO IstoricTranzactii(actiune, data_executiei, mesaj) VALUES('PR Insert', CURRENT_TIMESTAMP, 'Inserted')
COMMIT TRANSACTION
INSERT INTO IstoricTranzactii(actiune, data_executiei, mesaj) VALUES('PR Insert', CURRENT_TIMESTAMP, 'Insert rollback ended')

-- Deadlock
-- T1
SET TRANSACTION ISOLATION LEVEL SERIALIZABLE;
BEGIN TRAN;
UPDATE Roluri SET salariu=7300 WHERE rol='Asistent';
WAITFOR DELAY '00:00:05';
UPDATE Angajati SET nume='B' WHERE prenume='A';
COMMIT TRAN;
INSERT INTO IstoricTranzactii(actiune,data_executiei,mesaj) VALUES ('Deadlock', CURRENT_TIMESTAMP, 'First transaction - victim')


-- T2 gresit
SET TRANSACTION ISOLATION LEVEL SERIALIZABLE;
BEGIN TRAN;
UPDATE Angajati SET nume='C' WHERE prenume='A';
WAITFOR DELAY '00:00:05';
UPDATE Roluri SET salariu=7000 WHERE rol='Asistent';
COMMIT TRAN;
INSERT INTO IstoricTranzactii(actiune,data_executiei,mesaj) VALUES('Deadlock', CURRENT_TIMESTAMP, 'Second transaction - succeeded')


-- T2 solutie
SET DEADLOCK_PRIORITY HIGH;
BEGIN TRANSACTION;
UPDATE Angajati SET nume='C' WHERE prenume='A';
WAITFOR DELAY '00:00:05';
UPDATE Roluri SET salariu=7000 WHERE rol='Asistent';
COMMIT TRAN;
INSERT INTO IstoricTranzactii(actiune,data_executiei,mesaj) VALUES('Deadlock', CURRENT_TIMESTAMP, 'Second transaction - succeeded')

SELECT * FROM Roluri
SELECT * FROM Angajati
SELECT * FROM IstoricTranzactii



-- C# procedures deadlock
GO
CREATE OR ALTER PROCEDURE run_thread1
AS
    BEGIN
        BEGIN TRANSACTION
        UPDATE Roluri SET salariu=5100 WHERE rol='Receptioner';
        WAITFOR DELAY '00:00:10'
        UPDATE Angajati SET nume = nume + ' THR1' WHERE nume='Istrate';
        COMMIT TRANSACTION
    END

GO
CREATE OR ALTER PROCEDURE run_thread2
AS
    BEGIN
		SET DEADLOCK_PRIORITY HIGH
		-- SET DEADLOCK_PRIORITY LOW
        BEGIN TRANSACTION
        UPDATE Roluri SET salariu=5100 WHERE rol='Receptioner';
        WAITFOR DELAY '00:00:10'
        UPDATE Angajati SET nume = nume + ' THR2' WHERE nume='Istrate';
        COMMIT TRANSACTION
    END

