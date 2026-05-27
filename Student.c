#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student
{
    int id;
    char name[50];
    float marks;
};

void addStudent()
{
    FILE *fp;
    struct Student s;

    fp = fopen("students.dat", "ab");

    printf("Enter ID: ");
    scanf("%d", &s.id);

    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);

    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fwrite(&s, sizeof(s), 1, fp);

    fclose(fp);

    printf("Student Added Successfully.\n");
}

void displayStudents()
{
    FILE *fp;
    struct Student s;

    fp = fopen("students.dat", "rb");

    if(fp == NULL)
    {
        printf("No records found.\n");
        return;
    }

    printf("\nStudent Records:\n");

    while(fread(&s, sizeof(s), 1, fp))
    {
        printf("ID: %d | Name: %s | Marks: %.2f\n",
               s.id, s.name, s.marks);
    }

    fclose(fp);
}

void searchStudent()
{
    FILE *fp;
    struct Student s;
    int id, found = 0;

    fp = fopen("students.dat", "rb");

    printf("Enter Student ID to Search: ");
    scanf("%d", &id);

    while(fread(&s, sizeof(s), 1, fp))
    {
        if(s.id == id)
        {
            printf("Record Found:\n");
            printf("ID: %d\nName: %s\nMarks: %.2f\n",
                   s.id, s.name, s.marks);
            found = 1;
        }
    }

    if(!found)
    {
        printf("Record not found.\n");
    }

    fclose(fp);
}

void deleteStudent()
{
    FILE *fp, *temp;
    struct Student s;
    int id, found = 0;

    fp = fopen("students.dat", "rb");
    temp = fopen("temp.dat", "wb");

    printf("Enter Student ID to Delete: ");
    scanf("%d", &id);

    while(fread(&s, sizeof(s), 1, fp))
    {
        if(s.id != id)
        {
            fwrite(&s, sizeof(s), 1, temp);
        }
        else
        {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if(found)
        printf("Record Deleted Successfully.\n");
    else
        printf("Record not found.\n");
}

void updateStudent()
{
    FILE *fp;
    struct Student s;
    int id, found = 0;

    fp = fopen("students.dat", "rb+");

    printf("Enter Student ID to Update: ");
    scanf("%d", &id);

    while(fread(&s, sizeof(s), 1, fp))
    {
        if(s.id == id)
        {
            printf("Enter New Name: ");
            scanf(" %[^\n]", s.name);

            printf("Enter New Marks: ");
            scanf("%f", &s.marks);

            fseek(fp, -sizeof(s), SEEK_CUR);
            fwrite(&s, sizeof(s), 1, fp);

            found = 1;
            break;
        }
    }

    fclose(fp);

    if(found)
        printf("Record Updated Successfully.\n");
    else
        printf("Record not found.\n");
}

int main()
{
    int choice;

    while(1)
    {
        printf("\n===== Student Management System =====\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                addStudent();
                break;

            case 2:
                displayStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                updateStudent();
                break;

            case 5:
                deleteStudent();
                break;

            case 6:
                exit(0);

            default:
                printf("Invalid Choice.\n");
        }
    }

    return 0;
}