#include<iostream>
#include<list>
using namespace std;
//Defined Tree Structure
struct t
{
	int data;
	struct t *l;struct t *r;
};
//Adding elements to Tree 
void insert(struct t **root,int data)
{
	struct t * cur = new struct t;
	cur->data =data;
	cur->l=cur->r=NULL;
	*root = cur;
}

//Printing the tree Nodes Using Inorder without recursion and stack
void inorder(struct t *root)
{
	if(!root)
		return;

	struct t * cur = root;
	while(cur)
	{
		if(!cur->l)
		{
			cout<<cur->data<<" ";
			cur = cur->r;
		}
		else
		{
			struct t * pre = cur->l;
			for(;pre->r!=NULL && pre->r!=cur;)
				pre =pre->r;
	
			if(!pre->r)
			{
				pre->r=cur;
				cur = cur->l;
			}
			else
			{
				pre->r=NULL;
				cout<<cur->data<<" ";
				cur = cur->r;
			}
		}
	}
}
//swap left and right child of each node present in Tree for every level.

//Given Input Tree 
//		5
//	 3		 7
//2	   4  6		8

//Expected Output Tree
//		5
//	 7		 3
//4	   2  8		6
void swapNodeInSameLevel(struct t **root)
{
	struct t * cur = *root;
	if(cur==NULL)
		return;
	list<struct t *> l;
	l.push_back(cur);
	while(!l.empty())
	{
		struct t * temp = l.front();
		l.pop_front();

		//If Both left and right children present, then swap the node data
		if(temp->l&&temp->r)
		{
			int d = temp->l->data;
			temp->l->data=temp->r->data;
			temp->r->data=d;
		}
		//If only right children present,then assign right child to left child and make right child null. 
		else if(!temp->l&&temp->r)
		{
			temp->l=temp->r;
			temp->r=NULL;
		}
		//If only left children present,then assign left child to right child and make left child null. 
		else if(temp->l&&!temp->r)
		{
			temp->r=temp->l;
			temp->l=NULL;
		}

		//If Left child present, then insert into Queue
		if(temp->l)
			l.push_back(temp->l);

		//If Right child present, then insert into Queue
		if(temp->r)
			l.push_back(temp->r);
	}
	//Update the Initial Tree(i.e *root) to Updated Tree(i.e cur) 
	*root = cur;
}
