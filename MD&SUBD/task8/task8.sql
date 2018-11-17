CREATE OR REPLACE TRIGGER on_teeth_update
    BEFORE UPDATE ON teeth
    FOR EACH row
BEGIN
    IF :NEW.teeth_type_id = 1 AND :OLD.teeth_type_id != 1 THEN
        Raise_Application_Error(-20100, 'You can not set baby teeth');
    END IF;

    IF :NEW.teeth_type_id = 2 AND :OLD.teeth_type_id > 2 THEN
        Raise_Application_Error(-20101, 'You can not set permanent teeth when it already artificial, absent or have dental crown');
    END IF;

    IF :NEW.teeth_type_id = 4 AND :OLD.teeth_type_id = 5 THEN
        Raise_Application_Error(-20102, 'You can not change absent teeth to dental crown');
    END IF;
END on_teeth_update;
