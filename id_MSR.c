#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char data_input();
void get_data(char *data);
void class(int num1);
void verification_netmask(char *MSR_input, int num1, int num2, int num3, int num4);
void network_Address (int num1, int num2, int num3, int num4);
void Broadcast_Address (int num1, int num2, int num3, int num4);

int main (){
    data_input();
    return 0;
}

char data_input(){
    char *data_input=NULL;
    data_input=getenv("QUERY_STRING");
    get_data(data_input);
}


void get_data(char *data_input) {
    char n1[100] = {0},
        n2[100] = {0},
        n3[100] = {0}, 
        n4[100] = {0},
        m1[100] = {0},
        m2[100] = {0},
        m3[100] = {0}, 
        m4[100] = {0},
        IP_input[100] = {0},
        MSR_input[100] = {0};
    int i,
        wordIP=0,
        wordMSR=0,
        num1 = 0,
        num2 = 0, 
        num3 = 0, 
        num4 = 0,
        numM1 = 0,
        numM2 = 0, 
        numM3 = 0, 
        numM4 = 0,
        valid = 1;


    //get IP and MSR
    sscanf(data_input, "%99[^&]&%99s", IP_input, MSR_input);

    //verify if it has a word
    for(i=5; IP_input[i]!='\0'; i++){
        if(IP_input[i]>='a'&& IP_input[i]<='z'||IP_input[i]<='z'||IP_input[i]>='A'&& IP_input[i]<='Z'){
            wordIP=1;
        }
    }
    for(i=4; MSR_input[i]!='\0'; i++){
        if(MSR_input[i]>='a'&& MSR_input[i]<='z'||MSR_input[i]<='z'||MSR_input[i]>='A'&& MSR_input[i]<='Z'){
            wordMSR=1;
        }
    }    

    if (strncmp(IP_input, "Data=", 5) == 0 || strncmp(MSR_input, "MRS=", 4) == 0 || wordIP==0 || wordMSR==0 || i<=19) {
        sscanf(IP_input + 5, "%99[^.].%99[^.].%99[^.].%99s", n1, n2, n3, n4);
        sscanf(MSR_input + 4, "%99[^.].%99[^.].%99[^.].%99s", m1, m2, m3, m4);
        num1 = atoi(n1);
        num2 = atoi(n2);
        num3 = atoi(n3);
        num4 = atoi(n4);
        numM1 = atoi(m1);
        numM2 = atoi(m2);
        numM3 = atoi(m3);
        numM4 = atoi(m4);

       if (num1 < 0 || num1 > 256 || num2 < 0 || num2 > 256 || num3 < 0 || num3 > 256 || num4 < 0 || num4 > 256 || numM1 < 0 || numM1 > 256 || numM2 < 0 || numM2 > 256 || numM3 < 0 || numM3 > 256 || numM4 < 0 || numM4 > 256) {
            valid = 0;
        }
    }else {
        valid = 0;
    }

    printf("Content-Type: text/html\n\n");
    printf("<!DOCTYPE HTML>\n");
    printf("<HTML>\n");
    printf("<HEAD><LINK rel=\"stylesheet\" href=\"fond.css\"/></HEAD>\n");
    printf("<BODY>\n");

    if (!valid) {
        printf("<B>Invalid IP Address.</B><BR>\n");
        printf("<FORM ACTION=\"id_MSR.cgi\" METHOD=\"get\">\n");
        printf("<LABEL FOR=\"Data\">IP :</LABEL>\n");
        printf("<INPUT TYPE=\"text\" NAME=\"Data\" PLACEHOLDER=\"Ex: xxx.xxx.xxx.xxx\" required>\n");
        printf("<LABEL FOR=\"MRS\">MRS :</LABEL>\n");
        printf("<INPUT TYPE=\"text\" NAME=\"MRS\" PLACEHOLDER=\"Ex: xxx.xxx.xxx.xxx\" required>\n");
        printf("<INPUT TYPE=\"SUBMIT\" VALUE=\"Send\">\n");
        printf("</FORM>\n");
    } else {
        class(num1);
        printf("<BR>\n");
        verification_netmask(MSR_input, num1, num2, num3, num4);
        printf("</BODY>\n");
        printf("</HTML>\n");
    }
}

void class(int num1){
    if (num1>=0 && num1<=127){
        printf("        IPv4: A Class</BR>");
    }
    else if(num1>127 && num1<=191){
        printf("        IPv4: B Class</BR>");
    }
    else if(num1>191 && num1<=223){
        printf("        IPv4: C Class</BR>");
    }
    else if(num1>223 && num1<=239){
        printf("        IPv4: D Class</BR>");
    }
    else if(num1>239 && num1<=255){
        printf("        IPv4: E Class</BR>");
    }
}


void verification_netmask(char *MSR_input, int num1, int num2, int num3, int num4){
    char A[]="255.0.0.0",
        B[]="255.255.0.0",
        C[]="255.255.255.0";
    if(strcmp(MSR_input+4, A)==0){
        printf("netmask valid</BR>");
        network_Address(num1, num2, num3, num4);
        Broadcast_Address(num1, num2, num3, num4);

    }else if(strcmp(MSR_input+4, B)==0){
        printf("netmask valid</BR>");
        network_Address(num1, num2, num3, num4);
        Broadcast_Address(num1, num2, num3, num4);

    }else if(strcmp(MSR_input+4, C)==0){
        printf("netmask valid</BR>");
        network_Address(num1, num2, num3, num4);
        Broadcast_Address(num1, num2, num3, num4);

    }else{
        printf("Unknown netmask</BR>");
        //printf("<B>Invalid IP Address.</B><BR>\n");
        printf("<FORM ACTION=\"id_MSR.cgi\" METHOD=\"get\">\n");
        printf("<LABEL FOR=\"Data\">IP :</LABEL>\n");
        printf("<INPUT TYPE=\"text\" NAME=\"Data\" PLACEHOLDER=\"Ex: xxx.xxx.xxx.xxx\" required>\n");
        printf("<LABEL FOR=\"MRS\">MRS :</LABEL>\n");
        printf("<INPUT TYPE=\"text\" NAME=\"MRS\" PLACEHOLDER=\"Ex: xxx.xxx.xxx.xxx\" required>\n");
        printf("<INPUT TYPE=\"SUBMIT\" VALUE=\"Send\">\n");
        printf("</FORM>\n");
    }
}

void network_Address (int num1, int num2, int num3, int num4){
    char A[]="255.0.0.0",
        B[]="255.255.0.0",
        C[]="255.255.255.0";
    if(num1>=0 && num1<=127){
        printf("    %d.%d.%d.%d</BR>[AND]</BR>    %s</BR>_____________</BR>", num1, num2, num3, num4, A);
        printf("    %d.0.0.0</BR></BR>", num1);
        printf("IP Address=%d.%d.%d.%d</BR>", num1, num2, num3, num4);
        printf("MSR=%s</BR>", A);
        printf("network_Address=%d.0.0.0</BR>", num1);
    }else if(num1>127 && num1<192){
        printf("    %d.%d.%d.%d</BR>[AND]</BR>    %s</BR>_____________</BR>", num1, num2, num3, num4, B);
        printf("    %d.%d.0.0</BR></BR>", num1, num2);
        printf("IP Address=%d.%d.%d.%d</BR>", num1, num2, num3, num4);
        printf("MSR=%s</BR>", B);
        printf("network_Address=%d.%d.0.0</BR>", num1, num2);
    }else if(num1>191 && num1<224){
        printf("    %d.%d.%d.%d</BR>[AND]</BR>    %s</BR>_____________</BR>", num1, num2, num3, num4, C);
        printf("    %d.%d.%d.0</BR></BR>", num1, num2, num3);
        printf("IP Address=%d.%d.%d.%d</BR>", num1, num2, num3, num4);
        printf("MSR=%s</BR>", C);
        printf("network_Address=%d.%d.%d.0</BR>", num1, num2, num3);
    }else if(num1>223 && num1<256){
        printf("Unknown</BR>");
    }
}

void Broadcast_Address (int num1, int num2, int num3, int num4){
    if(num1>=0 && num1<=127){
        printf("Broadcast_Address=%d.255.255.255</BR></BR>", num1);
    }else if(num1>127 && num1<192){
        printf("Broadcast_Address=%d.%d.255.255</BR></BR>", num1, num2);
    }else if(num1>191 && num1<224){
        printf("Broadcast_Address=%d.%d.%d.255</BR></BR>", num1, num2, num3);

    }else if(num1>223 && num1<256){
        printf("Unknown</BR>");
    }
}