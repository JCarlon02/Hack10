/*
* Author: Jayden Carlon. Worked with Dalton and Parker.
* This program takes the first input of a file containing
* a DNA sequence and the second is the name of the output
* file.
* Date: 11/04/2019
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "protein_utils.h"

int main(int argc, char **argv) {

  char *inputFile = argv[1];
  char *fileToCreate = argv[2];

  if(argc > 3){
    return 1;
  }


  FILE *dnaFile;
  dnaFile = fopen(inputFile, "r");
  FILE *proteinFile;
  proteinFile = fopen(fileToCreate, "w");
  if(dnaFile == NULL){
    return 1;
  }


  int countB = 0;
  while(fgetc(dnaFile) != EOF){
    countB++;
  }

  rewind(dnaFile);

  char *dna;
  dna = (char *) malloc(sizeof(char) * (countB + 1));
  dna[countB] = '\0';

  char c;
  int count = 0;
  while((c = fgetc(dnaFile)) != EOF){
    if(c == 'A' || c == 'C' || c == 'G'){
      dna[count] = c;
      count++;
    }else if (c == 'T'){
      dna[count] = 'U';
      count++;
    }
  }

  dna[count] = '\0';
  fclose(dnaFile);

  char **rnaData = (char **) malloc(sizeof(char *) * (count / 3));
  for(int i = 0; i < (count / 3); i++){
    rnaData[i] = (char *) malloc(sizeof(char) * 4);
  }

  int z = 0;
  for(int i = 0; i < (count / 3); i++){
    for(int j = 0; j < 4; j++){
      if(j == 3){
        rnaData[i][j] = '\0';
      }else {
        rnaData[i][j] = dna[z];
        z++;
      }
    }
  }

  int r = 0;
  char protein = ' ';
  while(protein != 'x' || r < (count / 3)){
    protein = rnaToProtein(rnaData[r]);
    if(protein != 'x' && protein != '\0'){
      fprintf(proteinFile, "%c", protein);
      r++;
    } else if(protein == 'x'){
      exit(0);
    } else if(protein == '\0'){
      exit(0);
    }
  }

  fclose(proteinFile);
  free(dna);
  for(int q = 0; q < (count /3); q++){
    free(rnaData[q]);
  }
  free(rnaData);
}
