Esse é um simulador para avaliação de desempenho de estimadores DFSA para cadeira de Sistemas de Comunicação

## Todos:
- [ ] Colocar grid nos gráficos
- [ ] Checar implementação do Eom-Lee
- [ ] Implementar IV2

## Easy run:
Se estiver em um linux, usar [run-full.sh](./run-full.sh) **da pasta raiz do projeto**
```bash
git clone <url desse repo>
cd simulador-dfsa
sh run-full.sh
```
ou então

```bash
# se o executável gerado pelo cmake estiver na raiz do projeto:
simulador --out plots/out && python plots/main.py plots/out.csv plots/images
```

## Parâmetros Configuráveis

- `--initial-tags`: Número de tags da primeira simulação (padrão 100)
- `--increment-tags`: Incremento do número em cada simulação (padrão 100)
- `--max-tags`: Número máximo de tags que serão simuladas (padrão 1000)
- `--repetitions`:número de repetições para tirar a média do resultado para uma certa quantidade de etiquetas (padrão 5)
- `--initial-frame`: tamanho do quadro inicial (padrão 64)
- `--no-po2`: se passado, não vai limitar os quadros a serem uma potência de 2
- `--estimators`: estimadores a serem rodadas. nomes separados por vírgula (padrão lb,shoute,eom-lee,iv2)
    - `lb`: Lower Bound estimator
    - `shoute`: Shoute estimator
    - `eom-lee`: Eom Lee estimator
    - `iv2`: Improved ---
- `--out`: path onde será salvo os resultados dos experimentos  

## Gráficos a serem plotados
> Usar esses [parâmetros de configuração (Seção 3)](http://www.cin.ufpe.br/~pasg/gpublications/AnGo11.pdf)

- Quantidade total de slots
- Quantidade total de slots vazios
- Quantidade total de slots em colisão
- Tempo médio de execução do estimador

## Slotted Aloha
Algoritmo de resolução de conflitos para leitura de RFIDs

## FSA (Framed Slotted Aloha)
1. Leitor manda um comando request para as tags, informando o tamanho do frame
2. As tags escolhem um frame aleatório para emitir seus dados. Caso a tag dê a sorte de ser a única a ter escolhido um frame, então a leitura dessa tag é bem sucedida e ela não responde nos frames seguintes. Caso duas tags mandem no mesmo frame, então houve uma colisão, e elas terão que repetir o processo no frame seguinte.
3. Esse processo se repete até todas as tags serem lidas (ou seja, quando não há colisões)

## DFSA (Dynamic Framed Slotted Aloha)
Parecido com o FSA, mas o tamanho do frame é dinamicamente ajustado por algum estimador do número de tags, o que torna o algoritmos mais eficiente

## Integrantes
- Vitor Lopes Maia Albuquerque
- Daniel Henrique Amorim Correia

## Referências
- <http://www.cin.ufpe.br/~pasg/gpublications/AnGo11.pdf>
- <http://www.cin.ufpe.br/~pasg/gpublications/AnGo11.pdf>
