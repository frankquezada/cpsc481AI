#include <iostream>
#include "AddStruct.h"
using namespace std;

void publish(sum*&);
void listen(sum*&,int&);
int main(){
sum *head = NULL;
int addition = 0;
publish(head);
listen(head,addition);
cout << addition << endl;

}
