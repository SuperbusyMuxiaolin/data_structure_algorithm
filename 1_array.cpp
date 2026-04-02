#include <iostream>


void insert(int *arr, int index, int value, int size){
    for(int j=size-1;j>index;j--){
        arr[j]=arr[j-1];
    }
    arr[index]= value;
}
void test01(){
    int arr[3]={1,2,3};
    insert(arr, 2,10,3);
    for(int i=0;i<3;i++){
        std::cout<<arr[i]<<"";
    }
    std::cout<<std::endl;
}
int main(){
    test01();
}