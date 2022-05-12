#!/usr/bin/env ruby

require 'optparse'
require 'csv'
require "sqlite3"

file_name = ARGV.first
col_sep = "\t"
OptionParser.new do |parser|
  parser.on("-sSEPARATOR", "--sep=SEPARATOR", "Separador de colunas CSV") do |sep|
    col_sep = sep
  end
end.parse!

db = SQLite3::Database.new "pedidos.db"
db.execute <<-SQL
  CREATE TABLE IF NOT EXISTS pedido_alunos (
    id integer primary key,
    nome string,
    login string,
    email string,
    telefone string,
    curso string,
    pagamento string
  );
  CREATE TABLE IF NOT EXISTS pedido_camisas (
    id integer primary key,
    aluno_id integer,
    tamanho string,
    cor string,
    quantidade integer,
    FOREIGN KEY(aluno_id) REFERENCES pedido_alunos(id),
  );
SQL

regex_form = /((\w)-(\w+): (\d))/
headers = {
  created_at: "Carimbo de data/hora",
  name: "Nome Completo",
  login: "Login do DCC (@dcc.ufmg.br)",
  email: "Email para Contato",
  telephone: "Telefone", 
  course: "Curso",
  shirts: "Quais camisas você quer pedir?", 
  payment: "Comprovante de Pagamento"
}

CSV.foreach(file_name, col_sep: col_sep, 
  headers: true, liberal_parsing: true, converters: %i[numeric date_time]).with_index(1) do |row, idx|
  data = row.to_h.transform_keys { |k| headers.key k }

  db.execute("INSERT INTO pedido_alunos (id, nome, login, email, telefone, curso, pagamento) VALUES (?,?,?,?,?,?,?)",
    [
      idx,
      data[:name],
      data[:login],
      data[:email],
      data[:telephone],
      data[:course],
      data[:payment]
    ]
  )

  matches = data[:shirts].scan(regex_form)
  matches.each do |match|
    _, size, color, quant = match
    db.execute("INSERT INTO pedido_camisas (aluno_id, tamanho, cor, quantidade) VALUES (?,?,?,?)", [idx, size, color, quant])
  end
end