#' @title  
#' Conexao com o BD SQL Server.
#' 
#' @description 
#' Esta função faz conexão com o BD SQL Server do NI a partir dos parâmetros informados. Como são setadas
#' variáveis de ambiente para os parâmetros, não é necessário fazer requisição desta função a partir da API OpenCPU. 
#' Esta função é utilizada de forma automática pelas demais funções. (Não utilizar!)
#'
#' @param driver driver SQL Server ODBC. Sys.getenv("CAEXDB_CONNECTION_DRIVER")="FreeTDS"
#' @param server server SQL Server. Default: Sys.getenv("CAEXDB_CONNECTION_SERVER")="caexsqldb.mppr"
#' @param port porta SQL Server. Default: Sys.getenv("CAEXDB_CONNECTION_PORT")="1433"
#' @param login login do usuário. Default: Sys.getenv("CAEXDB_CONNECTION_UID")
#' @param passwd senha do usuário. Default: Sys.getenv("CAEXDB_CONNECTION_PWD")
#' @param encod encoding. "UTF-8" para Linux e "latin1" para Windows
#'
#' @return Retorna uma lista de tabelas em formato dbplyr, que devem ser processadas pelas demais funções.
#' 
#' @details 
#' * 1. Para obter informações a respeito do código R desta função, acessar o link: http://opencpu.mppr/ocpu/library/BuscaContrato/R/SQLcon/print
#' 
#' @examples
#' SQLcon()
#'
#' @export
hello <- function() {
	setwd("/home/gtsaito/Desktop/Gui/Oficinas1")

	fileConn <- file("output.txt")
	writeLines(("Hello Another World"), fileConn)
	close(fileConn)

	return(getwd())
}
