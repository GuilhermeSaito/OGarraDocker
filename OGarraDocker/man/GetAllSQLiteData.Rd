% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/OGarraDocker.R
\name{GetAllSQLiteData}
\alias{GetAllSQLiteData}
\title{Get all data from DataBase SQLite Connection.}
\usage{
GetAllSQLiteData(dataTableName = "OGarraDockerDB")
}
\arguments{
\item{dataTableName}{Nome da tabela a ser pego as informações. Por padrão = "OGarraDockerDB"}
}
\value{
Retorna um json contendo todas as informações do banco
}
\description{
Essa função resgata todos os registros da tabela
}
\details{
* 1. Para obter informações a respeito do código R desta função, acessar ...
}
\examples{
GetAllSQLiteData()

}
