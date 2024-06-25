/* Filipe Resendes 96859 */


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


#define TASK_MAX 10000
#define ID_MAX 9999
#define DESC_CAR 100
#define UTL_CAR 100
#define UTL_MAX 50
#define ATV_CAR 100
#define SID_MAX 6
#define ATV_MAX 10
#define CAR_GRP 100


typedef struct {
	int id;
	char descricao[DESC_CAR];
	char utilizador[UTL_CAR];
	char atividade[ATV_CAR];
	int duracao;
	int instante;
}info;
info tarefa[TASK_MAX];			/* Tabela de tarefas  */ 


int task_id = 0, instante = 0, n_utl = 0, n_atv = 2;
char lista_utl[UTL_MAX][UTL_CAR];
char lista_atv[ATV_MAX][ATV_CAR] = {"TO DO", "IN PROGRESS", "DONE"};


void g(){
	int i, c = 0;
	char nome_grupo[CAR_GRP];
	getchar();
	for (i = 0; (c = getchar()) != '\n';)
		nome_grupo[i++] = c;
	nome_grupo[i] = '\0';
	if (tem_utilizador(nome_grupo))
		printf("user already exists\n");
	else {
		if (n_utl >= UTL_MAX)
			printf("too many users\n");
		else{
			n_utl++;
			strcpy(lista_utl[n_utl], nome_grupo);
		}
	}
	c = getchar();
	i = 0;
	while (c != '\0'){
		c = getchar();
		if (c == ' '){
			i = 0;
			if (!tem_utilizador(nome_utl))
				printf("no such user\n");
		}
		nome_utl[i++] = c;
	}
}




/*
Verfica se tem dada atividade
*/
int tem_atividade(char in_atividade[ATV_CAR]){
	int i;
	for (i = 0; i <= n_atv; i++){
		if (strcmp(lista_atv[i], in_atividade) == 0)
			return 1;
	}
	return 0;
}


/*
Verifica se a atividade tem apenas maiusculas
*/
int so_maiusculas(char in_atividade[ATV_CAR]){
	int i, len_atv;
	len_atv = strlen(in_atividade);
	for(i = 0; i <= len_atv; i++){
		if (in_atividade[i] < 'A' || in_atividade[i] > 'Z')
			return 0;
	}
	return 1;
}


/*
Verifica se tem dado utilizador
*/
int tem_utilizador(char in_utilizador[UTL_CAR]){
	int i;
	for (i = 0; i <= n_utl; i++){
		if (strcmp(lista_utl[i], in_utilizador) == 0)
			return 1;
	}
	return 0;
}


/*
Verifica se tem dada descricao
*/
int tem_descricao(char in_descricao[DESC_CAR]){
	int i;
	for (i = 1; i <= task_id; i++){
		if (strcmp(tarefa[i].descricao, in_descricao) == 0)
			return 1;
	}
	return 0;
}


/*
Adiciona uma atividade ou lista todas as atividades
*/
void a(){
	char in_atividade[ATV_CAR];
	int i, c;
	if (getchar() == '\n')
		for (i = 0; i <= n_atv; i++)
			printf("%s\n", lista_atv[i]);
	else{
		for (i = 0; (c = getchar()) != '\n';)
			in_atividade[i++] = c;
		in_atividade[i] = '\0';
		if (tem_atividade(in_atividade))
			printf("duplicate activity\n");
		else{
			if (so_maiusculas(in_atividade))
				printf("invalid description\n");
			else{
				if (n_atv >= ATV_MAX)
					printf("too many activities\n");
				else{
					n_atv++;
					strcpy(lista_atv[n_atv], in_atividade);
				}
			}
		}
	}
}


/*
Lista ordenadamente as tarefas do comando d
*/
void ordena_instantes(char in_atividade[ATV_CAR]){
	int i, j,temp, run = 1, r = 0;
	int t_atv[ID_MAX];
	for (i = 0; i <= task_id; i++)
		if (strcmp(tarefa[i].atividade, in_atividade) == 0)
			t_atv[r++] = i;
	while (run){
		run = 0;
		for (i = 0; i < r; i++)
			for (j = i; j < r - 1; j++){
				if (tarefa[t_atv[j]].instante > tarefa[t_atv[j+1]].instante){
					temp = t_atv[j];
					t_atv[j] = t_atv[j+1];
					t_atv[j+1] = temp;
					run = 1;
				}
				if (tarefa[t_atv[j]].instante == tarefa[t_atv[j+1]].instante)
					if (strcmp(tarefa[t_atv[j]].descricao, tarefa[t_atv[j+1]].descricao) > 0){
						temp = t_atv[j];
						t_atv[j] = t_atv[j+1];
						t_atv[j+1] = temp;
						run = 1;
					}
			}
	}
	for (i = 0; i < r; i++)
		printf("%d %d %s\n", tarefa[t_atv[i]].id,
		tarefa[t_atv[i]].instante, tarefa[t_atv[i]].descricao);
}


/*
Lista todas as tarefas que estejam numa dada atividade
*/
void d(){
	int i, c;
	char in_atividade[ATV_CAR];
	getchar();
	for (i = 0; (c = getchar()) != '\n';)
		in_atividade[i++] = c;
	in_atividade[i] = '\0';
	if (!(tem_atividade(in_atividade)))
		printf("no such activity\n");
	else{
		ordena_instantes(in_atividade);
	}
}


/*
Move uma tarefa de uma atividade para a outra
*/
void m(){
	int c, i, in_id, duration;
	char in_utilizador[UTL_CAR], in_atividade[ATV_CAR];
	scanf(" %d", &in_id);
	if (in_id > task_id)
		printf("no such task\n");
	else {
		getchar();
		for (i = 0; ((c = getchar()) != ' ');)
			in_utilizador[i++] = c;
		in_utilizador[i] = '\0';
		for (i = 0; ((c = getchar()) != '\n');)
			in_atividade[i++] = c;
		in_atividade[i] = '\0';
		if (strcmp(in_atividade, "TO DO") == 0)
			printf("task already started\n");
		else {
			if (!(tem_utilizador(in_utilizador)))
				printf("no such user\n");
			else {
				if (!(tem_atividade(in_atividade)))
					printf("no such activity\n");
				else{
					if (strcmp(tarefa[in_id].atividade, "TO DO") == 0)
						tarefa[in_id].instante = instante;
					if (strcmp(in_atividade, "DONE") == 0){
						duration = instante - tarefa[in_id].instante;
						printf("duration=%d slack=%d\n", duration, duration - tarefa[in_id].duracao);
						strcpy(tarefa[in_id].atividade, in_atividade);
					}
					strcpy(tarefa[in_id].atividade, in_atividade);
					strcpy(tarefa[in_id].utilizador, in_utilizador);
				}
			}
		}
	}
}


/*
Adiciona um utilizador ou lista todos os utilizadores
*/
void u(){
	int i, c;
	char in_utilizador[UTL_CAR];
	if (getchar() == '\n'){
		for (i = 1; i <= n_utl; i++)
			printf("%s\n", lista_utl[i]);
	}
	else {
		for (i = 0; (c = getchar()) != '\n';)
			in_utilizador[i++] = c;
		in_utilizador[i] = '\0';
		if (tem_utilizador(in_utilizador))
			printf("user already exists\n");
		else {
			if (n_utl >= UTL_MAX)
				printf("too many users\n");
			else{
				n_utl++;
				strcpy(lista_utl[n_utl], in_utilizador);
			}
		}
	}
}


/*
Avanca o tempo do sistema
*/
void n(){
	int in_duracao;
	scanf(" %d", &in_duracao);
	if (in_duracao < 0)
		printf("invalid time\n");
	else{
		instante += in_duracao;
		printf("%d\n", instante);
	}
}


/*
Lista ordenadamente as tarefas do comando l
*/
void ordena_descricoes(){
	int i, j, temp, run = 1;
	int lista_ids[ID_MAX];
	for (i = 0; i < task_id; i++)
		lista_ids[i] = i + 1;
	while (run){
		run = 0;
		for (i = 0; i < task_id; i++)
			for (j = i; j < task_id - 1; j++)
				if (strcmp(tarefa[lista_ids[j]].descricao, tarefa[lista_ids[j+1]].descricao) > 0){
					temp = lista_ids[j];
					lista_ids[j] = lista_ids[j+1];
					lista_ids[j+1] = temp;
					run = 1;
				}
	}
	for (i = 0; i < task_id; i++){
		printf("%d %s #%d %s\n", tarefa[lista_ids[i]].id, 
		tarefa[lista_ids[i]].atividade, tarefa[lista_ids[i]].duracao, 
		tarefa[lista_ids[i]].descricao);
	}
}


/*
lista as tarefas
*/
void l(){
	int c, l = 0, in_id, m;
	char str_id[SID_MAX];
	char* resto[SID_MAX];
	if (getchar() == '\n')
		ordena_descricoes();
	else {
		while ((c = getchar()) != EOF){
			if (c == ' ' || c == '\n'){
				in_id = strtol(str_id, resto, 10);
				if (in_id <= task_id)
					printf("%d %s #%d %s\n", tarefa[in_id].id, 
					tarefa[in_id].atividade, tarefa[in_id].duracao, tarefa[in_id].descricao);
				else
					printf("no such task\n");
				l = 0;
				for (m = 0; m < SID_MAX; m++)
					str_id[m] = '\0';         /* limpa a string */			}
			else
				str_id[l++] = c;
			if (c == '\n')	
				break;
		}
	}
}


/*
adiciona uma nova tarefa ao sistema
*/
void t(){
	int in_duracao, i, c;
	char in_descricao[DESC_CAR];
	scanf(" %d ", &in_duracao);
	if (task_id > ID_MAX)
			printf("too many tasks\n");
	else{
		for (i = 0; (c = getchar()) != '\n';)
			in_descricao[i++] = c;
		in_descricao[i] = '\0';
		if (tem_descricao(in_descricao))
			printf("duplicate description\n");
		else{
			if (in_duracao < 1)
				printf("invalid duration\n");
			else{
				task_id++;
				tarefa[task_id].id = task_id;
				tarefa[task_id].duracao = in_duracao;
				strcpy(tarefa[task_id].descricao, in_descricao);
				strcpy(tarefa[task_id].atividade, "TO DO");
				printf("task %d\n", task_id);
			}
		}
	}
}


int main(){
	int c;
	while ((c = getchar()) != 'q'){	
		if (c == 't')
			t();
		if (c == 'l')
			l();
		if (c == 'n')
			n();
		if (c == 'u')
			u();
		if (c == 'm')
			m();
		if (c == 'd')
			d();
		if (c == 'a')
			a();
		if(c == 'g')
			g();
		}
	return 0;
}