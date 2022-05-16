#!/usr/bin/env ruby

require "csv"
require "sqlite3"

db = SQLite3::Database.new "pedidos.db"
db.execute_batch <<-SQL
  DROP TABLE IF EXISTS pedido_alunos;
  CREATE TABLE IF NOT EXISTS pedido_alunos (
    id integer primary key,
    nome string,
    login string,
    email string,
    telefone string,
    curso string,
    pagamento string
  );
  DROP TABLE IF EXISTS pedido_camisas;
  CREATE TABLE IF NOT EXISTS pedido_camisas (
    id integer primary key,
    aluno_id integer,
    tamanho string,
    cor string,
    quantidade integer,
    FOREIGN KEY(aluno_id) REFERENCES pedido_alunos(id)
  );
SQL

regex_form = /((\w+)-(\w+): (\d))/
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

CSV.foreach(ARGV.first,
  headers: true, liberal_parsing: true, converters: :date_time) do |row|
  data = row.to_h.transform_keys { |k| headers.key k }
  data.transform_values! { |d| d&.strip }

  db.execute("INSERT INTO pedido_alunos (nome, login, email, telefone, curso, pagamento)
    VALUES (?,?,?,?,?,?);",
    [data[:name], data[:login], data[:email], data[:telephone], data[:course], data[:payment]])
  student_id = db.last_insert_row_id.to_i

  matches = data[:shirts].scan(regex_form)
  matches.each do |match|
    _, size, color, quant = match
    # debugger if student_id > 100
    db.execute("INSERT INTO pedido_camisas (aluno_id, tamanho, cor, quantidade)
      VALUES (?,?,?,?);",
      [student_id, size, color, quant])
  end
end

CSV.open(ARGV[1], "w", write_headers: true, headers: %w[Tamanho Cor Curso Quantidade]) do |csv|
  db.execute("SELECT tamanho, cor, curso, SUM(quantidade) as total FROM pedido_camisas
    INNER JOIN pedido_alunos on pedido_alunos.id = pedido_camisas.aluno_id
    GROUP BY tamanho, cor, curso ORDER BY total DESC;") do |row|
    csv << row
  end
end

CSV.open(ARGV[2], "w", write_headers: true, headers: %w[Nome Email Telefone]) do |csv|
  db.execute("SELECT nome, email, telefone FROM pedido_alunos GROUP BY email ORDER BY nome;") do |row|
    csv << row
  end
end
