/*Il dizionario della lingua italiana*/
/*Come si può evincere dal titolo l'idea alla base di questo programma è quello di creare un algoritmo in grado di simulare il funzionamento di un
dizionario della lingua italiana,cioè la ricerca di una parola digitata dall'utente e visualizzare il significato della parola corrispondente fra i
vari disponibili. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DIM 100

/*Per gestire bene le varie parole nel dizionario è utile avvalersi dei record che in C prendono il nome di struct, in particolare ogni parola è
identificata da una struct i cui due parametri sono parola cioè una stringa resa in C tramite un array di char e un'altra stringa significato che è
per l'appunto il significato della parola corrispondente,entrambi i due array hanno size DIM,questa parola viene riconosciuta dal programma come il
valore 100 in qualsiasi parte del codice grazie alla define corrispondente. Molto importante in questo caso è l'uso del typedef con la struct, in
questo modo il tipo di struct sopra descritta può essere indicato scrivendo solamente Vocabolo che diventa infatti un nuovo tipo*/
typedef struct{
    char parola[DIM];
    char significato[DIM];
}Vocabolo;

void ord_sel_max_S(Vocabolo[DIM],int);
void scambiare_S(Vocabolo *,Vocabolo *);
int ric_bin(char chiave[],Vocabolo elenco[DIM],int n);
void min_dizionario(Vocabolo dizionario[DIM],int n);

/*Il main è la zona in cui riempiremo il nostro dizionario,richiameremo le funzioni che andremo ad utilizzare e viene spiegato tramite delle printf
come utilizzare il nostro dizionario.*/
int main()
{
/*Tra le variabili di input che andiamo ad utilizzare vi è l'array di struct dizionario indicato di tipo Vocabolo,il quale verrà riempito nei
rispettivi parametri da il nome che andremo a cercare e dal corrispettivo significato. La variabile cdr è una stringa anch'essa identificata
tramite un array di caratteri,in questo modo tramite una scanf posso assegnare da tastiera una stringa a questa variabile la quale corrisponderà
al nome del significato che l'utente vuole visualizzare. Alla variabile scelta può essere assegnato tramite scanf un valore da 0 a 1 o qualsiasi altro
valore nel caso si volesse chiudere il programma,il valore della variabile scelta è la chiave della condizione grazie al quale possiamo controllare la
struttura if.Nel caso il valore di scelta digitato sia uguale a 0 potremmo assegnare una stringa alla variabile cdr e ricercare la stringa col
rispettivo significato,se selta invece sarà uguale a 1 allora potremmo osservare tutti i vocaboli presenti nel dizionario fino ad ora. La peculiarità
di questo dizionario è che grazie alla funzione strlwr sia la chiave sia il nome di un vocabolo, può essere scritto in maiuscolo o minuscolo o con
caratteri misti, questo verrà spiegato meglio più avanti.Tutto ciò avviene all'interno di un ciclo do while il quale ci permette di compiere azioni
con il nostro dizionario finchè non premiamo il tasto 0 una volta richiestoci.*/
    char cdr[DIM];
    int n,i,indice,scelta,hu;
    Vocabolo dizionario[DIM]={{"bomba","\"Involucro contenente esplosivo\""},
                                {"buca","\"Cavita del terreno\""},
                                {"buddismo","\"Religione indiana\""},
                                {"cicca","\"Avanzo di sigaro o di sigaretta\""},
                                {"carne","\"La parte dei tessuti molli del corpo\""},
                                {"chioma","\"Folta capigliatura\""},
                                {"abete","\"Nome di alcuni alberi\""},
                                {"zappa","\"Arnese da contadino\""},
                                {"abiosfera","\"Parte del nostro pianeta dove non e' possibile la vita\""},
                                {"abisso","\"Luogo in cui la grande profondita' conferisce un aspetto buio e pauroso\""},
                                {"focaccia","\"Alimento a base di farina\""},
                                {"antonio","\"Nome proprio di persona\""},
                                {"bambu","\"Nome comune di una pianta\""},
                                {"argilla", "\"Tipo di roccia sedimentaria\""},
                                {"collare","\"Oggetto da mettere al collo degli animali\""},
                                {"pizza","\"Buona quella fatta a Napoli\""},
                                {"buongiorno","\"Forma di saluto al mattino\""},
                                {"buonanotte","\"Forma di saluto alla sera\""},
                                {"fiat","\"Marca di automobili\""},
                                {"SPIAGGIA","\"Mi piace fare il bagno\""},
                                {"coppia","\"Abbinamento di due cose o persone\""}};
    n=21;
    system("color 02");
    printf("\n\t\t\t - DIZIONARIO DELLA LINGUA ITALIANA - \t\t\t \n\n\n");
    do{
        ord_sel_max_S(dizionario,n);
        printf("\n\tID:0-Cerca una Parola nel dizionario.\n");
        printf("\tID:1-Parole presenti nel dizionario.\n");
        printf("\tPREMERE-Qualsiasi altro tasto per uscire\n\n");
        printf("\tDigitare l'ID della tua scelta: ");
        fflush(stdin);
        scanf("%d",&scelta);
        fflush(stdin);
        if (scelta==0){
            printf("\tInserire parola da ricercare: ");
            scanf("%s",&cdr);
            indice=ric_bin(cdr,dizionario,n);
            printf("\n\t%s\n\n",dizionario[indice].significato);
        }
        else if(scelta==1){
            printf("\n\tLe parole presenti in questo dizionario sono:\n");
            for(i=0;i<n;i++){
                printf("\t-%s\n",dizionario[i].parola);
            }
        }
        else
            return 0;
        printf("\n");
        printf("\n\tVuoi compiere un'altra operazione? (0 == No || 1 == Si)\n\tScegli: ");
        scanf("%d",&hu);
        system("cls");
    }while( hu==1);
    system("cls");
    system("pause");
}

/*La funzione scambiare_S si occupa di scambiare due elementi, in questo caso l'elemento più grande del nostro array con quello nella posizione
corrispettiva.*/
void scambiare_S(Vocabolo *s1,Vocabolo *s2)
{
    Vocabolo temp;
    temp=*s1;
    *s1=*s2;
    *s2=temp;
}

/*La void ord_sel_max_S si occupa del vero e proprio ordinamento del nostro dizionario in base al parametro parola dei nostri vocaboli in modo che
sia indicizzato per lettere e che si possa utilizzare la ricerca binaria. Questa funzione si avvale della scambiare_S e dells funzione stlwr di string.h
la prima per mettere la parola da ordinare nella giusta posizione, la seconda per rendere minuscolo qualsiasi vocabolo scritto nel dizionario in modo
da poterlo scrivere sia in maiuscolo che in minuscolo on in caratteri misti, ciò viene fatto facendo scorrere il dizionario dal primo elemento
fino all'ultimo,successivamente questo viene ordinata scorrendo l'array dall'ultimo elemento fino al primo e scambianfo le parole in modo corretto
grazie al displaicement negl'indici. */
void ord_sel_max_S(Vocabolo dizionario[DIM],int n)
{
    int i;
    for(i=0;i<n;i++)
        strlwr(dizionario[i].parola);
    for(i=n-1;i>0;i--)
        scambiare_S(&dizionario[i],&dizionario[max_ind_S(dizionario,i+1)]);
}

/*Nella function max_ind_S viene ricercato l'indice della parola via via più grande scorrendo l'array e viene fatto ritornare quest'ultimo alla
funzione chiamante */
int max_ind_S(Vocabolo dizionario[DIM],int n)
{
    int i,i_max;
    i_max=0;
    for (i=1;i<n;i++)
        if (strcmp(dizionario[i].parola,dizionario[i_max].parola)>0)
            i_max=i;
    return i_max;
}

/*Nella function ric_bin avviene la ricerca della parola all'interno dell'array una volta inserita la chiave, per funzionare però la ricerca binaria
necessità che il dizionario su cui opera venga prima ordinato, cosa che avviene grazie alla funzione sopra illustrata. La ricerca binaria in
questione nel caso in cui la parola digitata da ricercare non sia presente nel dizionario restituirà una stampa a video dove apparirà la scritta
"Vocabolo non trovato", altrimenti come prima cosa la chiave digitata viene resa minuscola treamite la funzione strlwer, in modo che qualunque sia il
modo in cui essa venga scritta non dia problemi, successivamente viene ricercata la parola nel dizionaria. Il meccanismo con cui la funzione ricerca la
parola è il seguente. Viene preso l'elemento medio della matrice tramite l'operazione di mediano e avviene il confronto tramite strcmp tra il parametro
parola del dizionario di indice mediano e la chiave, se la parola e maggiore viene scartata la parte precendente al del'array e la ricerca viene
effettuata sull'altra nel caso inverso la parte ad essere scartata è quella successiva al mediano. Una volta trovata la parola la parola viene fatto
ritornare l'indice della parola trovata che corrisponde al mediano in modo da sapere in che posizione si trovi quest'ultima.*/
int ric_bin(char chiave[],Vocabolo elenco[DIM],int n)
{
    int mediano,primo=0,ultimo=n-1,i;
    strlwr(chiave);
    while(primo<=ultimo){
          mediano=(primo + ultimo)/2;
          if(strcmp(chiave,elenco[mediano].parola)==0)
             return mediano;
          if(strcmp(chiave,elenco[mediano].parola)<0)
             ultimo=mediano-1;
          else
             primo=mediano+1;
    }
    printf("\n\tVocabolo non trovato");
    return -1;
}



