### O GARRA DOCKER

Este projeto foi desenvolvido para a matéria de Oficinas de Integração 1, do curso de Engenharia da Computação da Universidade Tecnológica Federal do Paraná.


## Conteúdo

- Código do Arduino, para o funcionamento da parte eletrônica do projeto
- Código em R, para o funcionamento da API e utilização do banco, feito em SQLite.

## Como Arrumar os arquivos para ser executado localmente

- Primeiramente, a API não está funcionando em um servidor, portanto, para a utilização da mesma é necessário que seja baixado o R e alguns pacotes dele.
- Depois de baixar a linguagem e os pacotes necessários, é precisso mudar o caminho do banco, no arquivo (OGarraDocker -> R -> OGarraDocker.R), que está na função "setwd()".
- Por fim, para atualizar o pacote que será necessário para a utilização da API, é essencial executar o arquivo "update.R".

## Como Rodar a API

Após feito os passos acima, com o pacote "opencpu" baixado, execute os seguintes comandos em um ambiente R ou no terminar do RStudio
```
library("opencpu")
```
```
ocpu_start_app("OGarraDocker")
```
ou
```
ocpu_start_server()
```

Assim a API ja está no ar, **localmente**

## Como Testar a API na Web, localmente

Dado os comandos acima, caso tenha utilizado o comando "ocpu_start_app("OGarraDocker")", vai abrir uma tela parecida com essa no navegador:
[![texto alt](urldaimagem)](urldolink)

Com essa tela, arrume o link para algo como "http://localhost:qualPortaEh/ocpu/test/" (caso tenha executado o comando "ocpu_start_server()" é possível digitar esse link no navegador diretamente), assim aparecerá outra tela:
[![texto alt](urldaimagem)](urldolink)

Mudar o método para "POST" e arrumar o "ENDPOINT" para algo como: "../library/NomeDoPacote/R/NomeDaFuncaoASerChamada/json"

Se houver parametros para passar para a API, simplesmente as adicione. E Aperte "Ajax Request".