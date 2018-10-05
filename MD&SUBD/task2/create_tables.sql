CREATE TABLE doctor (
    person_id       INTEGER NOT NULL,
    qualification   VARCHAR2(120) DEFAULT 'none'
);

ALTER TABLE doctor
    ADD CHECK ( qualification IN (
        'BM',
        'BMBS',
        'BmedSci',
        'MBChB',
        'none'
    ) );

ALTER TABLE doctor ADD CONSTRAINT doctor_pk PRIMARY KEY ( person_id );

CREATE TABLE medicine (
    id            INTEGER NOT NULL,
    description   CLOB,
    name          VARCHAR2(45) NOT NULL
);

ALTER TABLE medicine ADD CONSTRAINT medicine_pk PRIMARY KEY ( id );

CREATE TABLE patient (
    person_id            INTEGER NOT NULL,
    personal_doctor_id   INTEGER NOT NULL
);

ALTER TABLE patient ADD CONSTRAINT patient_pk PRIMARY KEY ( person_id );

CREATE TABLE person (
    person_id     INTEGER NOT NULL,
    first_name    VARCHAR2(45) NOT NULL,
    surname       VARCHAR2(45) NOT NULL,
    middle_name   VARCHAR2(45),
    address       VARCHAR2(120) NOT NULL,
    birth_date    DATE NOT NULL
);

ALTER TABLE person ADD CONSTRAINT person_pk PRIMARY KEY ( person_id );

ALTER TABLE person
    ADD CONSTRAINT person__un UNIQUE ( first_name,
                                       surname,
                                       middle_name,
                                       birth_date,
                                       address );

CREATE TABLE prescription (
    visit_id            INTEGER NOT NULL,
    medicine_id         INTEGER NOT NULL,
    prescription_date   DATE NOT NULL
);

ALTER TABLE prescription
    ADD CONSTRAINT prescription_pk PRIMARY KEY ( visit_id,
                                                 medicine_id,
                                                 prescription_date );

CREATE TABLE teeth (
    patient_id      INTEGER NOT NULL,
    teeth_type_id   INTEGER NOT NULL,
    teeth_number    INTEGER NOT NULL
);

ALTER TABLE teeth ADD CONSTRAINT teeth_pk PRIMARY KEY ( patient_id,
                                                        teeth_number );

CREATE TABLE teeth_type (
    id     INTEGER NOT NULL,
    type   VARCHAR2(48) NOT NULL
);

ALTER TABLE teeth_type ADD CONSTRAINT teeth_type_pk PRIMARY KEY ( id );

CREATE TABLE visit (
    id               INTEGER NOT NULL,
    visit_datetime   DATE NOT NULL,
    description      CLOB,
    cost             NUMBER(2) NOT NULL,
    patient_id       INTEGER NOT NULL,
    doctor_id        INTEGER,
    card_number      VARCHAR2(45) DEFAULT '0'
);

ALTER TABLE visit ADD CONSTRAINT visit_pk PRIMARY KEY ( id );

ALTER TABLE doctor
    ADD CONSTRAINT doctor_person_fk FOREIGN KEY ( person_id )
        REFERENCES person ( person_id )
            ON DELETE CASCADE;

ALTER TABLE patient
    ADD CONSTRAINT patient_doctor_fk FOREIGN KEY ( personal_doctor_id )
        REFERENCES doctor ( person_id );

ALTER TABLE patient
    ADD CONSTRAINT patient_person_fk FOREIGN KEY ( person_id )
        REFERENCES person ( person_id )
            ON DELETE CASCADE;

ALTER TABLE prescription
    ADD CONSTRAINT prescription_medicine_fk FOREIGN KEY ( medicine_id )
        REFERENCES medicine ( id )
            ON DELETE CASCADE;

ALTER TABLE prescription
    ADD CONSTRAINT prescription_visit_fk FOREIGN KEY ( visit_id )
        REFERENCES visit ( id )
            ON DELETE CASCADE;

ALTER TABLE teeth
    ADD CONSTRAINT teeth_patient_fk FOREIGN KEY ( patient_id )
        REFERENCES patient ( person_id )
            ON DELETE CASCADE;

ALTER TABLE teeth
    ADD CONSTRAINT teeth_teeth_type_fk FOREIGN KEY ( teeth_type_id )
        REFERENCES teeth_type ( id )
            ON DELETE CASCADE;

ALTER TABLE visit
    ADD CONSTRAINT visit_doctor_fk FOREIGN KEY ( doctor_id )
        REFERENCES doctor ( person_id )
            ON DELETE CASCADE;

ALTER TABLE visit
    ADD CONSTRAINT visit_patient_fk FOREIGN KEY ( patient_id )
        REFERENCES patient ( person_id )
            ON DELETE CASCADE;

CREATE SEQUENCE medicine_sequence START WITH 1 MAXVALUE 1000 NOCACHE ORDER;

CREATE OR REPLACE TRIGGER medicine_id_trg BEFORE
    INSERT ON medicine
    FOR EACH ROW
    WHEN ( new.id IS NULL )
BEGIN
    :new.id := medicine_sequence.nextval;
END;
/