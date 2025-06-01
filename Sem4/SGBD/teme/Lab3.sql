USE ClinicaMedicala;

GO

CREATE OR ALTER FUNCTION validareServiciuMedical
(@denumire VARCHAR(40), @detalii VARCHAR(250), @cost DECIMAL(10,2))
RETURNS VARCHAR(100)
AS
BEGIN
	DECLARE @mesaj VARCHAR(100)
	SET @mesaj = ''

	IF(@denumire = '')
		SET @mesaj += 'Denumirea serviciului nu a fost completata.'

	IF(@detalii = '')
		SET @mesaj += 'Detaliile serviciului nu au fost completate.'

	IF(@cost < 0.00)
		SET @mesaj += 'Costul nu poate fi negativ.'

	RETURN @mesaj
END

GO

CREATE OR ALTER FUNCTION validarePacient
(@nume VARCHAR(40), @prenume VARCHAR(40), @cnp VARCHAR(13), @data_nasterii DATE, @gen VARCHAR(1), @adresa VARCHAR(60), @telefon VARCHAR(15), @email VARCHAR(40))
RETURNS VARCHAR(100)
AS
BEGIN
	DECLARE @mesaj VARCHAR(100)
	SET @mesaj = ''

	IF(@nume = '')
		SET @mesaj += 'Numele nu poate fi necompletat.'

	IF(@prenume = '')
		SET @mesaj += 'Preumele nu poate fi necompletat.'

	IF(LEN(@cnp) <> 13)
		SET @mesaj += 'CNP invalid.'

	IF(@data_nasterii > GETDATE())
		SET @mesaj += 'Data nasterii invalida.'

	IF(@gen NOT IN ('F','M'))
		SET @mesaj += 'Gen invalid.'

	IF(@adresa = '')
		SET @mesaj += 'Adresa nu poate fi necompletata.'

	IF(@telefon = '')
		SET @mesaj += 'Telefonul nu poate fi necompletat.'

	IF(@email = '')
		SET @mesaj += 'Emailul nu poate fi necompletat.'

	RETURN @mesaj
END

GO

CREATE TABLE IstoricLogare
(
	id INT PRIMARY KEY IDENTITY(1,1),
	actiune VARCHAR(30),
	tabel VARCHAR(30),
	data_executiei DATETIME
)

GO

CREATE OR ALTER PROCEDURE AddPacientServiciu @denumire VARCHAR(40), @detalii VARCHAR(250), @cost DECIMAL(10,2), @nume VARCHAR(40), @prenume VARCHAR(40), @cnp VARCHAR(13), @data_nasterii DATE, @gen VARCHAR(1), @adresa VARCHAR(60), @telefon VARCHAR(15), @email VARCHAR(40)
AS
BEGIN
	BEGIN TRAN
	BEGIN TRY

		DECLARE @mesaj VARCHAR(100) = '';

		DECLARE @mesaj_serviciu VARCHAR(100) = dbo.validareServiciuMedical(@denumire, @detalii, @cost);
		IF (@mesaj_serviciu <> '')
			SET @mesaj += @mesaj_serviciu + CHAR(13) + CHAR(10);

		DECLARE @mesaj_pacient VARCHAR(100) = dbo.validarePacient(@nume, @prenume, @cnp, @data_nasterii, @gen, @adresa, @telefon, @email);
		IF (@mesaj_pacient <> '')
			SET @mesaj += @mesaj_pacient + CHAR(13) + CHAR(10);

		IF (@mesaj <> '')
		BEGIN
			RAISERROR(@mesaj, 14, 1);
		END


		DECLARE @idServiciu INT
		DECLARE @idPacient INT

		INSERT INTO ServiciiMedicale(Denumire, Detalii, Cost) VALUES(@denumire, @detalii, @cost)
		SET @idServiciu = SCOPE_IDENTITY()
		INSERT INTO IstoricLogare(actiune, tabel, data_executiei) VALUES ('Insert', 'ServiciiMedicale', CURRENT_TIMESTAMP)
		
		INSERT INTO Pacienti(Nume, Prenume, CNP, Data_nasterii, Gen, Adresa, Telefon, Email) VALUES(@nume, @prenume, @cnp, @data_nasterii, @gen, @adresa, @telefon, @email)
		SET @idPacient = SCOPE_IDENTITY()
		INSERT INTO IstoricLogare(actiune, tabel, data_executiei) VALUES ('Insert', 'Pacienti', CURRENT_TIMESTAMP)

		INSERT INTO PacientServiciu(ID_pacient, ID_serviciu, Data_serviciu) VALUES (@idPacient, @idServiciu, GETDATE())
		INSERT INTO IstoricLogare(actiune, tabel, data_executiei) VALUES ('Insert', 'PacientServiciu', CURRENT_TIMESTAMP)

		COMMIT TRAN
		SELECT 'Transaction committed'
	END TRY
	BEGIN CATCH
		ROLLBACK TRAN
		SELECT 'Transaction rollbacked'
	END CATCH
END

SELECT * FROM Pacienti
SELECT * FROM ServiciiMedicale
SELECT * FROM PacientServiciu
SELECT * FROM IstoricLogare

-- corect
EXEC AddPacientServiciu 'Analize sange', 'Examinare monstre de sange', 100.00, 'Costea', 'Cornelia', '6970212066789','1997-02-12', 'F', 'Str. George Enescu, nr. 67', '0771897456', '@costea.cornelia@gmail.com'

-- gresite
EXEC AddPacientServiciu '', 'Examinare monstre de sange', 100.00, 'Costea', 'Cornelia', '6970212066789','1997-02-12', 'F', 'Str. George Enescu, nr. 67', '0771897456', '@costea.cornelia@gmail.com'
EXEC AddPacientServiciu 'Analize sange', '', 100.00, 'Costea', 'Cornelia', '6970212066789','1997-02-12', 'F', 'Str. George Enescu, nr. 67', '0771897456', '@costea.cornelia@gmail.com'
EXEC AddPacientServiciu 'Analize sange', 'Examinare monstre de sange', -100.00, 'Costea', 'Cornelia', '6970212066789','1997-02-12', 'F', 'Str. George Enescu, nr. 67', '0771897456', '@costea.cornelia@gmail.com'
EXEC AddPacientServiciu 'Analize sange', 'Examinare monstre de sange', 100.00, '', 'Cornelia', '6970212066789','1997-02-12', 'F', 'Str. George Enescu, nr. 67', '0771897456', '@costea.cornelia@gmail.com'
EXEC AddPacientServiciu 'Analize sange', 'Examinare monstre de sange', 100.00, 'Costea', '', '6970212066789','1997-02-12', 'F', 'Str. George Enescu, nr. 67', '0771897456', '@costea.cornelia@gmail.com'
EXEC AddPacientServiciu 'Analize sange', 'Examinare monstre de sange', 100.00, 'Costea', 'Cornelia', '6970212066789123456','1997-02-12', 'F', 'Str. George Enescu, nr. 67', '0771897456', '@costea.cornelia@gmail.com'
EXEC AddPacientServiciu 'Analize sange', 'Examinare monstre de sange', 100.00, 'Costea', 'Cornelia', '6970212066789','2025-10-10', 'F', 'Str. George Enescu, nr. 67', '0771897456', '@costea.cornelia@gmail.com'
EXEC AddPacientServiciu 'Analize sange', 'Examinare monstre de sange', 100.00, 'Costea', 'Cornelia', '6970212066789','1997-02-12', 'abcd', 'Str. George Enescu, nr. 67', '0771897456', '@costea.cornelia@gmail.com'
EXEC AddPacientServiciu 'Analize sange', 'Examinare monstre de sange', 100.00, 'Costea', 'Cornelia', '6970212066789','1997-02-12', 'F', '', '0771897456', '@costea.cornelia@gmail.com'
EXEC AddPacientServiciu 'Analize sange', 'Examinare monstre de sange', 100.00, 'Costea', 'Cornelia', '6970212066789','1997-02-12', 'F', 'Str. George Enescu, nr. 67', '', '@costea.cornelia@gmail.com'
EXEC AddPacientServiciu 'Analize sange', 'Examinare monstre de sange', 100.00, 'Costea', 'Cornelia', '6970212066789','1997-02-12', 'F', 'Str. George Enescu, nr. 67', '0771897456', ''

GO

CREATE OR ALTER PROCEDURE AddPacientServiciu2 @denumire VARCHAR(40), @detalii VARCHAR(250), @cost DECIMAL(10,2), @nume VARCHAR(40), @prenume VARCHAR(40), @cnp VARCHAR(13), @data_nasterii DATE, @gen VARCHAR(1), @adresa VARCHAR(60), @telefon VARCHAR(15), @email VARCHAR(40)
AS
BEGIN
	DECLARE @inserareServicii INT
	SET @inserareServicii = 0

	BEGIN TRAN
	BEGIN TRY
		DECLARE @mesaj_serviciu VARCHAR(100) = dbo.validareServiciuMedical(@denumire, @detalii, @cost);
		IF (@mesaj_serviciu <> '')
		BEGIN
			RAISERROR(@mesaj_serviciu, 14, 1)
		END
		DECLARE @idServiciu INT

		INSERT INTO ServiciiMedicale(Denumire, Detalii, Cost) VALUES(@denumire, @detalii, @cost)
		SET @idServiciu = SCOPE_IDENTITY()
		INSERT INTO IstoricLogare(actiune, tabel, data_executiei) VALUES ('Insert', 'ServiciiMedicale', CURRENT_TIMESTAMP)
		
		COMMIT TRAN
		SELECT 'Transaction ServiciiMedicale commited'
		SET @inserareServicii = @idServiciu
	END TRY
	BEGIN CATCH
		ROLLBACK TRAN
		SELECT 'Transaction ServiciiMedicale rollbacked'
		INSERT INTO IstoricLogare(actiune, tabel, data_executiei) VALUES ('Rollback', 'ServiciiMedicale', CURRENT_TIMESTAMP)
	END CATCH

	DECLARE @inserarePacient INT
	SET @inserarePacient = 0

	BEGIN TRAN
	BEGIN TRY
		DECLARE @mesaj_pacient VARCHAR(100) = dbo.validarePacient(@nume, @prenume, @cnp, @data_nasterii, @gen, @adresa, @telefon, @email);
		IF (@mesaj_pacient <> '')
		BEGIN
			RAISERROR(@mesaj_pacient, 14, 1)
		END
		DECLARE @idPacient INT

		INSERT INTO Pacienti(Nume, Prenume, CNP, Data_nasterii, Gen, Adresa, Telefon, Email) VALUES(@nume, @prenume, @cnp, @data_nasterii, @gen, @adresa, @telefon, @email)
		SET @idPacient = SCOPE_IDENTITY()
		INSERT INTO IstoricLogare(actiune, tabel, data_executiei) VALUES ('Insert', 'Pacienti', CURRENT_TIMESTAMP)

		COMMIT TRAN
		SELECT 'Transaction Pacienti committed'
		SET @inserarePacient = @idPacient
	END TRY
	BEGIN CATCH
		ROLLBACK TRAN
		SELECT 'Transaction Pacienti rollbacked'
		INSERT INTO IstoricLogare(actiune, tabel, data_executiei) VALUES ('Rollback', 'Pacienti', CURRENT_TIMESTAMP)
	END CATCH

	BEGIN TRAN
	BEGIN TRY
		IF(@inserarePacient = 0 OR @inserareServicii = 0)
		BEGIN
			RAISERROR(@mesaj_pacient, 14, 1)
		END

		INSERT INTO PacientServiciu(ID_pacient, ID_serviciu, Data_serviciu) VALUES (@idPacient, @idServiciu, GETDATE())
		INSERT INTO IstoricLogare(actiune, tabel, data_executiei) VALUES ('Insert', 'PacientServiciu', CURRENT_TIMESTAMP)

		COMMIT TRAN
		SELECT 'Transaction PacientServiciu committed'
	END TRY
	BEGIN CATCH
		ROLLBACK TRAN
		SELECT 'Transaction PacientServiciu rollbacked'
		INSERT INTO IstoricLogare(actiune, tabel, data_executiei) VALUES ('Rollback', 'PacientServiciu', CURRENT_TIMESTAMP)
	END CATCH
END

SELECT * FROM Pacienti
SELECT * FROM ServiciiMedicale
SELECT * FROM PacientServiciu

-- corect
EXEC AddPacientServiciu2 'Analize sange', 'Examinare monstre de sange', 100.00, 'Costea', 'Cornelia', '6970212066789','1997-02-12', 'F', 'Str. George Enescu, nr. 67', '0771897456', '@costea.cornelia@gmail.com'

-- gresite
EXEC AddPacientServiciu2 '', 'Examinare monstre de sange', 100.00, 'Costea', 'Cornelia', '6970212066789','1997-02-12', 'F', 'Str. George Enescu, nr. 67', '0771897456', '@costea.cornelia@gmail.com'
EXEC AddPacientServiciu2 'Analize sange', '', 100.00, 'Costea', 'Cornelia', '6970212066789','1997-02-12', 'F', 'Str. George Enescu, nr. 67', '0771897456', '@costea.cornelia@gmail.com'
EXEC AddPacientServiciu2 'Analize sange', 'Examinare monstre de sange', -100.00, 'Costea', 'Cornelia', '6970212066789','1997-02-12', 'F', 'Str. George Enescu, nr. 67', '0771897456', '@costea.cornelia@gmail.com'
EXEC AddPacientServiciu2 'Analize sange', 'Examinare monstre de sange', 100.00, '', 'Cornelia', '6970212066789','1997-02-12', 'F', 'Str. George Enescu, nr. 67', '0771897456', '@costea.cornelia@gmail.com'
EXEC AddPacientServiciu2 'Analize sange', 'Examinare monstre de sange', 100.00, 'Costea', '', '6970212066789','1997-02-12', 'F', 'Str. George Enescu, nr. 67', '0771897456', '@costea.cornelia@gmail.com'
EXEC AddPacientServiciu2 'Analize sange', 'Examinare monstre de sange', 100.00, 'Costea', 'Cornelia', '6970212066789123456','1997-02-12', 'F', 'Str. George Enescu, nr. 67', '0771897456', '@costea.cornelia@gmail.com'
EXEC AddPacientServiciu2 'Analize sange', 'Examinare monstre de sange', 100.00, 'Costea', 'Cornelia', '6970212066789','2025-10-10', 'F', 'Str. George Enescu, nr. 67', '0771897456', '@costea.cornelia@gmail.com'
EXEC AddPacientServiciu2 'Analize sange', 'Examinare monstre de sange', 100.00, 'Costea', 'Cornelia', '6970212066789','1997-02-12', 'abcd', 'Str. George Enescu, nr. 67', '0771897456', '@costea.cornelia@gmail.com'
EXEC AddPacientServiciu2 'Analize sange', 'Examinare monstre de sange', 100.00, 'Costea', 'Cornelia', '6970212066789','1997-02-12', 'F', '', '0771897456', '@costea.cornelia@gmail.com'
EXEC AddPacientServiciu2 'Analize sange', 'Examinare monstre de sange', 100.00, 'Costea', 'Cornelia', '6970212066789','1997-02-12', 'F', 'Str. George Enescu, nr. 67', '', '@costea.cornelia@gmail.com'
EXEC AddPacientServiciu2 'Analize sange', 'Examinare monstre de sange', 100.00, 'Costea', 'Cornelia', '6970212066789','1997-02-12', 'F', 'Str. George Enescu, nr. 67', '0771897456', ''

