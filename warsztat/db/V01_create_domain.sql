CREATE DOMAIN percent_type AS integer NOT NULL DEFAULT 0 CHECK(VALUE IN(0, 5, 10, 15, 20, 25));

CREATE DOMAIN auto_type AS varchar(20) NOT NULL DEFAULT 'person' CHECK(VALUE IN('person', 'lorry', 'bus', 'motorcycle'));

CREATE DOMAIN price_type AS numeric(10, 2) CHECK(VALUE > 0);

CREATE DOMAIN registration_type AS text NOT NULL CHECK(VALUE ~ '(^[A-Z][A-Z] [A-Z0-9][A-Z0-9][A-Z0-9][A-Z0-9][A-Z0-9]$)|(^[A-Z][A-Z][A-Z] [A-Z0-9][A-Z0-9][A-Z0-9][A-Z0-9][A-Z0-9]?$)');

CREATE DOMAIN phone_type AS integer CHECK(100000000 <= VALUE AND VALUE <= 999999999);
