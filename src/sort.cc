#include "sort.h"

void troca(Objeto* vobj, int i, int j){

    Objeto temp = vobj[j];
    vobj[j] = vobj[i];
    vobj[i] = temp;

}

//SelectionSort
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
