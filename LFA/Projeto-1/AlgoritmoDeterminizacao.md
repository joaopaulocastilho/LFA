# Algoritmo para determinização do autômato

<table>
  <thead>
    <tr>
      <th>Passo:</th>
      <th>Ação</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>1</td>
      <td>Criar uma matriz com os estados já existentes e dizendo para onde eles mapeiam.
      Exemplo: S -> S; A -> A.
      Por que? Imagine uma situação em que a determinização do estado [AB] por "a" leve para <̱S\>, precisamos saber se esse estado não foi gerado como um estado determinizado.</td>
    </tr>
    <tr>
      <td>2</td>
      <td>Identificar um estado que contenha uma indeterminização.</td>
    </tr>
    <tr>
      <td>3</td>
      <td>Ordenar a transição indeterministica, em ordem crescente de acordo com os índices.</td>
    </tr>
    <tr>
      <td>4</td>
      <td>Procurar se aqueles estados já não foram associados a um novo estado na matriz de determinização.
        Exemplo: se no estado anterior tinhamos o indeterminismo {A, B} e nesse também temos o indeterminismo {A, B}, certamente ele já está no vetor, basta procurar por ele.</td>
    </tr>
    <tr>
      <td>5</td>
      <td>Trocar o indeterminismo pelo novo estado gerado, que corresponde a ele mesmo.</td>
    </tr>
    <tr>
      <td>6</td>
      <td>Eliminar estados inalcançáveis a partir de S novamente, pois provavelmente terá novamente.
      Exemplo: figura 1.</td>
    </tr>
  </tbody>
</table>

<figure>
  <p><img src="image/AFND-AFD.jpg"
    alt="Figura 1">
  <figcaption>Figura 1- Determinização do AFND. Os estados em vermelho são inalcançáveis a partir de S</figcaption>
</figure>
