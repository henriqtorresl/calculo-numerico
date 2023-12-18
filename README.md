# Trabalho de Métodos Numéricos para Engenharia

## Descrição do Projeto

Este projeto consiste em um programa em linguagem C para realizar o ajuste de curvas a conjuntos de dados, utilizando diferentes métodos: ajuste linear, ajuste quadrático, ajuste exponencial e ajuste polinomial. O código foi desenvolvido como parte de um trabalho prático para a disciplina de Métodos Numéricos para Engenharia.

## Utilização

1. **Compilação:** Compile o código utilizando um compilador C padrão, como o GCC (OBS.: quando você executar o comando abaixo, ele vai gerar um arquivo com o nome 'ajuste_curvas'):
    ```bash
    gcc main.c -o ajuste_curvas -lm
    ```

2. **Execução:** Execute o arquivo gerado:
    ```bash
    ./ajuste_curvas
    ```

3. **Entrada de Dados:** O programa espera um arquivo chamado "dados.txt" contendo pares de valores x e y. Certifique-se de que esse arquivo está presente e bem formatado.

4. **Escolha do Tipo de Ajuste:** O usuário será solicitado a escolher o tipo de ajuste desejado: linear, quadrático, exponencial ou polinomial.

5. **Resultados:** Após o usuário informar o tipo de ajuste que ele deseja, o código vai gerar um arquivo com o conteúdo necessário para plotar o gráfico com o Gnuplot.
Para que seja possível visualizar o gráfico novamente após o arquivo ter sido gerado, execute o comando:
    ```bash
    gnuplot nome_do_script_gerado.gp
    ```
## Requisitos para rodar o código

- Compilador C (GCC recomendado)
- Gnuplot instalado no sistema

## Informações

Para dúvidas ou sugestões, entre em contato com o autor do código:

- **Nome:** HENRIQUE TORRES LANDIN
- **Matrícula:** 202016524
- **Professor:** LINDOMAR BOMFIM DE CARVALHO DE JESUS

Esse código foi desenvolvido como parte de um trabalho acadêmico e pode ser utilizado e modificado conforme necessário.