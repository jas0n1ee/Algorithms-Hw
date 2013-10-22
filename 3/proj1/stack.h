 typedef struct { 
   LNode* top;    
   int length;  
 }Stack;
 void InitStack ( Stack &S )
 { 
   S.top = NULL;  
   S.length = 0;  
 } 
 void Push ( Stack &S, ElemType e )
 {
   LNode p = new LNode;   
   if(!p) exit(1);  
   p -> data = e;
   p -> next = S.top; 
   S.top = p;    
   ++S.length;   
 } 
 
 bool Pop ( Stack &S, SElemType &e )
 { 
   if ( !S.top )
     return FALSE; 
   else 
     {
       e = S.top -> data;   
       q = S.top; 
       S.top = S.top -> next;  
       --S.length;       
       delete q;       
       return TRUE;
     }
 }
