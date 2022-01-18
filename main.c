#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>



union Dane{
    unsigned long long var;
};



unsigned long long pick_num(unsigned long long a,union Dane *data){
    unsigned long long tmp,tmp1;
    tmp1=data->var-1;
    if(tmp1 >a)
        tmp1= tmp1-a;
    else
    {
        tmp= a-tmp1;
        a=tmp1;
        tmp1=tmp;
    }

    if (tmp1) {
        return rand() % tmp1 + a;
    } else {
        return a;
    }
}

unsigned long long gcd(unsigned long long x,union Dane *dane){
    unsigned long  long tmp,tmp1;
    tmp= x;
    tmp1=dane->var;
    while (tmp != tmp1){
        if(tmp>tmp1)
            tmp = tmp-tmp1;
        else
            tmp1= tmp1-tmp;
    }
    return tmp;
}

unsigned long long pot_mod(unsigned long long a,unsigned long long b,unsigned long long c){

    unsigned long long result =1,x;
    x=a;
    do{
        x%=c;
        if(b&1){
            result *=x;
            result %= c;
        }
        x*=x;
    } while (b>>1);
    return result;
}

bool czy_pierwsza(union Dane *dane){
    bool flaga = true;
    for (unsigned long long i = 2; i <dane->var; ++i) {
        if(dane->var % i == 0) {
            flaga = false;
            break;
        }
    }
    if(flaga)
        return true;
    else
        return false;
}


int main(int argc,char **argv) {

    srand(time(NULL));
    union Dane *data = malloc(sizeof(union Dane));
    data->var= strtoull(argv[1],0,0);
    unsigned long long x,y,i=1;

    if(czy_pierwsza(data)){
        printf("0");
        free(data);
        exit(0);
    }

    x= pick_num(2,data);
    //printf("%llu",x);
    //printf("\n%llu",data->var);

    if(gcd(x,data) != 1) {
        printf("%llu",gcd(x,data));
        free(data);
        exit(0);

    }
    while (gcd(x-1,data) == 1){
        x = pot_mod(x,i,data->var);
        i++;
    }
    if(x== 1) {
        printf("-1");
        free(data);
        exit(0);
    }
    else
        printf("%llu", gcd(x-1,data));
    free(data);

    return 0;
}
