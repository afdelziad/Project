#include<stdio.h>
#include<stdlib.h>


void Echange(float *a,float *b)
{
    float temp ;

    temp = *a ;
    *a = *b ;
    *b = temp ;

}

float* Initialiser_Estimation_Budget(int *N)
{
    do
    {
        printf("Entrer la taille du tableau : ");
        scanf("%d",N);
    } while ( *N <= 0 );
    
    float *T = calloc(*N,sizeof(float));

    if ( T == NULL )
    {
        printf("Allocation memoire invalide \n");
    }

    return T;

}

void Remplir_Estimation_Budget(float *T,int *N,int index,float Nouvelle_Estimation)
{
    if ( index >= 0 && index < *N )
    {
        T[index] = Nouvelle_Estimation ;
    }
    else
    {
        printf("Index invalid \n");
    }

}

float* Ajouter_Estimation_Budget(float *T,int *N,float Nouvelle_Estimation)
{
    float *Temp = realloc(T,(*N+1)*sizeof(float));

    if ( Temp == NULL )
    {
        printf("Reallocation de Memoire invalide \n");
        return NULL ;
    }

    Temp[*N] = Nouvelle_Estimation ;
    (*N)++ ;

    return Temp ;

}

float* Supprimer_Estimation_Budget(float *T,int *N,int index)
{
    if ( index < 0 || index >= *N )
    {
        printf("Index introuvable \n");
        return T ;
    }
    
    for ( int i = index ; i < *N-1 ; i++)
    {
        T[i] = T[i+1] ;
    }
    
    (*N)-- ; 

    if ( *N == 0 )
    {
        free(T);
        return NULL ;
    }

    float *Temp = realloc(T,(*N)*sizeof(float));

    if ( Temp == NULL )
    {
        return T ;
    }

    return Temp ;
}

void Trier_Estimation_Budget(float *T,int *N)
{
    float temp ;

    for ( int i = 0 ; i < *N - 1 ; i++)
    {
        for ( int j = i+1 ; j < *N ; j++)
        {
            if ( T[i] > T[j] )
            {
                Echange(&T[i],&T[j]);
            }
        }   
    }
    
}

void Afficher_Estimation_Budget(float *T,int *N)
{
    if ( *N == 0 )
    {
        printf("Le tableau est vide \n");
        return ;
    }

    for ( int i = 0 ; i < *N ; i++)
    {
        printf("Budget[%d] : %.2f \n",i,T[i]);
    }
    
}

int main()
{
    float *Budget = NULL ;
    int N = 0 ;
    int initialise = 0 ;
    int choix , index ;
    float Nouvelle_Estimation ;

    printf("\n--- Menu : Estimation Budgetaire ---\n");
    printf("1- Initialiser le tableau : \n");
    printf("2- Remplir le tableau : \n");
    printf("3- Ajouter une estimation : \n");
    printf("4- Supprimer une estimation \n");
    printf("5- Afficher l'estimation : \n");
    printf("6- Trier le tableau \n");
    printf("0- Quitter (Liberer la memoire) \n");

    do
    {   
        printf("\nVotre choix : ");
        scanf("%d",&choix);

        if ( choix >= 2 && choix <= 6 && !initialise )
        {
            printf("\nVeuiller d'abord initialiser le tableau ( Option 1 ) \n");
            continue ;
        }

        switch ( choix )
        {
        case 1 :
            if ( initialise )
            {
                printf("\nLe tableau est deja bien initialise \n");
                break ;
            }
            
            Budget = Initialiser_Estimation_Budget(&N);
            
            if ( Budget != NULL )
            {
                initialise = 1 ;
                printf("\nInitialisation effectue avec succes \n");
            }

            break ;
        case 2 :
            for ( int i = 0 ; i < N ; i++)
            {
                printf("Budget[%d] : ",i);
                scanf("%f",&Nouvelle_Estimation);

                Remplir_Estimation_Budget(Budget,&N,i,Nouvelle_Estimation);
            }

            break ;
        case 3 :
        {   
            printf("\nEntrer la nouvelle estimation : ");
            scanf("%f",&Nouvelle_Estimation);

            float *Temp = Ajouter_Estimation_Budget(Budget,&N,Nouvelle_Estimation);

            if ( Temp != NULL )
            {
                Budget = Temp ;
                printf("\nEstiamtion ajoutee avec succes \n");
            }

            break ;
        }
        case 4 :
            printf("\nEntrer l'index que vous voulez supprimer : ");
            scanf("%d",&index);

            if ( index < 0 || index >= N )
            {
                printf("\nIndex introuvable \n");
                break ;
            }
            
            Budget = Supprimer_Estimation_Budget(Budget,&N,index);
            
            if ( N == 0 )
            {
                initialise = 0 ;
                printf("\nLe tableau est vide \n"); 
            }
            else
            {
                printf("\nEstimation supprime avec succes \n");
            }

            break ;
        case 5 :    
            printf("\nLe tableau des estimations : \n");

            Afficher_Estimation_Budget(Budget,&N);

            break ;
        case 6 :
            Trier_Estimation_Budget(Budget,&N);

            printf("\nLe tableau trie : \n");

            Afficher_Estimation_Budget(Budget,&N);

            break ;
        case 0 :
            free(Budget);
            Budget = NULL ;

            printf("\nMemoire libere avec succes \n");

            break ;
        }
 
    } while ( choix != 0 );
    
    return 0 ;
}