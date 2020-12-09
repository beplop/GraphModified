#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main(void) {
    int directed = 0;// ориентированность графа
    int is_weight = 0;// взвешенность графа
    int c;
    int vertices = 0;// кол-во вершин (кружки)
    int edges = 0;// кол-во ребер (палочки)
    int del = -1;
    int exit = 0;
    int num = 0;
    int num_max = 0;
    int position [25];
    int count = 1;

    FILE* MatrF = fopen("matr.txt", "r");
    if (MatrF == NULL) {
        printf("No such File!!!");
    }
    else {
        printf("File is read successfully!\n"); 
        while (!feof(MatrF)) {                // подсчет вершин (кружочки)
            if ((fgetc(MatrF)) == ';') {
                vertices++;
            }
        }
        fclose(MatrF);
        FILE* MatrFile = fopen("matr.txt", "r");  
        while ((c = fgetc(MatrFile)) != ';') {      //подсчет ребер (палочки)
            if (c == ',')
                edges++;
        }
        edges++;
        fclose(MatrFile);
 
        while (exit == 0)
        {
            int matrix[vertices][edges];
            if (del!= -1)
            {
                MatrFile = fopen("matr.txt", "r");  // считывание всей матрицы
                for (int i = 0; i < vertices; i++) {
                    int j = 0;
                    while ((c = fgetc(MatrFile)) != ';')
                        fscanf(MatrFile, "%d", &matrix[i][j++]);
                }
                fclose(MatrFile);

                MatrFile = fopen("matr.txt", "w");  // запись в матрицу
                for (int i = 0; i < vertices; i++) {
                    int j = 0;
                    while (j < edges) {
                        if (j == del)
                        {
                            j++;
                        }
                       
                        fprintf(MatrFile, " %d", matrix[i][j++]);
                        if (j == edges )
                        {
                            fprintf(MatrFile, ";\n");
                        }
                        else
                        {
                            fprintf(MatrFile, ",");
                        }
                    }
                }
                fclose(MatrFile);
                --edges;
                del = -1;
            }

        MatrFile = fopen("matr.txt", "r");  // считывание всей матрицы
        for (int i = 0; i < vertices; i++) {
            int j = 0;
            while ((c = fgetc(MatrFile)) != ';')
                fscanf(MatrFile, "%d", &matrix[i][j++]);
        }
        fclose(MatrFile);

        for (int i = 0; i < vertices; i++) {    //првоерка на ориентированность графа и взвешенность
            for (int j = 0; j < edges; j++) {
                printf("%d ", matrix[i][j]);
                if (matrix[i][j] > 1)
                    is_weight = 1;
                if (matrix[i][j] < 0)
                    directed = 1;
            }
            printf("\n");
        }
        char weight[edges];// массив взвешенных узлов
        if (is_weight) {
            for (int j = 0; j < edges; j++) {
                for (int i = 0; i < edges; i++) {
                    if (matrix[i][j] > 0)
                        weight[j] = matrix[i][j];
                }
                printf("%d - %d\n", j, weight[j]);
            }
        }
        
            char VertNames[vertices]; // массив вершин
            for (int i = 0; i < vertices; i++)
                VertNames[i] = 'a' + i;
            char Connect[edges][2];// массив соединенных вершин
            for (int j = 0; j < edges; j++) {
                int k = 0;
                for (int i = 0; i < vertices; i++) {
                    if (matrix[i][j] < 0)
                        Connect[j][1] = VertNames[i];
                    if (matrix[i][j] > 0)
                        Connect[j][k++] = VertNames[i];
                }
            }

            FILE* GraphF = fopen("graph.dot", "w");
            if (GraphF == NULL) {
                printf("Problem with making a file");
            }
            else {
                printf("Graph file is made successfully!\n");
                if (directed)
                    fprintf(GraphF, "di");
                fprintf(GraphF, "graph Test {\n");
                for (int i = 0; i < edges; i++) {
                    if (!directed) {
                        fprintf(GraphF, "%c -- %c ", Connect[i][0], Connect[i][1]);
                        if (!is_weight) { fprintf(GraphF, ";\n"); }
                    }
                    else {
                        fprintf(GraphF, "%c -> %c ", Connect[i][0], Connect[i][1]);
                        if (!is_weight) { fprintf(GraphF, ";\n"); }
                    }
                    if (is_weight)
                        fprintf(GraphF, "[label = %d] \n", weight[i]);
                }
                fprintf(GraphF, "}\n");
                fclose(GraphF);
                system("dot -Tpng graph.dot -o graph.png");
            }

                printf("\n");
                for (int i = 0; i < edges; i++) {
                    printf("%d) ", i);
                    for (int j = 0; j < 2; j++) {
                        if (!Connect[i][j]) {
                            Connect[i][j] = Connect[i][j - 1];
                        }
                        printf("%c ", Connect[i][j]);
                    }
                    printf("\n");
                }

                putchar('\n');
                printf("Choose:\n1)visualize graph\n2)delete edge\n3)Search for the vertice with maximum degree\n4)exit\n>>");
                int navigate;
                scanf("%d", &navigate);

                switch (navigate)
                {

                case 1:

                    system("cygstart graph.png");

                    putchar('\n');
                    printf("------------------------------------------\n");
                    break;

                case 2:
                    printf("Enter number of edge for delete:\n>>");
                    
                    
                    scanf("%d", &del);
                    printf("------------------------------------------\n");
                   
                    break;

                case 3: //степень вершины - это число выходящих из нее рёбер
                    
                    for (int j = 0; j < vertices; j++) {
                        for (int k = 0; k < 2; k++)
                        {
                            for (int i = 0; i < edges; i++) {
                                if (Connect[i][k] == VertNames[j])
                                {
                                    num++;

                                }
                                if (num > num_max)
                                {
                                        num_max = num;
                                        position[0] = j;
                                }
                            }
                        }
                        num = 0;
                    }
                    int n = 1;
                            
                            for (int j = 0; j < vertices; j++) {
                                
                                for (int k = 0; k < 2; k++)
                                {
                                    for (int i = 0; i < edges; i++) {
                                        if (Connect[i][k] == VertNames[j])
                                        {
                                            num++;

                                        }
                                        
                                    }
                                }
                                if (num == num_max)
                                {
                                    if (VertNames[j] != VertNames[position[0]])
                                    {
                                        position[n] = j;
                                        n++;
                                        count++;
                                    }
                                }
                               num = 0;
                            }
                        
                        putchar('\n');
                        if (count == 1)
                        {
                            printf("Vertice with maximum degree: %c\n", VertNames[position[0]]);
                        }
                        else
                        {
                            printf("There are multiple vertices with maximum degree or all vertices have the same degree:\n");
                            for (int i = 0; i < count; i++)
                            {
                                printf("%d) ", i + 1);
                                printf("Vertice with maximum degree: %c\n", VertNames[position[i]]);
                            }
                        }
                        printf("------------------------------------------\n");
                        Sleep(5000);
                        count = 1;
                        num_max = 0;
                    break;
                
                case 4:
                    exit = 1;
                    break;
                }
            
        }
    }
    return 0;
}
