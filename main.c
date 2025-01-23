#include<stdio.h>
#include <malloc.h>
#include <string.h>
struct pass_records {
	int age;
	char gender;
	char tclass;
	int seat;
	struct pass_records *next;
};
struct pass_records * head,*temp,*mover,*ptr,*senior_fc,*women_fc,*senior_ec,*women_ec,*others_fc,*others_ec;
void assign(struct pass_records *temp){
	ptr=(struct pass_records *)malloc(sizeof(struct pass_records));
	ptr->age=temp->age;
	ptr->gender=temp->gender;
	ptr->tclass=temp->tclass;
	ptr->seat=temp->seat;
	ptr->next=NULL;	
}
void assign_locator(struct pass_records *ptr,struct pass_records *temp){
	ptr->age=temp->age;	
	ptr->gender=temp->gender;	
	ptr->tclass=temp->tclass;	
	ptr->seat=temp->seat;	
	ptr->next=NULL;
}
void insert(){
	temp=head;
	while (temp!=NULL){
		if (temp->age>60 && temp->tclass=='F'){
			if (senior_fc!=NULL){
				mover=senior_fc;
				while (mover->next!=NULL)
					mover=mover->next;
				assign(temp);
				mover->next=ptr;
			}
			else{
				senior_fc=(struct pass_records *)malloc(sizeof(struct pass_records));
				assign_locator(senior_fc,temp);
			}	  
		}
		else if (temp->age<=60 && temp->tclass=='F'&& temp->gender=='F'){
			if (women_fc!=NULL){
				mover=women_fc;
				while (mover->next!=NULL)
					mover=mover->next;
				assign(temp);	
				mover->next=ptr;			
			}
			else{
				women_fc=(struct pass_records *)malloc(sizeof(struct pass_records));
				assign_locator(women_fc,temp);
			}		
		}
		if (temp->age>60 && temp->tclass=='E'){
			if (senior_ec!=NULL){
				mover=senior_ec;
				while (mover->next!=NULL)
					mover=mover->next;
				assign(temp);	
				mover->next=ptr;		
			}
			else{
				senior_ec=(struct pass_records *)malloc(sizeof(struct pass_records));
				assign_locator(senior_ec,temp);
			}
		}
		else if (temp->age<=60 && temp->tclass=='E'&& temp->gender=='F'){
			if (women_ec!=NULL){
				mover=women_ec;
				while (mover->next!=NULL)
					mover=mover->next;
				assign(temp);
				mover->next=ptr;
			}
			else{
				women_ec=(struct pass_records *)malloc(sizeof(struct pass_records));
				assign_locator(women_ec,temp);
			}
		}
		else if (temp->tclass=='F' && temp->age <=60 && temp->gender!='F'){
			if (others_fc!=NULL){
				mover=others_fc;
				while (mover->next!=NULL)
					mover=mover->next;
				assign(temp);
				mover->next=ptr;		
			}
			else{
				others_fc=(struct pass_records *)malloc(sizeof(struct pass_records));
				assign_locator(others_fc,temp);
			}	
		}
		else if(temp->tclass=='E' && temp->age <=60 && temp->gender!='F'){
			if (others_ec!=NULL){
				mover=others_ec;
				while(mover->next!=NULL)
					mover=mover->next;
				assign(temp);	
				mover->next=ptr;		
			}
			else{
				others_ec=(struct pass_records *)malloc(sizeof(struct pass_records));
				assign_locator(others_ec,temp);
			}
		}
		temp=temp->next;
	}
	temp=senior_fc;
	while(temp->next!=NULL)
		temp=temp->next;
	temp->next=women_fc;
	temp=women_fc;
	while(temp->next!=NULL)
		temp=temp->next;
	temp->next=senior_ec;
	temp=senior_ec;
	while(temp->next!=NULL)
		temp=temp->next;
	temp->next=women_ec;
	temp=women_ec;
	while(temp->next!=NULL)
		temp=temp->next;
	temp->next=others_fc;
	temp=others_fc;
	while(temp->next!=NULL)
		temp=temp->next;
	temp->next=others_ec;
}
void free_memory(){
	temp=head;
	while(temp!=NULL){
		mover=temp;
		temp=temp->next;
		free(mover);
	}
}
void push(int age,char gender,char tclass,int seat){
	temp=(struct pass_records *)malloc(sizeof(struct pass_records));
	temp->age=age;
	temp->gender=gender;
	temp->tclass=tclass;
	temp->seat=seat;
	temp->next=NULL;
	if (head!=NULL)
		temp->next=head;
	head=temp;
}
void swap(struct pass_records *mover,struct pass_records *ptr){
	temp=(struct pass_records *)malloc(sizeof(struct pass_records));
	temp->age=mover->age;
	mover->age=ptr->age;
	ptr->age=temp->age;	
	temp->tclass=mover->tclass;
	mover->tclass=ptr->tclass;
	ptr->tclass=temp->tclass;
	temp->gender=mover->gender;
	mover->gender=ptr->gender;
	ptr->gender=temp->gender;	
	temp->seat=mover->seat;
	mover->seat=ptr->seat;
	ptr->seat=temp->seat;
}
void sub_sort(struct pass_records *start,struct pass_records *end){
	mover=start;
	while(mover!=end){
		ptr=mover->next;
		while (ptr!=end){
			if (mover->seat>ptr->seat)
				swap(mover,ptr);
			ptr=ptr->next;	
		}
		mover=mover->next;
	}
}
void sort(){
	sub_sort(senior_fc,women_fc);
	sub_sort(women_fc,senior_ec);
	sub_sort(senior_ec,women_ec);
	sub_sort(women_ec,others_fc);
	sub_sort(others_fc,others_ec);
	sub_sort(others_ec,NULL);	
}

void main (){
	head=senior_fc=women_fc=senior_ec=women_ec=others_fc=others_ec=NULL;
	//Feeding the customer details
	push(10,'F','F',26);push(79,'M','E',34);push(84,'M','E',81);push(25,'M','F',55);
	push(20,'M','F',70);push(90,'F','F',78);push(33,'M','F',63);push(34,'M','F',7);
	push(20,'M','F',76);push(53,'M','E',94);push(30,'F','E',82);push(32,'M','F',74);
	push(22,'M','E',69);push(20,'M','F',62);push(80,'F','E',61);push(20,'M','F',12);
	push(10,'M','E',16);push(71,'M','F',39);push(32,'M','E',96);push(19,'M','F',19);
	push(75,'M','E',18);push(72,'F','E',46);push(26,'M','E',73);push(14,'M','F',37);
	push(34,'M','F',90);push(44,'M','E',98);push(81,'M','F',68);push(37,'M','F',67);
	push(34,'M','F',49);push(33,'F','F',28);push(29,'M','E',80);push(10,'F','E',45);
	push(33,'M','F',99);push(25,'M','F',51);push(18,'M','F',64);
	insert();
	sort();
	free_memory();
	printf("\n----------------------------------------------------------BOARDING SEQUENCE-------------------------------------------------------\n");
}
