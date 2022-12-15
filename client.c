#include <stdio.h>
#include <stdlib.h>
const char A = 65;
const char C = 67;
const char F = 70;
const char M = 77;
const char P = 80;
const char Q = 81;
const char S = 83;
const char a = 97;
const char c = 99;
const char f = 102;
const char m = 109;
const char p = 112;
const char q = 113;
const char s = 115;

struct produit
{
    int id;
    char titre[50];
    float prix;
    int quantite;
};
typedef struct produit Product;

struct facture
{
    Product products[30];
    float total;
};
typedef struct facture Bill;

void readProducts(Product p[30], int n)
{
    printf("-----------------------------------------------\n");
    printf(" ID \t||\t TITRE \t||\t PRIX \n");
    printf("-----------------------------------------------\n");
    for (int i = 0; i < n; i++)
    {
        printf(" %d \t||\t %s \t||\t %.2f \n", p[i].id, p[i].titre, p[i].prix);
        printf("-----------------------------------------------\n");
    }
}

void addProductToFact(Bill *fact, Product products[20], int n, int *npr)
{
    int id, qt, test;
    int np = *npr;
    test = 0;
    printf("Donner l'id du produit a ajouter dans la facture : ");
    scanf("%d", &id);
    for (int i = 0; i < *npr; i++)
    {
        if (fact->products[i].id == id)
        {
            printf("Le produit existe deja dans la facture !!!\n");
            test = 1;
        }
    }
    if (test == 0)
    {
        do
        {
            printf("Donner la quantite de ce produit : ");
            scanf("%d", &qt);
        } while (qt < 1);
        for (int i = 0; i < n; i++)
        {
            if (products[i].id == id)
            {
                fact->products[np] = products[i];
                fact->products[np].quantite = qt;
                *npr = *npr + 1;
            }
        }
    }
}

void readFact(Bill *fact, int npr)
{
    float somme;
    printf("------------------------------------------------------------------------------------\n");
    printf("ID\t||\tTITLE\t||\tPRICE\t||\tQUANTITY\t||\tTOTAL\n");
    printf("------------------------------------------------------------------------------------\n");
    somme = 0;
    for (int i = 0; i < npr; i++)
    {
        printf("%d\t||\t%s\t||\t%.2f\t||\t%d\t\t||\t%.2f\n", fact->products[i].id, fact->products[i].titre, fact->products[i].prix, fact->products[i].quantite, (fact->products[i].prix * fact->products[i].quantite));
        printf("------------------------------------------------------------------------------------\n");
        somme = somme + (fact->products[i].prix * fact->products[i].quantite);
    }
    fact->total = somme;
    printf("\t\t\t\t\t\t\t\t||\t%.2f\n", fact->total);
    printf("\t\t\t\t\t\t\t\t--------------------\n", fact->total);
}

void updateProductInFact(Bill *fact, int npr)
{
    int id, test, qt;
    printf("Donner l'id du produit pour modifier sa quantite : ");
    scanf("%d", &id);
    test = 0;
    for (int i = 0; i < npr; i++)
    {
        if (fact->products[i].id == id)
        {
            do
            {
                printf("Donner la quantite de ce produit : ");
                scanf("%d", &qt);
            } while (qt < 1);
            fact->products[i].quantite = qt;
            test = 1;
        }
    }
    if (test == 0)
    {
        printf("PAS DE PRODUIT DANS LA FACTURE AYANT CET ID !!!\n");
    }
}

void deleteProductFromFact(Bill *fact, int *npr)
{
    int id, test, pos;
    Product newp;
    printf("Donner l'id du produit a supprimer de la facture : ");
    scanf("%d", &id);
    test = 0;
    for (int i = 0; i < *npr; i++)
    {
        if (fact->products[i].id == id)
        {
            pos = i;
            test = 1;
            break;
        }
    }
    if (test == 0)
    {
        printf("PAS DE PRODUIT DANS LA FACTURE AYANT CET ID !!!\n");
    }
    else
    {
        for (int i = pos; i < *npr - 1; i++)
        {
            fact->products[i] = fact->products[i + 1];
        }
        fact->products[*npr - 1] = newp;
        *npr = *npr - 1;
    }
}

int main()
{
    FILE *file;
    Bill fact;
    Product products[20];
    Product pr;
    char choix;
    int n, id, npr;
    npr = 0;
    do
    {
        file = fopen("products.txt", "r");
        if (!file)
        {
            printf("ERREUR FICHIER!!!\n");
            exit(1);
        }
        printf("c : Consulter la liste des produits\n");
        printf("a : Ajouter un produit dans la facture\n");
        printf("f : Afficher les details de la facture\n");
        printf("m : Modifier la quantite d'un produit dans la facture\n");
        printf("s : Supprimer un produit de la facture\n");
        printf("p : Payer la facture\n");
        printf("q : Quitter le programme\n");
        printf("Votre choix : ");
        fflush(stdin);
        scanf("%c", &choix);
        n = 0;
        id = -1;
        while (!feof(file))
        {
            fscanf(file, "%d %s %f", &pr.id, pr.titre, &pr.prix);
            if (id != pr.id)
            {
                id = pr.id;
                products[n] = pr;
                n++;
            }
        }
        fclose(file);
        if ((choix == A) || (choix == a))
        {
            readProducts(products, n);
            addProductToFact(&fact, products, n, &npr);
            printf("VOTRE FACTURE : \n");
            readFact(&fact, npr);
        }
        else if ((choix == C) || (choix == c))
        {
            readProducts(products, n);
        }
        else if ((choix == f) || (choix == F))
        {
            printf("VOTRE FACTURE : \n");
            readFact(&fact, npr);
        }
        else if ((choix == M) || (choix == m))
        {
            printf("VOTRE FACTURE : \n");
            readFact(&fact, npr);
            updateProductInFact(&fact, npr);
            printf("VOTRE FACTURE : \n");
            readFact(&fact, npr);
        }
        else if ((choix == p) || (choix == P))
        {
            printf("VOTRE FACTURE : \n");
            readFact(&fact, npr);
            printf("Vous avez payer %.2f Dt.\n", fact.total);
            printf("Mercii !!!\n");
        }
        else if ((choix == S) || (choix == s))
        {
            printf("VOTRE FACTURE : \n");
            readFact(&fact, npr);
            deleteProductFromFact(&fact, &npr);
            printf("VOTRE FACTURE : \n");
            readFact(&fact, npr);
        }
        else if ((choix != Q) && (choix != q))
        {
            printf("choix erroné ! Veuillez réessayer !\n");
        }

    } while ((choix != Q) && (choix != q) && (choix != p) && (choix != P));
    printf("Au revoir !!!");
    return 0;
}