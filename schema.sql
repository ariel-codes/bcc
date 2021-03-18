PRAGMA foreign_keys= OFF;


DROP TABLE IF EXISTS orgao_superior;
CREATE TABLE orgao_superior
(
    codigo_sup INTEGER PRIMARY KEY,
    nome       TEXT
) WITHOUT ROWID;

DROP TABLE IF EXISTS orgao_subordinado;
CREATE TABLE orgao_subordinado
(
    codigo_sub INTEGER PRIMARY KEY,
    nome       TEXT,
    codigo_sup INTEGER,
    FOREIGN KEY (codigo_sup) references orgao_superior (codigo_sup)
) WITHOUT ROWID;

DROP TABLE IF EXISTS unidade_gestora;
CREATE TABLE unidade_gestora
(
    codigo_gest INTEGER PRIMARY KEY,
    nome        TEXT
) WITHOUT ROWID;

DROP TABLE IF EXISTS pessoa_juridica;
CREATE TABLE pessoa_juridica
(
    cnpj TEXT PRIMARY KEY,
    nome TEXT
) WITHOUT ROWID;

-- DROP TABLE IF EXISTS compra;
-- CREATE TABLE compra
-- (
--     id                INTEGER PRIMARY KEY,
--     unidade_gestora   INTEGER,
--     orgao_subordinado INTEGER,
--     pessoa_juridica   INTEGER,
--     FOREIGN KEY (unidade_gestora) references unidade_gestora (id),
--     FOREIGN KEY (orgao_subordinado) references orgao_subordinado (id),
--     FOREIGN KEY (pessoa_juridica) references pessoa_juridica (id)
-- ) WITHOUT ROWID;
--
-- DROP TABLE IF EXISTS item_compra;
-- CREATE TABLE item_compra
-- (
--     id     INTEGER PRIMARY KEY,
--     compra INTEGER,
--     FOREIGN KEY (compra) references compra (id)
-- ) WITHOUT ROWID;
--
-- DROP TABLE IF EXISTS termo_aditivo;
-- CREATE TABLE termo_aditivo
-- (
--     id     INTEGER PRIMARY KEY,
--     compra INTEGER,
--     FOREIGN KEY (compra) references compra (id)
-- ) WITHOUT ROWID;
--
DROP TABLE IF EXISTS modalidade_compra;
CREATE TABLE modalidade_compra
(
    codigo_mod INTEGER PRIMARY KEY,
    modalidade TEXT
) WITHOUT ROWID;

DROP TABLE IF EXISTS licitacao;
CREATE TABLE licitacao
(
    numero         INTEGER,
    codigo_mod     INTEGER,
    processo       TEXT,
    objeto         TEXT,
    situacao       TEXT,
    codigo_gest    INTEGER,
    codigo_sub     INTEGER,
    municipio      TEXT,
    data_resultado TEXT,
    data_abertura  TEXT,
    valor          REAL,

    PRIMARY KEY (numero, objeto),
    FOREIGN KEY (codigo_mod) references modalidade_compra (codigo_mod),
    FOREIGN KEY (codigo_gest) references unidade_gestora (codigo_gest),
    FOREIGN KEY (codigo_sub) references orgao_subordinado (codigo_sub)
) WITHOUT ROWID;

DROP TABLE IF EXISTS item_licitacao;
CREATE TABLE item_licitacao
(
    numero          INTEGER,
    codigo_mod      INTEGER,
    processo        TEXT,
    codigo_gest     INTEGER,
    codigo_sub      INTEGER,
    descricao       TEXT,
    vencedor_cnpj   TEXT,
    quantidade_item INTEGER,
    valor_item      REAL,

    FOREIGN KEY (codigo_mod) references modalidade_compra (codigo_mod),
    FOREIGN KEY (codigo_gest) references unidade_gestora (codigo_gest),
    FOREIGN KEY (codigo_sub) references orgao_subordinado (codigo_sub),
    FOREIGN KEY (vencedor_cnpj) references pessoa_juridica (cnpj)
);

DROP TABLE IF EXISTS participante_licitacao;
CREATE TABLE participante_licitacao
(
    numero      INTEGER,
    codigo_mod  INTEGER,
    processo    TEXT,
    codigo_gest INTEGER,
    codigo_sub  INTEGER,
    descricao   TEXT,
    cnpj        TEXT,
    vencedor    INTEGER,

    FOREIGN KEY (codigo_gest) references unidade_gestora (codigo_gest),
    FOREIGN KEY (codigo_mod) references modalidade_compra (codigo_mod),
    FOREIGN KEY (codigo_sub) references orgao_subordinado (codigo_sub),
    FOREIGN KEY (cnpj) references pessoa_juridica (cnpj)
);
PRAGMA foreign_keys= ON;