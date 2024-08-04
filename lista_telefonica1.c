#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>


struct person {
    char name[35];
    char address[50];
    char father_name[35];
    char mother_name[30];
    long int mobile_phone;
    char sex[8];
    char email[100];
};

void menu();
void got(char *name);
void start();
void back();
void addrecord();
void listrecord();
void modifyrecord();
void deleterecord();
void searchrecord();

int main() {
    system("color 5f");
    start();
    return 0;
}

void back() {
    start();
}

void start() {
    menu();
}

void menu() {
    system("cls");
    printf("\t\t**********************usando clions pq vscode fica sendo bosta comigo no C**********************");
    printf("\n\n\t\t\t MENU\t\t\n\n");
    printf("\t1. Add New\t2. List\t\t3. Exit\n\t4. Modify\t5. Search\t6. Delete\n");

    switch (getch()) {
        case '1':
            addrecord();
            break;
        case '2':
            listrecord();
            break;
        case '3':
            exit(0);
            break;
        case '4':
            modifyrecord();
            break;
        case '5':
            searchrecord();
            break;
        case '6':
            deleterecord();
            break;
        default:
            system("cls");
            printf("\n Enter 1 to 6 only");
            printf("\n Enter any key");
            getch();
            menu();
    }
}
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void addrecord() {
    system("cls");
    FILE *f;
    struct person p;
    f = fopen("project", "ab+");
    if (f == NULL) {
        perror("Error opening file");
        return;
    }
    printf("\nEnter the name: ");

    clear_input_buffer();
    got(p.name);
    printf("\nEnter the address: ");
    got(p.address);
    printf("\nEnter father's name: ");
    got(p.father_name);
    printf("\nEnter the mother's name: ");
    got(p.mother_name);
    printf("\nEnter the phone number: ");
    scanf("%ld", &p.mobile_phone);
    fflush(stdin);
    printf("\nEnter the sex: ");
    got(p.sex);
    printf("\nEnter the email: ");
    got(p.email);
    fwrite(&p, sizeof(p), 1, f);
    fflush(stdin);
    printf("\nRecord saved");

    fclose(f);
    printf("\n\nEnter any key");
    getch();
    system("cls");
    menu();
}

void listrecord() {
    struct person p;
    FILE *f;
    f = fopen("project", "rb");
    if (f == NULL) {
        printf("\nFile opening error in listing.");
        exit(1);
    }
    while (fread(&p, sizeof(p), 1, f) == 1) {
        printf("\n\n\nYour record is\n\n");
        printf("\nName: %s\nAddress: %s\nFather's name: %s\nMother's name: %s\nMobile number: %ld\nSex: %s\nEmail: %s",
               p.name, p.address, p.father_name, p.mother_name, p.mobile_phone, p.sex, p.email);
        getch();
        system("cls");
    }
    fclose(f);
    printf("\nEnter any key");
    getch();
    system("cls");
    menu();
}

void searchrecord() {
    struct person p;
    FILE *f;
    char name[100];
    int found = 0;

    f = fopen("project", "rb");
    if (f == NULL) {
        printf("\nError opening file");
        exit(1);
    }
    printf("\nEnter name of person to search\n");
    got(name);
    while (fread(&p, sizeof(p), 1, f) == 1) {
        if (strcmp(p.name, name) == 0) {
            printf("\n\t Detail Information About %s", name);
            printf("\nName: %s\nAddress: %s\nFather's name: %s\nMother's name: %s\nMobile number: %ld\nSex: %s\nEmail: %s",
                   p.name, p.address, p.father_name, p.mother_name, p.mobile_phone, p.sex, p.email);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Record not found");
    }
    fclose(f);
    printf("\nEnter any key");
    getch();
    system("cls");
    menu();
}

void deleterecord() {
    struct person p;
    FILE *f, *ft;
    int flag = 0;
    char name[100];
    f = fopen("project", "rb");
    if (f == NULL) {
        printf("Contacts not added yet.");
        return;
    } else {
        ft = fopen("temp", "wb+");
        if (ft == NULL) {
            printf("File not opening");
            return;
        }
        printf("Enter contact's name: ");
        got(name);
        while (fread(&p, sizeof(p), 1, f) == 1) {
            if (strcmp(p.name, name) != 0) {
                fwrite(&p, sizeof(p), 1, ft);
            } else {
                flag = 1;
            }
        }
        fclose(f);
        fclose(ft);
        if (flag != 1) {
            printf(" No contacts to be deleted ");
            remove("temp");
        } else {
            remove("project");
            rename("temp", "project");
            printf(" Contact has been deleted. ");
        }
    }
    printf("\n Enter any key");
    getch();
    system("cls");
    menu();
}

void modifyrecord() {
    int c;
    FILE *f;
    int flag = 0;
    struct person p, s;
    char name[50];
    f = fopen("project", "rb+");
    if (f == NULL) {
        printf("\nContact is not added yet");
        exit(1);
    } else {
        system("cls");
        printf("\nEnter contact that you want to modify:\n");
        got(name);
        while (fread(&p, sizeof(p), 1, f) == 1) {
            if (strcmp(name, p.name) == 0) {
                printf("\nEdit the name: ");
                got(s.name);
                printf("\nEdit the address: ");
                got(s.address);
                printf("\nEdit father's name: ");
                got(s.father_name);
                printf("\nEdit mother's name: ");
                got(s.mother_name);
                printf("\nEdit the phone number: ");
                scanf("%ld", &s.mobile_phone);
                fflush(stdin); // Clear input buffer
                printf("\nEdit sex: ");
                got(s.sex);
                printf("\nEdit email: ");
                got(s.email);
                fseek(f, -sizeof(p), SEEK_CUR);
                fwrite(&s, sizeof(p), 1, f);
                flag = 1;
                break;
            }
        }
        if (flag == 1) {
            printf("\nYour contact has been updated");
        } else {
            printf("\nContact not found");
        }
        fclose(f);
    }
    printf("\nEnter any key");
    getch();
    system("cls");
    menu();
}

void got(char *name) {
    int i = 0;
    char c;
    do {
        c = getch();
        if (c != 8 && c != 13) {
            name[i] = c;
            putch(c);
            i++;
        } else if (c == 8 && i > 0) {
            i--;
            printf("\b \b"); // Move cursor back, print space, move cursor back again
        }
    } while (c != 13);
    name[i] = '\0';
}
