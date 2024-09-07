#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_PERSO 100
#define FILE_LOGIN_SIGNIN "login.txt"

/*typedef struct{
    char name_fic_compare[100];
}name;*/

void creation();
void Verification_account(char *student_name, char *student_passwords1, char *student_passwords2, int equal_ID, int equal_passwords);

int main (){
    creation();
    return 0;
}

void creation(){
    int i,
        j,
        equal_ID=0,
        equal_passwords=0,
        data_length=0;
    char *content_length=NULL,
        Data[100]={0},
        name_fic_compare[100]={0},
        name_fic[100]={0},
        student_name[100]={0},
        student_passwords1[100]={0},
        student_passwords2[100]={0};
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


        sscanf(Data, "ID=%99[^&]&Passwords1=%99[^&]&Passwords2=%99s", student_name, student_passwords1, student_passwords2);

        FILE *fic=fopen(FILE_LOGIN_SIGNIN, "r");
        

        for(i=0; fgets(name_fic_compare, sizeof(name_fic_compare), fic); i++){
            sscanf(name_fic_compare, "%99[^;]", name_fic);
            if(strcmp(name_fic, student_name)==0){
                equal_ID=1;
            }else if(strcmp(student_passwords2, student_passwords1)==0){
                equal_passwords=1;
            }
        }


        Verification_account(student_name, student_passwords1, student_passwords2, equal_ID, equal_passwords);

        fclose(fic);
    }
}


void Verification_account(char *student_name, char *student_passwords1, char *student_passwords2, int equal_ID, int equal_passwords){
    if(equal_ID==1){
        printf ("content-type: text/html\n\n"); 
        printf("<!DOCTYPE HTML>\n");
        printf("<HTML>");
        printf(" <LINK rel=\"stylesheet\" href=\"fond.css\"/>");
        printf("    <LINK rel=\"stylesheet\" href=\"Style.css\"/>");
        printf("    <BODY>\n\t\t<H1><P id=\"title\">This name is already used. Please try again</H1>");
        printf("    <FORM ACTION=\"creat_account.cgi\" METHOD=\"post\">");
        printf("        <LABEL FOR=\"ID\">Enter your ID:</LABEL></BR>");
        printf("        <INPUT TYPE=\"text\" NAME=\"ID\" required></P>");        

        printf("        <LABEL FOR=\"password\">Passwords:</LABEL></BR>");
        printf("        <INPUT TYPE=\"password\" NAME=\"Passwords1\" required></P>");

        printf("        <LABEL FOR=\"password\">Verification Passwords:</LABEL></BR>");
        printf("        <INPUT TYPE=\"password\" NAME=\"Passwords2\" required></P>");

        printf("        <INPUT TYPE=\"SUBMIT\" VALUE=\"Create account\">");        
        printf("     </FORM></BR>");    
        printf("     </BODY>");
        printf("</HTML>");
    }else if (equal_passwords==1){
        FILE *fic=fopen(FILE_LOGIN_SIGNIN, "a+");
        fprintf(fic, "%s;%s;\n", student_name, student_passwords1);
        //fclose(fic);
        
        printf ("content-type: text/html\n\n"); 
        printf("<!DOCTYPE HTML>\n");
        printf("<HTML>");
        printf("    <BODY>");
        printf(" <LINK rel=\"stylesheet\" href=\"fond.css\"/>");
        printf("    <LINK rel=\"stylesheet\" href=\"Style.css\"/>");
        printf("    <FORM ACTION=\"login.html\" METHOD=\"post\">");
        printf("    Creation account succesfully</BR>");
        printf("    <INPUT TYPE=\"SUBMIT\" VALUE=\"Return to login\">");
        printf("     </FORM></BR>");
        printf("    </BODY>");
        printf("</HTML>");
    }else{
        printf ("content-type: text/html\n\n"); 
        printf("<!DOCTYPE HTML>\n");
        printf("<HTML>");
        printf(" <LINK rel=\"stylesheet\" href=\"fond.css\"/>");
        printf("    <LINK rel=\"stylesheet\" href=\"Style.css\"/>");
        printf("    <BODY>\n\t\t<H1><P id=\"title\">Wrong Passwords! Please try again</H1>");
        printf("    <FORM ACTION=\"creat_account.cgi\" METHOD=\"post\">");
        printf("        <LABEL FOR=\"ID\">Enter your ID:</LABEL></BR>");
        printf("        <INPUT TYPE=\"text\" NAME=\"ID\" required></P>");        

        printf("        <LABEL FOR=\"password\">Passwords:</LABEL></BR>");
        printf("        <INPUT TYPE=\"password\" NAME=\"Passwords1\" required></P>");

        printf("        <LABEL FOR=\"password\">Verification Passwords:</LABEL></BR>");
        printf("        <INPUT TYPE=\"password\" NAME=\"Passwords2\" required></P>");

        printf("        <INPUT TYPE=\"SUBMIT\" VALUE=\"Create account\">");        
        printf("     </FORM></BR>");    
        printf("     </BODY>");
        printf("</HTML>");       
    }
}