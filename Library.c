#include<stdio.h>
#include<stdlib.h>
#include<memory.h>
#include<string.h>
#include<conio.h>

typedef struct date
{
    int dd;
    int mm;
    int yyyy;
}date;

typedef struct book
{
    int book_id;
    char book_name[25];
    char author_name[20];
    char subject[20];
    int edition;
}book;

typedef struct member
{
    int lib_code;
    char member_name[20];
    char type[8];
    char department[3];
    date issue_date;
    date return_date;
}member;

typedef struct issue
{
    int lib_code;
    int no_issued_books;
    date issue_date;
    date return_date;
    int book_id[5];
}issue;

date cal_return_date(date );
int cal_fine(int );
int count_days(date ,date);
int ifleap(int );

int main()
{
    int choice;
    void add_member();
    void add_book();
    void delete_member();
    void delete_book();
    void search_member();
    void search_book();
    void update_member();
    void update_book();
    void display_member();
    void display_book();
    void sort_members();
    void issue_book();
    void return_book();

    while(1)
    {
    	system("cls");
    	
        printf("\t\t********Library Management Tool********\n");
        printf("\n\n1->Add Member\n");
        printf("2->Add Book\n");
        printf("3->Search Member\n");
        printf("4->Search Book\n");
        printf("5->Delete Member\n");
        printf("6->Delete Book\n");
        printf("7->Update Member\n");
        printf("8->Update Book\n");
        printf("9->Display Members\n");
        printf("10->Display Book\n");
        printf("11->Display Member in Sorted order\n");
        printf("12->Issue Book(s)\n");
        printf("13->Return Books\n");
        printf("14->Exit\n");

        printf("\nEnter your choice\n");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
            add_member();
            break;

            case 2:
            add_book();
            break;

            case 3:
            search_member();
            break;

            case 4:
            search_book();
            break;

            case 5:
            delete_member();
            break;

            case 6:
            delete_book();
            break;

            case 7:
            update_member();
            break;

            case 8:
            update_book();
            break;

            case 9:
            display_member();
            break;

            case 10:
            display_book();
            break;

            case 11:
            sort_members();
            break;

            case 12:
            issue_book();
            break;

            case 13:
            return_book();
            break;

            case 14:
            exit(0);
            break;

            default:
            printf("wrong choice\n");
            break;
        }
    }
}

void add_member()
{
    FILE *fp;
    member M;
	
	system("cls");
	
    fp=fopen("files//member","ab");

    if(fp==NULL)
    {
        printf("\nunable to open file\n");
        printf("Enter Any key to Go back\n");
        getch();
        return;
    }

    printf("Enter name : ");
    fflush(stdin);
    gets(M.member_name);

    printf("Enter library code : ");
    fflush(stdin);
    scanf("%d",&M.lib_code);

    printf("Enter designation (student or faculty) : ");
    fflush(stdin);
    gets(M.type);

    printf("Enter department : ");
    fflush(stdin);
    gets(M.department);

    fwrite(&M,sizeof(M),1,fp);

    printf("\nmember added\n\n");

    fclose(fp);

	printf("Enter any key to continue\n");
    getch();
}

void add_book()
{
    FILE *fp;
    book B;

	system("cls");
	
    fp=fopen("files//book","ab");

    if(fp==NULL)
    {
        printf("\nunable to open file\n");
        printf("Enter any key to go back\n");
        getch();
        return;
    }

    printf("Enter book name : ");
    fflush(stdin);
    gets(B.book_name);

    printf("Enter book ID : ");
    fflush(stdin);
    scanf("%d",&B.book_id);

    printf("Enter book author : ");
    fflush(stdin);
    gets(B.author_name);

    printf("Enter the book subject/genre\n");
    fflush(stdin);
    gets(B.subject);

    printf("Enter book edition : ");
    fflush(stdin);
    scanf("%d",&B.edition);

    fwrite(&B,sizeof(B),1,fp);

    printf("\nbook added\n");

    fclose(fp);

	printf("Enter any key to continue\n");
    getch();
}

void search_member()
{
    int m_num,flag=0;
    member M;
    FILE *fp;

	system("cls");
	
    fp=fopen("files//member","rb");

    if(fp==NULL)
    {
        printf("Unable to open file\n");
        printf("Enter any key to go back\n");
        getch();
        return;
    }

    printf("enter the member library code : ");
    scanf("%d",&m_num);
    while(fread(&M,sizeof(M),1,fp))
        if(m_num==M.lib_code)
        {
            printf("\n\nmember details :-\n\n");
            printf("%d%20s%10s%5s\n",M.lib_code,M.member_name,M.type,M.department);
            fclose(fp);
			flag = 1;
            gets(M.department);
        } 
    fclose(fp);
    
    if(flag==0)
    	printf("Member not found\n");
    
	printf("Enter any Key to continue\n");
    getch();
}

void search_book()
{
    int flag=0,b_id;
    book B;
    FILE *fp;

	system("cls");
	
    fp=fopen("files//book","rb");

    if(fp==NULL)
    {
        printf("Unable to open file\n");
        printf("Enter any key to go back\n");
        getch();
        return;
    }

    printf("enter the Book ID : ");
    fflush(stdin);
    scanf("%d",&b_id);

    while(fread(&B,sizeof(B),1,fp))
	{
        if(b_id == B.book_id)
        {
            printf("%d%20s%25s%25s%10d\n",B.book_id,B.book_name,B.author_name,B.subject,B.edition);
            flag=1;
            gets(B.author_name);
        }
	}
    if(flag==0)
        printf("\nThe book related to this subject/genre is not available\n");

    fclose(fp);

    printf("\nEnter any key to continue\n");
    getch();
}

void delete_member()
{
    int l_id,flag=0;
    member M;
    FILE *fp1,*fp2;

	system("cls");
	
    fp1=fopen("files//member","rb");

    if(fp1==NULL)
    {
        printf("Unable to open file\n");
        printf("Enter any key to go back\n");
        getch();
        return;
    }

    fp2=fopen("files//temp","wb");

    if(fp2==NULL)
    {
        printf("Unable to open\n");
        return;
    }

    printf("Enter library code : ");
    scanf("%d",&l_id);

    while(fread(&M,sizeof(M),1,fp1))
    {
        if(l_id!=M.lib_code)
            fwrite(&M,sizeof(M),1,fp2);
        else
        {
            printf("Member record deleted\n");
            flag=1;
        }
    }

    if(flag==0)
        printf("Member not found\n");

    fclose(fp1);
    fclose(fp2);

    remove("files//member");
    rename("files//temp","files//member");

	printf("\nEnter any key to continue\n");
    getch();
}

void delete_book()
{
    int b_id,flag=0;
    book B;
    FILE *fp1,*fp2;

	system("cls");
	
    fp1=fopen("files//book","rb");

    if(fp1==NULL)
    {
        printf("Unable to open file\n");
        printf("Enter any key to go back\n");
        getch();
        return;
    }

    fp2=fopen("files//temp","wb");

    if(fp2==NULL)
    {
        printf("Unable to open\n");
        return;
    }

    printf("Enter the book_id : ");
    scanf("%d",&b_id);

    while(fread(&B,sizeof(B),1,fp1))
    {
        if(B.book_id!=b_id)
            fwrite(&B,sizeof(B),1,fp2);
        else
        {
                printf("Record of the book with book id %d is deleted\n",b_id);
                flag=1;
        }
    }

    if(flag==0)
            printf("Book not found\n");

    fclose(fp1);
    fclose(fp2);

    remove("files//book");
    rename("files//temp","files//book");

	printf("Enter any key to continue\n");
    getch();
}

void update_member()
{
    int l_id,flag=0;
    member M;
    FILE *fp1,*fp2;

	system("cls");
	
    fp1=fopen("files//member","rb");

    if(fp1==NULL)
    {
        printf("Unable to open file\n");
        printf("Enter any key to go back\n");
        getch();
        return;
    }

    fp2=fopen("files//temp","wb");

    if(fp2==NULL)
    {
        printf("Unable to open file\n");
        printf("Enter any key to go back\n");
        getch();
        return;
    }

    printf("Enter the member id : ");
    scanf("%d",&l_id);

    while(fread(&M,sizeof(M),1,fp1))
    {
        if(M.lib_code==l_id)
        {
            printf("Enter name : ");
            fflush(stdin);
            gets(M.member_name);

            printf("Enter library code : ");
            fflush(stdin);
            scanf("%d",&M.lib_code);

            printf("Enter designation (student or faculty) : ");
            fflush(stdin);
            gets(M.type);

            printf("Enter department : ");
            fflush(stdin);
            gets(M.department);

            fwrite(&M,sizeof(M),1,fp2);

            flag=1;

            printf("\nRecord Updated\n");

        }
        else
            fwrite(&M,sizeof(M),1,fp2);

    }

    if(flag==0)
        printf("member not found\n");

    fclose(fp1);
    fclose(fp2);

    remove("files//member");
    rename("files//temp","files//member");

	printf("Enter any key to continue\n");
    getch();
}

void update_book()
{
    int b_id,flag=0;
    book B;
    FILE *fp1,*fp2;

	system("cls");
	
    fp1=fopen("files//book","rb");

    if(fp1==NULL)
    {
        printf("Unable to open file\n");
        printf("Enter any key to go back\n");
        getch();
        return;
    }

    fp2=fopen("files//temp","wb");

    if(fp2==NULL)
    {
        printf("Unable to open file\n");
        printf("Enter any key to go back\n");
        getch();
        return;
    }

    printf("Enter book ID : ");
    scanf("%d",&b_id);

    while(fread(&B,sizeof(B),1,fp1))
    {
        if(b_id==B.book_id)
        {
            printf("Enter book name : ");
            fflush(stdin);
            gets(B.book_name);

            printf("Enter book ID : ");
            fflush(stdin);
            scanf("%d",&B.book_id);

            printf("Enter book author : ");
            fflush(stdin);
            gets(B.author_name);

            printf("Enter the book subject/genre\n");
            fflush(stdin);
            gets(B.subject);

            printf("Enter book edition : ");
            fflush(stdin);
            scanf("%d",&B.edition);

            fwrite(&B,sizeof(B),1,fp2);

            flag=1;
        }
        else
            fwrite(&B,sizeof(B),1,fp2);
    }

    if(flag==0)
        printf("Book not found");

    fclose(fp1);
    fclose(fp2);

    remove("files//book");
    rename("files//temp","files//book");

	printf("Enter any key to continue\n");
    getch();
}

void display_member()
{
    FILE *fp;
    member M;

	system("cls");
	
    fp=fopen("files//member","rb");

    if(fp==NULL)
    {
        printf("Unable to open file\n");
        printf("Enter any key to go back\n");
        getch();
        return;
    }

    while(fread(&M,sizeof(M),1,fp))
        printf("%d%20s%10s%5s\n",M.lib_code,M.member_name,M.type,M.department);

    fclose(fp);
    
    printf("Enter any key to continue\n");
    getch();
}

void display_book()
{
    FILE *fp;
    book B;

	system("cls");
    fp=fopen("files//book","rb");

    if(fp==NULL)
    {
        printf("Unable to open file\n");
        printf("Enter any key to go back\n");
        getch();
        return;
    }

    while(fread(&B,sizeof(B),1,fp))
        printf("%d%20s%25s%25s%10d\n",B.book_id,B.book_name,B.author_name,B.subject,B.edition);

    fclose(fp);
	
	printf("Enter any key to continue\n");
    getch();
}

void sort_members()
{
    member M,*r_no;
    int m,i=0,j;
    FILE *fp;

	system("cls");
	
    fp=fopen("files//member","rb");

    if(fp==NULL)
    {
        printf("Unable to open file\n");
        printf("Enter any key to go back\n");
        getch();
        return;
    }

    fseek(fp,0,2);

    m=ftell(fp)/sizeof(M);
	printf("%d",m);
    r_no=(member *)malloc(sizeof(member)*m);

    rewind(fp);

    while(fread(&M,sizeof(M),1,fp))
        r_no[i++]=M;
	
    for(i=0;i<m-1;i++)
    {
            for(j=i+1;j<m;j++)
            {
                if(r_no[j].lib_code<r_no[i].lib_code)
                {
                        M=r_no[i];
                        r_no[i]=r_no[j];
                        r_no[j]=M;
                }
            }
    }

    printf("Members sorted as follows :-\n\n");

    for(i=0;i<m;i++)
        printf("%6d%20s%10s%5s\n",r_no[i].lib_code,r_no[i].member_name,r_no[i].type,r_no[i].department);

    free(r_no);
    fclose(fp);

	printf("Enter any key to continue\n");
    getch();
}

void issue_book()
{
    FILE *fp;
    issue I;
    int i;

	system("cls");
	
    fp=fopen("files//issue_record","ab");

    if(fp==NULL)
    {
        printf("Unable to open file\n");
        printf("Enter any key to go back\n");
        getch();
        return;
    }

    printf("Enter Library Id : ");
    fflush(stdin);
    scanf("%d",&I.lib_code);

    printf("number of books to be issued : ");
    fflush(stdin);
    scanf("%d",&I.no_issued_books);

    printf("Enter the book id of book to be issued :-\n\n");
    for(i=0;i<I.no_issued_books;i++)
    {
        fflush(stdin);
        scanf("%d",&I.book_id[i]);
    }

    printf("Enter issue date (dd mm yyyy)  : ");
    fflush(stdin);
    scanf("%d %d %d",&I.issue_date.dd,&I.issue_date.mm,&I.issue_date.yyyy);

    I.return_date=cal_return_date(I.issue_date);

    printf("return date is %d-%d-%d",I.return_date.dd,I.return_date.mm,I.return_date.yyyy);

    fwrite(&I,sizeof(I),1,fp);

    fclose(fp);

	printf("\nEnter any key to continue\n");
    getch();
}

void return_book()
{
    FILE *fp1,*fp2,*fp3;
    member M;
    date t_date;
    issue I,temp;
    int i,flag=0;

	system("cls");
	
    fp1=fopen("files//member","rb");
    printf("Enter library code : ");
    fflush(stdin);
    scanf("%d",&i);

    while(fread(&M,sizeof(M),1,fp1))
    {
        if(i==M.lib_code)
        {
            flag=1;
            fclose(fp1);
            break;
        }
    }

    if(flag==0)
    {
        printf("Member does not exist\n");
        fclose(fp1);
        return ;
    }

    fp2=fopen("files//issue_record","rb");
    fp3=fopen("files//temp","wb");
    flag=0;
    while(fread(&I,sizeof(I),1,fp2))
    {
        if(I.lib_code==i)
        {
            flag=1;
            temp=I;
        }
        fwrite(&I,sizeof(I),1,fp3);
    }
    if(flag==0)
    {
        printf("No issue records found");
    }
    else
    {
        printf("Enter Today's date : ");
        scanf("%d %d %d",&t_date.dd,&t_date.mm,&t_date.yyyy);
        i=count_days(temp.return_date,t_date);

        printf("Book returned\n");
        printf("fine = %d\n",cal_fine(i));
    }


    fclose(fp1);
    fclose(fp2);
    fclose(fp3);

    remove("files//issue_records");
    rename("files//temp","files//issue_records");

	printf("Enter any key to continue");
    getch();
}

int ifleap(int year)
{
    if (year%400 == 0)
        return 1;

    if (year%100 == 0)
        return 0;

    if (year%4 == 0)
        return 1;

    return 0;
}

int count_days(date d1,date d2)
{
    long int n1,n2,i;
    int month_days[]={30,28,31,30,31,30,31,31,30,31,30,31};

    n1=d1.yyyy*365+d1.dd;
    n2=d2.yyyy*365+d2.dd;

    for(i=0;i<d1.mm;i++)
        n1+=month_days[i];
    for(i=0;i<d2.mm;i++)
        n2+=month_days[i];

    if(ifleap(d1.yyyy))
        n1+=1;

    if(ifleap(d2.yyyy))
        n2+=1;

    return (n2-n1);

}

int cal_fine(int t_days)
{

    if(t_days<=0)
        return 0;
    else if(t_days<=15)
        return t_days*1;
    else if(t_days<=30)
        return ((t_days-15)*2 + 15);
    else if(t_days<=45)
        return ((t_days-30)*3 + 30);
    else
        return ((t_days-45)*5 + 45);
}

date cal_return_date(date i_date)
{
    int d=i_date.dd,m=i_date.mm,y=i_date.yyyy,i;
    int month_days[]={30,28,31,30,31,30,31,31,30,31,30,31};

    for (i=0;i<90;i++)
    {
        d++;
        if (d > month_days[m-1] || ( m==2 && d==29 && !ifleap(y) ) )
        {
            d = 1;
            m++;
            if (m==13)
            {
                m = 1;
                y++;
            }
        }
    }
    i_date.dd=d;
    i_date.mm=m;
    i_date.yyyy=y;

    return i_date;
}

