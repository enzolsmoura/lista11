#include <stdio.h>
#include <stdlib.h>
#include "../include/sqlite3.h"

/*
 * PERGUNTAS
 *
 * 1) QUANTOS JOGOS HÁ NO BANCO DE DADOS?
 * 2) QUAIS SÃO OS JOGOS MAIS VENDIDOS?
 * 3) QUAIS PLATAFORMAS TEM MAIS JOGOS VENDIDOS?
 * 4) QUAIS GÊNEROS TEM MAIS JOGOS VENDIDOS?
 * 5) QUAIS OS JOGOS MAIS VENDIDOS EM CADA REGIÃO? (NA/EU/JP)
 * 6) QUAIS GÊNEROS MAIS VENDIDOS EM CADA REGIÃO?
 * 7) QUAL REGIÃO CONSOME MAIS JOGOS DO GÊNERO Role-playing?
 *
 */


int main() {
  sqlite3 *db = NULL;
  sqlite3_stmt *stmt = NULL;
  int conexao, i, total;
  printf("Criando conexao com o banco:\n");
  conexao = sqlite3_open("vg_sales.db", &db);
  if (conexao != SQLITE_OK){
    printf("Erro ao conectar ao banco\n");
    exit(-1);
  } 
  printf("Sucesso na conexao!\n");
  sqlite3_prepare(db, "SELECT COUNT() FROM vgsales", -1, &stmt, NULL);
  while (sqlite3_step(stmt) != SQLITE_DONE){
    for (i = 0; i < sqlite3_column_count(stmt); i++)
      printf("Total de jogos no banco de dados: %s\n\n", sqlite3_column_text(stmt, i));
    printf("\n");
  }
  sqlite3_finalize(stmt);
  sqlite3_prepare(db, "SELECT name,global_sales FROM vgsales ORDER BY global_sales DESC LIMIT 10", -1, &stmt, NULL);
  printf("Jogos mais vendidos (Top 10): \n");
  for (i = 0; i < sqlite3_column_count(stmt); i++)
    printf("%s\t", sqlite3_column_name(stmt, i));
  printf("\n");
  while (sqlite3_step(stmt) != SQLITE_DONE){
    for (i = 0; i < sqlite3_column_count(stmt); i++)
      printf("%s\t", sqlite3_column_text(stmt, i));
    printf("\n");
  }

  sqlite3_close(db);

  return 0;
}
