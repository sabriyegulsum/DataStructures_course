#include<stdio.h>
#include<stdlib.h>
typedef enum{false,true} bool;
struct node{
    struct node *prev;
    int data;
    struct node *next;
};
typedef struct node node;
node *head;
void insertAtHead(int key)
{
    if(head==NULL)
    {
        head=(node *)malloc(sizeof(node));
        head->data=key;
        head->prev=NULL;
        head->next=NULL;
    }
    else
    {
        node *newnode=(node *)malloc(sizeof(node));
        newnode->data=key;
        newnode->next=head;
        head->prev=newnode;
        newnode->prev=NULL;
    }
}
void insert_At_Last(int key)
{
    if(head==NULL)
    {
        head=(node *)malloc(sizeof(node));
        head->data=key;
        head->next=NULL;
        head->prev=NULL;
    }
    else
    {
        node *newnode=(node *)malloc(sizeof(node));
        newnode->data=key;
        node *temp=head;
        while(temp->next!=NULL)             //double linked list te son eleman head i tutmaz NULL u tutar bu pointlere dikkat baby :)
            temp=temp->next;
        temp->next=newnode;
        newnode->next=NULL;
        newnode->prev=temp;
    }
}
void add_otherNode(node *other_node, int number)
{
    node *temp=head;
    int i;
    if(head ==NULL)
    {
        printf("bu liste boştur.Yazdiğiniz eleman ilk başa eklenmiştir\n");
        head=other_node;
        head->next=NULL;
        head->prev=NULL;
        return ;
    }
    for(i=1;i<number;i++)
        temp=temp->next;
    other_node->next=temp->next;
    temp->next=other_node;
    other_node->prev=temp;
}
node *create_newNode(int key)
{
    node *new=(node *)malloc(sizeof(node));
    new->data=key;
    return new;
}
void print(void)
{
    if(head==NULL)
    {
        printf("listede eleman yoktur");
        return ;
    }
    node *temp=head;
    while(temp!=NULL)
    {
        printf("%d\n",temp->data);
        temp=temp->next;
    }
}
void delete(int key)
{
    if(head==NULL)
    {
        printf("listede eleman yoktur");
        return ;
    }
    if(head->data==key)
    {
        head=head->next;
        free(head->prev);
    }
    else
    {
        node *temp=head;            //burada değişken kullanmak zorundayim head globalde tanimli ilerleyemem
        while(temp->data!=key)
            temp=temp->next;
        temp->prev->next=temp->next;        //işte burada ikinci bir değişkene ihtiyaö duyuyorduk ama temp->prev deyip kolaylikla bie önceki
        if(temp->next!=NULL)                //düğüme ulaşabiliyorum:)
            temp->next->prev=temp->prev; 
        free(temp);                                   
    }                                      
}
node *locate(node *head,int key)
{
    node *locate=NULL;
    while(head->data!=key)
    {
        if(head==NULL)
            break;
        head=head->next;
    }
    locate=head;
    return locate;
}
bool is_member(node *other_node)
{
    while(head!=NULL && head!=other_node)
        head=head->next;
    return (head==other_node);              //eğer eşitse 1 döner değilse 0 değeri dönecektir
}
int main()
{
    int secim,num;
    node *p;
    printf("1-başa eleman ekle\n");
    printf("2-sona eleman ekle\n");
    printf("3-araya eleman ekle\n");
    printf("4-listeyi yazdir\n");
    printf("5-bir elemani sil\n");
    printf("6-bitir\n");
    while(1)
    {
        printf("seçiminiz...");
        scanf("%d",&secim);
        switch(secim)
        {
            case 1:printf("eklemek istediğiniz sayiyi giriniz"); scanf("%d",&num); insertAtHead(num);
                break;
            case 2: printf("eklemek istediğiniz sayiyi giriniz"); scanf("%d",&num); insert_At_Last(num);
                break;
            case 3:printf("eklemek istediğiniz sayiyi giriniz"); scanf("%d",&num); node *new=create_newNode(num);
                   printf("hangi elemandan sonraya eklemek istiyorsunuz?"); scanf("%d",&num); add_otherNode(new,num);
                break;
            case 4:print();
                break;
            case 5: printf("silmek istediğiniz elemanin verisini giriniz");scanf("%d",&num);delete(num);
                break;
            case 6: exit(1);
                break;
            default:printf("yanliş seçim yaptiniz\n");
        }
    }
    return 0;
}
//p=head->next->next;
//int a=is_member(p);
//printf("\nara:%d",a); 
//bool return eden fonksiyon o düğüm var mı diye bakıyor sona geldiğinde eşitmi diye sorduğunda değilse 0 öyle ise 1 döndürüyor
//sadece farklı gelen return (head==other) da return ün içine kkoşu koyup sonucu bir sayiya eşitlemeden direk return etmek mantıklıymiş :)
