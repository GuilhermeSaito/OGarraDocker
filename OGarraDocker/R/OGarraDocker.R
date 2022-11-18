# ------------------------- Provavelmente nao vai precisar usar essa funcao de criar a tabela, ja q ela ja cria quando insere, mas vai ficar ai soh de backup

#' @title
#' Create DataBase SQLite Connection.
#'
#' @description
#' Essa função cria uma tabela no tipo de sqlite
#'
#' @param dataTableName Nome da tabela a fazer a conexão. Por padrão = "OGarraDockerDB# ------------------------- Provavelmente nao vai precisar usar essa funcao de criar a tabela, ja q ela ja cria quando insere, mas vai ficar ai soh de backup

#' @title
#' Create DataBase SQLite Connection.
#'
#' @description
#' Essa função cria uma tabela no tipo de sqlite
#'
#' @param dataTableName Nome da tabela a fazer a conexão. Por padrão = "OGarraDockerDB"
#' @param fieldsName Nome das colunas a serem criadas para a tabela, pode ser no tipo de vector ou data frame
#'
#' @return Retorna verdadeiro caso foi possível a criação da tabela ou false, caso o contrário
#'
#' @details
#' * 1. Para obter informações a respeito do código R desta função, acessar ...
#'
#' @examples
#' CreateSQLiteDataTable(fieldsName = c("id", "nome", "data"))
#'
#' @export
CreateSQLiteDataTable <- function(dataTableName = "OGarraDockerDB", fieldsName) {
    # Soh alterar aqui depois para colocar o local certinho
    setwd("/home/gtsaito/Desktop/Gui/Oficinas1")

    if (!DBI::dbCanConnect(RSQLite::SQLite(), dbname = dataTableName)) {
        return(0)
    }

    # Faz a conxao com a base de dados e cria a tabela, se nao existir
    con <- DBI::dbConnect(RSQLite::SQLite(), dbname = dataTableName)

    # O dado para ser inserido na tabela precisa ser do tipo de data frame ou vector
    if ((!is.data.frame(fieldsName)) & (!is.vector(fieldsName))) {
        fieldsName <- as.data.frame(fieldsName)
    }

    # Cria a tabela e retorna o valor do resultado, se nao for possivel criar, vai ser retornado o valor
    return(DBI::dbCreateTable(conn = con, name = dataTableName, fields = fieldsName, temporary = FALSE))
}

#' @title
#' Insert in DataBase SQLite Connection.
#'
#' @description
#' Essa função insere registros em uma tabela no tipo de sqlite
#'
#' @param dataTableName Nome da tabela a fazer a conexão. Por padrão = "OGarraDockerDB"
#' @param dataToInsert Data Frame contendo os dados a serem inseridos na tabela
#'
#' @return Retorna verdadeiro caso foi possível a insercao na tabela ou false, caso o contrário
#'
#' @details
#' * 1. Para obter informações a respeito do código R desta função, acessar ...
#'
#' @examples
#' InsertSQLiteDataTable(as.data.frame(list(id = c("1", "2", "3"), name = c("a", "b", "c"), data = c("12-10-2022", "10-4-1992", "25-4-2001"))))
#'
#' @export
InsertSQLiteDataTable <- function(dataTableName = "OGarraDockerDB", dataToInsert) {
    if (!DBI::dbCanConnect(RSQLite::SQLite(), dbname = dataTableName)) {
        return(0)
    }

    # Faz a conxao com a base de dados e cria a tabela, se nao existir
    con <- DBI::dbConnect(RSQLite::SQLite(), dbname = dataTableName)

    # O dado para ser inserido na tabela precisa ser do tipo de data frame
    if (!is.data.frame(dataToInsert)) {
        dataToInsert <- as.data.frame(dataToInsert)
    }

    # Escreve na tabela que fez a conexao
    DBI::dbWriteTable(conn = con, dataTableName, dataToInsert, append = TRUE)

    # Encerra a conexao
    DBI::dbDisconnect(con)

    return(1)
}

#' @title
#' Get all data from DataBase SQLite Connection.
#'
#' @description
#' Essa função resgata todos os registros da tabela
#'
#' @param dataTableName Nome da tabela a ser pego as informações. Por padrão = "OGarraDockerDB"
#'
#' @return Retorna um json contendo todas as informações do banco
#'
#' @details
#' * 1. Para obter informações a respeito do código R desta função, acessar ...
#'
#' @examples
#' GetAllSQLiteData()
#'
#' @export
GetAllSQLiteData <- function(dataTableName = "OGarraDockerDB") {
    if (!file.exists(paste0(dirname(rstudioapi::getSourceEditorContext()$path), "/", dataTableName, ".db"))) {
        dir.create(paste0(dirname(rstudioapi::getSourceEditorContext()$path), "/", dataTableName, ".db"), recursive = T)
    }

    # Faz a conxao com a base de dados
    con <- DBI::dbConnect(RSQLite::SQLite(), paste0(dirname(rstudioapi::getSourceEditorContext()$path), "/", dataTableName))

    data <- dplyr::tbl(con, dataTableName)

    return(data)

    # Nao pode encerrar a conexao aqui hahahaha
    DBI::dbDisconnect(con)
}

#' @title
#' Remove row from DataBase SQLite Connection.
#'
#' @description
#' Essa função remove registros de tabela no tipo de sqlite
#'
#' @param dataTableName Nome da tabela a fazer a conexão. Por padrão = "OGarraDockerDB"
#' @param idToRemove Id correspondente para remover o registro
#'
#' @return Retorna verdadeiro caso foi possível a remoção na tabela ou false, caso o contrário
#'
#' @details
#' * 1. Para obter informações a respeito do código R desta função, acessar ...
#'
#' @examples
#' RemoveSQLiteDataTable(idToRemove = 1)
#'
#' @export
RemoveSQLiteDataTable <- function(dataTableName = "OGarraDockerDB", idToRemove) {
    if (!DBI::dbCanConnect(RSQLite::SQLite(), dbname = dataTableName)) {
        return(0)
    }

    # Faz a conxao com a base de dados e cria a tabela, se nao existir
    con <- DBI::dbConnect(RSQLite::SQLite(), dbname = dataTableName)

    # Prepara a query para ser executada
    query <- paste0("DELETE FROM ", dataTableName, " WHERE id = ", as.character(idToRemove))

    # Escreve na tabela que fez a conexao
    DBI::dbSendQuery(conn = con, statement = query)

    return(1)
}

#' @title
#' Retrieve data from DataBase SQLite Connection.
#'
#' @description
#' Essa função resgata os registros em que os ids forem iguais ao passado por parametro, deleta-os e retorna eles
#'
#' @param dataTableName Nome da tabela a ser pego as informações. Por padrão = "OGarraDockerDB"
#' @param idToRetrieve Id correspondente para retirar do registro
#'
#' @return Retorna um json contendo as informações do banco pedidas
#'
#' @details
#' * 1. Para obter informações a respeito do código R desta função, acessar ...
#'
#' @examples
#' GetAllSQLiteData(idToRetrieve = 1)
#'
#' @export
RetrieveSQLiteData <- function(dataTableName = "OGarraDockerDB", idToRetrieve) {
    if (!DBI::dbCanConnect(RSQLite::SQLite(), dbname = dataTableName)) {
        return(0)
    }

    # Faz a conxao com a base de dados
    con <- DBI::dbConnect(RSQLite::SQLite(), dataTableName)

    # Prepara a query para ser executada
    query <- paste0("SELECT * FROM ", dataTableName, " WHERE id = ", idToRetrieve)

    query_response <- DBI::dbSendQuery(conn = con, statement = query)
    # Retorna os dados da ultima query feita
    data <- DBI::dbFetch(query_response)

    # ------------------------------ NAO ESQUECER DE COLOCAR O NAMESPACE AQUI ------------------------------
    # Remove os registros resgatados
    RemoveSQLiteDataTable(idToRemove = idToRetrieve)

    return(data)
}
