Esse é um simulador para avaliação de desempenho de estimadores DFSA para cadeira de Sistemas de Comunicação


## Parâmetros Configuráveis

- `--initial-tags`: Número de tags da primeira simulação
- `--increment-tags`: Incremento do número em cada simulação
- `--max-tags`: Número máximo de tags que serão simuladas
- `--repetitions`:número de repetições para tirar a média do resultado para uma certa quantidade de etiquetas
- `--initial-frame`: tamanho do quadro inicial
- `--no-po2`: se passado, não vai limitar os quadros a serem uma potência de 2
- `--estimators`: estimadores a serem rodadas. nomes separados por vírgula
    - `lb`: Lower Bound estimator
    - `shoute`: Shoute estimator
    - `eom-lee`: Eom Lee estimator
    - `iv2`: Improved ---

## Gráficos a serem plotados
> Usar esses [parâmetros de configuração (Seção 3)](http://www.cin.ufpe.br/~pasg/gpublications/AnGo11.pdf)

- Quantidade total de slots
- Quantidade total de slots vazios
- Quantidade total de slots em colisão
- Tempo médio de execução do estimador

## Integrantes
- Vitor Lopes Maia Albuquerque
- Daniel Henrique Amorim Correia

## Referências
- <http://www.cin.ufpe.br/~pasg/gpublications/AnGo11.pdf>
- <http://www.cin.ufpe.br/~pasg/gpublications/AnGo11.pdf>
