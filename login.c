#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_STUD 1000
#define FILE_LOGIN_SIGNIN "login.txt"

typedef struct{
    char name_student_fic[100];
    char passwords_student_fic[100];
    /*int char_name_fic;
    int char_password_fic;*/
}compare_students_fic;

//void login();
int post_data_fic (compare_students_fic *L1);
void comparison (compare_students_fic *L1, int count_students_fic);

int main (){
    int count_students_fic=0;
    compare_students_fic *L1=NULL;
    L1=(compare_students_fic *)malloc(MAX_STUD*sizeof(compare_students_fic));
    //login();
    count_students_fic=post_data_fic(L1);
    comparison(L1, count_students_fic);
    return 0;
}


int post_data_fic (compare_students_fic *L1){
    int i,
        j;
    char name_login_fic[100]={0};
    FILE *fic=fopen(FILE_LOGIN_SIGNIN, "r");

    for(i=0, j=0; fgets(name_login_fic, sizeof(name_login_fic), fic); i++, j++){
        sscanf(name_login_fic, "%99[^;];%99[^;]", L1[i].name_student_fic, L1[i].passwords_student_fic);
        /*L1[i].char_name_fic=strlen(L1[i].name_student_fic);
        L1[i].char_password_fic=strlen(L1[i].passwords_student_fic);*/
    }

    /*printf("<HTML>\n");
    printf("\t<BODY>\n");
    
    /*for(i=0; i<j; i++){
        printf ("    %s %s</BR>", L1[i].name_student_fic, L1[i].passwords_student_fic);
        //printf("%d=>%d</BR>", L1[i].char_name_fic, L1[i].char_password_fic);
    }
    //printf("%s</BR>", data);
    printf ("\n\t</BODY>\n</HTML>\n");*/

    fclose(fic);
    return (j);
}

void comparison (compare_students_fic *L1, int count_students_fic){
    int i,
        count=0,
        data_length=0;
    char *content_length=NULL,
        Data[100]={0},
        char_name_input[100]={0},
        char_passwords_input[100]={0};
    int length_name=0,
        length_passwords=0;

    content_length=getenv("CONTENT_LENGTH");

    if(content_length!=0){
        data_length=atoi(content_length);
    }

    if(data_length>0){
        char data[data_length+1];
        fread(data, 1, data_length, stdin);
        data[data_length]='\0';
        for (i=0; data[i]!='\0'; i++){
            if (data[i]=='+'){
                Data[i]=' ';
                continue;
            }else{
                Data[i]=data[i];
            }
        }
        sscanf(Data, "ID=%99[^&]&Passwords1=%99s", char_name_input, char_passwords_input);
        //length_name=strlen(char_name_input);
        //length_passwords=strlen(char_passwords_input);



        for (i=0; i<count_students_fic; i++){
            //printf (">>>    %s %s</BR>", L1[i].name_student_fic, L1[i].passwords_student_fic);
            //printf("%d=>%d</BR>", L1[i].char_name_fic, L1[i].char_password_fic);
            if (/*L1[i].char_name_fic==length_name && L1[i].char_password_fic==length_passwords && */strcmp(L1[i].name_student_fic, char_name_input)==0 && strcmp(L1[i].passwords_student_fic, char_passwords_input)==0){
                count=1;
            }    
        }
        if (!count){
            printf("content-type: text/html\n\n");
            printf("<HTML>");
            printf(" <LINK rel=\"stylesheet\" href=\"fond.css\"/>");
            printf("    <LINK rel=\"stylesheet\" href=\"Style.css\"/>");
            printf("    <BODY>\n\t\t<H1><P id=\"title\">Please try again, wrong ID or Passwords</H1>");
            printf("    <FORM ACTION=\"login.cgi\" METHOD=\"post\">");
            printf("        <LABEL FOR=\"ID\">Enter your ID:</LABEL></BR>");
            printf("        <INPUT TYPE=\"text\" ID=\"ID\" NAME=\"ID\" required></P>");        

            printf("        <LABEL FOR=\"firstname\">Passwords:</LABEL></BR>");
            printf("        <INPUT TYPE=\"password\" ID=\"Passwords\" NAME=\"Passwords1\" required></P>");
                            
            printf("        <INPUT TYPE=\"SUBMIT\" VALUE=\"Login\">");        
            printf("     </FORM></BR>");
            printf ("\n\t</BODY>\n</HTML>\n");
        }else{
            printf("content-type: text/html\n\n");
            printf("<HTML>\n");
            printf("\t<BODY>\n");
            printf("    Connection succesfully</BR>");
            printf("    WELCOME TO IPv4</BR>");
            printf("    <FORM ACTION=\"id.html\" METHOD=\"post\">");
            printf("    <INPUT TYPE=\"SUBMIT\" VALUE=\"Start\">");
            printf("     </FORM></BR>");
            printf ("\n\t</BODY>\n</HTML>\n");  
        }
    }
    /*printf("%s</BR>", Data);
    printf("%d = %d</BR>", length_name, length_passwords);
    printf("%s = %s</BR>", char_name_input, char_passwords_input);*/
}
