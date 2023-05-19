//motivation behind making this project was to demonstrate to you c++ and OOP concepts like encapsulation, friend class, friend functions,etc.
//graph project and c++ oops concepts used.
//all variables have good names for clear understanding and a good practice.
//explaination for each logic will be done to you on pen and paper.

#include <iostream>
#include<bits/stdc++.h>
using namespace std;

class graph;//forward declaration

//this is node of graph.
class node{
    
    friend class graph;  //this is the node and class graph is container class hence we need to make graph class as friend so that it can access all
                         //private elements of node class easily.this is friend class concept in object oriented programming.
    private:
    
    int data;
    bool mark;  //this mark is for technique mark and sweep method
    int refcount;  //this count is for technique refdelete method but take care before deleting a node that it also doesn't has any children.
    node* next1;
    node* next2;
    node* next3;
    
    public:
    node(int data)
    {
        this->data=data;
        next1=0;
        next2=0;
        next3=0;
        mark=0;
        refcount=0;
    }
    int getdata(){return data;}
    void setdata(int data){this->data=data;}
    void setnext1(node* next1){this->next1=next1;};
    void setnext2(node* next2){this->next2=next2;};
    void setnext3(node* next3){this->next3=next3;};
    node* getnext1(){return next1;}
    node* getnext2(){return next2;}
    node* getnext3(){return next3;}
};

class graph{
    
    private:
    node** arr;//arr is pointer pointing to array of type node* on heap.(adj list)
    int size;
    
    public:
    graph(int n,vector<int>&givenarr)
    {
        arr=new node*[n];
        size=n;
        for(int i=0;i<givenarr.size();i++)
        {
            arr[givenarr[i]]=new node(givenarr[i]);
        }
    }
    
    node* get_arr_elements(int index){return arr[index];}
    //this is used to make that adj list (arr)
    void addedge(int source,int dest1,int dest2,int dest3)
    {
        node* mov=arr[source];
        if(dest1!=-1)
        {
            arr[dest1]->refcount++;
            mov->next1=arr[dest1];
        }
        if(dest2!=-1) 
        {
            arr[dest2]->refcount++;
            mov->next2=arr[dest2];
        }
        if(dest3!=-1) 
        {
            arr[dest3]->refcount++;
            mov->next3=arr[dest3];
        }
    }
    void printadjlist()
    {
        for(int i=0;i<size;i++)
        {
            if(arr[i])
            {
                node* mov=arr[i];
                cout<<mov->data<<" -> ";
                if(mov->next1) cout<<mov->next1->data<<" ";
                if(mov->next2) cout<<mov->next2->data<<" ";
                if(mov->next3) cout<<mov->next3->data;
                cout<<endl;
            }
            
        }
    }
    void tellrefcountofallnodes()
    {
        for(int i=0;i<size;i++)
        {
            if(arr[i])
            {
                node* mov=arr[i];
                cout<<mov->data<<" -> ";
                cout<<mov->refcount;
                cout<<endl;
            }
            
        }
    }
    
    //it travels from the root to all other connected nodes like void travel() of graphs.
    void travelmark(node* root)
    {
        root->mark=1;
        if(root->next1) travelmark(root->next1);
        if(root->next2) travelmark(root->next2);
        if(root->next3) travelmark(root->next3);
    }
    
    void sweep()
    {
        for(int i=0;i<size;i++)
        {
            if(arr[i])
            {
                node* mov=arr[i];
                if(mov->mark==0)   //nodes whose mark is 0 we first decrease all children's refcount and then mark arr[i] as null.
                {  
                    if(mov->next1) mov->next1->refcount--;
                    if(mov->next2) mov->next2->refcount--;
                    if(mov->next3) mov->next3->refcount--;
                    arr[i]=0;
                }
            }
        }
    }
    void refdelete()  //here with reference delete method take care that the node should not have any children.
    {
        for(int i=0;i<size;i++)
        {
            if(arr[i])
            {
                node* mov=arr[i];
                if(mov->refcount==0)
                {
                    if(mov->next1==0&&mov->next2==0&&mov->next3==0) arr[i]=0;  
                }
            }
        }
    }
    
};


int main()
{
    
    int n=11;
    vector<int>givenarr{1,2,3,5,7,8,9,10};   //this part is to be confirm that these are the nodes to be interconnected to each other.
    graph g1(n,givenarr);                     //hence added one by one the nodes 1,2,3,5,7,8,9,10
    
    
    node* root1=g1.get_arr_elements(5);   // this roots are used in mark and sweep method to travel the connected nodes and mark them
    node* root2=g1.get_arr_elements(1);
    
    g1.addedge(1,2,9,10);
    g1.addedge(3,8,10,-1);  //now adding the edges
    g1.addedge(5,1,-1,-1);
    g1.addedge(7,1,8,-1);
    g1.addedge(8,9,-1,-1);
    
    cout<<"adjacency list before mark and sweep method"<<endl;
    g1.printadjlist();
    cout<<endl;
    g1.tellrefcountofallnodes();
    cout<<endl;
    
    g1.travelmark(root1);
    g1.sweep();
    
    cout<<"adjacency list after mark and sweep method"<<endl;
    cout<<endl;
    g1.printadjlist();
    cout<<endl;
    g1.tellrefcountofallnodes();
    
    return 0;
}

