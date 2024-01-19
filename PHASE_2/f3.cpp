#include<bits/stdc++.h>
using namespace std;

int flag = 0;
int Allocate();
void Read();
void Write();
void simulation();
void INIT();
void MOS();
void Load();
void PrintMem();
void STARTEXECUTION();
void EXECUTE_USER_PROGRAM();

char M [300][4];
char IR [4];
char R [4];
int IC;
int C;
int SI;

struct PCB{
    char JID[4];
    int TTL;
    int TLL; 
};

struct PCB jpcb;
int TTC,  LLC, PI, TI;
int PTR;
int flags[100], locs, pcr, cnt=0, key[30], value[30], key_index, currentLine, T,  gen_address, EM;
char buffer[100];

int main()
{
    FILE *f=NULL;
    char ch;
    f=fopen("Input.txt","r");
    if(f==NULL)
    {
        cout<<"File not found\n";
        exit(1);
    }
    fclose(f);

    cout<<"\nExecuting Program\n";
    INIT();
    Load();

    return 0; 
}

void INIT()
{
    for(int i=0;i<300;i++)
    {
        for(int j=0;j<4;j++)
            M[i][j]=' ';
    }
    for(int i=0;i<4;i++)
    {
        IR[i]=' ';
        R[i]=' ';
    }
    IC=0;
    SI=0;
    C=0;
    T=0;
    currentLine=0;
    jpcb.TTL=0;
    jpcb.TLL=0;
    TTC=0;
    LLC=0;
    PI=0;
    TI=0;
    EM=0;

    locs=-1;
    pcr=0;
    key_index=-1;
    cnt=0;

}

int Allocate()
{
    srand(time(NULL));
    int address;
    int l=0;
    while(1)
    {
        address = rand()%30;
        for(int i=0;i<=locs;i++)
        {
            if(flags[i] == address){
                l=1;
                break;
        }
       
        }
        if(l==0)
        {
            break;
        }
        else
        {
            l=0;
        }
    }
    locs++;
    flags[locs] = address;
    return address;
}


void Load()
{
    int i=0;
    FILE *fp=NULL;
    char ch;
    fp=fopen("Input.txt","r");


    while (fgets(buffer, 41, fp) != NULL)
    {
        if (buffer[0]=='$' && buffer[1]=='A' && buffer[2]=='M' && buffer[3]=='J')
        {
            PTR=Allocate()*10;
            jpcb.JID[0]=buffer[4];
            jpcb.JID[1]=buffer[5];
            jpcb.JID[2]=buffer[6];
            jpcb.JID[3]=buffer[7];

            jpcb.TTL=(buffer[8]-'0')*1000+(buffer[9]-'0')*100+(buffer[10]-'0')*10+(buffer[11]-'0');
            jpcb.TLL=(buffer[12]-'0')*1000+(buffer[13]-'0')*100+(buffer[14]-'0')*10+(buffer[15]-'0');

            for(int i=PTR;i<PTR+10;i++){
                M[i][0]='0';

                M[i][2]='*';
                M[i][3]='*';
            }
            
            cout<<"New Job Started\n";
            cout<<"JID : "<<jpcb.JID[0]<<jpcb.JID[1]<<jpcb.JID[2]<<jpcb.JID[3]<<endl;
            cout<<"TTL : "<<jpcb.TTL<<endl;
            cout<<"TLL : "<<jpcb.TLL<<endl;
            cout<<"PTR : "<<PTR<<"\n\n";

            int col=0;
            int temp,temp1;

            while(1)
            {
                    
                fgets(buffer, 100, fp);
                if((buffer[0]=='$' && buffer[1]=='D' && buffer[2]=='T' && buffer[3]=='A')) break;
                temp=Allocate();
                temp1=temp*10;
                M[PTR+pcr][0]='1';
                M[PTR+pcr][3]=temp%10+'0';
                M[PTR+pcr][2]=temp/10+'0';
                pcr++;
                
                col=0;
                for(int i=0;i<strlen(buffer)-1;i++)
                {
                        if (buffer[i]==' ') break;
                        M[temp1][col]=buffer[i];
                        col++;
                        if(col==4)
                        {
                            temp1++;
                            col=0;
                        }
                }       
            }
            
            currentLine =ftell(fp);       
        }
        if((buffer[0]=='$' && buffer[1]=='D' && buffer[2]=='T' && buffer[3]=='A'))
        {
            STARTEXECUTION();
        }


        if((buffer[0]=='$' && buffer[1]=='E' && buffer[2]=='N' && buffer[3]=='D'))
        {
            i++;    
            PrintMem();
            cout<<"\nJob nded\n";
            cout<<"\nPress Enter for Next Job\n";

            getchar();
            INIT();
        }
    }

    
}

void PrintMem()
{
    cout<<"Memory block is:\n";;
    int i,j;
      for(int i = 0; i<300; i++)
    { 
        cout<<"Memory["<<i<<"]\t";
        for( j = 0; j<4; j++ )
        {  
            cout<<M[i][j];
        }
        cout<<endl;
        if(i%10==9) cout<<endl;
    }  
}

int Address_AddressMap2(int IC ){
        if(IC%10 == 0 && IC!=0){
            cnt++;
        }
        int address=(M[PTR+cnt][2]-'0')*10+(M[PTR+cnt][3]-'0');
        
        address=address*10+IC%10;
        
        return address;
    
        
    }
    
int AddressMap2(int add){
    if(IR[0]=='H' && IR[1]==' ' && IR[2]==' ' && IR[3]==' ') return 0;



    if(IR[0]=='B' && IR[1]=='T') return 0;
        
    
    if(IR[2]-'0'<0 || IR[2]-'0'>9 || IR[3]-'0'<0 || IR[3]-'0'>9){
        PI=2;
        MOS();
        return 0;
    } 
    
    for(int i=0;i<=key_index;i++){
        if(key[i]==(add/10)*10){
            return (value[i])*10+add%10;
        }
    }
    
    {
        PI=3;
        MOS();
        
        return 0;

    }
}

void Terminate(int msg){
    T=1;
    
    FILE *fp=NULL;
    fp=fopen("Output.txt","a");
    char id[10];
    fprintf(fp,"\nJob ID: \n");
    fputc(jpcb.JID[0],fp);
    fputc(jpcb.JID[1],fp);
    fputc(jpcb.JID[2],fp);
    fputc(jpcb.JID[3],fp);
    fprintf(fp,"\n");
    
    switch (msg)
    {
    case 0:
        fputs("  Job terminated normally no error\n",fp);
        break;
    case 1:
        fputs("  Data out of range \n",fp);
        break;
    case 2:
        fputs("  Line limit exceeded error \n",fp);
        break;
    case 3:
        fputs("  Time limit exceeded error \n",fp);
        break;
    case 4:
        fputs("  Invalid opcode error \n",fp);
        break;
    case 5:
        fputs("  Invalid operand error \n",fp);
        break;
    case 6:
        fputs("  Invalid page fault error \n",fp);
        break;
    case 7:
        fputs("  Time limit exceeded and invalid opcode \n",fp);
        break;
    case 8:
        fputs("  Time limit exceeded and invalid operand \n",fp);
        break;
    
    
    }
    fputs("IC : ",fp);
    fprintf(fp,"%d\n",IC);
    fputs("IR : ",fp);
    fputc(IR[0],fp);
    fputc(IR[1],fp);
    fputc(IR[2],fp);
    fputc(IR[3],fp);
    fputs("\nTTC : ",fp);
    fprintf(fp,"%d\n",TTC);
    fprintf(fp,"TTL : %d\n",jpcb.TTL);
    fputs("LLC : ",fp);
    fprintf(fp,"%d\n",LLC);
    fprintf(fp,"TLL : %d\n\n",jpcb.TLL);

}


void STARTEXECUTION(){
    IC=0;
    EXECUTE_USER_PROGRAM();
}



void EXECUTE_USER_PROGRAM(){
    while(1){
    int addr=Address_AddressMap2(IC);
    for(int i=0;i<4;i++){
        
        IR[i]=M[addr][i];
    }
    IC++;

    simulation();
    gen_address=AddressMap2((IR[2]-'0')*10+(IR[3]-'0'));
    if(T==1){
        break;
    }

    if(TI==2){
        MOS();
        break;
    }
    
    
    else if(IR[0]=='G' && IR[1]=='D'){
        SI=1;
        MOS();
        if(T==1) break;
        
    }
    else if(IR[0]=='P' && IR[1]=='D'){
        SI=2;
        MOS();
        if(T==1) break;
            
    }
    else if(IR[0]=='H' && IR[1]==' '){
        SI=3;
        MOS();
        break;
    }
    else if(IR[0]=='L' && IR[1]=='R'){
        int row = AddressMap2((IR[2]-'0')*10+(IR[3]-'0'));
        for(int i=0;i<4;i++)
            R[i]=M[row][i];
    
    }
    else if(IR[0]=='S' && IR[1]=='R'){
        int row = AddressMap2((IR[2]-'0')*10+(IR[3]-'0'));
        for(int i=0;i<4;i++)
             M[row][i]=R[i];
    
        
    }
    else if(IR[0]=='B' && IR[1]=='T'){
        if(C==1)
        {
            IC=(IR[2]-'0')*10+(IR[3]-'0');
            C=0;
         }
    }
    else if(IR[0]=='C' && IR[1]=='R'){
          int row = AddressMap2((IR[2]-'0')*10+(IR[3]-'0'));
    
        for(int i=0;i<4;i++){
            if(R[i]!=M[row][i]){
                C=0;
                break;
            }
            else{
                C=1;
            }
        }
    }
    else
    {
         PI=1;
      
        MOS();
        break;
    }

    }
}
    

void simulation(){
    TTC++;
    if(TTC>jpcb.TTL){
        TI=2;
        
    }
}



void MOS(){

    if(TI==0){
        if(SI==1){
            Read();
        }
        else if(SI==2){
            Write();
        }
        else if(SI==3){
            Terminate(0);
        }
        else if(PI==1){
            Terminate(4);
        }
         else if(PI==2){
                Terminate(5);
          }
        else if(PI==3){


            if((IR[0]=='G' && IR[1]=='D') || (IR[0]=='S' && IR[1]=='R') ){
     
                key_index++;
                key[key_index]=(IR[2]-'0')*10+(IR[3]-'0');
                value[key_index]=Allocate();
                int temp = value[key_index];
                M[PTR+pcr][0]='1';
                M[PTR+pcr][3]=temp%10+'0';
                M[PTR+pcr][2]=temp/10+'0';
                pcr++;
                PI=0;
                }
            else{

                Terminate(6);
            }
          }


        
    }


    else if(TI==2)
    {
        if(PI==0){

            if(IR[0]=='P' && IR[1]=='D'){
                Write();

            }
            Terminate(3);
        }
        else if(PI==1){
            Terminate(7);
        }
       else if(PI==2){
            Terminate(8);
        }
    else if(PI==3){
            Terminate(3);
        }



    }
    
        
}

void Read()
{
   int row = AddressMap2((IR[2]-'0')*10+(IR[3]-'0'));
    int col = 0;
    FILE *fp=NULL;
    fp=fopen("Input.txt","r");

    fseek(fp,currentLine,SEEK_SET);
    fgets(buffer, 100, fp);
    if((buffer[0]=='$' && buffer[1]=='E' && buffer[2]=='N' && buffer[3]=='D')){
         EM=1;
        Terminate(1);
        return;
    }
    for(int i=0;i<strlen(buffer)-1;i++){
        M[row][col]=buffer[i];
        col++;
        if(col==4){
            row++;
            col=0;
        }
    }
    currentLine =ftell(fp);
    SI=0;
    
}

void Write()
{
    FILE *fp=NULL;
    LLC++;
        if(LLC>jpcb.TLL){
            Terminate(2);

            return;
        }
    fp=fopen("Output.txt","a");
    if(flag==0) flag++;
    else fprintf(fp,"\n");
    int row = AddressMap2((IR[2]-'0')*10+(IR[3]-'0'));
    int col = 0;
    for(int i=row;i<row+10;i++){
        for(int j=0;j<4;j++){
            
            fputc(M[i][j],fp);

        }
        
        
    }
    SI=0;
    
}

