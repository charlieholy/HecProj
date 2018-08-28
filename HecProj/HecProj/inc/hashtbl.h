#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define TRUE   1
#define FALSE  0

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+ declarations                                                      +
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

struct HashTbl
{
	unsigned char empty;		/*indicates if entry is used or not  �����������Ŀ��ʹ�û�*/
    char str[32];				/*string payload  �ַ�����Ч�غ�*/
    struct HashTbl *left;
    struct HashTbl *right;
};

#define PRIME 5

class HashTable
{
	struct HashTbl hashTbl[PRIME];	/*the hash table itself*/

	int hashpjw(char *s); 

	/*binary tree routines needed for collision resoltuion
		������������Ҫ����ײresoltuion
	*/

	struct HashTbl* findNode(struct HashTbl* link, char *val);
	void insertNode(struct HashTbl** link, char *val);
	void printTree(struct HashTbl* link, int level);
	void deleteAll(struct HashTbl **link);

	public:
	HashTable();
	~HashTable();
	struct HashTbl* queryHashTbl(char *str);
	void addHashTblEntry(char *val);
	void printHashTbl();
};

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+ definitions                                                       +
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

HashTable::HashTable()
{
	int i;
	for(i=0;i<PRIME;i++)
	{ 
		hashTbl[i].empty = TRUE;
		hashTbl[i].str[0]='\0';
	}
	return;

}/*end constructor*/

/*-----------------------------------------------------------------*/

HashTable::~HashTable()
{
	int i;
	for(i=0;i<PRIME;i++)
	{ 
		deleteAll(&(hashTbl[i].left));
		deleteAll(&(hashTbl[i].right));
	}
	return;

}/*end destructor*/

/*-----------------------------------------------------------------*/

/*
if symbol exists in hash table, we get a pointer to the node
if a symbol does not exist in the hash table, we get NULL
��������д��ڹ�ϣ�����ǵõ�һ��ָ��ýڵ�
���һ�������в����ڹ�ϣ�����ǿ��Կ�
*/

struct HashTbl* HashTable::queryHashTbl(char *str)
{
	int hash;

	hash = hashpjw(str);

	if(hashTbl[hash].empty==TRUE)
	{ 
		return(NULL); 
	}
	
	return(findNode(&(hashTbl[hash]), str));

}/*end queryHashTbl*/

/*-----------------------------------------------------------------*/

void HashTable::addHashTblEntry(char *val)
{
	struct HashTbl *ptr;
	int hash;

	hash = hashpjw(val);
	
	printf("HashTable.addHashTblEntry(): hash(%s)=%d\n",val,hash);

	if(hashTbl[hash].empty==TRUE)
	{ 
		hashTbl[hash].empty=FALSE;
		strcpy(hashTbl[hash].str,val);
		hashTbl[hash].left = NULL;
		hashTbl[hash].right = NULL;
		return; 
	}
	
	ptr = &hashTbl[hash];
	insertNode(&ptr, val);
	return;

}/*end addHashTblEntry*/

/*-----------------------------------------------------------------*/

void HashTable::printHashTbl()
{
	int i;
	for(i=0;i<PRIME;i++)
	{ 
		if(hashTbl[i].empty == FALSE)
		{
			printf("--Hash Slot (%d)--\n",i);
			printTree(&(hashTbl[i]), 0);
			printf("\n");
		}
	}
	printf("\n");
	return;

}/*end printHashTbl*/

/*-----------------------------------------------------------------*/

int HashTable::hashpjw(char *s)
{
	unsigned char * p;
	unsigned h = 0, g;

	for (p = ((unsigned char*)s); *p != '\0'; p = p + 1)
	{
		h = (h << 4) + (*p);
		if (g = (h & 0xf0000000))
		{
			h = h ^ (g >> 24);
			h = h ^ g;
		}
	}

	return h % PRIME;

}/*end hashpjw*/

/*-----------------------------------------------------------------*/

struct HashTbl* HashTable::findNode(struct HashTbl* link, char *val)
{
    if(link==NULL)
    { 
        return(NULL); 
    }
    else if(strcmp(val,(*link).str)==0)
    { 
        return(link); 
    }
    else if(strcmp(val,(*link).str)>0 )
    { 
        return(findNode((*link).right,val)); 
    }
    else
    {
        return(findNode((*link).left,val));
    }

}/*end findNode*/

/*-----------------------------------------------------------------*/

void HashTable::insertNode(struct HashTbl** link, char *val)
{
    if( (*link) == NULL )
    {
        (*link) = (struct HashTbl*)malloc(sizeof(struct HashTbl));
		(*(*link)).empty	= FALSE;
		strcpy((*(*link)).str,val);
        (*(*link)).left		= NULL;
        (*(*link)).right	= NULL;
    }
    else if( strcmp(val,(*(*link)).str) == 0 )
    {
		printf("HashTable.insertNode(): redundant identifier %s\n",val);
        return;
    }
	else if( strcmp(val,(*(*link)).str) < 0 )
    {
        insertNode( &((*(*link)).left) , val);
    }
    else
    {
        insertNode( &((*(*link)).right) ,val);
    }
    return;

}/*end insertNode*/

/*-----------------------------------------------------------------*/

/*
print tree by giving root to node and zero as args	
��ӡ��������ڵ��Ϊ��args
*/

void HashTable::printTree(struct HashTbl* link, int level)
{
    int i;
    if(link==NULL)
    {
        return;
    }
    
	printTree((*link).right,level+1);

    for(i=0;i<level;i++){ printf("-"); }
    printf("identifier =%s\n",(*link).str);

	printTree((*link).left,level+1);
    
    return;

}/*end printTree*/

/*-----------------------------------------------------------------*/

void HashTable::deleteAll(struct HashTbl **link)
{
	if((*link)==NULL)
	{ 
		return; 
	}
	deleteAll(&((*(*link)).left));
	deleteAll(&((*(*link)).right));

	printf("HashTable.deleteAll(): freeing %s\n",(*(*link)).str);
	free((*link));
	*link=NULL;
	return;

}/*end deleteAll*/

/*-----------------------------------------------------------------*/

/*
Do not have routines to delete hash table entries
Take unnecessary time to perform demolition of the symbol table,
string table, and hash table. Effort spent taking them apart and
freeing them is wasted. Quicker, and easier to let the assembler
complete and let the operating system reclaim everything. 
û������ɾ����ϣ����Ŀ
��ȡ����Ҫ��ʱ�����в�����ű�
�ַ�������ϣ��Ŭ�������ǳ��˻���
�ͷ��������˷ѡ����죬�������û��
�����ģ����ò���ϵͳ�ջ�һ�С�
*/



