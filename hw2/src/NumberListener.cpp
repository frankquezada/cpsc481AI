#include <iostream>
#include "AddStruct.h"
using namespace std;

void listen(sum *&head, int &addition){
	sum *temp = head;
	for (int i = 0; i < 5; i++){
		sum *traverse = temp -> next;
		while (traverse != NULL){
			if (temp -> add == traverse -> add){
				temp->unique = 	 false;			
			}
			traverse = traverse -> next;		
		}
	temp = temp->next;
	}

	sum *traverse = head;
	while (traverse != NULL){
		if(traverse -> unique == true){
			addition += traverse -> add;		
		}
	traverse = traverse -> next;
	}


}
