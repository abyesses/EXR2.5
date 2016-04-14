//
//  main.c
//  omp_ej2
//
//  Created by Abraham Esses on 4/14/16.
//  Copyright © 2016 Abraham Esses. All rights reserved.
//

#include<omp.h>
#include<stdio.h>
int main()
{
    int tid,nthreads;
    int variable_inc = 0;
    #pragma omp parallel
    {
        #pragma omp sections shared(variable_inc) private(tid)
        {
            #pragma omp section
            {
                #pragma omp critical
                {
                    #pragma omp parallel num_threads(4)
                    {
                        tid = omp_get_thread_num();
                        printf("\nprueba");
                        if(tid == 0)
                        {
                            nthreads=omp_get_num_threads();
                            printf("\nNT: %d",nthreads);
                        }
                        #pragma omp atomic
                            variable_inc++;
                    }
                }
            }
            #pragma omp section
            {
                int * array = (int *)malloc(sizeof(int)*6);
                #pragma omp parallel num_threads(6)
                {
                    #pragma omp parallel for
                    for(int i = 0; i < 6; i++){
                        array[i] = rand()%10;
                        printf("Array[%d]: %d\n",i,array[i]);
                    }
                    #pragma omp barrier
                    {
                        #pragma omp master{
                            int acum = 0;
                            for (int j = 0;j < 6; j++){
                                acum += array[i];
                            }
                            printf("Sumatoria: %d\n",acum);
                            printf("Promedio: %d\n",acum/6);
                            free(array);
                        }
                    }
                }
            }
        }

    }
    return 0;
}