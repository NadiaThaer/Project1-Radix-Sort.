/*
  Nadia Thaer.
  1210021.
  s 1 .
*/
#include <stdio.h>
#include <stdlib.h>
#include<string.h>//To Use A function Of String.
#include<stdbool.h>//using it in Reading Function.
#include<ctype.h>
#define  MAX    31
#define  Indix  128//Indix of Array of Linked List.
FILE *input;//pointer To Input File.
FILE *output;//pointer to outputFile.
////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Define the Strcut of Doubly Linked List.//
typedef struct node *ptr;
struct node
{
    char Data[MAX];
    ptr next;
    ptr prev;
} ;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ptr tail=NULL;//This Pointer Is To Point in The Last Node Of My List.
ptr Array[Indix];//Define the Array of Doubly Linked List.
char nameOFFaile[20];//This Array Is To Store The Name Of File From User.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Menu();
ptr ReadFile(ptr L);
ptr Creat_Node(char *word);
ptr insert_End(ptr L, char *Data);
int GetSizeOfList(ptr L);
int Get_Max_Length_Of_word(ptr L);
ptr Delet_From_Big(ptr L);
ptr Delet_From_End(ptr L);
ptr Delet_At_Specific_Pos(ptr L ,int Pos);
void SaveInFail(ptr L);
int Serch_of_word_Location(ptr L,char *Data);
char Get_Char_Atpos(char *word,int pos);
ptr  preForm(ptr L);
void deletAllNode(ptr L);
ptr  Radix_Sort(ptr L);
ptr Without_Spacing(ptr L);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Note: The Description  of Function is Below .
int main()
{
    ptr List =NULL;//Define The Header of Doubly Linked List.
    int Choice=0;//Define This Var To Store The Choice Selected By User.
    char  Data[MAX];//This to store New Word<-------------->
    while (Choice < 8) {
        printf("\n\n---------------------------------------------------------Enter Your Choice-----------------------------------------------------------------------------\n");
        Menu();//Display Menu.
        scanf("%d", &Choice);//Read the Choice From User.
        switch (Choice) {
            case 1:List = ReadFile(List);//Upload Data From Input File.
                  if(List!=NULL)//Thats mean The File Dose Not Exist<---------->
                  {
                   int MaxLength =Get_Max_Length_Of_word(List);
                    int size =GetSizeOfList(List);//Size Of List.
                printf("Your Data Was Loaded, You have %d words and The Max length of the Word is %d\n",size,MaxLength);
                  }
                break;
            case 2:
                printf("--------------------------------The Strings before Sorting----------------------------------------\n");
                Display(List);
                break;
            case 3:
                    printf("The String has been sorted Enter Choice 4 To print it.\n");
                    List= Radix_Sort( List);//Calling Function Sort.
                break;
            case 4:printf("\n--------------------------------The Strings After Sorting----------------------------------------\n");
                              Display(List);
                                 break;
            case 5:
                /*this Function Do Tow Task:
                     1-Add the new word to List.
                     2-Sorted This List.
                     So List in Answer Contain sorted list with new word.
                     */
                             printf("Enter Data You Want To Added to List:\n");
                             scanf("%s", Data); // Reads up to 29 characters to accommodate the null-terminator
                                 if(isalpha(Data[0])==0)//This is To Check if The First Char is an A latter 'a'>>'z'Or 'A'>>'Z'
                           {
                              printf("********(%s)********** This Word is Not Stating With Char Later **So We Dont Add It to List.**\n",Data);
                                 break;
                           }
                             List = insert_End(List, Data);
                             List=Radix_Sort(List);
                             printf("\nYouer List After Add %s And Sort It Become\n",Data);
                             Display(List);
                             break;

                    break;
           case 6:printf("\n");
                  int position;//Define This Var To store the Value Come From Function(Serch_of_word_Location).
                  printf("Enter the word you want to Deleting\n");
                  char Data[MAX];
                  scanf("%s",Data);
                  position=Serch_of_word_Location( List,Data);//Find the position of the New word to Delet It
                   ////If position ==0 Then The list isEmpty.
                   ptr L;
                   L=List;//this Step is to Save the orginal List.
                  List=Delet_At_Specific_Pos(List,position);//List After Deleitng the new word
                  if(List==NULL)
                  {
                  List=L;/*this about if :Function Delet_At_Specific_Pos
                  Return Null This mean :
                  if the word you want to Deleated is Not in The List.
                  */
                  break;
                  }
            printf("After deleted (%s) From pos %d your List is become :\n",Data,position);
               Display(List);
               break;
        case 7: printf("----------------------------------------Your Data was Saved in Output File-----------------------------------------------");
                SaveInFail(List);
                break;
        case 8:
            break;

        }
    }
    ////After Ending Delet All THE NODE FROM MY LIST:
     deletAllNode( List);//to free List.
     printf("****************************************************Ending The Program **************************************************************************************");

    return 0;
}
///////////////////////////////////////////Function To Display The Menu//////////////////////////////////////////////////////
void Menu()
{
    printf("1-Load A Strings From File.\n");
    printf("2-Print The String before Sorting.\n");
    printf("3-Sort The String.\n");
    printf("4-Printing Sorted List.\n");
    printf("5-Adding New Word to List of Sorted List(And Sort it).\n");
    printf("6-Deleting word from the Sorted String.\n");
    printf("7-Save To output File.\n");
    printf("8-Exit.\n");

}
////////////////////////////////////////////////////////////Read From File To Load Data.////////////////////////////////////////////////////////////
ptr ReadFile(ptr L) {

    printf("Enter The Name Of File You Wont To Load A data From It(Note:your name must beas >>name.txt\n");
    scanf("%s",nameOFFaile);
    input = fopen(nameOFFaile, "r");//open File To Read It.
    if (input == NULL){
        printf("**********File could not Found**********\n");
        return NULL;
    }
    char *Data;//To Store The Data When I read It From File.
    bool keepread=true;//Initialize Flag and Put it True
    while(keepread)
    {
        fscanf(input,"%s",Data);
        if(feof(input)!=0)
        {
            /*feof() function  used to check if the file
         point to the end of the file or not.
          It returns a non-zero value if the end is reached, otherwise, it returns 0.
        */
        keepread=false;//To Get of From The Loop When Keep read ==False.
        break;
        }
        if(isalpha(Data[0])==0)//This is To Check if The First Char is an A latter 'a'>>'z'Or 'A'>>'Z'.
        printf("********(%s)********** This Word is Not Stating With Char Later **So We Do not Add It**\n\n",Data);
        else if(strlen(Data)>30)
          printf("********(%s)********** The length of this word is Grater than 30**So I Do not Add It** \n",Data);
        else
        L = insert_End(L,Data);//when I read A new Data Put It In The List Directly.
    }
    fclose(input);//Close The File.

    return L;// Return List After Update it.
}
//////////////////////////////////////////////////////////////Creat a node To Added it in The List//////////////////////////////////////////////
ptr Creat_Node(char *word)
{
    ptr newNode=(ptr)malloc(sizeof(struct node));
    strcpy(newNode->Data,word);
    newNode->next=NULL;
    newNode->prev=NULL;
    return newNode;
}
//////////////////////////////////////////////////////////Insert The Node In The End Of The List///////////////////////////////////////
ptr insert_End(ptr L, char *Data) {
    ptr newNode=Creat_Node(Data);//Creat a new Node Using Function Creat_Node.
    //First Step :Check if the List Is Empty THen The New Node Will Be The First Node I want To Add.
        if(L==NULL)
        {
        L=tail=newNode;
        }
        else//This Mean That The List is Not Empty So I will Add The New Node in The last of The List.
        {
          tail ->next=newNode;//Note:Tail is pointer I defined it To Pointer To the Last Node in The List.
           newNode->prev=tail;
          tail=newNode;//After this Step:The New Node is Will Be The Last Node So:The tail Will Pointer to New Node..
        }
    return L;//Return Updating List.
}
/////////////////////////////////////////////Display List in Recursion Way ////////////////////////////////////////////////////
void Display(ptr L) {
    if(L==NULL)//This Mean arraived to The End of List.
    {
        printf("NULL\n");//print Null when you Reach To End of List.
        return;//get out From Function
    }
       printf("%s<>",L->Data);//printing Data Before Call The Function To Do The Recursion.
        Display( L->next);
}
////////////////////////////////////////////////////////Get the Size of List==Number  Of Node That making List.  ////////////////////////////////////////////////////////////////////////
int GetSizeOfList(ptr L)
{
    //First Step:Check if The List Is Empty Or Not.
    if(L==NULL)
    {
        printf("Your List is Empty With Zero Node!!\n ");
        return 0;
    }
    int node=0;//Initialize the Counter=0;
    ptr temp=L;//This pointer point to The List.
    while(temp!=NULL)
    {

        temp=temp->next;
         node++;
    }

    return node;

}
///////////////////////////////////////////////////////////Get the Maximum Length of Word in The Input Data///////////////////////////////////////////////////////////////////
int Get_Max_Length_Of_word(ptr L)
{
   ///First Step:Check if The List is Empty.
    if(L==NULL)
    {
        printf("Your List is Empty!!\n");
        return -1;//This Mean No wOrd to Get Max!!!!!!!!!!!!!!!!
    }
    int Max_Length=0;//Initialize the Length=0;
    ptr temp=L;//Pointing to List.
    while(temp!=NULL)
    {
        if(strlen(temp->Data)>Max_Length)
        {
         Max_Length=strlen(temp->Data);//Update  Max Length.
        }


        temp=temp->next;//Update pointer.
    }
    return Max_Length;

}
///////////////////////////////////////////////////////This Function  is to Deleting  The First Node From List //////////////////////////////////////////////////////////////////
ptr Delet_From_Big(ptr L) {
    //First Step: We Need To Cheek if The List is Empty Or Not.
    if(L==NULL)
    {
        printf("The List IS Empty !!\n");
        return NULL;
    }
       ptr D=L;//This is To pointer to The Node I want To Deleting  It.
        L=D->next;//Update the Header of List To Point to The Second Node.
        L->prev=NULL;//Update  The prev pointer Becouse the List is Double .
        free(D);//use A function Free from C Laiprare
        return L;//After These Opration Return Updating List.
}
//////////////////////////////////////////////////////////This Function is to Deleting Last Node From List./////////////////////////////////////////////////////////////////////
ptr Delet_From_End(ptr L)
{
      //First Step: We Need To Cheek if The List is Empty Or Not.
    if(L==NULL)
    {
        printf("The List IS Empty !!\n");
        return NULL;
    }
    ptr d=tail;//Note:Tail is Pointer at the Last Node So It is Easy To Deleted it.
    d->prev->next=NULL;//Update the Pointer .
    tail=d->prev;//Updating The Tail .
    free(d);
    return L;//Return Updating List.
}
/////////////////////////////////////////////////////////////This Function is To Deleting The new Word that Added to The List After Determine its location  //////////////////////////
ptr Delet_At_Specific_Pos(ptr L ,int Pos)
{
//First Step: We Need To Cheek if The List is Empty Or Not.
   if(Pos==0)
    return ;
    if(L==NULL)
    {
        printf("The List IS Empty !!\n");
        return NULL;
    }
    if(Pos==1)
    {
        //This Mean Deleting The First Node.
        return Delet_From_Big(L) ;//Calling The Function That Deleting First Node.
    }
    else
        if(Pos==GetSizeOfList(L))//this Mean That The Node is The Last One.
        return Delet_From_End(L);////Calling The Function That Deleting Last Node.
    else if(Pos<GetSizeOfList(L))
    {
        //I need To Find the node in The position .
        //This i is to arraive To Pos;
        int i=1;
        ptr D=L;
        while(i<Pos)
        {

            D=D->next;
             i++;
        }

        //After Get out fROM tHE Loop The D will Point in The Node prev the node i want To Deleting it.
        D->prev->next=D->next;
        D->next->prev=D->prev;
        ///////////After To Line The Node I want To Deleting it is Ready To Deleting It.
        free(D);//Free it.
        ////////////////////////////////////////////////////////
        return L;//Return The Updating List.
    }
    else
    {
        printf("This Element is not include your List to Deleteting it.\n");
        return NULL;
    }
}
/////////////////////////////////////////////////////////////This Function Using To Determained Word Location in List/////////////////////////////////////////
int Serch_of_word_Location(ptr L,char *Data)
{
        //First Step: We Need To Cheek if The List is Empty Or Not.
    if(L==NULL)
    {
        printf("The List IS Empty !!\n");
        return 0;
    }


    ////////////////////////////////////////////////////////////////////////////////////
    ptr t = L;
    int pos = 1;
  while (t != NULL && strcmp(t->Data, Data) !=0) {//when is Come From Loop This mean Return To Word pos.
        pos++;
        t = t->next;
    }

    return pos;
}
///////////////////////////////////////////////////////////////////////Save To File //////////////////////////////////////////////////////
void SaveInFail(ptr L)
{
        if(L==NULL)
    {
        printf("Your List Is Empty !!\n");
        return;
    }
    output=fopen("output.txt","w");//Open The File Output.
    fprintf(output,"\n*****************************************The Updating List******************************************************* \n\n\n\n");
    ptr temp=L;//Point To List.
    while (temp != NULL)
        {
         fprintf(output,"%s<>",temp->Data);//Printing On File.
         temp = temp->next;//Updating The Pointer.
        }
    fprintf(output,"NULL\n");
    fclose(output);//Closing The File.

}
///////////////////////////////////////////////////////////////////////Get The Char at pos to Using It IN tHE Radix Sort.//////////////////////////////////////////////////////////
char  Get_Char_Atpos(char *word,int pos)
{
    char res;//To Store The REsult.
    if(word==NULL)//To Check that Word is Exicet
    {
        printf("Their is No Word To Comper It  !!\n");
        return NULL;
    }
    char *c;//this pointer of char i will use it to pointer to The Last Of Char.
    int Length=strlen(word);//get The Length of word.
        c = &word[Length -1];//the pointer of Char point to Last char.
        int i=0;
    while(i!=pos)
    {
        *c--;
        i++;
    }
    res=*c;//this mean the char res is Equle to the char the (pointr)c is point it .
    return res;
}
////////////////////////////////////////////////////////////////////////This is to prepaere The Word To Using it in Radix Sort./////////////////////////////////////////////////////////
ptr  preForm(ptr L)
{
      if(L==NULL)
    {
        printf("The List is Empty !!\n");
        return NULL;
    }
    ptr t=L;
    ptr res=NULL;//This will point to Updating List.
    char word[MAX];
    char spase[]="-";//Adde to the word .
    int maxofLength=Get_Max_Length_Of_word(L);
    while(t!=NULL)
    {
        strcpy(word,(t->Data));

        while(strlen(word)<maxofLength)
           {
            strcat(word,spase);//Added the spase to word
           }
         res=insert_End(res,word);//start to creat the list withspace.
        t=t->next;
    }
    return res;
}
////////////////////////////////////////////////////////////////////////Deleting All Node of List.///////////////////////////////////////////////////////////
void deletAllNode(ptr L)
{
    //First Step: We Need To Cheek if The List is Empty Or Not.
    if(L==NULL)
    {
        printf("The List IS Empty !!\n");
        return ;
    }
       ptr t=L;
    ptr deletingNode;
    while (t->next!= NULL)
    {
       deletingNode=t->next ;
       t->next =deletingNode->next;
       free(deletingNode) ;
    }
    L->next=NULL;

    printf("All Node is Deleted \n");



}
//////////////////////////////////////////////////////////////////////////Radix_Sort_Function/////////////////////////////////////////////////////////
ptr  Radix_Sort(ptr L)
{
     //First Step: We Need To Cheek if The List is Empty Or Not.
     if(L==NULL)
    {
        printf("The List Is Empty !!\n");
        return ;
    }
    int Max=Get_Max_Length_Of_word(L);//Get Max Length.
    ptr result=NULL;//This Will Store The Updating
    int digitinPOs=0;//This is to Handile And till what is The pos Digit I want.
    char word[MAX];//To store word.
    L=preForm(L);//preper the List To Sort It.
    ptr temp=L;//This Is point to L After Updating By Calling Function PreForm.
    //Initialize the Array of List.
    int j=0;//This Is To Arraive to Indix of Array Of List
    while(j<Indix)
    {
        Array[j]=NULL;
        j++;
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

while(digitinPOs<Max)//this Loop will work Max Time .
{
            temp=L;//Reset The Temp In Each Loop
           result=NULL;//To Preper it to Can Have The List From The Array Of List.
             j=0;
             while(j<Indix)//ReInitialize the Array of List In Each loop.
               {
                    Array[j]=NULL;
                      j++;
            }

    while(temp!=NULL)
    {
        char digit='0';//initialization char .
        digit=Get_Char_Atpos(temp->Data,digitinPOs);

        int indix=(int)digit;//Use the Type Casting.(the number is ==ACCI .

        //printf("\n char %c  in indix %d\n",digit,i);
        strcpy(word,temp->Data);
        Array[indix]=insert_End(Array[indix],word);
        temp=temp->next;
    }
   //I need To Get All Element From The Array Of List.
   j=0;
   ptr t=Array[j];
   while(j<Indix)
   {
       t=Array[j];

       while(t!=NULL)
       {
           char word[MAX];
           strcpy(word,t->Data);
           result=insert_End(result,word);
           L=result;//Updating the L to point to the Result.
           t=t->next;
       }
       j++;
   }
   digitinPOs++;
}

  return Without_Spacing(result);//this because i need to resulting without space after sorting.

}
 ///////////////////////////////////////////////////I need This Function After Using The Radix Sort To display Without Spacing. //////////////////////////////////////////////////////////////////////////////
ptr Without_Spacing(ptr L)
{

    ptr t=L;
    ptr resulet=NULL;
    while(t!=NULL)
    {
        char W[MAX];
        strcpy(W,t->Data);
        char res[MAX];
        int i=0;
        while(W[i]!='\0')
        {
            res[i]=W[i];
            if(W[i]=='-')
            {
               res[i]='\0';//Ending of String.
               break;
            }
            i++;
        }
       resulet=insert_End(resulet,res);
        t=t->next;
    }
                return resulet;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////***********   *Ending**    ****************///////////////////////////////////////////////////////
