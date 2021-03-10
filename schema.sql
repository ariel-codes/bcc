PRAGMA foreign_keys= ON;

CREATE TABLE orgao_superior
(
    id INTEGER PRIMARY KEY
);

CREATE TABLE orgao_subordinado
(
    id             INTEGER PRIMARY KEY,
    orgao_superior INTEGER,
    FOREIGN KEY (orgao_superior) references orgao_superior (id)
);

CREATE TABLE unidade_gestora
(
    id INTEGER PRIMARY KEY
);

CREATE TABLE pessoa_juridica
(
    id INTEGER PRIMARY KEY
);

CREATE TABLE compra
(
    id                INTEGER PRIMARY KEY,
    unidade_gestora   INTEGER,
    orgao_subordinado INTEGER,
    pessoa_juridica   INTEGER,
    FOREIGN KEY (unidade_gestora) references unidade_gestora (id),
    FOREIGN KEY (orgao_subordinado) references orgao_subordinado (id),
    FOREIGN KEY (pessoa_juridica) references pessoa_juridica (id)
);

CREATE TABLE item_compra
(
    id     INTEGER PRIMARY KEY,
    compra INTEGER,
    FOREIGN KEY (compra) references compra (id)
);

CREATE TABLE termo_aditivo
(
    id     INTEGER PRIMARY KEY,
    compra INTEGER,
    FOREIGN KEY (compra) references compra (id)
);

CREATE TABLE licitacao
(
    id                INTEGER PRIMARY KEY,
    unidade_gestora   INTEGER,
    orgao_subordinado INTEGER,
    FOREIGN KEY (unidade_gestora) references unidade_gestora (id),
    FOREIGN KEY (orgao_subordinado) references orgao_subordinado (id)
);

CREATE TABLE item_licitacao
(
    id        INTEGER PRIMARY KEY,
    licitacao INTEGER,
    FOREIGN KEY (licitacao) references licitacao (id)
);

CREATE TABLE participante_licitacao
(
    id              INTEGER PRIMARY KEY,
    item_licitacao  INTEGER,
    pessoa_juridica INTEGER,
    FOREIGN KEY (item_licitacao) references item_licitacao (id),
    FOREIGN KEY (pessoa_juridica) references pessoa_juridica (id)
);