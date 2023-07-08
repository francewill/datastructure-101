#include<stdio.h>
#include<stdlib.h>

int main(){
    int flag=1;  // loop checker
    char choice;

    float weight,height,bmi;
  
    printf("\nWelcome!");
    while(flag){
        printf("\nWhat unit do you want to use?");
        printf("\n[1] Metric System");
        printf("\n[2] Imperial System");
        printf("\n[0] Exit\n");
        printf(">>> ");
        scanf(" %c", &choice);
        switch (choice)  // switch case for user input
        {
        case '1':  // for metric system
            printf("\nEnter your weight (kg): ");
            scanf("%f", &weight);
            printf("\nEnter your height (cm): ");
            scanf("%f",&height);
            height= (height*0.01)*(height*0.01);  // convert it to meter
            bmi = weight/height;  // formula for getting bmi using metric system
            break;
        case '2': // for imperial system
            printf("Pounds and ft");
            printf("\nEnter your weight (lb): ");
            scanf("%f",&weight);
            printf("\nEnter your height (ft): ");
            scanf("%f", &height);
            height = (height*12)*(height*12);  // convert it to inches
            bmi = 703 * (weight/height);  // formula for getting bmi using imperial system

            break;
        case '0':
            printf("\nGoodbye!\n");
            flag = 0;
            exit(0);

        default:
            printf("Invalid choice!");
            break;
        }
        // conditions for category
        if(bmi <18.5){
            printf("\nYou're bmi is %f which is underweight\n", bmi);
        }else if(bmi >=18.5 && bmi <=24.99 ){
            printf("\nYou're bmi is %f which is healthy\n", bmi);
        }else if(bmi >=25 && bmi <=29.99){
            printf("\nYou're bmi is %f which is overweight\n", bmi);
        }else if(bmi >=30){
            printf("\nYou're bmi is %f which is obese\n", bmi);
        }
   
    };

    return 0;

}