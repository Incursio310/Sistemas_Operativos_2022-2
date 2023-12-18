#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include "Imprimir.h"

int main(void) {
    mkdir("2019", S_IRWXU);
    mkdir("2020", S_IRWXU);
    mkdir("2021", S_IRWXU);

    char directory1[100];
    getcwd(directory1, 100);

    chdir(strcat(directory1, "/2019"));

    getcwd(directory1, 100);

    mkdir("3000+", S_IRWXU);
    mkdir("6000+", S_IRWXU);
    mkdir("9000+", S_IRWXU);

//---------------------------------------

    char directory2[100];
    chdir("..");

    getcwd(directory2, 100);

    chdir(strcat(directory2, "/2020"));

    getcwd(directory2, 100);

    mkdir("3000+", S_IRWXU);
    mkdir("6000+", S_IRWXU);
    mkdir("9000+", S_IRWXU);

//---------------------------------------

    char directory3[100];
    chdir("..");

    getcwd(directory3, 100);

    chdir(strcat(directory3, "/2021"));

    getcwd(directory3, 100);

    mkdir("3000+", S_IRWXU);
    mkdir("6000+", S_IRWXU);
    mkdir("9000+", S_IRWXU);

    chdir("..");

    getcwd(directory3, 100);
    char directory4[100];
    getcwd(directory4, 100);

    chdir(strcat(directory3, "/alumnos"));

//----------------------------------------

    DIR *folder;
    struct dirent *entry;
    int files = 0;

    folder = opendir(directory3);
    if(folder == NULL)
    {
        perror("Unable to read directory");
        return(1);
    }

    char *nombre_archivo;
    char agno[25];
    char prioridad[25];
    FILE *fp;

    int nine_tri = 0, nine_six = 0, nine_nine = 0, zero_tri = 0, zero_six = 0, zero_nine = 0, one_tri = 0, one_six = 0, one_nine = 0;

    while( (entry=readdir(folder)) ){
        if(entry->d_type == 8){
            files++;

            nombre_archivo = entry->d_name;
            fp = fopen(nombre_archivo, "r");

            if(fp == NULL){
                fprintf(stderr, "Error al abrir el archivo");
                exit(1);
            }

            while(feof(fp) == 0){
                fgets(agno, 25, fp);
                fgets(prioridad, 25, fp);
            }

            fclose(fp);

            char pathsystem[150];

            if(atoi(agno) == 2019){
                if(atoi(prioridad)<6000){
                    strcat(pathsystem, "mv ");
                    strcat(pathsystem, nombre_archivo);
                    strcat(pathsystem, " ../2019/3000+/");
                    strcat(pathsystem, nombre_archivo);
                    system(pathsystem);
                    strcpy(pathsystem, "");
                    nine_tri += 1;
                }
                else if(atoi(prioridad)<9000){
                    strcat(pathsystem, "mv ");
                    strcat(pathsystem, nombre_archivo);
                    strcat(pathsystem, " ../2019/6000+/");
                    strcat(pathsystem, nombre_archivo);
                    system(pathsystem);
                    strcpy(pathsystem, "");
                    nine_six += 1;
                }
                else{
                    strcat(pathsystem, "mv ");
                    strcat(pathsystem, nombre_archivo);
                    strcat(pathsystem, " ../2019/9000+/");
                    strcat(pathsystem, nombre_archivo);
                    system(pathsystem);
                    strcpy(pathsystem, "");
                    nine_nine += 1;
                }
            }
            else if(atoi(agno) == 2020){
                if(atoi(prioridad)<6000){
                    strcat(pathsystem, "mv ");
                    strcat(pathsystem, nombre_archivo);
                    strcat(pathsystem, " ../2020/3000+/");
                    strcat(pathsystem, nombre_archivo);
                    system(pathsystem);
                    strcpy(pathsystem, "");
                    zero_tri += 1;
                }
                else if(atoi(prioridad)<9000){
                    strcat(pathsystem, "mv ");
                    strcat(pathsystem, nombre_archivo);
                    strcat(pathsystem, " ../2020/6000+/");
                    strcat(pathsystem, nombre_archivo);
                    system(pathsystem);
                    strcpy(pathsystem, "");
                    zero_six += 1;
                }
                else{
                    strcat(pathsystem, "mv ");
                    strcat(pathsystem, nombre_archivo);
                    strcat(pathsystem, " ../2020/9000+/");
                    strcat(pathsystem, nombre_archivo);
                    system(pathsystem);
                    strcpy(pathsystem, "");
                    zero_nine += 1;
                }
            }
            else{
                if(atoi(prioridad)<6000){
                    strcat(pathsystem, "mv ");
                    strcat(pathsystem, nombre_archivo);
                    strcat(pathsystem, " ../2021/3000+/");
                    strcat(pathsystem, nombre_archivo);
                    system(pathsystem);
                    strcpy(pathsystem, "");
                    one_tri += 1;
                }
                else if(atoi(prioridad)<9000){
                    strcat(pathsystem, "mv ");
                    strcat(pathsystem, nombre_archivo);
                    strcat(pathsystem, " ../2021/6000+/");
                    strcat(pathsystem, nombre_archivo);
                    system(pathsystem);
                    strcpy(pathsystem, "");
                    one_six += 1;
                }
                else{
                    strcat(pathsystem, "mv ");
                    strcat(pathsystem, nombre_archivo);
                    strcat(pathsystem, " ../2021/9000+/");
                    strcat(pathsystem, nombre_archivo);
                    system(pathsystem);
                    strcpy(pathsystem, "");
                    one_nine += 1;
                }
            }
        }
    }

    closedir(folder);

    imprimir(nine_tri, nine_six, nine_nine, zero_tri, zero_six, zero_nine, one_tri, one_six, one_nine);

    return 0;
}