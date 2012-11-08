#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int F[3][3];
int B[3][3];
int R[3][3];
int L[3][3];
int U[3][3];
int D[3][3];
int AUX[3][3];

void rotU(void)
{
    for(int i=0;i<3;i++)
    {
        AUX[0][i]=F[0][i];
        F[0][i]=R[0][i];
        R[0][i]=B[0][i];
        B[0][i]=L[0][i];
        L[0][i]=AUX[0][i];
    }
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            AUX[i][j]=U[i][j];
        }
    }
    U[0][0]=AUX[2][0];
    U[0][1]=AUX[1][0];
    U[0][2]=AUX[0][0];
    U[1][0]=AUX[2][1];
    U[1][2]=AUX[0][1];
    U[2][0]=AUX[2][2];
    U[2][1]=AUX[1][2];
    U[2][2]=AUX[0][2];
};

void rotu(void)
{
    for(int i=0;i<3;i++)
    {
        AUX[0][i]=F[0][i];
        F[0][i]=L[0][i];
        L[0][i]=B[0][i];
        B[0][i]=R[0][i];
        R[0][i]=AUX[0][i];
    }
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            AUX[i][j]=U[i][j];
        }
    }
    U[0][0]=AUX[0][2];
    U[0][1]=AUX[1][2];
    U[0][2]=AUX[2][2];
    U[1][0]=AUX[0][1];
    U[1][2]=AUX[2][1];
    U[2][0]=AUX[0][0];
    U[2][1]=AUX[1][0];
    U[2][2]=AUX[2][0];
};

void rotd(void)
{
    for(int i=0;i<3;i++)
    {
        AUX[2][i]=F[2][i];
        F[2][i]=R[2][i];
        R[2][i]=B[2][i];
        B[2][i]=L[2][i];
        L[2][i]=AUX[2][i];
    }
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            AUX[i][j]=D[i][j];
        }
    }
    D[0][0]=AUX[0][2];
    D[0][1]=AUX[1][2];
    D[0][2]=AUX[2][2];
    D[1][0]=AUX[0][1];
    D[1][2]=AUX[2][1];
    D[2][0]=AUX[0][0];
    D[2][1]=AUX[1][0];
    D[2][2]=AUX[2][0];
};

void rotD(void)
{
    for(int i=0;i<3;i++)
    {
        AUX[2][i]=F[2][i];
        F[2][i]=L[2][i];
        L[2][i]=B[2][i];
        B[2][i]=R[2][i];
        R[2][i]=AUX[2][i];
    }
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            AUX[i][j]=D[i][j];
        }
    }
    D[0][0]=AUX[2][0];
    D[0][1]=AUX[1][0];
    D[0][2]=AUX[0][0];
    D[1][0]=AUX[2][1];
    D[1][2]=AUX[0][1];
    D[2][0]=AUX[2][2];
    D[2][1]=AUX[1][2];
    D[2][2]=AUX[0][2];
};

void rotF(void)
{
    AUX[2][0]=U[2][0];
    AUX[2][1]=U[2][1];
    AUX[2][2]=U[2][2];
    U[2][0]=L[2][2];
    U[2][1]=L[1][2];
    U[2][2]=L[0][2];
    L[0][2]=D[2][2];
    L[1][2]=D[2][1];
    L[2][2]=D[2][0];
    D[2][2]=R[2][0];
    D[2][1]=R[1][0];
    D[2][0]=R[0][0];
    R[0][0]=AUX[2][0];
    R[1][0]=AUX[2][1];
    R[2][0]=AUX[2][2];
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            AUX[i][j]=F[i][j];
        }
    }
    F[0][0]=AUX[2][0];
    F[0][1]=AUX[1][0];
    F[0][2]=AUX[0][0];
    F[1][0]=AUX[2][1];
    F[1][2]=AUX[0][1];
    F[2][0]=AUX[2][2];
    F[2][1]=AUX[1][2];
    F[2][2]=AUX[0][2];
};

void rotf(void)
{
    AUX[2][0]=U[2][0];
    AUX[2][1]=U[2][1];
    AUX[2][2]=U[2][2];
    U[2][0]=R[0][0];
    U[2][1]=R[1][0];
    U[2][2]=R[2][0];
    R[0][0]=D[2][0];
    R[1][0]=D[2][1];
    R[2][0]=D[2][2];
    D[2][2]=L[2][2];
    D[2][1]=L[1][2];
    D[2][0]=L[0][2];
    L[0][2]=AUX[2][2];
    L[1][2]=AUX[2][1];
    L[2][2]=AUX[2][0];
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            AUX[i][j]=F[i][j];
        }
    }
    F[0][0]=AUX[0][2];
    F[0][1]=AUX[1][2];
    F[0][2]=AUX[2][2];
    F[1][0]=AUX[0][1];
    F[1][2]=AUX[2][1];
    F[2][0]=AUX[0][0];
    F[2][1]=AUX[1][0];
    F[2][2]=AUX[2][0];
};

void rotb(void)
{
    AUX[0][0]=U[0][0];
    AUX[0][1]=U[0][1];
    AUX[0][2]=U[0][2];
    U[0][0]=L[2][0];
    U[0][1]=L[1][0];
    U[0][2]=L[0][0];
    L[0][0]=D[0][2];
    L[1][0]=D[0][1];
    L[2][0]=D[0][0];
    D[0][2]=R[2][2];
    D[0][1]=R[1][2];
    D[0][0]=R[0][2];
    R[0][2]=AUX[0][0];
    R[1][2]=AUX[0][1];
    R[2][2]=AUX[0][2];
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            AUX[i][j]=B[i][j];
        }
    }
    B[0][0]=AUX[0][2];
    B[0][1]=AUX[1][2];
    B[0][2]=AUX[2][2];
    B[1][0]=AUX[0][1];
    B[1][2]=AUX[2][1];
    B[2][0]=AUX[0][0];
    B[2][1]=AUX[1][0];
    B[2][2]=AUX[2][0];
};

void rotB(void)
{
    AUX[0][0]=U[0][0];
    AUX[0][1]=U[0][1];
    AUX[0][2]=U[0][2];
    U[0][0]=R[0][2];
    U[0][1]=R[1][2];
    U[0][2]=R[2][2];
    R[0][2]=D[0][0];
    R[1][2]=D[0][1];
    R[2][2]=D[0][2];
    D[0][2]=L[2][0];
    D[0][1]=L[1][0];
    D[0][0]=L[0][0];
    L[0][0]=AUX[0][2];
    L[1][0]=AUX[0][1];
    L[2][0]=AUX[0][0];
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            AUX[i][j]=B[i][j];
        }
    }
    B[0][0]=AUX[2][0];
    B[0][1]=AUX[1][0];
    B[0][2]=AUX[0][0];
    B[1][0]=AUX[2][1];
    B[1][2]=AUX[0][1];
    B[2][0]=AUX[2][2];
    B[2][1]=AUX[1][2];
    B[2][2]=AUX[0][2];
};

void rotl(void)
{
    AUX[0][0]=U[0][0];
    AUX[1][0]=U[1][0];
    AUX[2][0]=U[2][0];
    U[0][0]=F[0][0];
    U[1][0]=F[1][0];
    U[2][0]=F[2][0];
    F[0][0]=D[2][2];
    F[1][0]=D[1][2];
    F[2][0]=D[0][2];
    D[0][2]=B[0][2];
    D[1][2]=B[1][2];
    D[2][2]=B[2][2];
    B[0][2]=AUX[0][0];
    B[1][2]=AUX[1][0];
    B[2][2]=AUX[2][0];
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            AUX[i][j]=L[i][j];
        }
    }
    L[0][0]=AUX[0][2];
    L[0][1]=AUX[1][2];
    L[0][2]=AUX[2][2];
    L[1][0]=AUX[0][1];
    L[1][2]=AUX[2][1];
    L[2][0]=AUX[0][0];
    L[2][1]=AUX[1][0];
    L[2][2]=AUX[2][0];
};

void rotL(void)
{
    AUX[0][0]=U[0][0];
    AUX[1][0]=U[1][0];
    AUX[2][0]=U[2][0];
    U[0][0]=B[2][2];
    U[1][0]=B[1][2];
    U[2][0]=B[0][2];
    B[0][2]=D[0][2];
    B[1][2]=D[1][2];
    B[2][2]=D[2][2];
    D[0][2]=F[2][0];
    D[1][2]=F[1][0];
    D[2][2]=F[0][0];
    F[0][0]=AUX[0][0];
    F[1][0]=AUX[1][0];
    F[2][0]=AUX[2][0];
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            AUX[i][j]=L[i][j];
        }
    }
    L[0][0]=AUX[2][0];
    L[0][1]=AUX[1][0];
    L[0][2]=AUX[0][0];
    L[1][0]=AUX[2][1];
    L[1][2]=AUX[0][1];
    L[2][0]=AUX[2][2];
    L[2][1]=AUX[1][2];
    L[2][2]=AUX[0][2];
};

void rotR(void)
{
    AUX[0][2]=U[0][2];
    AUX[1][2]=U[1][2];
    AUX[2][2]=U[2][2];
    U[0][2]=F[0][2];
    U[1][2]=F[1][2];
    U[2][2]=F[2][2];
    F[0][2]=D[2][0];
    F[1][2]=D[2][1];
    F[2][2]=D[2][2];
    D[0][0]=B[0][0];
    D[1][0]=B[1][0];
    D[2][0]=B[2][0];
    B[0][0]=AUX[2][2];
    B[1][0]=AUX[1][2];
    B[2][0]=AUX[0][2];
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            AUX[i][j]=R[i][j];
        }
    }
    R[0][0]=AUX[2][0];
    R[0][1]=AUX[1][0];
    R[0][2]=AUX[0][0];
    R[1][0]=AUX[2][1];
    R[1][2]=AUX[0][1];
    R[2][0]=AUX[2][2];
    R[2][1]=AUX[1][2];
    R[2][2]=AUX[0][2];
};

void rotr(void)
{
    AUX[0][2]=U[0][2];
    AUX[1][2]=U[1][2];
    AUX[2][2]=U[2][2];
    U[0][2]=B[2][0];
    U[1][2]=B[1][0];
    U[2][2]=B[0][0];
    B[0][0]=D[0][0];
    B[1][0]=D[1][0];
    B[2][0]=D[2][0];
    D[0][0]=F[2][2];
    D[1][0]=F[1][2];
    D[2][0]=F[0][2];
    F[0][2]=AUX[0][2];
    F[1][2]=AUX[1][2];
    F[2][2]=AUX[2][2];
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            AUX[i][j]=R[i][j];
        }
    }
    R[0][0]=AUX[0][2];
    R[0][1]=AUX[1][2];
    R[0][2]=AUX[2][2];
    R[1][0]=AUX[0][1];
    R[1][2]=AUX[2][1];
    R[2][0]=AUX[0][0];
    R[2][1]=AUX[1][0];
    R[2][2]=AUX[2][0];
};

void rotacao(char C)
{
    if(C == 'U')
    {
        rotU();
    }
    if(C == 'u')
    {
        rotu();
    }
    if(C == 'D')
    {
        rotD();
    }
    if(C == 'd')
    {
        rotd();
    }
    if(C == 'F')
    {
        rotF();
    }
    if(C == 'f')
    {
        rotf();
    }
    if(C == 'B')
    {
        rotB();
    }
    if(C == 'b')
    {
        rotb();
    }
    if(C == 'R')
    {
        rotR();
    }
    if(C == 'r')
    {
        rotr();
    }
    if(C == 'L')
    {
        rotL();
    }
    if(C == 'l')
    {
        rotl();
    }
};

bool original(void)
{
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(F[i][j] != 1 || B[i][j] != 2 || R[i][j] != 3 || L[i][j] != 4 || U[i][j] != 5 || D[i][j] != 6 )
                return false;
        }
    }
    return true;
};

int main(void)
{
    char cubo[80];
    char a;
    int i,j,n,mov;
    printf("moves go here: ");
    scanf("%s",&cubo);
        for(i=0;i<3;i++)
        {
            for(j=0;j<3;j++)
            {
                F[i][j] = 1;
                B[i][j] = 2;
                R[i][j] = 3;
                L[i][j] = 4;
                U[i][j] = 5;
                D[i][j] = 6;
            }
        }
        n = strlen(cubo);
        mov = 0;
        do
        {
            for(i=0;i<n;i++)
            {
                rotacao(cubo[i]);
                mov++;
            }
        }while(original() != true);
        for(i=0;i<3;i++)
        {
            for(j=0;j<3;j++)
            {
                printf("%d", F[i][j]);
            }
            printf("\t");
            for(j=0;j<3;j++)
            {
                printf("%d", B[i][j]);
            }
            printf("\t");
            for(j=0;j<3;j++)
            {
                printf("%d", R[i][j]);
            }
            printf("\t");
            for(j=0;j<3;j++)
            {
                printf("%d", L[i][j]);
            }
            printf("\t");
            for(j=0;j<3;j++)
            {
                printf("%d", U[i][j]);
            }
            printf("\t");
            for(j=0;j<3;j++)
            {
                printf("%d", D[i][j]);
            }
            printf("\n");
        }
        mov=mov/n;
        printf("movimentos: %d",mov);
};
