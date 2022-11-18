#!/usr/bin/Rscript

# ESTE SCRIPT DEVE SER EXECUTADO SOMENTE NA MÁQUINA DE TESTES. NÃO EXECUTAR NO HOST!
# A CADA EXECUÇÃO ALTERAR OS PATHS DE ACORDO COM A NECESSIDADE
# COMO DEFAULT, O PACOTE BuscaNFe É UTILIZADO

# pacote necessários
packages = c("devtools", "rstudioapi", "withr")

# verificar se estão instalados ou não
package.check <- lapply(
  packages,
  FUN = function(x) {
    if (!require(x, character.only = TRUE)) {
      install.packages(x, dependencies = TRUE)
      library(x, character.only = TRUE)
    }
  }
)

# local de trabalho
setwd("/home/gtsaito/Desktop/Gui/Oficinas1/OGarraDocker")
# setwd(dirname(rstudioapi::getSourceEditorContext()$path))
getwd()

# documenta
devtools::document(pkg = './OGarraDocker')

# build
devtools::build(pkg = './OGarraDocker', path = './source/')

# instalação para testes
withr::with_libpaths(new = .libPaths()[1], install.packages('./source/OGarraDocker_0.1.0.tar.gz', type='source', repos = NULL))
