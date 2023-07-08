#include<stdio.h>
#include<stdlib.h>

int main(){
    int flag=1;
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
        switch (choice)
        {
        case '1':
            printf("\nEnter your weight (kg): ");
            scanf("%f", &weight);
            printf("\nEnter your height (cm): ");
            scanf("%f",&height);
            height= (height*0.01)*(height*0.01);
            bmi = weight/height;
            break;
        case '2':
            printf("Pounds and ft");
            printf("\nEnter your weight (lb): ");
            scanf("%f",&weight);
            printf("\nEnter your height (ft): ");
            scanf("%f", &height);
            height = (height*12)*(height*12);
            bmi = 703 * (weight/height);

            break;
        case '0':
            printf("\nGoodbye!\n");
            flag = 0;
            exit(0);

        default:
            printf("Invalid choice!");
            break;
        }
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