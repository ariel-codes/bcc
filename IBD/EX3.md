EX3

## álgebra relacional

### 1.
𝐴 ← 𝜎~Ano=2020\ ∧\ Veículo="VLDB\ Journal"~(Artigo)

B ← 𝜎~Posição=1~(Autoria)

Resultado ← 𝜋~Nome~(𝜎~Pesquisador.PID=B.PID\ ∧\ B.AID=A.AID~(Pesquisador × A × B))

### 2.
𝐴 ← 𝜎~Ano=2020\ ∧\ Veículo="VLDB\ Journal"~(Artigo)

B ← 𝜎~Posição=1~(Autoria)

Resultado ← 𝜋~Nome~(Pesquisador ⋈ (A ⋈ B))

### 3.
A ← Pesquisador ⋈ 𝜋~PID~(Autoria)

Resultado ← 𝜋~Nome~(Pesquisador - A)

### 4.

Resultado ← 𝜋~PID~(Autoria ÷ 𝜎~Ano=2015~(Artigo))

### 5.

A ← Autoria ÷ 𝜎~Nome="J\ Silva"~(Pesquisador)

B ← 𝜌~(AID)~𝜋~Citante~(Citação ⋈~Citado=AID~ (Artigo ⋈ A))

C ← Autoria ÷ (Artigo ⋈ B)

Resultado ← Pesquisador ÷ C

### 6.
A ← 𝜌~(Citante,AnoCitante)~𝜋~AID,Ano~(Artigo)

B ← 𝜌~(Citado,AnoCitado)~(A)

C ← 𝜎~AnoCitante=AnoCitado~(A ⋈ Citação ⋈ B)

Resultado ← 𝜋~Citante~(C\)