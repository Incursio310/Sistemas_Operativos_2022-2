void imprimir(int nine_tri, int nine_six, int nine_nine, int zero_tri, int zero_six, int zero_nine, int one_tri, int one_six, int one_nine){


    printf("La cantidad de estudiantes de 2019 son: %d\n", (nine_tri+nine_six+nine_nine));
    printf("        La cantidad de estudiantes de 2019 con prioridad 3000-5999 son: %d\n", nine_tri);
    printf("        La cantidad de estudiantes de 2019 con prioridad 6000-8999 son: %d\n", nine_six);
    printf("        La cantidad de estudiantes de 2019 con prioridad 9000+ son: %d\n\n", nine_nine);

    printf("La cantidad de estudiantes de 2020 son: %d\n", (zero_tri+zero_six+zero_nine));
    printf("        La cantidad de estudiantes de 2020 con prioridad 3000-5999 son: %d\n", zero_tri);
    printf("        La cantidad de estudiantes de 2020 con prioridad 6000-8999 son: %d\n", zero_six);
    printf("        La cantidad de estudiantes de 2020 con prioridad 9000+ son: %d\n\n", zero_nine);

    printf("La cantidad de estudiantes de 2021 son: %d\n", (one_tri+one_six+one_nine));
    printf("        La cantidad de estudiantes de 2021 con prioridad 3000-5999 son: %d\n", one_tri);
    printf("        La cantidad de estudiantes de 2021 con prioridad 6000-8999 son: %d\n", one_six);
    printf("        La cantidad de estudiantes de 2021 con prioridad 9000+ son: %d\n", one_nine);
}