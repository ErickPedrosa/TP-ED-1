#include "sort.h"

//Função de troca de objetos.
void troca(Objeto* vobj, int i, int j){

    Objeto temp = vobj[j];
    vobj[j] = vobj[i];
    vobj[i] = temp;

}

//SelectionSort.
/*
void ordenaPorY(Objeto* vobj, int numObj) {
    for (int i = 0; i < numObj - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < numObj; j++) {
            if (vobj[j].getY() < vobj[min_idx].getY()) {
                min_idx = j;
            }
        }
        
        troca(vobj, i, min_idx);
    }
}
*/

//MergeSort - Função Merge.
void merge(Objeto* vobj, int esquerda, int meio, int direita) {
    int i, j, k;
    int n1 = meio - esquerda + 1;
    int n2 = direita - meio;

    
    Objeto* L = new Objeto[n1];
    Objeto* R = new Objeto[n2];

    for (i = 0; i < n1; i++)
        L[i] = vobj[esquerda + i];
    for (j = 0; j < n2; j++)
        R[j] = vobj[meio + 1 + j];

    i = 0; 
    j = 0; 
    k = esquerda; 

    while (i < n1 && j < n2) {
        if (L[i].getY() <= R[j].getY()) {
            vobj[k] = L[i];
            i++;
        } else {
            vobj[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        vobj[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        vobj[k] = R[j];
        j++;
        k++;
    }
    
    delete[] L;
    delete[] R;
}

//MergeSort - Função Recursiva que quebra o vetor em partes menores.
void mergeSort_recursivo(Objeto* vobj, int esquerda, int direita) {
    if (esquerda < direita) {
        int meio = esquerda + (direita - esquerda) / 2;

        mergeSort_recursivo(vobj, esquerda, meio);
        mergeSort_recursivo(vobj, meio + 1, direita);

        merge(vobj, esquerda, meio, direita);
    }
}

//MergeSort - Função que faz a chamada da função recursiva.
void ordenaPorY(Objeto* vobj, int numObj) {
    if (vobj == nullptr || numObj <= 1) {
        return; 
    }
    mergeSort_recursivo(vobj, 0, numObj - 1);
}



//InsertionSort
void ordenaPorId(SegmentoVisivel segmentos[], int numSegmentos) {
    
    for (int i = 1; i < numSegmentos; i++) {
        SegmentoVisivel chave = segmentos[i];
        int j = i - 1;

        while (j >= 0 && segmentos[j].idObjeto > chave.idObjeto) {
            segmentos[j + 1] = segmentos[j];
            j = j - 1;
        }

        segmentos[j + 1] = chave;
    }
}
    