//examples from http://cslibrary.stanford.edu/105/LinkedListProblems.pdf
#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node *next;
};

int Length(struct node *head){
    int count = 0;
    struct node *current = head;
    while(current != NULL){
        count++;
        current = current->next;
    }
    return count;
}

void Push(struct node **headRef, int newData){
    struct node *newNode = (struct node *) malloc(sizeof(struct node));
    newNode->data = newData;
    newNode->next = *headRef;
    *headRef = newNode;
}

struct node* BuildOneTwoThree(){
    struct node *head = NULL;
    Push(&head, 3);
    Push(&head, 2);
    Push(&head, 1);

    return head;
}

void print_linked_list(struct node *head){
    struct node *current = head;
    while(current != NULL){
        printf("address: %p, data: %d\n", current, current->data);
        current = current->next;
    }
}

//2. Changing a Pointer Using a Reference Pointer
//careful though this does not free the allocated memory, so then doesn't give access to free the memory that was allocated
void ChangeToNull(struct node **headRef){
    *headRef = NULL;
}

void ChangeToNull_and_free(struct node **headRef){
	struct node *curr = *headRef;

	while(curr != NULL){
		struct node *temp = curr;
		curr = curr->next;
		free(temp);
	}
	*headRef = NULL;
}

void add_node_to_end_without_tail(struct node **head_ref, int data_to_add){
    struct node *current = *head_ref;

    while(current->next != NULL){
        current = current->next;
    }
    struct node *new_node = (struct node *) malloc(sizeof(struct node));
    new_node->data = data_to_add;
    new_node->next = NULL;
    current->next = new_node;

}

//how about a function that builds a list from an array
//could be useful as it gives you the ability to have a dynamic array
struct node* build_list_from_int_array(int arr[], int arr_size){
    struct node *head = NULL;
    struct node *tail = head;

    //handle special case for 1st node to add to empty array
    struct node *first_node = (struct node *) malloc(sizeof(struct node));
    first_node->data = arr[0];
    first_node->next = NULL;
    head = first_node;
    tail = first_node;
    int a;
    for(a = 1; a < arr_size; a++){
        struct node *new_node = (struct node *) malloc(sizeof(struct node));
        new_node->data = arr[a];
        new_node->next = tail->next;
        tail->next = new_node;
        tail = tail->next;
    }

    return head;
}

int count_num_occurrences(struct node *list_head, int num_to_search_for){
    struct node *curr = list_head;
    int num_times = 0;
    while(curr != NULL){
        if(curr->data == num_to_search_for){
            num_times++;
        }
        curr = curr->next;
    }

    return num_times;
}

//2 — GetNth()
int get_data_at_nth_index(struct node *list_head, int index_of_interest){
    struct node *curr = list_head;
    //int curr_index = 0;
    int i;
    for(i = 0; i < index_of_interest; i++){

        if(curr == NULL){
            printf("List is shorter than index of interest\n");
            return -9999;
        }
        curr = curr->next;
    }
    return curr->data;
}

//3 — DeleteList()
void delete_list(struct node **list_head){
    struct node *curr = *list_head;

    while(curr != NULL){
        struct node *temp = curr;
        curr = curr->next;
        free(temp);
    }
    *list_head = NULL;
}

//4 — Pop()
int Pop(struct node **list_head){
    struct node *temp = *list_head;
    int data_to_ret = temp->data;
    *list_head = temp->next;
    free(temp);

    return data_to_ret;
}

//5 — InsertNth()
void insert_node_before_nth_index(struct node **list_head, int index, int data_to_insert){
    struct node *curr = *list_head;
    int current_index = 0;
	
    //special case where new node is to be inserted at beginning of list
    if(index == 0){
        struct node *new_node = (struct node *) malloc(sizeof(struct node));
        new_node->data = data_to_insert;
        new_node->next = curr;
        *list_head = new_node;
    }
    else{
        int a;
        for(a = 0; a < index - 1; a++){
            curr = curr->next;
            if(curr == NULL){
               printf("index to insert after was longer than list, insert failed\n");
               return;
            }
        }
        struct node *new_node = (struct node *) malloc(sizeof(struct node));
        new_node->data = data_to_insert;
        new_node->next = curr->next;
        curr->next = new_node;

    }

}

//6 — SortedInsert()
void insert_in_already_sorted_list(struct node **list_head, struct node *node_to_insert){
    //handle case where list is empty or new node needs to be inserted at very beginning of list
    if(*list_head == NULL || (*list_head)->data > node_to_insert->data){
        node_to_insert->next = *list_head;
        *list_head = node_to_insert;
    }
    else{
        struct node *curr = *list_head;
        while(curr->next != NULL && curr->next->data <= node_to_insert->data){
            curr = curr->next;
        }
        node_to_insert->next = curr->next;
        curr->next = node_to_insert;
    }
}

//7 - insertion_sort
void insertion_sort(struct node **list_head){
    struct node *new_sorted_list = NULL;
    struct node *curr = *list_head;

    while(curr != NULL){
        struct node *next = curr->next;
        insert_in_already_sorted_list(&new_sorted_list, curr);
        curr = next;
    }

    *list_head = new_sorted_list;
}

//8 — Append()
void append_list_to_another_list(struct node **list_head_a, struct node **list_head_b){
    if(*list_head_a == NULL){
        *list_head_a = *list_head_b;
    }
    else{
        struct node *curr = *list_head_a;
        while(curr->next != NULL){
            curr = curr->next;
        }
        curr->next = *list_head_b;
    }

}

//9 — FrontBackSplit()
void split_list_in_half_into_2_lists(struct node *orig_list, struct node **start_1st_half, struct node **start_2nd_half){
    int length_orig_list = Length(orig_list);
    // If the number of elements is odd, the extra element should go in the front list.
    //for instance 9 - 1 = 8 / 2 = 4 0-4 inclusive is 5 which fulfills that the first half would have the one more than the 2nd half in the odd amount of nodes situation
    //8 - 1 = 7 / 2 = 3 0-3 inclusive is 4 which is exactly half of 8
    int the_left_kind_of_half = (length_orig_list - 1) / 2;
    printf("size of array: %d, the_left_kind_of_half: %d\n", length_orig_list, the_left_kind_of_half);
    struct node *traveler = orig_list;
    int a;
    for(a = 0; a < the_left_kind_of_half; a++){
        traveler = traveler->next;
    }

    (*start_2nd_half) = traveler->next;
    traveler->next = NULL;
    (*start_1st_half) = orig_list;
}

//10 RemoveDuplicates() from a sorted list
void sort_list_remove_dupes(struct node **list_head){
    insertion_sort(list_head);
    printf("\nsorted:\n");
    print_linked_list(*list_head);
    printf("remove dupes:\n");

    struct node *current = *list_head;
    //int prev_node_data = current->data;
    while(current->next != NULL){
        if(current->next->data == current->data){
            struct node *temp = current->next;
            current->next = current->next->next;
            free(temp);
        }
        else{
            current = current->next;
        }

    }

    print_linked_list(*list_head);

}

//11 — MoveNode()
void move_1st_node_of_2nd_list_to_beginning_of_1st_list(struct node **first_list_head, struct node **second_list_head){
    struct node *temp = *second_list_head;
    *second_list_head = (*second_list_head)->next;
    temp->next = *first_list_head;
    (*first_list_head) = temp;
    //*second_list_head = (*second_list_head)->next;

    printf("\n");
    printf("move_1st_node_of_2nd_list_to_beginning_of_1st_list...\n");
    print_linked_list(*first_list_head);
    printf("\n");
    print_linked_list(*second_list_head);
}

//12 — AlternatingSplit()
void create_2_sublists_from_every_other_index(struct node *orig_list_head, struct node **new_list_head_1, struct node **new_list_head_2){
    struct node *current = orig_list_head;
    struct node *new_list_tail_1 = NULL;
    struct node *new_list_tail_2 = NULL;

    int even_steven = 1;
    while(current != NULL){
        //case for end of odd list
        if(current->next == NULL){
            new_list_tail_1->next = current;
            new_list_tail_1->next->next = NULL;
            new_list_tail_2->next = NULL;
            even_steven = 0;
            break;
        }

        if(*new_list_head_1 == NULL){
            *new_list_head_1 = current;
            *new_list_head_2 = current->next;
            new_list_tail_1 = *new_list_head_1;
            new_list_tail_2 = *new_list_head_2;
        }
        else{
            new_list_tail_1->next = current;
            new_list_tail_2->next = current->next;

            new_list_tail_1 = new_list_tail_1->next;
            new_list_tail_2 = new_list_tail_2->next;
        }

        current = current->next->next;

    }
    if(even_steven){
        new_list_tail_1->next = NULL;
        new_list_tail_2->next = NULL;
    }

}

//13— ShuffleMerge()
void shuffle_merge(struct node *list_one, struct node *list_two, struct node **new_list){
    struct node *curr_1 = list_one;
    struct node *curr_2 = list_two;

    struct node *new_list_curr = *new_list;
    while(curr_1 != NULL || curr_2 != NULL){

        if(new_list_curr == NULL){
            new_list_curr = curr_1;
            *new_list = new_list_curr;

            if(curr_1 != NULL){
                curr_1 = curr_1->next;
            }
        }
        else if(curr_1 != NULL){
            new_list_curr->next = curr_1;
            new_list_curr = new_list_curr->next;
            curr_1 = curr_1->next;
        }

        if(curr_2 != NULL){
            new_list_curr->next = curr_2;
            new_list_curr = new_list_curr->next;
            curr_2 = curr_2->next;
        }
    }
}

//14 — SortedMerge()
struct node* sorted_merge(struct node *sorted_list_1_head, struct node *sorted_list_2_head){
    struct node *sorted_merged_list_traveler = NULL;
    struct node *sorted_merged_list;
    //since both lists are already sorted, just repeatedly compare the heads (don't necessarily need to pop) march down each list until NULL
    //then I guess you can have a conditional to check if one of the other lists is NULL just add the current considered list node...
    struct node *curr_list_1 = sorted_list_1_head;
    struct node *curr_list_2 = sorted_list_2_head;
    while(curr_list_1 != NULL || curr_list_2 != NULL){
        //initial condition where sorted_merged_list is NULL...
        if(sorted_merged_list_traveler == NULL){
            printf("Well hello there, sorted_merged_list_traveler == NULL\n");
            if(curr_list_1->data <= curr_list_2->data){
                sorted_merged_list_traveler = curr_list_1;
                sorted_merged_list = sorted_merged_list_traveler; //Important to set the list head here to the traveler because the traveler has just been set to the 1st node of the sorted list!!!!!
                //sorted_merged_list_traveler = sorted_merged_list_traveler->next;
                curr_list_1 = curr_list_1->next;
            }
            else{
                sorted_merged_list_traveler = curr_list_2;
                sorted_merged_list = sorted_merged_list_traveler; //Important to set the list head here to the traveler because the traveler has just been set to the 1st node of the sorted list!!!!!
                curr_list_2 = curr_list_2->next;
            }
        }

        if(curr_list_1 == NULL){
            sorted_merged_list_traveler->next = curr_list_2;
            sorted_merged_list_traveler = sorted_merged_list_traveler->next;
            curr_list_2 = curr_list_2->next;
        }
        else if(curr_list_2 == NULL){
            sorted_merged_list_traveler->next = curr_list_1;
            sorted_merged_list_traveler = sorted_merged_list_traveler->next;
            curr_list_1 = curr_list_1->next;
        }
        else{
            if(curr_list_1->data <= curr_list_2->data){
                sorted_merged_list_traveler->next = curr_list_1;
                sorted_merged_list_traveler = sorted_merged_list_traveler->next;
                curr_list_1 = curr_list_1->next;
            }
            else{
                sorted_merged_list_traveler->next = curr_list_2;
                sorted_merged_list_traveler = sorted_merged_list_traveler->next;
                curr_list_2 = curr_list_2->next;
            }
        }

    }

    return sorted_merged_list;
}

//15 — MergeSort()
void merge_sort(struct node **list_head){
    struct node *head_traveler = *list_head;
    struct node *split_list_1st_half;
    struct node *split_list_2nd_half;

    //base case to stop the recursion
    if(head_traveler == NULL || head_traveler->next == NULL){//we only have 1 or no nodes so nothing to divide up
        return;
    }

    //divide the current considered list in 1/2
    split_list_in_half_into_2_lists(head_traveler, &split_list_1st_half, &split_list_2nd_half);

    //RECURSION!!!!!
    merge_sort(&split_list_1st_half);
    merge_sort(&split_list_2nd_half);

    //then when stuff starts returning the comparisons are actually done and the sorted list is built from the tiniest divisions on up to the larger divisions until done as things return
    //since the actual smaller lists are being sorted in below recursion iterations, when they return control to the above level recursion iteration they RETURN SORTED LISTS
    *list_head = sorted_merge(split_list_1st_half, split_list_2nd_half); //the original list head is continually pointed to the larger and larger becoming sorted list
}

//16 — SortedIntersect()
//returns new list with new memory of the nodes of two lists that are the same
struct node* two_sorted_lists_intersection(struct node *sorted_list_1_head, struct node *sorted_list_2_head){
    struct node *intersection_list_head = NULL;
    struct node *intersection_list_traveler;
    struct node *sorted_list_1_curr = sorted_list_1_head;
    struct node *sorted_list_2_curr = sorted_list_2_head;

    while(sorted_list_1_curr != NULL && sorted_list_2_curr != NULL){

        if(sorted_list_1_curr->data == sorted_list_2_curr->data){
            //could use push, but think that I will do myself here
            //check if initial node to add to intersection_list
            if(intersection_list_head == NULL){
                struct node *new_node = (struct node*) malloc(sizeof(struct node));
                new_node->data = sorted_list_1_curr->data; //could use either sorted_list_1_curr->data or sorted_list_2_curr->data since equal
                intersection_list_traveler = new_node;
                intersection_list_head = intersection_list_traveler;
            }
            else{
                struct node *new_node = (struct node*) malloc(sizeof(struct node));
                new_node->data = sorted_list_1_curr->data; //could use either sorted_list_1_curr->data or sorted_list_2_curr->data since equal
                intersection_list_traveler->next = new_node;
                intersection_list_traveler = intersection_list_traveler->next;
            }

            //since current considered nodes from each list are both equal, increment indices of both lists
            sorted_list_1_curr = sorted_list_1_curr->next;
            sorted_list_2_curr = sorted_list_2_curr->next;
        }
        else{ //current considered nodes do not have equal data
            if(sorted_list_1_curr->data < sorted_list_2_curr->data){
                sorted_list_1_curr = sorted_list_1_curr->next;
            }
            else{
                sorted_list_2_curr = sorted_list_2_curr->next; //don't have to account for = to because if =, then would have been handled above with if(sorted_list_1_curr->data == sorted_list_2_curr->data)
            }
        }

    }

    return intersection_list_head;
}

//17 — Reverse()
void reverse_list(struct node **list_head){
    struct node *reversed_list = NULL;
    struct node *current = *list_head;
    struct node *next;

    while(current != NULL){
        next = current->next;
        current->next = reversed_list;
        reversed_list = current;
        current = next;
    }

    *list_head = reversed_list;
}

//18 — RecursiveReverse()
void RecursiveReverse(struct node **headRef){
    struct node *first;
    struct node *rest;

    //empty list base case
    if(*headRef == NULL){
        return;
    }

    first = *headRef;
    rest = first->next;

    if(rest == NULL){ //end of list
        return;
    }

    RecursiveReverse(&rest);

    first->next->next = first;
    first->next = NULL; //Ahhhhhh this triggers a return on the next recursive level up

    *headRef = rest;

}

int main()
{
    struct node *three_to_start = BuildOneTwoThree();
    print_linked_list(three_to_start);

    printf("length of list: %d\n", Length(three_to_start));

	//changing to ChangeToNull_and_free which ends up being the same thing as delete_list
	//needed to to avoid memory leak as if you just change the head of a list to point to NULL, whatever memory has already been allocated for the list persists
    //ChangeToNull(&three_to_start);
    ChangeToNull_and_free(&three_to_start);
	print_linked_list(three_to_start);

    printf("length of list: %d\n", Length(three_to_start));

    //when creating the pointer to the head of an empty list, need to set equal to NULL
    //THIS WAY THE RESULTING LIST WILL HAVE A NULL POINTER AT THE END AS YOU PUSH NODES ON THE LIST
    struct node *some_list_1_head = NULL;
    //for loop to push multiple nodes onto list
    int a;
    for(a = 0; a < 12; a++){
        Push(&some_list_1_head, a);
    }
    //Push(&some_list_1_head, 1);
    print_linked_list(some_list_1_head);

    add_node_to_end_without_tail(&some_list_1_head, 666);
    print_linked_list(some_list_1_head);

    int some_int_arr_1[] = {5, 3, 7, 9, 11, 2, 4, 777, 9};
    int size_of_some_int_arr_1 = sizeof(some_int_arr_1) / sizeof(some_int_arr_1[0]);

    struct node *some_int_arr_1_head = build_list_from_int_array(some_int_arr_1, size_of_some_int_arr_1);
    print_linked_list(some_int_arr_1_head);
    add_node_to_end_without_tail(&some_int_arr_1_head, 23);
    print_linked_list(some_int_arr_1_head);

    add_node_to_end_without_tail(&some_int_arr_1_head, 9);
    add_node_to_end_without_tail(&some_int_arr_1_head, 9);
    Push(&some_int_arr_1_head, 9);
    printf("\n");
    print_linked_list(some_int_arr_1_head);

    printf("%d: %d\n", 9, count_num_occurrences(some_int_arr_1_head, 9));

    printf("data at index %d: %d\n", 10, get_data_at_nth_index(some_int_arr_1_head, 10));

    insert_node_before_nth_index(&some_int_arr_1_head, 5, 111);
    print_linked_list(some_int_arr_1_head);

    struct node *a_new_node = (struct node *) malloc(sizeof(struct node));
    a_new_node->data = 42;
    a_new_node->next = NULL;
    insert_in_already_sorted_list(&some_int_arr_1_head, a_new_node);
    printf("\n");
    print_linked_list(some_int_arr_1_head);

    insertion_sort(&some_int_arr_1_head);
    printf("\n");
    print_linked_list(some_int_arr_1_head);

    int some_int_arr_2[] = {21, 22, 23, 24};
    int some_int_arr_2_size = sizeof(some_int_arr_2) / sizeof(some_int_arr_2[0]);
    struct node *some_int_arr_2_head = build_list_from_int_array(some_int_arr_2, some_int_arr_2_size);
    print_linked_list(some_int_arr_2_head);

    int some_int_arr_3[] = {31, 32, 33, 34, 56};
    int some_int_arr_3_size = sizeof(some_int_arr_3) / sizeof(some_int_arr_3[0]);
    struct node *some_int_arr_3_head = build_list_from_int_array(some_int_arr_3, some_int_arr_3_size);
    print_linked_list(some_int_arr_3_head);

    append_list_to_another_list(&some_int_arr_3_head, &some_int_arr_2_head);
    printf("\n");
    print_linked_list(some_int_arr_3_head);

    printf("\n");
    print_linked_list(some_int_arr_2_head);
    /*
    printf("Popped data: %d\n", Pop(&some_int_arr_1_head));
    print_linked_list(some_int_arr_1_head);
    //pop off all of their heads
    while(some_int_arr_1_head != NULL){
        printf("Popped data: %d\n", Pop(&some_int_arr_1_head));
    }
    */

    int some_int_arr_4[] = {31, 32, 33, 34, 35, 36, 90, 100};
    int some_int_arr_4_size = sizeof(some_int_arr_4) / sizeof(some_int_arr_4[0]);
    struct node *some_int_arr_4_head = build_list_from_int_array(some_int_arr_4, some_int_arr_4_size);
    print_linked_list(some_int_arr_4_head);

    printf("undivided list\n");
    print_linked_list(some_int_arr_4_head);
    printf("\n");

    struct node *first_half_some_int_arr_4_head, *second_half_some_int_arr_4_head;
    split_list_in_half_into_2_lists(some_int_arr_4_head, &first_half_some_int_arr_4_head, &second_half_some_int_arr_4_head);

    printf("\n");
    print_linked_list(first_half_some_int_arr_4_head);
    printf("\n");
    print_linked_list(second_half_some_int_arr_4_head);

    int some_int_arr_5[] = {0, 5, 5, 5, 2, 4, 77, 19, 4, 1, 0, 77, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 60, 101, 19};
    int some_int_arr_5_size = sizeof(some_int_arr_5) / sizeof(some_int_arr_5[0]);
    struct node *some_int_arr_5_head = build_list_from_int_array(some_int_arr_5, some_int_arr_5_size);
    printf("\n");
    print_linked_list(some_int_arr_5_head);
    printf("\n");
    sort_list_remove_dupes(&some_int_arr_5_head);

    int some_int_arr_6[] = {0, 1, 2, 3};
    int some_int_arr_6_size = sizeof(some_int_arr_6) / sizeof(some_int_arr_6[0]);
    struct node *some_int_arr_6_head = build_list_from_int_array(some_int_arr_6, some_int_arr_6_size);
    printf("\n");
    print_linked_list(some_int_arr_6_head);
    printf("\n");

    int some_int_arr_7[] = {4, 5, 6, 7, 8};
    int some_int_arr_7_size = sizeof(some_int_arr_7) / sizeof(some_int_arr_7[0]);
    struct node *some_int_arr_7_head = build_list_from_int_array(some_int_arr_7, some_int_arr_7_size);
    printf("\n");
    print_linked_list(some_int_arr_7_head);
    printf("\n");

    move_1st_node_of_2nd_list_to_beginning_of_1st_list(&some_int_arr_6_head, &some_int_arr_7_head);

    int some_int_arr_8[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    int some_int_arr_8_size = sizeof(some_int_arr_8) / sizeof(some_int_arr_8[0]);
    struct node *some_int_arr_8_head = build_list_from_int_array(some_int_arr_8, some_int_arr_8_size);
    printf("\n");
    print_linked_list(some_int_arr_8_head);
    printf("\n");

    struct node *every_other_index_list_1 = NULL, *every_other_index_list_2 = NULL;
    create_2_sublists_from_every_other_index(some_int_arr_8_head, &every_other_index_list_1, &every_other_index_list_2);
    printf("\n");
    print_linked_list(every_other_index_list_1);
    printf("\n");
    print_linked_list(every_other_index_list_2);

    int some_int_arr_9[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    int some_int_arr_9_size = sizeof(some_int_arr_9) / sizeof(some_int_arr_9[0]);
    struct node *some_int_arr_9_head = build_list_from_int_array(some_int_arr_9, some_int_arr_9_size);
    printf("\n");
    print_linked_list(some_int_arr_9_head);
    printf("\n");

    int some_int_arr_10[] = {10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23};
    int some_int_arr_10_size = sizeof(some_int_arr_10) / sizeof(some_int_arr_10[0]);
    struct node *some_int_arr_10_head = build_list_from_int_array(some_int_arr_10, some_int_arr_10_size);
    printf("\n");
    print_linked_list(some_int_arr_10_head);
    printf("\n");

    struct node *shuffle_merged_list = NULL;
    shuffle_merge(some_int_arr_9_head, some_int_arr_10_head, &shuffle_merged_list);
    printf("\n");
    print_linked_list(shuffle_merged_list);
    printf("\n");

    int some_int_arr_11[] = {0, 2, 6, 19, 21, 42};
    int some_int_arr_11_size = sizeof(some_int_arr_11) / sizeof(some_int_arr_11[0]);
    struct node *some_int_arr_11_head = build_list_from_int_array(some_int_arr_11, some_int_arr_11_size);
    printf("\n");
    print_linked_list(some_int_arr_11_head);
    printf("\n");

    int some_int_arr_12[] = {10, 11, 12, 23, 26, 77, 777, 1000};
    int some_int_arr_12_size = sizeof(some_int_arr_12) / sizeof(some_int_arr_12[0]);
    struct node *some_int_arr_12_head = build_list_from_int_array(some_int_arr_12, some_int_arr_12_size);
    printf("\n");
    print_linked_list(some_int_arr_12_head);
    printf("\n");

    struct node *sorted_merged_list;
    sorted_merged_list = sorted_merge(some_int_arr_11_head, some_int_arr_12_head);
    print_linked_list(sorted_merged_list);

    int some_int_arr_13[] = {666, 2, 3, 1, 19, 42, 88, 7, 7, 6, 14, 999, 1, 43, 41, 55, 64, 23, 55, 98745, 11111111, 9};
    int some_int_arr_13_size = sizeof(some_int_arr_13) / sizeof(some_int_arr_13[0]);
    struct node *some_int_arr_13_head = build_list_from_int_array(some_int_arr_13, some_int_arr_13_size);
    printf("\n");
    print_linked_list(some_int_arr_13_head);
    printf("\n");
    merge_sort(&some_int_arr_13_head);
    printf("After merge sort\n");
    printf("\n");
    print_linked_list(some_int_arr_13_head);
    printf("\n");

    int some_int_arr_14[] = {1, 3, 5, 7, 9, 11, 13, 15, 16, 17, 19, 21, 23, 25, 27, 29};
    int some_int_arr_14_size = sizeof(some_int_arr_14) / sizeof(some_int_arr_14[0]);
    struct node *some_int_arr_14_head = build_list_from_int_array(some_int_arr_14, some_int_arr_14_size);
    printf("\n");
    print_linked_list(some_int_arr_14_head);
    printf("\n");

    int some_int_arr_15[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32};
    int some_int_arr_15_size = sizeof(some_int_arr_15) / sizeof(some_int_arr_15[0]);
    struct node *some_int_arr_15_head = build_list_from_int_array(some_int_arr_15, some_int_arr_15_size);
    printf("\n");
    print_linked_list(some_int_arr_15_head);
    printf("\n");

    struct node *intersection_list;
    intersection_list = two_sorted_lists_intersection(some_int_arr_14_head, some_int_arr_15_head);
    printf("\n");
    print_linked_list(intersection_list);
    printf("\n");

    printf("\n");
    print_linked_list(intersection_list);
    printf("\n");

    reverse_list(&intersection_list);
    printf("\n");
    print_linked_list(intersection_list);
    printf("\n");

    int some_int_arr_16[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32};
    int some_int_arr_16_size = sizeof(some_int_arr_16) / sizeof(some_int_arr_16[0]);
    struct node *some_int_arr_16_head = build_list_from_int_array(some_int_arr_16, some_int_arr_16_size);
    printf("\n");
    print_linked_list(some_int_arr_16_head);
    printf("\n");
    RecursiveReverse(&some_int_arr_16_head);

    printf("\n");
    print_linked_list(some_int_arr_16_head);
    printf("\n");

    delete_list(&some_int_arr_16_head);
    delete_list(&some_int_arr_15_head);
    delete_list(&some_int_arr_14_head);
    delete_list(&intersection_list);
    delete_list(&some_int_arr_13_head);
    delete_list(&some_int_arr_11_head);
    delete_list(&some_int_arr_12_head);
    delete_list(&shuffle_merged_list);
    delete_list(&every_other_index_list_1);
    delete_list(&every_other_index_list_2);
    delete_list(&some_int_arr_6_head);
    delete_list(&some_int_arr_7_head);
    delete_list(&some_int_arr_5_head);
    delete_list(&first_half_some_int_arr_4_head);
    delete_list(&second_half_some_int_arr_4_head);
    delete_list(&some_int_arr_1_head);
    print_linked_list(some_int_arr_1_head);
	delete_list(&three_to_start);
	delete_list(&some_list_1_head);

    return 0;
}
