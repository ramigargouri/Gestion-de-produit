#include <stdio.h>
#include <stdlib.h>
const char A = 65;
const char C = 67;
const char M = 77;
const char Q = 81;
const char S = 83;
const char a = 97;
const char c = 99;
const char m = 109;
const char q = 113;
const char s = 115;

struct produit
{
    int id;
    char titre[50];
    float prix;
};
typedef struct produit Product;

void readProducts(Product p[30], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("id : %d \t titre : %s \t prix : %.2f\n", p[i].id, p[i].titre, p[i].prix);
    }
}

void addProduct(Product p[30], int n)
{
    Product newp;
    int id;
    FILE *f;
    printf("Donner le titre du produit : ");
    scanf("%s", newp.titre);
    do
    {
        printf("Donner le prix du produit : ");
        scanf("%f", &newp.prix);
    } while (newp.prix < 0);
    id = -1;
    for (int i = 0; i < n; i++)
    {
        if (p[i].id != i)
        {
            id = i;
            break;
        }
    }
    if (id == -1)
    {
        id = n;
    }
    f = fopen("products.txt", "w");
    if (!f)
    {
        printf("ERREUR FICHIER!!!\n");
        exit(1);
    }
    for (int i = 0; i <= n; i++)
    {
        if (i == id)
        {
            fprintf(f, "%d %s %.2f\n", id, newp.titre, newp.prix);
        }
        else
        {
            fprintf(f, "%d %s %.2f\n", p[i].id, p[i].titre, p[i].prix);
        }
    }

    fclose(f);
}

void updateProduct(Product p[30], int n)
{
    FILE *f;
    int id;
    int test;
    printf("Donner l'id du produit a modifier : ");
    scanf("%d", &id);
    test = 0;
    for (int i = 0; i < n; i++)
    {
        if (p[i].id == id)
        {
            test = 1;
            do
            {
                printf("Donner le nouveau prix du produit %s : ", p[i].titre);
                scanf("%f", &p[i].prix);
            } while (p[i].prix < 0);
        }
    }
    if (test == 0)
    {
        printf("PAS DE PRODUIT AVEC CET ID!!\n");
    }
    else
    {
        f = fopen("products.txt", "w");
        if (!f)
        {
            printf("ERREUR FICHIER!!!\n");
            exit(1);
        }
        for (int i = 0; i < n; i++)
        {
            fprintf(f, "%d %s %.2f\n", p[i].id, p[i].titre, p[i].prix);
        }
        fclose(f);
    }
}

void deleteProduct(Product p[30], int n)
{
    FILE *f;
    int id, test;
    printf("Donner l'id du produit a supprimer : ");
    scanf("%d", &id);
    test = 0;
    f = fopen("products.txt", "w");
    if (!f)
    {
        printf("ERREUR FICHIER!!!\n");
        exit(1);
    }
    for (int i = 0; i < n; i++)
    {
        if (p[i].id == id)
        {
            test = 1;
        }
        else
        {
            fprintf(f, "%d %s %.2f\n", p[i].id, p[i].titre, p[i].prix);
        }
    }
    fclose(f);
    if (test == 0)
    {
        printf("PAS DE PRODUIT A SUPPRIMER!!");
    }
}

int main()
{
    FILE *f;
    Product products[30];
    char choix;
    int n, id;
    Product p;
    do
    {
        f = fopen("products.txt", "r");
        if (!f)
        {
            printf("ERREUR FICHIER!!!\n");
            exit(1);
        }
        printf("c : Consulter la liste des produits\n");
        printf("a : Ajouter un produit\n");
        printf("m : modifier un produit\n");
        printf("s : supprimer un produit\n");
        printf("q : quitter le programme\n");
        printf("votre choix : ");
        fflush(stdin);
        scanf("%c", &choix);
        n = 0;
        id = -1;
        while (!feof(f))
        {
            fscanf(f, "%d %s %f", &p.id, p.titre, &p.prix);
            if (id != p.id)
            {
                id = p.id;
                products[n] = p;
                n++;
            }
        }
        fclose(f);

        if ((choix == 'A') || (choix == a))
        {
            addProduct(products, n);
        }
        else if ((choix == C) || (choix == c))
        {
            readProducts(products, n);
        }
        else if ((choix == M) || (choix == m))
        {
            readProducts(products, n);
            updateProduct(products, n);
        }
        else if ((choix == S) || (choix == s))
        {
            readProducts(products, n);
            deleteProduct(products, n);
        }
        else if ((choix != Q) && (choix != q))
        {
            printf("choix erroné ! Veuillez réessayer !\n");
        }

    } while ((choix != Q) && (choix != q));
    printf("Au revoir !!!");
    return 0;
}