#include<stdio.h>

struct SHA{
    int pv[100];
    int pn[100];
};
struct SHA process[100],token;

// cur = j    pst = i
void receive(int pst,int sn,int n,int cur){
    int i,j,valv,valn;
    if(process[cur].pn[pst] < sn){
        process[cur].pn[pst] = sn;
        valv = process[cur].pv[cur];
        valn = process[cur].pn[cur];
        switch(valv){
            case 0:
                process[cur].pv[pst] = 1;
                break;
            case 1:
                if(process[cur].pv[pst] != 1){
                    process[cur].pv[pst] = 1;
                    receive(cur,valn,n,pst);
                }
                break;
            case 2:
                process[cur].pv[pst] = 1;
                break;
            case 3:
                process[cur].pv[pst] = 1;
                token.pv[pst] = 1;
                token.pn[pst] = sn;
                process[cur].pv[cur] = 0;
                process[pst].pv[pst] = 3;
                break;
        }
    }
}


void request(int pst,int n){
    int sn,i,j;
    process[pst].pv[pst] = 1;
    process[pst].pn[pst] +=1;
    sn = process[pst].pn[pst];

    for(j=1;j<=n;j++){
        if(process[pst].pv[j] == 1){
            receive(pst,sn,n,j);
        }
    }
}


int main(){
    int queue[100],qvar=0;
    int n,tk,con=1,val,i,j,pst;
    printf("Enter how many process\n");
    scanf("%d",&n);
    
     // 0-none 1-req 2-exe 3-hold
    for(i=1;i<=n;i++){
        for(j=1;j<=n;j++){
            process[i].pv[j] = 0;
            process[i].pn[j] = 0;
        }
    }
    
    for(i=2;i<=n;i++){
        for(j=i-1;j>=1;j--){
            process[i].pv[j] = 1;
        }
    }

    process[1].pv[1] = 3;
    token.pv[1] = 3; 
    for(i=1;i<=n;i++){
        token.pv[i] = 0;
        token.pn[i] = 0;
    }

    while(con){
        printf("1. Start\n");
        printf("2. Execute\n");
        printf("3. Exit\n");
        printf("4. Process Queue\n");
        printf("5. Processes token and state\n");
        printf("6. Token value \n");
        scanf("%d",&val);
        
        switch(val){
            i =0;
            j =0;
            case 1:
                printf("Enter which process want to send request\n");
                scanf("%d",&pst);
                if(process[pst].pv[pst] == 3){
                    printf("This process has token\n\n");
                    break;
                }
                else{
                    request(pst,n);
                }
                break;
            case 2:
                for(i=1;i<=n;i++){
                    if(process[i].pv[i] == 3){
                        break;
                    }
                }
                printf("Process %d is executing\n",i);
                process[i].pv[i] = 2;
                break;
            case 3:
                for(i=1;i<=n;i++){
                    if(process[i].pv[i] == 2){
                        break;
                    }
                }
                printf("Process %d is exits\n",i);
                process[i].pv[i] = 0;
                token.pv[i] = 0;
                for(j=1;j<=n;j++){
                    if(process[i].pn[j] > token.pn[j]){
                        token.pv[j] = process[i].pv[j];
                        token.pn[j] = process[i].pn[j];
                    }else{
                        process[i].pv[j] = token.pv[j];
                        process[i].pn[j] = token.pn[j];
                    }
                }
                process[i].pv[i] = 3;
                break;
            case 5: 
                for(i=1;i<=n;i++){
                    printf("Process %d\n",i);
                    for(j=1;j<=n;j++){
                        printf("%d\t", process[i].pv[j]);
                        printf("%d\n\n", process[i].pn[j]);
                    }
                }
                break;
            case 6:
                 for(i=1;i<=n;i++){
                    printf("%d\t", token.pv[i]);
                    printf("%d\n\n",token.pn[i]);
                 }
        }
        printf("Continue\n");
        scanf("%d",&con);
    }
}