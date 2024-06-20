#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdbool.h>

#define MAX_EMPLOYEE 100
#define RESET   "\033[om"
#define RED    "\033[31m"
#define GREEN  "\033[32m"
#define YELLOW "\033[33m"
#define BLUE   "\033[34m"
#define WHITE  "\033[37m"
#define CYAN   "\033[0;36m"
//define a structure for employees
typedef struct{
    int id;
    char name[50];
    float salary;
}Employee;
//function proto type 
void addemployee(Employee employees[],int *count);
void displayemployee(Employee employees[],int count);
void updateemployee(Employee employees[],int count);
void deleteemployee(Employee employees[],int *count);
bool secur(int epass);
void bar(int percentage);

int main(){
    Employee employees[MAX_EMPLOYEE];
    int count=0,choice;

    while (1){
        printf(YELLOW"\t\t\t_____________________________\n");
        printf("   \t\t\t|                           |");
        printf("\n \t\t\t| Employee managment system |\n");
        printf("   \t\t\t|___________________________|");
        printf("\n\n");
        printf(RED"\n\t1. add employe.\n");
        printf("\t2. Display Employees.\n");
        printf(BLUE"\t3. Update employee.\n");
        printf("\t4. Delete employee.\n");
        printf(WHITE"\t5. Exit.\n ");
        printf("\n\t Enter your choice : ");
        scanf("%d",&choice);
//switch statment calling the function

        switch (choice){
        case 1 : 
        addemployee(employees,&count);
        break;

        case 2 :
        displayemployee(employees,count);
        break;

        case 3 : 
        updateemployee(employees,count);
        break;

       case 4 :
       deleteemployee(employees,&count);
        break;

        case 5 :
        printf("EXIT");
        return 0;

        default : 
        printf("Enter the valid number from the option's !") ;
        }
    }
    return 0;
}
//function to add employee 
    void addemployee(Employee employees[],int *count){
        if(*count >= MAX_EMPLOYEE){
        printf("maximum space limit ,no more data can be added .");
        return ;
        }
        printf("\nENTER the detail of employee :\n");
        printf("Enter id : ");
        scanf("%d",&employees[*count].id);
        printf("\nEnter name : ");
        scanf("%s",&employees[*count].name);
        printf("\nEnter salary : ");
        scanf("%f",&employees[*count].salary);

        (*count)++;
        for(int i =0;i<=100;i++){
            bar(i);
            usleep(100000);
        }
        printf("\n");
        printf(CYAN"\n Employee added succesfully .\n");
    }
//function to display employee .
    void displayemployee(Employee employees[],int count){
        if(count == 0 ){
            printf("No detail to display . ");
            return ;
        }
        printf("\n");
    printf("\t\t\t############################\n");
    printf("\t\t\t#                          #\n");
    printf("\t\t\t#     List of employees    #\n");
    printf("\t\t\t#                          #\n");
    printf("\t\t\t############################\n");
    printf("\n");
        printf("\n i'd |\t\t Name |\t\t \tSalary |\n");
        for(int i=0 ; i < count ; i++){
            printf("\n %d|\t\t %s |\t\t %f |\n",employees[i].id,employees[i].name,employees[i].salary);
            printf("__________________________________________________");
            printf("\n");
            printf("\n");
        }
    }
//function to update employee 
    void updateemployee(Employee employees[],int count){
        int found =0 ,id,epass;
        if(count == 0){
            printf("No data to be updated .");
            return ;
        }
        
        printf(GREEN"\nENTER THE PASSWORD TO UPDATE THE DATA : ");
        scanf("%d",&epass);

        if(!secur(epass)){
            printf(RED"ACCESS DENIED WRONG PASSWORD . \n");
            return;
        }
        printf("ACCESS GRANTED CORRECT PASSWORD .\n");

        printf(WHITE"\nEnter id to be updated : ");
        scanf("%d",&id);

        for(int i = 0; i< count ; i++){
            if(employees[i].id == id){
                found = 1;
                printf("\nEnter new name : ");
                scanf("%s",&employees[i].name);
                printf("\n Enter new salary : ");
                scanf("%f",&employees[i].salary);

                 for(int i =0;i<=100;i++){
            bar(i);
            usleep(100000);
        }
        printf("\n");
                printf(CYAN"\nDATA UPDATED SUCCESFULLEY !!\n");
            }
        }
        if(!found ){
            printf(RED"Employee with this id %d not found .\n",id);
        }
        }
//function to deleate employee

    void deleteemployee(Employee employees[],int *count){
        int found = 0 , id,epass;
        if(count ==0 ){
            printf(RED"no data present to delete");
            return ;
        }
        //calling secure function in deleteemployee function .
        printf(GREEN"\nENTER THE PASSWORD TO ACCES THE DATA : ");
        scanf("%d",&epass);

        if(!secur(epass)){
            printf(RED"ACCESS DENIED WRONG PASSWORD . \n");
            return;
        }
        printf("ACCESS GRANTED CORRECT PASSWORD .");
        printf(WHITE"Enter the id to be deleated : ");
        scanf("%d",&id);
// this for loop will first iterate in all structures and find the entered id .
//then inner loop will deleate the entered employee and shift the other employee at that place .
        for(int i = 0 ; i< *count ; i++){
            if(employees[i].id == id){
                found =1;
                for(int j =i ; j < *count - 1 ; j++){
                    employees[j] = employees[j+1];
                }
                    (*count)--;
            }
        }
        
        printf(RED"\nEMPLOYEE DATA DELEATED .\n");
        if(!found){
            printf("\nEmployee id %d not found .",id);
        }
    }

    bool secur(int epass){
    int spass;
    FILE *pass;
    pass = fopen("pass.txt","r");
    if(pass == NULL){
    perror("\nFAILED TO OPEN FILE .\n");
    return ;
    }
    fscanf(pass,"%d",&spass);
    fclose(pass);
    
 return epass == spass ;

    }

//function of loading bar 
void bar(int percentage){
    int bar_width = 30;
    printf("Loading");
    int pos = bar_width*percentage /100;
    for(int i =0 ; i<bar_width;++i){
        if(i<pos){
            printf(".");
        }
        else if (i==pos){
            printf("!");
        }
        else printf(" ");
    }
    printf("|%d%%\r",percentage);
    fflush(stdout);
}
