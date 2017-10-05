#include <iostream>
#include "AddStruct.h"
using namespace std;

void publish(sum *&head){
	sum *current = NULL;

	std::cout << "Enter 5 numbers from 0 - 100 and unique numbers will be added: ";
	for (int i = 0; i < 5; i++){
		sum *temp = new sum;
		cin >> temp -> add;
		while (temp->add< 0 || temp->add > 100){
			cout << "Input number not in range. Submit again correctly: ";
			cin >> temp -> add;
		}
		temp -> unique = true;
		temp -> next = NULL;
		if (head == NULL){
			head = temp;
			current = temp;
		}
		else{
			current -> next = temp;
			current = temp;	
		}
	}
}

