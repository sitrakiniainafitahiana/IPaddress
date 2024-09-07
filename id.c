#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char data_input();
void get_data(char *data);
void use_data(int num1, int num2, int num3, int num4);
void class(int num1);
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
        n4[100] = {0};
    int i,
        count=0,
        num1 = 0,
        num2 = 0, 
        num3 = 0, 
        num4 = 0,
        valid = 1;
    
    for(i=5; data_input[i]!='\0'; i++){
        if(data_input[i]>='a'&& data_input[i]<='z'||data_input[i]>='A'&& data_input[i]<='Z'){
            count=1;
        }
    }
    // Verify if it start without "Data="
    if (strncmp(data_input, "Data=", 5) == 0 && count==0 && i<=19) {
        // Extract the part of IP Addresse
        
        sscanf(data_input + 5, "%99[^.].%99[^.].%99[^.].%99s", n1, n2, n3, n4);

        num1 = atoi(n1);
        num2 = atoi(n2);
        num3 = atoi(n3);
        num4 = atoi(n4);

        if (num1 < -1 || num1 > 256 || num2 < -1 || num2 > 256 || num3 < -1 || num3 > 256 || num4 < -1 || num4 > 256) {
            valid = 0;
        }
    } else {
        valid = 0;
    }

    printf("Content-Type: text/html\n\n");
    printf("<!DOCTYPE HTML>\n");
    printf("<HTML>\n");
    printf("<HEAD><LINK rel=\"stylesheet\" href=\"fond.css\"/></HEAD>\n");
    printf("<BODY>\n");

    if (!valid) {
        printf("<B>Invalid IP Address.</B><BR>\n");
        printf("<FORM ACTION=\"id.cgi\" METHOD=\"get\">\n");
        printf("<LABEL FOR=\"Data\">IP :</LABEL>\n");
        printf("<INPUT TYPE=\"text\" NAME=\"Data\" PLACEHOLDER=\"Ex: xxx.xxx.xxx.xxx\" required>\n");
        printf("<INPUT TYPE=\"SUBMIT\" VALUE=\"Envoyer\">\n");
        printf("</FORM>\n");
    } else {
        printf("<B>Addresse IP valide</B><BR>\n");
        class(num1);
        printf("<BR>\n");
        network_Address(num1, num2, num3, num4);
        Broadcast_Address(num1, num2, num3, num4);
    }

    printf("</BODY>\n");
    printf("</HTML>\n");
}

void use_data(int num1, int num2, int num3, int num4){
    int Not_IP=256;
    if (num1 >= Not_IP||num1 < -1||num2 >= Not_IP||num2 < -1||num3 >= Not_IP||num3 < -1||num4 >= Not_IP||num4 < -1){ 
        printf("<!DOCTYPE HTML>\n");
        printf("<HTML>");
        printf("    <LINK rel=\"stylesheet\" href=\"fond.css\"/>");
        printf("    <LINK rel=\"stylesheet\" href=\"Style.css\"/>");
        printf("    <BODY>");
        printf("        <B>invalid IP Address</B></BR>");
        printf("    </BODY>");
        printf("</HTML>");
    }else{
        printf("<!DOCTYPE HTML>\n");
        printf("<HTML>");
        printf("    <LINK rel=\"stylesheet\" href=\"fond.css\"/>");
        printf("    <LINK rel=\"stylesheet\" href=\"Style.css\"/>");
        printf("    <BODY>");
        printf("        <B>valid IP Address</B></BR>");

        class(num1);
        printf("\n");
        network_Address(num1, num2, num3, num4);
        Broadcast_Address(num1, num2, num3, num4);
        printf("    </BODY>");
        printf("</HTML>");
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

void network_Address (int num1, int num2, int num3, int num4){
    if(num1>=0 && num1<=127){
        printf("    %d.%d.%d.%d</BR>[AND]</BR>    255.0.0.0</BR>_____________</BR>", num1, num2, num3, num4);
        printf("    %d.0.0.0</BR></BR>", num1);
        printf("IP Address=%d.%d.%d.%d</BR>", num1, num2, num3, num4);
        printf("MSR=255.0.0.0</BR>");
        printf("network_Address=%d.0.0.0</BR>", num1);
    }else if(num1>127 && num1<192){
        printf("    %d.%d.%d.%d</BR>[AND]</BR>    255.255.0.0</BR>_____________</BR>", num1, num2, num3, num4);
        printf("    %d.%d.0.0</BR></BR>", num1, num2);
        printf("IP Address=%d.%d.%d.%d</BR>", num1, num2, num3, num4);
        printf("MSR=255.255.0.0</BR>");
        printf("network_Address=%d.%d.0.0</BR>", num1, num2);
    }else if(num1>191 && num1<224){
        printf("    %d.%d.%d.%d</BR>[AND]</BR>    255.255.255.0</BR>_____________</BR>", num1, num2, num3, num4);
        printf("    %d.%d.%d.0</BR></BR>", num1, num2, num3);
        printf("IP Address=%d.%d.%d.%d</BR>", num1, num2, num3, num4);
        printf("MSR=255.255.225.0</BR>");
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
