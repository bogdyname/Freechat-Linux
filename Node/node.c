typedef struct Node
{
  int value;
  struct Node *next;
} Node;

Node *head = NULL;


/*

*/
void push(Node **head, int data)
{
  Node *tmp = (Node*) malloc(sizeof(Node)); //new connect
  tmp->value = data; //set value for new connect
  tmp->next = (*head); //set pointer of previous connect
  (*head) = tmp; //set pointer of new connect for head pointer

  return;
}


/*
  Head pointer can change yourself value.
  So I need to pass pointer to pointer.


*/
int pop(Node **head)
{
  Node *prev = NULL; //default pointer
  int val; //value in end of list

  if(head == NULL) //check pointer in the head
  {
    exut(-1);
  }

  prev = (*head); //
  val = prev->value;
  (*head) = (*head)->next;

  free(prev);

  return val;
}
