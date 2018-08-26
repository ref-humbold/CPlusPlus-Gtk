/* TWORZENIE DZIEDZIN */
CREATE DOMAIN procent AS integer NOT NULL DEFAULT 0 CHECK(VALUE IN(0, 5, 10, 15, 20, 25));

CREATE DOMAIN typauto AS char(1) NOT NULL DEFAULT 'o' CHECK(VALUE IN('o', 'c', 'a', 'm'));

CREATE DOMAIN typcena AS numeric(10, 2) CHECK(VALUE > 0);

CREATE DOMAIN rejestr AS text NOT NULL CHECK(VALUE ~ '(^[A-Z][A-Z]:[A-Z0-9][A-Z0-9][A-Z0-9][A-Z0-9][A-Z0-9]$)|(^[A-Z][A-Z][A-Z]:[A-Z0-9][A-Z0-9][A-Z0-9][A-Z0-9]?$)');

CREATE DOMAIN nrtel AS integer CHECK(100000000 <= VALUE AND VALUE <= 999999999);

/* TWORZENE TABEL */
CREATE TABLE clients (id serial PRIMARY KEY, imie text, nazwisko text, telefon nrtel, firma text DEFAULT NULL, rabat procent);

CREATE TABLE samochody (model text PRIMARY KEY, marka text NOT NULL, typ typauto, waga double precision CHECK(waga > 0));

CREATE TABLE uslugi (nazwa text PRIMARY KEY, cena typcena);

CREATE TABLE zlecenia (id serial PRIMARY KEY, data_zlec timestamp DEFAULT now(), data_real timestamp DEFAULT NULL, nr_rej rejestr, faktura boolean DEFAULT FALSE, koszt typcena, kli_id integer, sam_model text);

CREATE TABLE czesci (id serial PRIMARY KEY, producent text, ilosc integer CHECK(ilosc >= 0), typ text, uniw boolean DEFAULT TRUE);

CREATE TABLE zamowienia (id serial PRIMARY KEY, data_zamow timestamp DEFAULT now(), data_real timestamp DEFAULT NULL, firma text, ilosc integer CHECK(ilosc > 0), cena typcena, cze_id integer);

CREATE TABLE zleusl (zle_id integer, usl_nazwa text);

CREATE TABLE czesam (cze_id integer, sam_model text);

CREATE TABLE czeusl (cze_id integer, usl_nazwa text);

/* DODANIE KLUCZY OBCYCH */
ALTER TABLE zlecenia ADD CONSTRAINT fk_zle_kli FOREIGN KEY (kli_id) REFERENCES clients(id) ON DELETE SET NULL DEFERRABLE;
ALTER TABLE zlecenia ADD CONSTRAINT fk_zle_sam FOREIGN KEY (sam_model) REFERENCES samochody(model) ON DELETE SET NULL DEFERRABLE;

ALTER TABLE zamowienia ADD CONSTRAINT fk_zam_cze FOREIGN KEY (cze_id) REFERENCES czesci(id) ON DELETE SET NULL DEFERRABLE;

ALTER TABLE zleusl ADD CONSTRAINT fk_zleusl_zle FOREIGN KEY (zle_id) REFERENCES zlecenia(id) ON DELETE CASCADE DEFERRABLE;
ALTER TABLE zleusl ADD CONSTRAINT fk_zleusl_usl FOREIGN KEY (usl_nazwa) REFERENCES uslugi(nazwa) ON DELETE SET NULL DEFERRABLE;

ALTER TABLE czesam ADD CONSTRAINT fk_czesam_cze FOREIGN KEY (cze_id) REFERENCES czesci(id) ON DELETE CASCADE DEFERRABLE;
ALTER TABLE czesam ADD CONSTRAINT fk_czesam_sam FOREIGN KEY (sam_model) REFERENCES samochody(model) ON DELETE CASCADE DEFERRABLE;

ALTER TABLE czeusl ADD CONSTRAINT fk_czeusl_cze FOREIGN KEY (cze_id) REFERENCES czesci(id) ON DELETE CASCADE DEFERRABLE;
ALTER TABLE czeusl ADD CONSTRAINT fk_czeusl_usl FOREIGN KEY (usl_nazwa) REFERENCES uslugi(nazwa) ON DELETE CASCADE DEFERRABLE;

/* TWORZENIE RÓL I NADANIE PRAW ROLOM */
CREATE ROLE sprzedawca;
CREATE ROLE mechanik;
CREATE ROLE magazynier;

GRANT SELECT ON uslugi, samochody TO sprzedawca;
GRANT SELECT, INSERT, UPDATE ON clients, zlecenia, zleusl TO sprzedawca;

GRANT SELECT ON zlecenia, samochody, uslugi TO mechanik;
GRANT SELECT, INSERT, UPDATE ON czesci, czesam, czeusl TO mechanik;
GRANT UPDATE(data_real) ON zlecenia TO mechanik;

GRANT SELECT ON czesci TO magazynier;
GRANT SELECT, INSERT, UPDATE ON zamowienia TO magazynier;

GRANT ALL ON ALL SEQUENCES IN SCHEMA public TO sprzedawca, magazynier, mechanik;

/* REGUŁY, FUNKCJE I WYZWALACZE */
CREATE OR REPLACE RULE czesam_rule AS ON INSERT TO czesam DO ALSO UPDATE czesci SET uniw = FALSE WHERE czesci.id = NEW.cze_id;

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
        UPDATE czesci SET ilosc = ilosc+NEW.ilosc WHERE id = NEW.cze_id;
    ELSIF OLD.ilosc <> NEW.ilosc
    THEN
        UPDATE czesci SET ilosc = ilosc-OLD.ilosc+NEW.ilosc WHERE id = NEW.cze_id;
    END IF;
    RETURN NULL;
END;
$f$ LANGUAGE plpgsql;
CREATE TRIGGER zam_trg AFTER UPDATE ON zamowienia FOR EACH ROW EXECUTE PROCEDURE zam_trg_func();

