#include <unistd.h>
#include <sys/wait.h>
#include "leercadena.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

int main(int argc, char* argv[]) {
  char command[256];
  char **comando;
  char* bg_process_list[3] = {"","",""}; 
  int id_bgProcess[3]={0,0,0}; //Array en donde se guardaran los ID de los procesos en background
 	while (1) {
    printf("> ");
    leer_de_teclado(256, command);
    comando = de_cadena_a_vector(command);
    int size_v = my_size(comando);
    if (strcmp(command,"salir") == 0) break;
    //Mira si es background y guarda el nombre del proceso
    if(is_bg(comando,size_v) != -1){
        for(int i=0;i<3;i++){
          if(strcmp(bg_process_list[i],"") == 0){
             bg_process_list[i] = nombre_tarea(comando,size_v);
             break;
          }
        }
      comando[size_v - 1]=NULL;
    }else if (strcmp(comando[0],"detener") == 0){  //Funcion de detener
      printf("El proceso con id %s fue asesinado \n", comando[1]);
      for (int l=0;l<3;l++){
        if(id_bgProcess[l]==atoi(comando[1])){
          id_bgProcess[l]=0;
          break;
        }
      }
      kill(atoi(comando[1]),15);
    //lista las tareas en background con su respectivo id
    }else if (strcmp(command,"tareas") == 0){
      for(int i=0;i<3;i++){
        if(strcmp(bg_process_list[i],"") != 0 && id_bgProcess[i]!=0){
          printf ("%s [ %d ]\n",bg_process_list[i],         
             id_bgProcess[i]);
        }
      }
    }
  pid_t rc = fork();
  assert(rc >= 0);
  if (rc == 0){ 
    execvp(comando[0], comando); 
    exit(EXIT_FAILURE);
  }else{ 
    if(bg== 1){
       for (int h=0;h<3;h++){
            if(id_bgProcess[h]==0){
              id_bgProcess[h]=rc;
              break;
              }
        }
      bg=0;
      signal(SIGCHLD, SIG_IGN);
    }else
      wait(NULL); 
    }
  }
    return 0;
}