#include<stdio.h>
#include<stdlib.h>
struct node{
    int data;
    struct node *next;
};
typedef struct node node;
node *head;                 //if you define head in global everythinh is change :)
node * insertAtFront(int key)
{
    if(head==NULL)
    {
        head=(node *)malloc(sizeof(node));
        head->data=key;
        head->next=head;                //bu kısımda patlama.Normal single listeden farklı bir eleman oluşturduğunda nasıl nextini
        return head;                    //null a bağlıyosuın burada head e bağlaman gerekiyor :)
    }
    else
    {
        node *temp,*last;
        last=head;
        temp=(node *)malloc(sizeof(node));
        temp->data=key;
        while(last->next!=head)
            last=last->next;
        temp->next=head;
        last->next=temp;
        head=temp;
    }
    return head;
}
void insertAtLast(int key)
{
    if(head==NULL)
    {
        head=(node *)malloc(sizeof(node));
        head->data=key;
        return ;
    }
    else
    {
        node *temp;
        node *last=head;
        temp=(node *)malloc(sizeof(node));
        temp->data=key;
        while(last->next!=head)
            last=last->next;
        temp->next=head;
        last->next=temp;
        //başa ekleme fonksiyonundan tek farkı temp i head e eşitlemeyiz o kadar
    }
}
void insert_at_last(int key)                //bu fooksiyonda temp değişkeni oluşturmadan last->next için yer alıp ona değerler atayıp
{                                           //onun ->next ini de 'last->next->next' eşitliyorum
    if(head==NULL)
    {
        head=(node *)malloc(sizeof(node));
        head->data=key;
    }
    else
    {
        node *last;
        last=head;
        while(last->next!=head)
            last=last->next;
        last->next=(node *)malloc(sizeof(node));
        last->next->data=key;
        last->next->next=head;
    }
}
void concatenate(node *head1, node *head2)
{
    node *last=head1;
    while(last->next!=head1)
        last=last->next;
    last->next=head2;
    last=head2;
    while(last->next!=head2)
        last=last->next;
    last->next=head1;
}
node *locate(int key)
{
    if(head==NULL)
    {
        printf("listede hiç elemamn yoktur");
        return head;
    }
    else
    {
        node *locate=head;
        while(locate->data!=key)
        {
            if(locate->next==head)
            {
                printf("listede aradiğiniz eleman yoktur");
                return head;
            }
            locate=locate->next;
        }
        printf("aradiğiniz key bulunmuştur");
        return locate;
    }
}
void delete(int key)
{
    if(head==NULL)              //->liste boş olabilir
    {
        printf("liste boştur");
        return ;
    }
    node *temp=head,*last=head;
    if(head->data==key)             //->ilk eleman silinecek olabilir
    {                               //ama bu dairesel liste olduğu için ilk elemanı sildiğinde son elmanı da yeni heade eşitlemek gerekiyor
        while(last->next!=head)         //!Bu kısım önemli daha head değişmeden son elemana gitmem gerekiyor
            last=last->next;            //eğer değiştikten sonra yani ilk head i siildikten sonra last ile sonucuyu arasan diğer head i
        head=head->next;                //tutan node u bulursun
        free(temp);
        last->next=head;
    }
    else if(temp->next==head)
        printf("sileceğiniz veri listede yoktur");
    else
    {
        while(temp->next->data!=key)
        {
            if(temp->next->next==head)
            {
                printf("silmek istediiğiniz eleman listede yoktur");
                break;
            }
            temp=temp->next;
        }
        if(temp->next->next==head)
        {
            last=temp->next;
            temp->next=temp->next->next;
            free(last);
        }
        else
        {
            last=temp->next;
            temp->next=temp->next->next;
            free(last);
        }
    }
}
void print(void)
{
    node *temp=head;
    while(temp->next!=head)
    {
        printf("%d\n",temp->data);
        temp=temp->next;
    }
    printf("%d",temp->data);
}
int main()
{
    int secim,number;
    printf("1-başa düğüm ekle\n");
    printf("2-sona düğüm ekle\n");
    printf("3-iki listeyi birleştir\n");
    printf("4-listeden bir düğümü sil\n");
    printf("5-listeyi yazdir\n");
    while(1)
    {
        printf("seçiminiz..");
        scanf("%d",&secim);
        switch (secim)
        {
        case 1:printf("eklemek istediğiniz sayiyi giriniz\n"); scanf("%d",&number);head=insertAtFront(number);
            break;
        case 2:printf("eklemek istediğiniz sayiyi giriniz\n"); scanf("%d",&number);insertAtLast(number);
            break;
        case 4:printf("silmek istediğiniz sayiyi giriniz\n"); scanf("%d",&number); delete(number);   
            break;
        case 5: print();
            break;
        case 6:exit(1);
            break;
        default:printf("yanliş seçim yaptiniz\n");
            break;
        }
    }
    return 0;
}
//listeyi oluştururkekn hata alıyorum :(
//hatanını sebebi bulundu eğer ilk düğümü oluşturduktan sonra next'ini kendisine bağlamayı unutursan patlar:)
//yarın sabah github a atııcam