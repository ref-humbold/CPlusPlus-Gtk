/* WSTAWIANIE DO TABEL */

INSERT INTO klienci(imie, nazwisko, telefon, rabat) VALUES('Rafal', 'Kaleta', 111444777, 15);
INSERT INTO klienci(imie, nazwisko, telefon, firma, rabat) VALUES('Michal', 'Karpinski', 222555888, 'IIUwr', 10);
INSERT INTO klienci(imie, nazwisko, telefon, firma) VALUES('Piotr', 'Wieczorek', 333666999, 'IIUwr');
INSERT INTO klienci(imie, nazwisko, telefon) VALUES('Jakub', 'Michaliszyn', 444000444);

INSERT INTO samochody(model, marka, waga) VALUES('Astra', 'Opel', 1.5);
INSERT INTO samochody(model, marka, waga) VALUES('Corsa', 'Opel', 1.6);
INSERT INTO samochody(model, marka, waga) VALUES('Polo', 'Volkswagen', 1.44);
INSERT INTO samochody(model, marka, waga) VALUES('Golf', 'Volkswagen', 1.57);
INSERT INTO samochody(model, marka, typ, waga) VALUES('Actros', 'Mercedes', 'c', 18.0);
INSERT INTO samochody(model, marka, typ, waga) VALUES('Integra', 'Honda', 'm', 0.238);

INSERT INTO uslugi(nazwa, cena) VALUES('wymiana opon', 70.0);
INSERT INTO uslugi(nazwa, cena) VALUES('przeglad techniczny', 300.0);
INSERT INTO uslugi(nazwa, cena) VALUES('wymiana oleju', 125.0);
INSERT INTO uslugi(nazwa, cena) VALUES('czyszczenie klimatyzacji', 90.0);
INSERT INTO uslugi(nazwa, cena) VALUES('regulacja silnika', 245.0);

INSERT INTO zlecenia(data_zlec, data_real, nr_rej, kli_id, sam_model) VALUES(timestamp '2016-04-19 17:16:40', timestamp '2016-04-22 11:31:18', 'DW13579', 1, 'Polo');
INSERT INTO zlecenia(data_zlec, nr_rej, faktura, kli_id, sam_model) VALUES(timestamp '2016-04-26', 'DOA2034', 'true', 2, 'Corsa');
INSERT INTO zlecenia(data_zlec, nr_rej, kli_id, sam_model) VALUES(timestamp '2016-05-05', 'DBA98E65', 3, 'Integra');

INSERT INTO czesci(producent, ilosc, typ) VALUES('Borygo', 10, 'plyn chlodniczy');
INSERT INTO czesci(producent, ilosc, typ) VALUES('Stomil', 12, 'opony letnie');
INSERT INTO czesci(producent, ilosc, typ, uniw) VALUES('Shell', 7, 'olej napedowy', 'false');

INSERT INTO zamowienia(data_zamow, firma, ilosc, cena, cze_id) VALUES(timestamp '2016-04-24 10:53:29', 'Stomil', 16, 60.0, 2);
INSERT INTO zamowienia(data_zamow, firma, ilosc, cena, cze_id) VALUES(timestamp '2016-04-30 18:22:07', 'QAuto', 1, 22.5, 3);

INSERT INTO zleusl(zle_id, usl_nazwa) VALUES(1, 'wymiana opon');
INSERT INTO zleusl(zle_id, usl_nazwa) VALUES(2, 'regulacja silnika');
INSERT INTO zleusl(zle_id, usl_nazwa) VALUES(2, 'czyszczenie klimatyzacji');
INSERT INTO zleusl(zle_id, usl_nazwa) VALUES(3, 'przeglad techniczny');

INSERT INTO czesam(cze_id, sam_model) VALUES(3, 'Astra');
INSERT INTO czesam(cze_id, sam_model) VALUES(3, 'Corsa');

INSERT INTO czeusl(cze_id, usl_nazwa) VALUES(1, 'regulacja silnika');
INSERT INTO czeusl(cze_id, usl_nazwa) VALUES(2, 'wymiana opon');
INSERT INTO czeusl(cze_id, usl_nazwa) VALUES(3, 'wymiana oleju');
INSERT INTO czeusl(cze_id, usl_nazwa) VALUES(3, 'regulacja silnika');

/* TWORZENIE UŻYTKOWNIKÓW */
CREATE ROLE marek WITH LOGIN ENCRYPTED PASSWORD 'marek1' IN ROLE sprzedawca;
CREATE ROLE zdzislaw WITH LOGIN ENCRYPTED PASSWORD 'zdzislaw2' IN ROLE mechanik;
CREATE ROLE robert WITH LOGIN ENCRYPTED PASSWORD 'robert3' IN ROLE magazynier;

