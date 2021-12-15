#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <stdbool.h>

int adminAccess();
void insertVehicle(int *paid,int *unpaid);
void deleteVehicle(int *paid,int *unpaid);
void VehicleInfo(int *p,int *q);     //display
int isEmpty(int facility);
int isFull(int facility);
void isEmptyy(int *p,int *q);
void isFulll(int *p,int *q);
void updateStatus();    //whether vehicle is present or not
void longestStay();     //arrival time - departure time
void uniqueList();
void unionList();
void intersectionList();
void payment();

struct list{
    char Company[10];
    char Modal[30];
    int vehiclenumber; 
    struct list *next;
}*unionFirst;

struct list1{
    char Company[10];
    char Modal[30]; 
}Unique_paid[15], Unique_free[20];

struct vehicle{
    int arrivalTime[2];     // Sorting point; Format(24 Hours)
    int vehicleNumber;  // 4 digit Number
    char modalName[30];
    char companyName[10];
    int paidFacility;
    int departureTime[2];
    int location;
}parking1[15], parking2[20];


int paidParking[15]={0}, freeParking[20]={0};

int adminAccess(){
    char username[10]; 
    char password[6]; 
 
    printf("\n\t\t\t\t\t\t=> WELCOME TO PARKING MANAGEMENT SYSTEM <=\t\t\n");
    printf("\n\nEnter Correct UserName and Password for login\n");
    
    printf("Enter your username : "); 
    scanf("%s",username); 
    
    printf("Enter your password : "); 
    scanf("%s",password); 
    
    if(strcmp(username,"ADMR")==0){
        if(strcmp(password,"admr")==0){ 
        printf("\nPassWord is correct , Welcome to System sir....\n\n"); 
              return 1;
        }
        else {
            printf("PassWord is not correct , Try again\n\n");
            return 0;
        }
    }else{
        printf("Username/Password is not correct , Try again\n\n");
        return 0;
    }
}

void insertVehicle(int *paid, int *unpaid){
    struct vehicle vehicleInfo;
    
    printf("\n\nArrival Time(Format => 24 Hours) : ");  //format(24 Hours)
    scanf("%d %d", &vehicleInfo.arrivalTime[0],&vehicleInfo.arrivalTime[1]);
    
    printf("Enter Company Name : ");
    scanf("%s",vehicleInfo.companyName);
    
    int i;
    for(i=0; vehicleInfo.companyName[i]!='\0'; i++){
        if(vehicleInfo.companyName[i]>='a' && vehicleInfo.companyName[i]<='z')
            vehicleInfo.companyName[i]=vehicleInfo.companyName[i] - 32;
    }
    vehicleInfo.companyName[i]='\0';
    
    printf("Enter Modal Name : ");
    scanf("%s",vehicleInfo.modalName);
    
    for(i=0; vehicleInfo.modalName[i]!='\0'; i++){
        if(vehicleInfo.modalName[i]>='a' && vehicleInfo.modalName[i]<='z')
            vehicleInfo.modalName[i]=vehicleInfo.modalName[i] - 32;
    }
    vehicleInfo.modalName[i]='\0';
    
    printf("Enter Vehicle Number : ");
    scanf("%d", &vehicleInfo.vehicleNumber);
    
    printf("Paid(Press 1) / Free(Press 0) : ");   //paid : 1, free : 0
    scanf("%d", &vehicleInfo.paidFacility);

    if(isFull(vehicleInfo.paidFacility)){
        printf("No Free Slot.");
        return;
    }

    if(vehicleInfo.paidFacility){
        int i;
        printf("Available Slots \n");
        for(i=0; i<15; i++){
            if(*(paid+i) == 0)
                printf("%d ",i+1);
        }
    }

    else{
        int j;
        printf("Available Slots \n");
        for(j=0; j<20; j++){
            if(*(unpaid+j) == 0)
                printf("%d ",j+1);
        }
    }
    
    printf("\nEnter Location from available slots : ");
    scanf("%d", &vehicleInfo.location);

    if(vehicleInfo.paidFacility){
            parking1[vehicleInfo.location-1]=vehicleInfo;
            *(paid + vehicleInfo.location-1)=1;
    }

    else{
        parking2[vehicleInfo.location-1]=vehicleInfo;
        *(unpaid + vehicleInfo.location-1)=1;
    }
}


void deleteVehicle(int *paid, int *unpaid){
    struct vehicle departingVehicleInfo;
    int arrivedTime;
    int vehicleeNumber;
    char modallName[30];
    char companyyName[10];
    int departeeTime;
    
    printf("\nWhere is your car?\nPaid(Press 1)/Free(Press 0) : ");   //paid : 1, free : 0
    scanf("%d", &departingVehicleInfo.paidFacility);
    
    printf("Enter Location at which car was parked : ");
    scanf("%d", &departingVehicleInfo.location);
    
    printf("Enter departure time : ");
    scanf("%d %d",&parking1[(departingVehicleInfo.location)-1].departureTime[0],&parking1[departingVehicleInfo.location-1].departureTime[1]);

    if(departingVehicleInfo.paidFacility){
            if(*(paid + (departingVehicleInfo.location)-1) == 0) {
                printf("\nNo such Car was parked at this location in paid facility.");
            }
            else {                
                printf("\nVehicle %s of model %s with %d (id/number) arrived at %d:%d is departing at %d:%d.\n",parking1[departingVehicleInfo.location-1].companyName,parking1[departingVehicleInfo.location-1].modalName,parking1[departingVehicleInfo.location-1].vehicleNumber,parking1[departingVehicleInfo.location-1].arrivalTime[0],parking1[departingVehicleInfo.location-1].arrivalTime[1],parking1[departingVehicleInfo.location-1].departureTime[0],parking1[departingVehicleInfo.location-1].departureTime[1]);
                payment(parking1[departingVehicleInfo.location-1].arrivalTime[0],parking1[departingVehicleInfo.location-1].arrivalTime[1],parking1[departingVehicleInfo.location-1].departureTime[0],parking1[departingVehicleInfo.location-1].departureTime[1]);
                *(paid + departingVehicleInfo.location-1)=0;
            }
    }
    
    else{
            if(*(unpaid + (departingVehicleInfo.location)-1)==0) {
                printf("\nNo such Car was parked at this location in free facility.");
            }
            else {
                printf("\nVehicle %s of model %s with %d (id/number) arrived at %d:%d is departing at %d:%d.\n",parking2[departingVehicleInfo.location-1].companyName,parking2[departingVehicleInfo.location-1].modalName,parking2[departingVehicleInfo.location-1].vehicleNumber,parking2[departingVehicleInfo.location-1].arrivalTime[0],parking2[departingVehicleInfo.location-1].arrivalTime[1],parking2[departingVehicleInfo.location-1].departureTime[0],parking2[departingVehicleInfo.location-1].departureTime[1]);
                printf("Cost: Rs. 0 (unpaid facility)\n\n");
                *(unpaid + departingVehicleInfo.location-1)=0;
            }
    }
}

void payment(int arr1,int arr2,int dep1,int dep2){
    printf("Charges: Rs. 20 per an Hour.\n");
    int strttime,endtime;
    float cost;    
    strttime=(arr1*60)+arr2;
    endtime=(dep1*60)+dep2;    
    cost=(endtime-strttime)*(0.33);
    printf("Total time: %d:%d\n",(endtime-strttime)/60,(endtime-strttime)%60);
    printf("Your charges: Rs %0.02f\n\n",cost);
}

int isFull(int facility){
    if(facility){
        int i;
        for(i=0; i<15; i++){
            if(paidParking[i]==0)
                return 0;
        }
        return 1;
    }
    else{
        int j;
        for(j=0; j<20; j++){
            if(freeParking[j]==0)
                return 0;
        }
        return 1;
    }
}

void isFulll(int *p,int *q){
    int i,count1=0,count2=0;
    for(i=0;i<15;i++){
        if(*(p+i) == 0){
            printf("\nPaid Parking is not Full.\n");
            break;
        }
        count1++;
    }
    if(count1 == 15) {
        printf("\nPaid Parking is Full.\n");
    }
    for(i=0;i<20;i++){
        if(*(q+i) == 0){
            printf("\nFree Parking is not Full.\n");
            break;
        }
        count2++;
    }
    if(count2 == 20) {
        printf("\nFree Parking is Full.\n");
    }
}

int isEmpty(int facility){
    if(facility){
        int i;
        for(i=0; i<15; i++){
            if(paidParking[i]==1)
                return 0;
        }
        return 1;
    }
    else{
        int j;
        for(j=0; j<20; j++){
            if(freeParking[j]==1)
                return 0;
        }
        return 1;
    }
}

void isEmptyy(int *p,int *q){
    int i,count1=0,count2=0;
    for(i=0;i<15;i++){
        if(*(p+i) == 1){
            printf("\nPaid Parking is not Empty\n");
            break;
        }
        count1++;
    }
    if(count1 == 15) {
        printf("\nPaid Parking is Empty.\n");
    }
    for(i=0;i<20;i++){
        if(*(q+i) == 1){
            printf("\nFree Parking is not EMpty.\n");
            break;
        }
        count2++;
    }
    if(count2 == 20) {
        printf("\nFree Parking is Empty.\n");
    }
}
void VehicleInfo(int *p,int *q)
{
	int i = 0;
	printf("\n\t\t\t\t\t\t########### PARKING STATUS FOR PAID FACILITY ##########\t\t\n");
	for (i = 0; i < 15; i++){
//	if(*(p+i) == 0) {
//	    printf("Display Parking lot status");
//	    printf("\t\t\t----------------------------------------------\n");
//		printf("Location: %d\n",i+1);
//		printf("Vehicle Number: NULL\n");
//		printf("Vehicle Modal Name: NULL\n");
//		printf("Arrival Time: NULL\n");
//		printf("Vehicle Company Name: NULL\n");
//		printf("Parking charges: NULL\n");
//		printf("\t\t\t----------------------------------------------\n");
//	    }
        
	    if(*(p+i) == 1){
        printf("Display Parking lot status");
		printf("\t\t\t----------------------------------------------\n");
		printf("Location: %d\n",i+1);
		printf("Vehicle Number: %d\n", parking1[i].vehicleNumber);
		printf("Vehicle Modal Name: %s\n", parking1[i].modalName);
		printf("Arrival Time: %d:%d\n", parking1[i].arrivalTime[0],parking1[i].arrivalTime[1]);
		printf("Vehicle Company Name: %s\n", parking1[i].companyName);
		printf("\t\t\t----------------------------------------------\n");
	}
	}
	printf("\n\t\t\t\t\t\t########### PAKRING STATUS FOR FREE FACILITY ##########\t\t\n");
	for (i = 0; i < 20; i++){
	    
//	if(*(q+i) == 0) {
//	    printf("Display Parking lot status");
//	    printf("\t\t\t----------------------------------------------\n");
//	    printf("Location: %d\n",i+1);
//		printf("Vehicle Number: NULL\n");
//		printf("Vehicle Modal Name: NULL\n");
//		printf("Arrival Time: NULL\n");
//		printf("Vehicle Company Name: NULL\n");
//		printf("Parking charges: NULL\n");
//		printf("\t\t\t----------------------------------------------\n");
//	    }
        
	    if(*(q+i) == 1){
        printf("Display Parking lot status");
		printf("\t\t\t----------------------------------------------\n");
		printf("Location: %d\n",i+1);
		printf("Vehicle Number: %d\n", parking2[i].vehicleNumber);
		printf("Vehicle Modal Name: %s\n", parking2[i].modalName);
		printf("Arrival Time: %d:%d\n", parking2[i].arrivalTime[0],parking2[i].arrivalTime[1]);
		printf("Vehicle Company Name: %s\n", parking2[i].companyName);
		printf("\t\t\t----------------------------------------------\n");
	}
	}
}
void updateStatus()
{   
    int i=0;
    char companyNamee[10];
    char modalNamee[30];
    int number;
    int count=0;
    
    printf("\nEnter the company of car: ");
    scanf("%s",companyNamee);
    printf("\nEnter the modal of car: ");
    scanf("%s",modalNamee);
    printf("\nEnter the vehicle number of car\n");
    scanf("%d",&number);
    
    /*int j=0;
    while (companyNamee[j]!='\0'){
        j++;
    }  
    char CName[j+1];
    j=0;
    while (companyNamee[j]!='\0'){
        CName[j]=companyNamee[j];        
        j++;
    }    
    CName[j]='\0';*/

    int j=0;
    while (modalNamee[j]!='\0'){
        j++;
    }  
    char MName[j+1];
    j=0;
    while (modalNamee[j]!='\0'){
        MName[j]=modalNamee[j];        
        j++;
    }    
    MName[j]='\0';    
        
    printf("First Checking in Paid\n");
    for(i=0;i<15;i++){
        if(strcmp(companyNamee,parking1[i].companyName)==0){            
            if (strcmp(MName,parking1[i].modalName)==0){
                if(number == parking1[i].vehicleNumber){
                    printf("This car is present at slot number %d.\n",i+1);
                    break;  
                }
            }
        }
        count++;
    }
    if(count == 15) printf("This car is not available here..\n");
    count = 0;
    
    printf("Now Checking in Free\n");
    for(i=0;i<20;i++){
        if(strcmp(companyNamee,parking2[i].companyName)==0){
            if (strcmp(MName,parking2[i].modalName)==0){
                if(number == parking2[i].vehicleNumber){
                    printf("This car is present at slot number %d.\n",i+1);
                    break;
                }
            }
        }
        count++;
    }
    if(count == 20) printf("This car is not available here..\n");
    count = 0;
}

void unionInsertLast (char vehicle[],char modal[],int x) {
    struct list *t = (struct list *)malloc(sizeof(struct list));
    strcpy(t->Company,vehicle);
    strcpy(t->Modal,modal);
    t->vehiclenumber = x;
    t->next = NULL;
    struct list *temp;
    temp=unionFirst;
    if(temp == NULL) {
        unionFirst= t;
    }
    else{
        while (temp->next!=NULL){
            temp=temp->next;
        }
        temp->next = t;
    }
}

void Display(){
    struct list *temp;
    temp=unionFirst;
    char VName[10];
    char MName[30];
    while(temp!=NULL){
    printf("%s ",temp->Company);
    printf("%s ",temp->Modal);
    printf("%d \n",temp->vehiclenumber);
    temp=temp->next;
    }
}

void unionList(){
    int j=0;
    printf("this function basically unite all vehicle of this compnay from both facility..\n");

    char VName[10];
    printf("Enter Company : ");
    scanf("%s",VName);
    char Mname[30];
    while (VName[j]!='\0'){
        j++;
    }  
    char CName[j+1];
    j=0;
    while (VName[j]!='\0'){
        CName[j]=VName[j];        
        j++;
    }    
   CName[j]='\0';
    for(int i=0;i<15;i++){
        if(strcmp(CName,parking1[i].companyName) == 0){
            strcpy(Mname,parking1[i].modalName);
            unionInsertLast(CName,Mname,parking1[i].vehicleNumber);
        }
    }
    for(int i=0;i<20;i++){
        if(strcmp(CName,parking2[i].companyName) == 0){
            strcpy(Mname,parking2[i].modalName);
            unionInsertLast(CName,Mname,parking2[i].vehicleNumber);
        }
    }

    Display();  
}  

void unique(){
    int check1, check2;
    int itre1=0, itre2=0;

    int Unique1[15]={0}, Unique2[20]={0};

    
    for(check1=0; check1<15; check1++){
        if(paidParking[check1]==1){
            if(Unique1[check1]!=2){
                Unique1[check1]=1;
            }
           

            for(check2=check1+1; check2<15; check2++){
                if(paidParking[check2]==1){
                    if(0==stricmp(parking1[check1].companyName, parking1[check2].companyName)){
                        if(0==stricmp(parking1[check1].modalName, parking1[check2].modalName)){
                            Unique1[check2]=2;
                        }
                    }
                }
            }
        }
       
    }

    
    for(check1=0; check1<20; check1++){
        if(freeParking[check1]==1){
           
            if(Unique2[check1] != 2){
                Unique2[check1]=1;
                
            }

            for(check2=check1+1; check2<20; check2++){
                if(freeParking[check2]==1){
                    if(0==stricmp(parking2[check1].companyName, parking2[check2].companyName)){
                        if(0==stricmp(parking2[check1].companyName, parking2[check2].companyName))
                            Unique2[check2]=2;
                    }
                }
            }
        }
    }

    printf("\n");
    printf("Paid Parking (Company : Model)\n");
    for(int i=0; i<15; i++){
        if(Unique1[i]==1)
            printf("%s : %s\n",parking1[i].companyName, parking1[i].modalName);
    } 

    printf("\nFree Parking (Company : Model)\n");
    for(int i=0; i<20; i++){
        if(Unique2[i]==1)
            printf("%s : %s\n",parking2[i].companyName, parking2[i].modalName);
    } 
    printf("\n");
}

void largestStayList(int *paid, int *unpaid){
    int longesttime=0, staytime1[15]={0}, staytime2[20]={0},departureTime[2];
    printf("Enter Current Time(Hour,Minute): ");
    scanf("%d %d",&departureTime[0],&departureTime[1]);

    int i,count1=0,count2=0;
    for(i=0;i<15;i++){
        if(*(paid+i) == 0){
            //printf("\nPaid Parking is not Full.\n");
            break;
        }
        count1++;
    }
    if(count1 == 15) {
        printf("\nPaid Parking is Full.\n");
    }else{
        for (int i = 0; i < 15; i++){
        int time;
        if(*(paid+i)==1){
            time=((departureTime[0]*60)+(departureTime[1]))-((parking1[i].arrivalTime[0]*60)+(parking1[i].arrivalTime[1]));
            staytime1[i]=time;
            if (time>longesttime)
            {
                longesttime=time;
            }
            
        }
    }
    }
    for(i=0;i<20;i++){
        if(*(unpaid+i) == 0){
            //printf("\nFree Parking is not Full.\n");
            break;
        }
        count2++;
    }
    if(count2 == 20) {
        printf("\nFree Parking is Full.\n");
    }else{
        for (int i = 0; i < 15; i++){
        int time;
        if(*(paid+i)==1){
            time=((departureTime[0]*60)+(departureTime[1]))-((parking1[i].arrivalTime[0]*60)+(parking1[i].arrivalTime[1]));
            staytime1[i]=time;
            if (time>longesttime)
            {
                longesttime=time;
            }
            
        }
    }
    }
    for (int i = 0; i < 15; i++){
        int time;
        if(*(paid+i)==1){
            time=((departureTime[0]*60)+(departureTime[1]))-((parking1[i].arrivalTime[0]*60)+(parking1[i].arrivalTime[1]));
            staytime1[i]=time;
            if (time>longesttime)
            {
                longesttime=time;
            }            
        }
    }

    for (int i = 0; i < 15; i++){
        int time;
        if(*(unpaid+i)==1){
            time=((parking2[i].departureTime[0]*60)+(parking2[i].departureTime[1]))-((parking2[i].arrivalTime[0]*60)+(parking2[i].arrivalTime[1]));
            staytime2[i]=time;
            if(time>longesttime){
                longesttime=time;
            }
        }
    }

    printf("\n***(according to current time)***\n\n");
    for (int i = 0; i < 15; i++){
        if (longesttime==staytime1[i]){
            printf("Company: %s\n",parking1[i].companyName);
            printf("Model Name: %s\n",parking1[i].modalName);
            printf("Vehical Number: %d\n",parking1[i].vehicleNumber);            
            printf("Paid Facility: %d\n",parking1[i].paidFacility);
            printf("Location: %d\n",parking1[i].location);
            printf("Arrivaltime: %d:%d\n\n",parking1[i].arrivalTime[0],parking1[i].arrivalTime[1]);
        }        
    }
    for (int i = 0; i < 20; i++){
        if (longesttime==staytime2[i]){
            printf("Company: %s\n",parking2[i].companyName);
            printf("Model Name: %s\n",parking2[i].modalName);
            printf("Vehical Number: %d\n",parking2[i].vehicleNumber);            
            printf("Paid Facility: %d\n",parking2[i].paidFacility);
            printf("Location: %d\n",parking2[i].location);
            printf("Arrivaltime: %d:%d\n\n",parking2[i].arrivalTime[0],parking2[i].arrivalTime[1]);
        }
    }   
}

void intersectionList(int *paid,int *unpaid){
    char CName[10],MName[30];
    printf("Enter Comapany: ");
    scanf("%s",CName);
    printf("Enter Model: ");
    scanf("%s",MName);

    int j=0;
    while (CName[j]!='\0'){
        j++;
    }
    char CN[j+1];
    j=0;
    while (CName[j]!='\0'){
        CN[j]=CName[j];        
        j++;
    }
    CN[j]='\0';
    j=0;
    while (MName[j]!='\0'){
        j++;
    }
    char MN[j+1];
    j=0;
    while (MName[j]!='\0'){
        MN[j]=MName[j];
        j++;
    }
    MN[j]='\0';
    
    int check1=0,check2=0;
    for (int i = 0; i < 15; i++){       
        if (strcmp(CN,parking1[i].companyName)==0){
            if (strcmp(MN,parking1[i].modalName)==0){
                printf("\nCompany: %s\n",parking1[i].companyName);
                printf("Model Name: %s\n",parking1[i].modalName);
                printf("Vehical Number: %d\n",parking1[i].vehicleNumber);            
                printf("Paid Facility: %d\n",parking1[i].paidFacility);
                printf("Location: %d\n",parking1[i].location);
                printf("Arrivaltime: %d:%d\n\n",parking1[i].arrivalTime[0],parking1[i].arrivalTime[1]);
                check1++;
            }
        }
    }
    if (check1==0){
        printf("\nCouldn't Found same Model in paid parking..\n\n");    
    }
    for (int i = 0; i < 20; i++){
        if (strcmp(CN,parking2[i].companyName)==0){
            if (strcmp(MN,parking2[i].modalName)==0){
                printf("\nCompany: %s\n",parking2[i].companyName);
                printf("Model Name: %s\n",parking2[i].modalName);
                printf("Vehical Number: %d\n",parking2[i].vehicleNumber);            
                printf("Paid Facility: %d\n",parking2[i].paidFacility);
                printf("Location: %d\n",parking2[i].location);
                printf("Arrivaltime: %d:%d\n\n",parking2[i].arrivalTime[0],parking2[i].arrivalTime[1]);
                check2++;
            } 
        }        
    }
    if (check2==0){
        printf("\nCouldn't Found same Model in unpaid parking..\n\n");    
    }   
}

int main(){   
    if(adminAccess() == 0){
        return 0;
    }
    
    int *paid, *unpaid;
    int choice;
    paid=paidParking;
    unpaid=freeParking;

    parking1[5].arrivalTime[0]=4,parking1[5].arrivalTime[1]=26;
    strcpy(parking1[5].companyName, "Honda");
    strcpy(parking1[5].modalName, "Activa3G");
    parking1[5].location=6;
    parking1[5].paidFacility=1;
    parking1[5].vehicleNumber=1551;

    parking1[12].arrivalTime[0]=2,parking1[12].arrivalTime[1]=46;
    strcpy(parking1[12].companyName, "Honda");
    strcpy(parking1[12].modalName, "Activa3G");
    parking1[12].location=13;
    parking1[12].paidFacility=1;
    parking1[12].vehicleNumber=1553;

    parking1[9].arrivalTime[0]=1,parking1[9].arrivalTime[1]=24;
    strcpy(parking1[9].companyName, "Bajaj");
    strcpy(parking1[9].modalName, "Pulsar");
    parking1[9].location=10;
    parking1[9].paidFacility=1;
    parking1[9].vehicleNumber=1891;

    parking2[11].arrivalTime[0]=4,parking2[11].arrivalTime[1]=26;
    strcpy(parking2[11].companyName, "Mahindra");
    strcpy(parking2[11].modalName, "Mojo_300_ABS");
    parking2[11].location=12;
    parking2[11].paidFacility=0;
    parking2[11].vehicleNumber=2243;

    parking2[2].arrivalTime[0]=5,parking2[2].arrivalTime[1]=23;
    strcpy(parking2[2].companyName, "TVS");
    strcpy(parking2[2].modalName, "Scooty");
    parking2[2].location=3;
    parking2[2].paidFacility=0;
    parking2[2].vehicleNumber=2502;

    parking2[6].arrivalTime[0]=3,parking2[6].arrivalTime[1]=42;
    strcpy(parking2[6].companyName, "TVS");
    strcpy(parking2[6].modalName, "Scooty");
    parking2[6].location=7;
    parking2[6].paidFacility=0;
    parking2[6].vehicleNumber=2500;
    
    paidParking[5]=1;
    paidParking[9]=1;

    freeParking[11]=1;
    freeParking[2]=1;
    freeParking[6]=1; 

    int key;
    do{
        printf("\n1 : Insertion\n2 : Deletion\n3 : Union List\n4 : Intersection List\n5 : Unique List\n6 : LargestStay List\n7 : IsEmpty\n8 : IsFull\n9 : Display\n10 : Update\n11 : Exit");
        printf("\nEnter key : ");
        
        scanf("%d", &key);
        switch(key){
            case 1:     // Insertion 
                insertVehicle( paid, unpaid);
                break;

            case 2:     // Deletion
                deleteVehicle( paid, unpaid);
                break;

            case 3:     // Union list
                unionList();
                unionFirst=NULL;
                break;

            case 4:     // Intersection
                intersectionList(paid,unpaid);
                break;

            case 5:    // Distingise By company
                unique(paid,unpaid);
                break;

            case 6:     // Biggest Payment
                largestStayList(paid,unpaid);
                break;

            case 7:     // Checking Empty for whole parking
                isEmptyy(paid,unpaid);
                break;
            
            case 8:     // Checking Full For whole parking
                isFulll(paid,unpaid);
                break;

            case 9:     // Getting Information
                VehicleInfo(paid,unpaid);
                break;
                
            case 10:    // Checking for existance
                updateStatus();
                break;
                
            case 11:    // Exit
                printf("Thanks for login Admin.....\n");
                exit(0);

            default:    // Wrong key added
                printf("Enter key from given choices\n");
        }
    }while(key!=11);
    
    return 0;
}