#include <stdio.h>
#include <stdlib.h>


int metric0(int num, int lotto[], int size) {
  int count = 0;
  for (int i=0; i < size; i++)
    if (lotto[i] == num)
      count++;
    return count;
}

int metric1(int num, int lotto[], int size) {
  int flag = 0, dn=0;
  for (int i=0; i < size; i++) {
    if (lotto[i] == num){
      flag = 1;
      dn=i/7;
      break;
    }
     if(flag==0)
      dn=10;
  }
  return dn;
}

int metric2(int num, int lotto[], int size) {
    int res = metric0(num, lotto, size)+metric1(num, lotto, size);
  return res;
}

float metric3(int num, int lotto[], int size) {
  float K=size/7;
  if(metric0(num, lotto, size)==0){
    return 0;
  }
  float rd = metric1(num, lotto, size)-K/metric0(num, lotto, size);
  return rd;

}

void bubbleSort(float* metrics, int* nums, int size)  
{  
    
    int i, j, tempn;  
    float tempm;
    for (i = 0; i < size-1; i++){
        for (j = 0; j < size-i-1; j++){  
            if (metrics[j] < metrics[j+1]){
                tempm = metrics[j];
                metrics[j] = metrics[j+1];
                metrics[j+1] = tempm;
                tempn = nums[j];
                nums[j] = nums[j+1];
                nums[j+1] = tempn;
            }  
        }
    }
}  


int main(void) {
  int number, metric, size;
  char filename[50];
  FILE *pointer ;

  scanf("%d %d %s", &number, &metric, &filename[0]);
  
    pointer = fopen(filename,"r");

     size = 10;
    int *numbers = malloc (size * sizeof(int));


  if (pointer == NULL) {
    printf("File Error!");
    return 0;
  }
  if(number<1 || number>49){
      printf("Wrong Input!");
      return 0;
  }
  if(metric<0 || metric>3){
      printf("Wrong Input!");
      return 0;
  }


    int i = 0;
    do{
        numbers[i] = -1;
        fscanf(pointer, "%d,", &numbers[i]);
        i++;
        if(i == size){
            numbers = realloc (numbers, (size+10)*sizeof(int));
        }
    }while(numbers[i-1] != -1);

    size = i-1;
    int limit = 49;
    float metarray[limit];
    int place[limit];
    
    
    for(i=0; i<limit; i++){
      if(metric==0){
        metarray[i] = (float)metric0(i+1, numbers, size);
        place[i] = i+1;
      }
      else if(metric==1){
        metarray[i] = (float)metric1(i+1, numbers, size);
        place[i] = i+1;
      }
      else if(metric==2){
        metarray[i] = (float)metric2(i+1, numbers, size);
        place[i] = i+1;
      }
      else if(metric==3){
        metarray[i] = metric3(i+1, numbers, size);
        place[i] = i+1;
      }
    }
    
    bubbleSort(metarray, place, limit);
    
    for (i = 0; i < number; i++){
        printf("%d ", place[i]);
    }

  return 0;
}
