-- CREATE DOMAIN
CREATE DOMAIN percentage AS integer NOT NULL DEFAULT 0 CHECK(VALUE IN(0, 5, 10, 15, 20, 25));

CREATE DOMAIN auto_type AS char(1) NOT NULL DEFAULT 'o' CHECK(VALUE IN('o', 'c', 'a', 'm'));

CREATE DOMAIN price_type AS numeric(10, 2) CHECK(VALUE > 0);

CREATE DOMAIN registration AS text NOT NULL CHECK(VALUE ~ '(^[A-Z][A-Z] [A-Z0-9][A-Z0-9][A-Z0-9][A-Z0-9][A-Z0-9]$)|(^[A-Z][A-Z][A-Z] [A-Z0-9][A-Z0-9][A-Z0-9][A-Z0-9][A-Z0-9]?$)');

CREATE DOMAIN phone AS integer CHECK(100000000 <= VALUE AND VALUE <= 999999999);

-- CREATE TABLE
CREATE TABLE clients (id serial PRIMARY KEY, imie text, nazwisko text, telefon phone, firma text DEFAULT NULL, rabat percentage);

CREATE TABLE cars (model text PRIMARY KEY, marka text NOT NULL, typ auto_type, waga double precision CHECK(waga > 0));

CREATE TABLE uslugi (nazwa text PRIMARY KEY, cena price_type);

CREATE TABLE zlecenia (id serial PRIMARY KEY, data_zlec timestamp DEFAULT now(), data_real timestamp DEFAULT NULL, nr_rej registration, faktura boolean DEFAULT FALSE, koszt price_type, kli_id integer, sam_model text);

CREATE TABLE carparts (id serial PRIMARY KEY, producent text, ilosc integer CHECK(ilosc >= 0), typ text, uniw boolean DEFAULT TRUE);

CREATE TABLE zamowienia (id serial PRIMARY KEY, data_zamow timestamp DEFAULT now(), data_real timestamp DEFAULT NULL, firma text, ilosc integer CHECK(ilosc > 0), cena price_type, cze_id integer);

CREATE TABLE zleusl (zle_id integer, usl_nazwa text);

CREATE TABLE czesam (cze_id integer, sam_model text);

CREATE TABLE czeusl (cze_id integer, usl_nazwa text);

-- ALTER TABLE ADD CONSTRAINT FOREIGN KEY
ALTER TABLE zlecenia ADD CONSTRAINT fk_zle_kli FOREIGN KEY (kli_id) REFERENCES clients(id) ON DELETE SET NULL DEFERRABLE;
ALTER TABLE zlecenia ADD CONSTRAINT fk_zle_sam FOREIGN KEY (sam_model) REFERENCES cars(model) ON DELETE SET NULL DEFERRABLE;

ALTER TABLE zamowienia ADD CONSTRAINT fk_zam_cze FOREIGN KEY (cze_id) REFERENCES carparts(id) ON DELETE SET NULL DEFERRABLE;

ALTER TABLE zleusl ADD CONSTRAINT fk_zleusl_zle FOREIGN KEY (zle_id) REFERENCES zlecenia(id) ON DELETE CASCADE DEFERRABLE;
ALTER TABLE zleusl ADD CONSTRAINT fk_zleusl_usl FOREIGN KEY (usl_nazwa) REFERENCES uslugi(nazwa) ON DELETE SET NULL DEFERRABLE;

ALTER TABLE czesam ADD CONSTRAINT fk_czesam_cze FOREIGN KEY (cze_id) REFERENCES carparts(id) ON DELETE CASCADE DEFERRABLE;
ALTER TABLE czesam ADD CONSTRAINT fk_czesam_sam FOREIGN KEY (sam_model) REFERENCES cars(model) ON DELETE CASCADE DEFERRABLE;

ALTER TABLE czeusl ADD CONSTRAINT fk_czeusl_cze FOREIGN KEY (cze_id) REFERENCES carparts(id) ON DELETE CASCADE DEFERRABLE;
ALTER TABLE czeusl ADD CONSTRAINT fk_czeusl_usl FOREIGN KEY (usl_nazwa) REFERENCES uslugi(nazwa) ON DELETE CASCADE DEFERRABLE;

-- CREATE ROLE / GRANT
CREATE ROLE sprzedawca;
CREATE ROLE mechanik;
CREATE ROLE magazynier;

GRANT SELECT ON uslugi, cars TO sprzedawca;
GRANT SELECT, INSERT, UPDATE ON clients, zlecenia, zleusl TO sprzedawca;

GRANT SELECT ON zlecenia, cars, uslugi TO mechanik;
GRANT SELECT, INSERT, UPDATE ON carparts, czesam, czeusl TO mechanik;
GRANT UPDATE(data_real) ON zlecenia TO mechanik;

GRANT SELECT ON carparts TO magazynier;
GRANT SELECT, INSERT, UPDATE ON zamowienia TO magazynier;

GRANT ALL ON ALL SEQUENCES IN SCHEMA public TO sprzedawca, magazynier, mechanik;

-- CREATE OR REPLACE RULE / CREATE OR REPLACE FUNCTION / CREATE TRIGGER
CREATE OR REPLACE RULE czesam_rule AS ON INSERT TO czesam DO ALSO UPDATE carparts SET uniw = FALSE WHERE carparts.id = NEW.cze_id;

CREATE OR REPLACE FUNCTION zleusl_trg_func() RETURNS TRIGGER AS $f$
BEGIN
    WITH tab AS (SELECT zlecenia.id, sum(uslugi.cena) FROM zlecenia JOIN zleusl ON zleusl.zle_id = zlecenia.id JOIN uslugi ON zleusl.usl_nazwa = uslugi.nazwa GROUP BY zlecenia.id HAVING zlecenia.id = NEW.zle_id) UPDATE zlecenia SET koszt = tab.sum FROM tab WHERE zlecenia.id = tab.id;
    RETURN NULL;
END;
$f$ LANGUAGE plpgsql;
CREATE TRIGGER zleusl_trg AFTER INSERT OR UPDATE ON zleusl FOR EACH ROW EXECUTE PROCEDURE zleusl_trg_func();

CREATE OR REPLACE FUNCTION zam_trg_func() RETURNS TRIGGER AS $f$
BEGIN
    IF OLD.data_real IS NULL AND NEW.data_real IS NOT NULL
    THEN
        UPDATE carparts SET ilosc = ilosc + NEW.ilosc WHERE id = NEW.cze_id;
    ELSIF OLD.ilosc <> NEW.ilosc
    THEN
        UPDATE carparts SET ilosc = ilosc - .ilosc + NEW.ilosc WHERE id = NEW.cze_id;
    END IF;
    RETURN NULL;
END;
$f$ LANGUAGE plpgsql;
CREATE TRIGGER zam_trg AFTER UPDATE ON zamowienia FOR EACH ROW EXECUTE PROCEDURE zam_trg_func();

