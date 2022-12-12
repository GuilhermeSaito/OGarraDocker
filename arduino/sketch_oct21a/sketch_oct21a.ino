#include "algoritmo_ordenacao.h"

#include <LiquidCrystal.h>
#include <Stepper.h>
#include <Servo.h>

Servo myservo;

int pos = 0;    // variable to store the servo position
int claw = 0;

// Para entrar na aplicacao, deve apertar no botao selecionado primeiro
/*
	-1 - Nao foi apertado o botao select de inicial
	1 - Foi apertado o botao e entrara na parte de selecionar a prioridade do container
	2 - Prepara todos as estruturas de dados para executar o algoritmo, se estiver no modo automatico
	3 - Foi selecionado a prioridade do container e pode operar a garra
*/
int selected;

// Guardar se a escolha foi manual ou automatico
/*
	-1 - Nao foi apertado nada ainda
	1 - Modo MANUAL selecionado
	2 - Modo AUTOMATICO selecionado
*/
int selected_manual_automatico;
// Mostrar na Tela do LCD se vai ser automatico ou manual
int option_manual_automatico;

// Guardar se a escolha foi adicionar ou remover o container
/*
	-1 - Nao foi apertado nada ainda
	1 - Adicionar container selecionado
	2 - Remover container selecionado
*/
int select_add_remove_container;
// Mostrar na Tela do LCD se vai ser adicionar ou remover
int option_add_remove_container;

// Variavel para setar a prioridade do container
int prioridade_container;

// Variavel para setar o id do container
int container_id;

const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;//Pinos para ligar o display
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);//Define os pinos que serão usados para ligar o display

const int stepsPerRevolution = 200;//Define o No de passos de uma volta completa 

//Inicializa a biblioteca para ligacao ao motor 
Stepper myStepper(stepsPerRevolution, 2, 3, 12, 13);
int anguloAberturaServo;
int anguloFechamentoServo;

void setup() {
	// Inicializacao das variaveis para estado e valor de container
	selected = -1;
	selected_manual_automatico = -1;
	option_manual_automatico = 1;
	select_add_remove_container = -1;
	option_add_remove_container = 1;
	prioridade_container = 0;
	container_id = 0;

	myservo.attach(11);
    myStepper.setSpeed(60);
	anguloAberturaServo = 110;
	anguloFechamentoServo = 10;

    lcd.begin(16, 2);//Define o número de colunas e linhas do display
    lcd.setCursor(0, 0);//Define o cursor para a coluna 0, linha 0
    lcd.print(" O GARRA DOCKER ");

    Serial.begin(9600);
}

void open(){
  	lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(" ABRINDO GARRA ");

	myservo.write(anguloAberturaServo);
	// for (pos = 0; pos <= 130; pos += 1) { // goes from 0 degrees to 180 degrees

	// 	// in steps of 1 degree

	// 	myservo.write(pos);              // tell servo to go to position in variable 'pos'

	// 	delay(15);                       // waits 15ms for the servo to reach the position

	// }

	// Espera 1 segundo para fechar a garra
	delay(1000);
	claw = 1;
}

void close(){
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print(" FECHANDO GARRA ");

	myservo.write(anguloFechamentoServo);
	// for (pos = 130; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees

	// 	myservo.write(pos);              // tell servo to go to position in variable 'pos'

	// 	delay(15);                       // waits 15ms for the servo to reach the position

  	// }

	// Espera 1 segundo para continuar o programa
	delay(1000);
  	claw = 0;
}

//Função para botão select
void select() {
    if(!claw)
      open();
    else
      close();
}

//Função para botão right
void right() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("APERTOU O BOTAO");
    lcd.setCursor(0, 1);
    lcd.print("     RIGHT      ");
}

//Função para botão left
void left() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("APERTOU O BOTAO");
    lcd.setCursor(0, 1);
    lcd.print("      LEFT      ");
}

//Função para botão up
void up() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("SUBINDO GARRA");
    Serial.println("counterclockwise");
    for (int s = 0; s < stepsPerRevolution; s++) {
      myStepper.step(1);
    //myStepper2.step(-1);
    }

}

//Função para botão down
void down() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("DESCENDO GARRA");
    Serial.println("clockwise");

    for (int s = 0; s < stepsPerRevolution; s++) {
      	myStepper.step(-1);
    }
}

// Funcoa para inicializar o projeto, soh esperar o usuario apertar o botao select
void start_project() {
	lcd.clear();
    lcd.setCursor(0, 0);
	lcd.print("SELECIONE");

	if ((analogRead(0)) < 800) { // SELECT
		// Setando as variaveis para nao passar mais aqui e definir para onde deve ir
		selected_manual_automatico = option_manual_automatico;
		selected = 1;
	}
	// Limitando as escolhas para 1 ou 2, nao eh possivel escolher outra.
	else if ((analogRead(0)) < 200) { // UP
		if (option_manual_automatico == 1) {
			option_manual_automatico = option_manual_automatico + 1;
			lcd.setCursor(0, 1);
			lcd.print("AUTOMATICO");
		}
	}
	else if ((analogRead(0)) < 400) { // DOWN
		if (option_manual_automatico == 2) {
			option_manual_automatico = option_manual_automatico - 1;
			lcd.setCursor(0, 1);
			lcd.print("MANUAL");
		}
	}
	delay(100);
}

// Funcao para mostrar a prioridade do container no lcd
void show_container_priority() {
	lcd.clear();
    lcd.setCursor(0, 0);
	lcd.print("PRIORITY CONTA");
	lcd.setCursor(0, 1);
	lcd.print(prioridade_container);
}

// Funcao para aumentar ou diminuir a prioridade do container com o shield
void set_container_priority() {
	if ((analogRead(0)) < 800) { // SELECT
		selected = 2;
	}
	else if ((analogRead(0)) < 200) { // UP
		prioridade_container = prioridade_container + 1;
	}
	else if ((analogRead(0)) < 400) { // DOWN
		if (prioridade_container > 0) {
			prioridade_container = prioridade_container - 1;
		}
	}

	// Delay de 0.5 segundos para conseguir selecionar legal a prioridade do container
	delay(500);
}

// Funcao para mostrar o id do container no lcd
void show_container_id() {
	lcd.clear();
    lcd.setCursor(0, 0);
	lcd.print("ID CONTAINER");
	lcd.setCursor(0, 1);
	lcd.print(container_id);
}

// Funcao para aumentar ou diminuir o id do container com o shield
void set_container_id() {
	if ((analogRead(0)) < 800) { // SELECT
		select_add_remove_container = 3;
	}
	else if ((analogRead(0)) < 200) { // UP
		container_id = container_id + 1;
	}
	else if ((analogRead(0)) < 400) { // DOWN
		if (container_id > 0) {
			container_id = container_id - 1;
		}
	}

	// Delay de 0.5 segundos para conseguir selecionar legal a prioridade do container
	delay(500);
}

// Funcao para permitir que o usuario escolha se deseja adicionar ou remover um container
void add_remove_container() {
	lcd.clear();
    lcd.setCursor(0, 0);
	lcd.print("CONTAINER");

	if ((analogRead(0)) < 800) { // SELECT
		// Setando as variaveis para nao passar mais aqui e definir para onde deve ir
		select_add_remove_container = option_manual_automatico;
	}
	// Limitando as escolhas para 1 ou 2, nao eh possivel escolher outra.
	else if ((analogRead(0)) < 200) { // UP
		if (option_add_remove_container == 1) {
			option_add_remove_container = option_add_remove_container + 1;
			lcd.setCursor(0, 1);
			lcd.print("REMOVER");
		}
	}
	else if ((analogRead(0)) < 400) { // DOWN
		if (option_add_remove_container == 2) {
			option_add_remove_container = option_add_remove_container - 1;
			lcd.setCursor(0, 1);
			lcd.print("ADICIONAR");
		}
	}
	delay(100);
}

// Funcao que vai preparar a esturura de dados para o algoritmo, caso seja escolhido o modo automatico
void add_container_algorithm() {
	// Cria o patio (matriz) de 4 linhas e 5 colunas
	pilha** patio[4][5];

    for (int i = 0; i < 5; i++)
        patio[i] = createStack(4); //cria pilhas de altura 4

// ---------------- FAZER A CHAMADA DA API AQUI PARA POPULAR O PATIO E O ALGORITMO SABER ONDE COLOCAR ----------------------

	// Se puder inserir o container
	if (can_add_container(patio)) {
		// Chamada da funcao do algoritmo implementado em "algoritmo_ordenacao.h"
		add_container(patio, prioridade_container);

		// ---------------- ELE TAMBEM PRECISA SABER MEXER A GARRA HAHAHAHA ----------------------

		// ---------------- O ALGORITMO PRECISA RETORNAR O LOCAL ONDE FOI COLOCADO, LINHA x COLUNA ----------------------

		// ---------------- FAZER A CHAMADA DA API FALANDO Q ESSE CONTAINER FOI INSERIDO NA LINHA x E COLUNA y ----------------------
	}

	// Terminou o conjunto de acoes de inserir.
	selected = -1;
}

// Funcao que vai preparar a esturura de dados para o algoritmo, caso seja escolhido o modo automatico
void remove_container_algorithm() {
	// Cria o patio (matriz) de 4 linhas e 5 colunas
	pilha** patio[4][5];

    for (int i = 0; i < 5; i++)
        patio[i] = createStack(4); //cria pilhas de altura 4

// ---------------- FAZER A CHAMADA DA API AQUI PARA POPULAR O PATIO E O ALGORITMO SABER ONDE COLOCAR ----------------------

	// Chamada da funcao do algoritmo implementado em "algoritmo_ordenacao.h"
	rm_container(patio, container_id);

	// ---------------- ELE TAMBEM PRECISA SABER MEXER A GARRA HAHAHAHA ----------------------

	// ---------------- O ALGORITMO PRECISA RETORNAR O LOCAL ONDE FOI COLOCADO, LINHA x COLUNA ----------------------

	// ---------------- FAZER A CHAMADA DA API FALANDO Q ESSE CONTAINER FOI INSERIDO NA LINHA x E COLUNA y ----------------------

	// Terminou o conjunto de acoes de remover.
	selected = -1;
}

void loop() {
    Serial.println(analogRead(0));//Exibe a leitura do pino analógico A0 no monitor serial
    delay(100);

	// Esperando o usuario selecionar o select para inicializar o projeto
	if (selected == -1) {
		start_project();
	}
	// Usuario apertou o select e precisa setar a prioridade do container
	else if (selected == 1) {
		set_container_priority();
		show_container_priority();
	}
	// Executar no modo Automatico
	else if (selected == 2 && selected_manual_automatico == 2) {
		// Nao foi selecionado nenhuma opcao ainda
		if (select_add_remove_container == -1)
			add_remove_container();
		// Selecionado para adicionar um container
		else if (select_add_remove_container == 1)
			add_container_algorithm();
		// Selecionado para remover um container mas precisa setar o id do container primeiro
		else if (select_add_remove_container == 2) {
			show_container_id();
			set_container_id();
		}
		// Remove o container selecionado 
		else if (select_add_remove_container == 3)
			rm_container();
	}
	// Executar no modo Manual
	// Prioridade do container setar e usuario pode operar a garra
	else if (selected == 3 && selected_manual_automatico == 1) {
		if ((analogRead(0)) < 80) { //Se a leitura for menor que 80 chama a função right
			right();
		}
		else if ((analogRead(0)) < 200) {//Se a leitura for menor que 200 chama a função up
			up();
		}
		else if ((analogRead(0)) < 400) {//Se a leitura for menor que 400 chama a função down
			down();
		}
		else if ((analogRead(0)) < 600) {//Se a leitura for menor que 600 chama a função left
			left();
		}
		else if ((analogRead(0)) < 800) {//Se a leitura for menor que 800 chama a função select
			select();
		}
	}

    //Gira o motor no sentido horario a 90 graus
    /*for (int i = 0; i <= 3; i++)
    {
        myStepper.step(-512);
        delay(2000);
    }

    //Gira o motor no sentido anti-horario a 120 graus
    for (int i = 0; i <= 2; i++)
    {
        myStepper.step(682);
        delay(2000);
    }

    //Gira o motor no sentido horario, aumentando a
    //velocidade gradativamente
    for (int i = 10; i <= 60; i = i + 10)
    {
        myStepper.setSpeed(i);
        myStepper.step(40 * i);
    }
    delay(2000);
*/
}
