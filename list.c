#include<stdlib.h>
#include<stdio.h>

typedef enum{false,true} bool;      //bool tipi c de olmadığı için kendimiz oluşturduk
struct node{
    int data;
    struct node *next;
};
typedef struct node node;
node * addHead(node *head, int key)                 //Normalde biz aşağıda yeni bir düğüm oluşturup değerlerini kullanıcıdan isteyip
{                                                  //sonra o düğümü ekiyorduk.Ama şimdi yeni bir düğüm için yer alıyorum. Fonkiyona parametre olarak düğümümün içine atacağım
    node *newNode =(node *)malloc(sizeof(node));  //değeri gönderiyorum sonra eşitliyorum tek fark bu. Birde head i mainde tanımlardık ama burada onuda parametre olarak alıyorum
    newNode->data=key;
    newNode->next=head;
    head=newNode;
    return head;
}
node *addLast(node *head,int key)
{
    node *temp;
    node *newNode=(node *)malloc(sizeof(node)); //yeni oluşturduğun düğümde node tipinde bir pointerdır. Bunu unutmamalısın 
    newNode->data=key;
    temp=head;
    while(temp->next!=NULL)
        temp=temp->next;
    temp->next=newNode;
    newNode->next=NULL;
    return head;
}
void listInfo(node *head)
{
    node *temp;
    int i=1;
    temp=head;
    
    while(temp!=NULL)
    {
        printf("%d.düğümün adresi:%p\nbilgisi:%d\nsonraki düğümün adresi:%p\n",i,temp,temp->data,temp->next);
        temp=temp->next;
        i++;
    }
}
void print(node *head)
{
    if(head==NULL)
    {
        printf("Bu listede hiç eleman yoktur");
        return;                                     //void olmasına rağmen sadece retrun yazılabilir sonuçta bir şey döndürmüyor :)
    }                                              //ek olarak return yazdığımımız için if den foknksiyonu geri döndürdük ve yeni bir else bloğoğu oluşturmaya gerek kalmadı :)
    node *temp=head;                              //eğer burada p->next!=NULL olana kadar dersem son eleman buna  uyar ve döngüye girmez yazdıramam
    while(temp!=NULL) 
    {
        printf("%d\n",temp->data);
        temp=temp->next;
    }
}
void print_Recursive(node *head)          //bu fonksiyonda parametre olarak aldiğım head kafanı karıştırmaasın.Buradaki adresin adın head değil *p de olablidi sonuçta head i
{                                       //ilerletiyotuz ama bu listedeki head in adresini değiştirmez.  parametre olan head gelir ilerler fonksiyon bittiğinde yok olup gider
    if(head==NULL)
        return;
    else
    {
        printf("%d\n",head->data);
        print_Recursive(head->next);
    }
}
void print_reverse(node *head)
{
    if(head==NULL)
        return;
    else
        print_reverse(head->next);
        printf("%d\n",head->data);
}
int count(node *head)
{
    int counter=0;
    while(head!=NULL)
    {
        counter++;
        head=head->next;
    }
    return  counter;
}
int count_recursive(node *head)
{
    if(head==NULL)
        return 0;
    else
        return  count_recursive(head->next)+1;       //neden burada return var yukarıdaki yazdığım fonksiyonda return yok, sadece aynı fonksiyonu geri geri çağırmak var
}                                                    //Yukarıda geriye bir şey döndürmesini istemiyorum.Sadece prinliyorum o kadar.Ama burada teker teker bütün elamanları null a
node *locate(node *head,int key)                     //kadar toplamam gerekiyor eğer sadece fonksiyonu geri çağırısam (return kullanmazsam) hadi kenarına da +1 koyalım her bir 
{                                                    //fonksiyonu +1 leyip gönderdin bu değerler tutulmadı her çağırmada uçtu gitti.Ama return o sayıları toplayıp gelir
    node *locate;                                    //bu yüzden eğer her hangi bir sonuç bulmak istiyorsan rekursif de o zaman return kullanman gerekiyor
    while(head!=NULL)
    {
        if(head->data!=key)
            head=head->next;
        else
        {
            locate=head;
            break;                              //aradığın düğümü buldun burada döngüden çıkman lazım
        }
    }
    return locate;
}
bool bool_locate(node *head,int key)
{
    node *locate;
    while(head!=NULL)
    {
        if(head->data!=key)
            head=head->next;
        else
        {
            locate=head;
            return true;
        }
    }
    return false;
}
void concatentete(node *head1, node *head2)         //iki listeyi birleştiren fonksiyon
{
    if(head1==NULL)
        head1=head2;
    else
    {
        while(head1->next!=NULL)
                head1=head1->next;
        head1->next=head2;
    }
}
node *_remove(node *head,int key)               //C de zaten remove adında özel bir fonksiyon vardır(dosyanın ismini siler) o yüzden _remove yazdım
{
    node *p=head;
    if(head==NULL)                          //Listede eleman olmayabilir
    {
        printf("Listede eleman yoktur");
        return head;
    }
    if(head->data==key)                     //head silinebilir
    {
        head=head->next;
        free(p);
        return head;
    }
    else if(p->next==NULL)
    {
        printf("Listede silinecek veri bulunamamiştir");
        return head;
    }
    else
    {
        while(p->next->data!=key)       //kontrol kısmında döngünün biz normalde null a kadar derken key i bulana kadar deyip içeride null sa return edecek şekilde kontrol 
        {                               //sağlıyor.Eğer döngüden çıktıysa kesinlikle key i bulmuş oluyor :))
            if(p->next->next==NULL)
            {
                printf("Silinece eleman bulunamamistir");
                return head;
            }
            p=p->next;
        }
        node *q;
        q=p->next;
        p->next=p->next->next;
        free(q);
        return head;
    }
}
void _print_reverse(node *head)             //bu attığım listeyi başka bir head2 poiter belirleyip addHead fonksiyonuna her elemanını attım
{                                           //tekrardan yer aömam gerekmedi çünkü addHaed bunu yapıyor :)
    node *head2,*temp;
    temp=head;
    while(temp!=NULL)
    {
        head2=addHead(head2,temp->data);    //return döndürüyor bende hangi listemin (head2) döndürülmesini istiyorsam onu atıyorum.İki tane head ollması karışmasın
        temp=temp->next;
    }
    print(head2);
}
node * destroy(node *head)
{
    if(head==NULL)
    {
        printf("\nListede silinecek eleman yoktur yoktur\n");
        return head;
    }
    node *temp;
    while(head!=NULL)
    {
        temp=head;
        head=head->next;
        free(temp);
    }
    printf("Listedeki bütün elemanlar silinmiştir\n");
    return head;
}
void destroy_recursively(node *head)
{
    if(head==NULL)
        return ;
    else
        destroy_recursively(head->next);
        free(head);
}
int main() 
{                 
    int a,data;                              
    node *head;
        printf("1-Listenin Basina Eleman Ekle\n");
        printf("2-Listenin Sonuna Eleman Ekle\n");
        printf("3-Listeyi Gorme\n");
        printf("4-Listeden verilen bir degere sahip dugum silmek\n"); 
        printf("5-Listeyi sil\n");
        printf("6-Listedeki eleman sayisi\n"); 
        printf("7-Listenin tum eleman bilgileri\n"); 
        printf("8-Programdan Cikma\n");
        while(1)
    { 
        printf("Seciminiz....?"); 
        scanf("%d",&a);
        switch(a)
        {
        case 1:printf("Eklemek istediginiz degerini giriniz..?"); scanf("%d",&data);
            head=addHead(head,data);
            break;
        case 2:printf("Eklemek istediginiz degerini giriniz..?"); scanf("%d",&data);
            head=addLast(head,data);
            break;
        case 3:
            print(head);
            break;
        case 4:printf("Silmek istediginiz degerini giriniz..?"); scanf("%d",&data);
            head=_remove(head,data);
            break;
        case 5:
            head=destroy(head);
            break;
        case 6:printf("Listede %d eleman vardir\n",count(head)); 
            break;
        case 7:listInfo(head);
            break;
        case 8:exit(1);
            break;
        default: printf("Yanlis secim\n");
        }
    } 
    return 0;
}
//Ben normalde yazdığım liste kodlarında main kısmında head için bellekten hemen ilkten garantiye alıp mallloc ile yer alırdım ama burada hiç yer ayırma yok listeni başa ve 
//sona ekle fonkisiyonları ile oluşturuyorsun zaten onların içindede malloc fonksiyonları var:)
//yarın dewam ke
//200 satırı göreceğiz inşAllah :)
//edit:gördük 😊