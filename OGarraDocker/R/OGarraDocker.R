# ------------------------- Provavelmente nao vai precisar usar essa funcao de criar a tabela, ja q ela ja cria quando insere, mas vai ficar ai soh de backup
#' @title
#' Remover Acentos
#'
#' @description
#' Esta funcao remove acentos da string recebida e retorna a mesma string sem os mesmos e tudo minusculo.
#'
#' @param x string recebida normal
#'
#' @return Retorna a mesma string mas sem os acentos e tudo minusculo
#'
#' @details
#' * 1. Para obter informações a respeito do código R desta função, acessar o link: http://opencpu.mppr/ocpu/library/GeoEmpresas/R/util_remove_accents/print
#'
#' @examples
#' util_remove_accents("Coração")
#'
#' @export
util_remove_accents <- function(x = "") {
  	y <- iconv(tolower(x), from = "UTF-8", to = "ASCII//TRANSLIT")

  	return(y)
}

#' @title
#' Remover caracteres especiais
#'
#' @description
#' Esta funcao remove caracteres especiais de string para conseguir processa-la de forma correta
#'
#' @param x string recebida com todos os caracteres
#'
#' @return Retorna a mesma string mas sem os caracteres especiais
#'
#' @details
#' * 1. Para obter informações a respeito do código R desta função, acessar o link: http://opencpu.mppr/ocpu/library/GeoEmpresas/R/util_remove_special_characters/print
#'
#' @examples
#' util_remove_special_characters("Avenida das Torres")
#' util_remove_special_characters("Avenida-das-Torres")
#'
#' @export
util_remove_special_characters <- function(x = "") {
	y <- gsub(
		"\\s+", "",
		gsub(
		"[!\"#$%&'()\\*\\+,/:<=>?@\\^_`\\{|\\}~]", "",
		gsub(
			"\\.", "",
			gsub(
			"/", "",
			gsub("-", "", x)
			)
		)
		)
	)

  return(y)
}

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
#' CreateSQLiteDataTable(fieldsName = "id; nome; data"))
#'
#' @export
CreateSQLiteDataTable <- function(dataTableName = "OGarraDockerDB", fieldsName) {
	# Setando o diretorio para conseguir utilizar o que eu preciso
	setwd("C:\\Users\\guilh\\Desktop\\aulasUTFPR\\2022_2\\Oficina1\\OGarraDocker\\OGarraDocker/database")

	if (!DBI::dbCanConnect(RSQLite::SQLite(), dbname = dataTableName)) {
		return(0)
	}

	# Faz a conxao com a base de dados e cria a tabela, se nao existir
	con <- DBI::dbConnect(RSQLite::SQLite(), dbname = dataTableName)

	# Considerando que o fields name vai vir com ;
	fieldsNameList <- trimws(strsplit(fieldsName, ";")[[1]])
	# Remove todos os . - ou outros characteres especiais dos cnpjs
	fieldsNameList <- OGarraDocker::util_remove_special_characters(fieldsNameList)

	# O dado para ser inserido na tabela precisa ser do tipo de data frame ou vector
	if (length(fieldsNameList) == 0) {
		return (-1)
	}

	# Cria um dataframe vazio sem linha e com a mesma quantidade de colunas
	fieldsNameDataFrame <- data.frame(matrix(NA, nrow = 0, ncol = length(fieldsNameList)))
	# Coloca o nome das colunas
	colnames(fieldsNameDataFrame) <- fieldsNameList

	# Cria a tabela e retorna o valor do resultado, se nao for possivel criar, vai ser retornado o valor
	result <- DBI::dbCreateTable(conn = con, name = dataTableName, fields = fieldsNameDataFrame, temporary = FALSE)
	return(result)
}
# CreateSQLiteDataTable(fieldsName = "id; nome; data")
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
#' InsertSQLiteDataTable(id = "1", nome = "Teste", data = "10-20-32")
#'
#' @export
InsertSQLiteDataTable <- function(dataTableName = "OGarraDockerDB", id, prioridade, dataEntrada, posLinha, posColuna) {
# ---------------------------- SOH PRECISA COLOCAR OS PARAMETROS PARA OS VALORES CERTINHOS ----------------------------

	# Setando o diretorio para conseguir utilizar o que eu preciso
	setwd("C:\\Users\\guilh\\Desktop\\aulasUTFPR\\2022_2\\Oficina1\\OGarraDocker\\OGarraDocker/database")

	if (!DBI::dbCanConnect(RSQLite::SQLite(), dbname = dataTableName)) {
		return(0)
	}

	# Faz a conxao com a base de dados e cria a tabela, se nao existir
	con <- DBI::dbConnect(RSQLite::SQLite(), dbname = dataTableName)

	# Preparando o dado como data frame para inserir, vai inserir o dado mesmo que esteja null
	dataToInsert <- data.frame(id = id, prioridade = prioridade, dataEntrada = dataEntrada, posLinha = posLinha, posColuna = posColuna)

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
	# Setando o diretorio para conseguir utilizar o que eu preciso
	setwd("C:\\Users\\guilh\\Desktop\\aulasUTFPR\\2022_2\\Oficina1\\OGarraDocker\\OGarraDocker/database")

	if (!DBI::dbCanConnect(RSQLite::SQLite(), dbname = dataTableName)) {
		return(0)
	}

	# Faz a conxao com a base de dados
	con <- DBI::dbConnect(RSQLite::SQLite(), dbname = dataTableName)

	query <- paste0("SELECT * FROM ", dataTableName)
	data <- DBI::dbGetQuery(con, query)

	return(data)

	# Nao pode encerrar a conexao aqui hahahaha
	DBI::dbDisconnect(con)
}

#' @title
#' Remove row from DataBase SQLite Connection and return the row that was removed.
#'
#' @description
#' Essa função remove registros de tabela no tipo de sqlite e a retorna para o chamamento
#'
#' @param dataTableName Nome da tabela a fazer a conexão. Por padrão = "OGarraDockerDB"
#' @param idToRemove Id correspondente para remover o registro
#'
#' @return Retorna o dado removido
#'
#' @details
#' * 1. Para obter informações a respeito do código R desta função, acessar ...
#'
#' @examples
#' RemoveSQLiteDataTable(idToRemove = 1)
#'
#' @export
RetrieveRemoveSQLiteDataTable <- function(dataTableName = "OGarraDockerDB", idToRemove) {
	# Setando o diretorio para conseguir utilizar o que eu preciso
	setwd("C:\\Users\\guilh\\Desktop\\aulasUTFPR\\2022_2\\Oficina1\\OGarraDocker\\OGarraDocker/database")

	if (!DBI::dbCanConnect(RSQLite::SQLite(), dbname = dataTableName)) {
		return(0)
	}

	# Faz a conxao com a base de dados
	con <- DBI::dbConnect(RSQLite::SQLite(), dbname = dataTableName)

	queryToRetrieve <- paste0("SELECT * FROM ", dataTableName, " WHERE id = ", idToRemove)
	dataRetrieved <- DBI::dbGetQuery(con, queryToRetrieve)

	# Prepara a query para ser executada
	query <- paste0("DELETE FROM ", dataTableName, " WHERE id = ", idToRemove)

	# Escreve na tabela que fez a conexao
	DBI::dbSendQuery(conn = con, statement = query)

	return(dataRetrieved)
}