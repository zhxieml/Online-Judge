template <class Type>
int binarySearch(const vector<Type> &data, 
                            const Type &x) 
{ int low = 1,  high = data.size() - 1, mid;
  while (low <= high )            //查找区间存在
   { mid = (low + high) / 2;      //计算中间位置
      if ( x == data[mid] )  return mid; 
      if ( x < data[mid]) high = mid - 1; 
             else low = mid + 1;
   }
  return 0;
} 
