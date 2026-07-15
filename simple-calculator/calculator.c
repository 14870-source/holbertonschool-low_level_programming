#include <stdio.h>

int main(void)
{
    int choice;

    do
    {
        printf("Simple Calculator\n");
        printf("1) Add\n");
        printf("2) Subtract\n");
        printf("3) Multiply\n");
        printf("4) Divide\n");
        printf("0) Quit\n");
        printf("Choice: ");

        scanf("%d", &choice);

        if (choice >= 1 && choice <= 4)
        {
            /* سيتم إضافة العمليات في المهام القادمة */
        }
        else if (choice == 0)
        {
            printf("Bye!\n");
        }
        else
        {
            printf("Invalid choice\n");
        }

    } while (choice != 0);

    return (0);
}
