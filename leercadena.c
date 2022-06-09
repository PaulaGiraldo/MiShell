/*
 * Este programa muestra como leer varias palabras del teclado (stdin)
 * Codigo tomado de: https://www.programiz.com/c-programming/c-strings
 *
 * Modificado por: John Sanabria - john.sanabria@correounivalle.edu.co
 * Fecha: 2021-02-26
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leercadena.h"

int bg=0;

int my_size(char** lista){
  int contador =0;
  for(int i=0;i<13;i++){
    if(lista[i] != NULL){
      contador++;
    }else break;
  }
  return contador;
}

int is_bg(char** lista, int size_v){
  int index = -1;
  for (int i = 0 ; i < size_v; i++){
    if (strcmp(lista[i],"&") == 0){
        index = i;
        bg = 1;
        break;
    } 
    
  }

  return index;
}

char* nombre_tarea(char** comando, int size_v){
  char* nombre;
  nombre = *comando;
  for(int i=0;i<size_v-2;i++){
    strcat(nombre," ");
    strcat(nombre,comando[i+1]);
    printf("%s\n",nombre);
  }
  return nombre;
}

/**
 * Lee un cadena por teclado.
 * @param[in] size tamano del buffer representado en cadena
 * @param[in] cadena buffer donde se almacenara lo leido de teclado
 * @param[out] tamano de la cadena leida
*/

int leer_de_teclado(int size, char* cadena) {
  fgets(cadena, size, stdin);
  cadena[strlen(cadena) - 1] = '\x0';

  return strlen(cadena);
}

char** de_cadena_a_vector(char* cadena) {
  int i;
  char *token;
  char *delim = " ";
  char** resultado;

  resultado = (char**)malloc(sizeof(char*));
  assert(resultado != NULL);
  i = 0;
  token = strtok(cadena,delim);
  while ( token != NULL) {
    int cad_longitud;
    char **result_temp;
    cad_longitud = strlen(token) + 1;
    // Copiar token en la posicion 'i'
    resultado[i] = strdup(token);
    //printf("|%s|\n",resultado[i]); fflush(stdout);
    // En busca de la proxima cadena
    token = strtok(NULL, delim);
    i++;
    result_temp = realloc(resultado, (i + 1)  * sizeof(*resultado));
    assert(result_temp != NULL);
    resultado = result_temp;
  }

  resultado[i] = NULL;
  return resultado;
}
