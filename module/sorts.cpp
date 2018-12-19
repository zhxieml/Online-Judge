template <class T>
void simpleInsertSort(T a[], int size)
{int k;
 T tmp;
 for (int j=1; j<size; ++j) {
     tmp = a[j];
     for ( k = j-1; tmp < a[k] && k >= 0; --k)
     a[k+1] = a[k];
     a[k+1] = tmp;
    }
} 

template <class T>
void shellSort(T a[], int size)
{int step, i, j;
 T tmp;
 for (step = size/2; step > 0; step /= 2)  //step为希尔增量
      for (i = step; i < size; ++i) {
	 tmp = a[i];
	 for (j = i - step; j >= 0 && a[j] > tmp;  j -= step) 
  	       a[j+step] = a[j];
	 a[j+step] = tmp;
         }
} 

template <class T>
void simpleSelectSort(T a[], int size)
{int  i, j, k; //k记录选择过程中最小元素的位置
 T tmp;
 for (i = 0; i < size -1; ++i) {
	 k = i;
	 for (j = i+1; j < size; ++j)
		 if (a[j] < a[k]) k = j;
	 tmp = a[i]; a[i] = a[k]; a[k] = tmp;
 }
} 

template <class T>
void bubbleSort(T a[], int size)
{  int i, j;
   T tmp;
   bool flag; //记录一趟起泡中有没有发生过交换
   for (i = 1; i < size; ++i) {
      flag = false;
      for (j = 0; j < size-i; ++j)
        if (a[j+1] < a[j])
          {tmp = a[j]; a[j] = a[j+1]; a[j+1] = tmp; flag = true;}
	  if (!flag) break;
     }
  } 
