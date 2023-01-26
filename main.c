#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define MAXLEN 256

// MARCIN BURCZYÑSKI

struct pytanie{
    char tresc[MAXLEN], o[4][MAXLEN], odp;
    int stanKonta0, stanKonta1, tab[4];
    struct pytanie* nast;
};
typedef struct pytanie PYTANIE;

PYTANIE* inicjalizujP(char* trescT, char* oAT, char* oBT, char* oCT, char* oDT, char odpT)
{

    PYTANIE* nowy;
    nowy=(PYTANIE*)malloc(sizeof(PYTANIE));

    strcpy(nowy->tresc, trescT);
    strcpy(nowy->o[0], oAT);
    strcpy(nowy->o[1], oBT);
    strcpy(nowy->o[2], oCT);
    strcpy(nowy->o[3], oDT);
    nowy->odp=odpT;

    nowy->nast=NULL;

    return nowy;
}

PYTANIE* inicjalizujP_no_arg()
{
    return inicjalizujP("0","0","0","0","0",'0');
}

int liczElementy(PYTANIE* head)
{
    if (head==NULL)
        return 0;
    int i=0;
    while (head!=NULL)
        i++;
    return i;
}


PYTANIE* pushBack(PYTANIE* head, char* trescT, char* oAT, char* oBT, char* oCT, char* oDT, char odpT)
{
    PYTANIE* nowy = inicjalizujP(trescT, oAT, oBT, oCT, oDT, odpT);
    PYTANIE* temp;
    temp=head;
    nowy->nast=NULL;


    if (head==NULL||head->odp=='0')
    {
        return nowy;
    }


    while(temp->nast!=NULL)
        temp=temp->nast;

    temp->nast=nowy;

    return head;
}

void wypiszListe(PYTANIE* head)
{
    while (head!=NULL)
    {
        wypiszPytanie(head);
        printf("Poprawna odpoweidz to:%c\n",head->odp);
        head=head->nast;
    }
}


void wypiszPytanie (PYTANIE* pyt)
{
   printf("%s\na.%sb.%sc.%sd.%s\n", pyt->tresc, pyt->o[0], pyt->o[1], pyt->o[2], pyt->o[3]);
}

void wypiszBalans(balans)
{
    printf("Twoj balans to: %d\n", balans);
}

int mechanikaPytania(PYTANIE* pytanie1, int balans)
{
    int tab[4], temp;

    for (int i=0;i<4;i++)
    {
       tab[i]=0;
    }
    pytanie1->stanKonta0=balans;
    for (int i=0;i<4;i++)
    {
        if (balans==0)
            break;

        while(1)
        {
            wypiszBalans(balans);
            wypiszPytanie(pytanie1);
            printf("Ile chcesz postawic na odpowiedz %c\n", i+97);
            scanf("%d", &temp);

            if (temp>=0 && temp<=balans)
            {
                tab[i]=temp;
                balans-=tab[i];
                system("cls");
                break;
            }

            printf("Blenda wartosc. Sprobuj jeszcze raz\n");
            Sleep(1000);
            system("cls");
        }
    }

    for (int i=0; i<4; i++)
    {
        pytanie1->tab[i]=tab[i];
    }

    balans=tab[pytanie1->odp-97];
    pytanie1->stanKonta1=balans;



   /* for (int i=0;i<4;i++)
    {
        printf("%c=%d\n",i+97,tab[i]);
    }
    wypiszBalans(balans);
    */
    return balans;
}

void wypiszHistorie(PYTANIE* head)
{
    while (head!=NULL)
    {
        printf("Stan konta przed pytaniem:%d\n",head->stanKonta0);
        wypiszPytanie(head);
        printf("\nA=%d  B=%d  C=%d  D=%d\n Poprawna odpowiedz to %c\n Stan konta po:%d\n\n", head->tab[0], head->tab[1], head->tab[2], head->tab[3], head->odp, head->stanKonta1);
        head=head->nast;
    }
}



PYTANIE* wczytajPytania(PYTANIE* head, char* sciezka)
{
    FILE* plik;
    plik=fopen(sciezka, "r");


    char* tresc, *oA, *oB, *oC, *oD, odp='a';

    tresc=(char*)malloc(sizeof(char)*MAXLEN);
    oA=(char*)malloc(sizeof(char)*MAXLEN);
    oB=(char*)malloc(sizeof(char)*MAXLEN);
    oC=(char*)malloc(sizeof(char)*MAXLEN);
    oD=(char*)malloc(sizeof(char)*MAXLEN);

    size_t x =256;


    for (int i=0; i<4; i++)
    {
        getline(&tresc, &x, plik);
        getline(&oA, &x, plik);
        getline(&oB, &x, plik);
        getline(&oC, &x, plik);
        getline(&oD, &x, plik);
        //printf("%s %s %s %s %s", tresc, oA, oB, oC, oD);
        head=pushBack(head, tresc, oA, oB, oC, oD, odp);
    }


    return head;
}

int powtarzaSie(int* t, int k)
{
    for (int i=0; i<k; i++)
    {
        if (t[i]==t[k])
            return 1;
    }

    return 0;
}


PYTANIE* losujOdpowiedz(PYTANIE* current)
{
    int a[4];
    int i = 0;
    while (i<4)
    {
        a[i]=rand()%4;
        if (powtarzaSie(a, i)==0)
            i++;
    }
    int x=0;
    for(int i=0;i<4;i++){
        if(a[i]==0)x=i;
    }

    current->odp=x+97;

    char oS[4][MAXLEN];

    for (int i=0; i<4; i++)
    {
        strcpy(oS[i],current->o[a[i]]);
    }

    for (int i=0; i<4; i++)
    {
        strcpy(current->o[i],oS[i]);
    }

    return current;

}


PYTANIE* losujOdpowiedz_old(PYTANIE* current)
{
    //czasem dzia³a poprawinie ten kod, czasem nie i nie mam pojêcia czemu
    //zostawiam tutaj ¿eby przeanalizowaæ póŸniej

    int a[4];
    char oS[4][MAXLEN];

    for (int i=0; i<4; i++)
    {
        strcpy(oS[i],current->o[i]);
        printf("%s\n",oS[i]);
    }

    a[0]=rand()%4;
    printf("%d\n",a[0]);
    current->odp=a[0]+97;

    int i=1;
    while (i<4)
    {
        a[i]=rand()%4;
        if (powtarzaSie(t, i)==0)
            i++;
    }


    for (int i=0; i<4; i++)
    {
        strcpy(current->o[i],oS[a[i]]);
        printf("%d ", a[i]);
    }
    printf("\n");
    return current;
}

void losujOdpowiedzi(PYTANIE* head)
{
    PYTANIE* temp;
    temp=head;

    while (temp!=NULL)
    {
        temp=losujOdpowiedz(temp);
        temp=temp->nast;
    }

}

int dlugoscListy(PYTANIE* head)
{
    int i=0;
    if (head==NULL)
        return 0;

    while (head!=NULL)
    {
        head=head->nast;
        i++;
    }

    return i;
}


void zamien2(PYTANIE** head, PYTANIE* a, PYTANIE* b)
{
    PYTANIE* temp1a, *temp1b, *temp;

    if (a==b)
        return 0;

    temp1a=*head;
    temp1b=*head;

    if (a==*head)
        temp1a=NULL;
    else
    {
        while (temp1a->nast!=a)
            temp1a=temp1a->nast;
    }

    if (b==*head)
        temp1b=NULL;
    else
    {
        while (temp1b->nast!=b)
            temp1b=temp1b->nast;
    }

    if (temp1a!=NULL)
        temp1a->nast=b;
    else
        *head=b;

    if (temp1b!=NULL)
        temp1b->nast=a;
    else
        *head=a;


    temp=a->nast;
    a->nast=b->nast;
    b->nast=temp;

}




PYTANIE* losujKolejnosc(PYTANIE* head, int len)
{
    PYTANIE* tempa, *tempb;

    int a,b;

    for (int i=0; i<10; i++)
    {
        a=rand()%len;
        b=rand()%len;

        tempa=head;
        tempb=head;

        for (int j=0; j<a; j++)
            tempa=tempa->nast;

        for (int j=0; j<b; j++)
            tempb=tempb->nast;

        zamien2((&head), tempa, tempb);

    }


    return head;
}

void czysc(PYTANIE** head)
{
    PYTANIE* temp;

    while ((*head)!=NULL)
    {
        temp=(*head)->nast;
        free(*head);
        (*head)=temp;
    }

}

int main()
{

    int balans=100;
    char c;

    srand(time(NULL));

    PYTANIE* head = NULL;
    PYTANIE* current;

    /*
    head=pushBack(head, "Testowe pytanie nr1.", "A-poprawna", "B", "C", "D", 'a');
    head=pushBack(head, "Testowe pytanie nr2.", "A", "B", "C", "D", 'a');
    head=pushBack(head, "Testowe pytanie nr3.", "A", "B", "C", "D", 'a');
    head=pushBack(head, "Testowe pytanie nr4.", "A", "B", "C", "D", 'a');
    */
    head=wczytajPytania(head, "input.txt");
    losujOdpowiedzi(head);
    head=losujKolejnosc(head,dlugoscListy(head));


    current=head;


   while (1)
   {
       system("cls");
       printf("        Postaw na stowke (Postaw na milion)\n\n\n\n 1.Rozpocznij gre\n 0.Wyjdz z gry\n\n");
       c = getchar();

       switch (c)
       {
           case '1':
           {
                while (current!=NULL)
                {
                    system("cls");
                    balans=mechanikaPytania(current, balans);
                    current=current->nast;
                    printf("Zostalo %d zlociszy\n",balans);
                    getchar();
                    getchar();
                }
                printf("Gratulacje! wygrales %d zlociszy\n\n",balans);
                getchar();
                getchar();
                system("cls");
                wypiszHistorie(head);
                printf("Nacisnij cokolwiek zeby skonczyc");
                getchar();
                getchar();
                current=head;
                break;
           }

           case '2':
           {
                wypiszListe(head);
                //wypiszListe(current);
                printf("Dlugosc listy wynosi %d\n", dlugoscListy(head));
                getchar();
                getchar();
                break;
           }

           case '0':
           {
               czysc(&head);
               return 0;
           }
       }

   }



    return 0;
}
