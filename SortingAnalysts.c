#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *n;
};

struct node *head = NULL, *new_node, *temp, *original_head = NULL;
int swap_count = 0;
int is_ascending = 1;

void create_node(int value) {
    new_node = (struct node *) malloc(sizeof(struct node));
    new_node->data = value;
    new_node->n = NULL;
}

void copy_list(struct node* src, struct node** dest) {
    struct node* temp = NULL;
    struct node* new_node = NULL;
    struct node* last = NULL;

    while (src != NULL) {
        new_node = (struct node*)malloc(sizeof(struct node));
        new_node->data = src->data;
        new_node->n = NULL;
        
        if (*dest == NULL) {
            *dest = new_node;
        } else {
            last->n = new_node;
        }
        last = new_node;
        src = src->n;
    }
}

void swap(struct node *a, struct node *b) {
    int temp = a->data;
    a->data = b->data;
    b->data = temp;
    swap_count++;
}

void bubble_sort() {
    int swapped;
    struct node* ptr1;
    struct node* lptr = NULL;

    if (head == NULL) {
        return;
    }
    
    do {
        swapped = 0;
        ptr1 = head;

        while (ptr1->n != lptr) {
            if ((is_ascending && ptr1->data > ptr1->n->data) || (!is_ascending && ptr1->data < ptr1->n->data)) {
                swap(ptr1, ptr1->n);
                swapped = 1;
            }
            ptr1 = ptr1->n;
        }
        lptr = ptr1;
    } while (swapped);
}

void selection_sort() {
    struct node *ptr1, *ptr2, *min;

    if (head == NULL) {
        return;
    }

    for (ptr1 = head; ptr1 != NULL && ptr1->n != NULL; ptr1 = ptr1->n) {
        min = ptr1;
        for (ptr2 = ptr1->n; ptr2 != NULL; ptr2 = ptr2->n) {
            if ((is_ascending && ptr2->data < min->data) || (!is_ascending && ptr2->data > min->data)) {
                min = ptr2;
            }
        }
        if (min != ptr1) {
            swap(min, ptr1);
        }
    }
}

void insertion_sort() {
    if (head == NULL || head->n == NULL) {
        return;
    }
    struct node *sorted = NULL;
    struct node *current = head;

    while (current != NULL) {
        struct node *n = current->n;

        if (sorted == NULL || (is_ascending && sorted->data >= current->data) || (!is_ascending && sorted->data <= current->data)) {
            current->n = sorted;
            sorted = current;
        } else {
            struct node *temp = sorted;
            while (temp->n != NULL && ((is_ascending && temp->n->data < current->data) || (!is_ascending && temp->n->data > current->data))) {
                temp = temp->n;
            }
            current->n = temp->n;
            temp->n = current;
        }
        swap_count++;
        current = n;
    }

    head = sorted;
}

void view_data() {
    temp = head;

    printf("| Data : ");
    while (temp != NULL) {
        printf(" %2d ", temp->data);
        temp = temp->n;
    }
    printf("\n");
}

void print_sorted_list() {
    printf("/=============================================-----------\n");
    view_data();
    printf("| Jumlah swap: %d\n", swap_count);
    printf("\\==================================--------------\n\n");
}

void sorted_list_menu() {
    int choice;
    do {
        printf("/=====================================\\ \n");
        printf("| 1. Kembali Ke Menu Sorting          |\n");
        printf("| 2. Exit                             |\n");
        printf("\\=====================================/\n");
        do {
            printf("\tInput >>  ");
            scanf("%d", &choice);
        } while (choice > 2 || choice < 1);
        
        if (choice == 2) {
            exit(0);
        }
        
    } while (choice != 1);

    struct node* temp_head = NULL;
    copy_list(original_head, &temp_head);
    head = temp_head;
}

void display() {
    struct node *ptr = head;
    if (ptr == NULL) {
        printf("/=====================================\\ \n");
        printf("|                Empty                |\n");
        printf("\\=====================================/\n");
    } else {
        printf("/=====================================\\ \n");
        printf("|                Display              |\n");
        printf("=============================================-----------\n");
        printf("| isi list: ");
        while (ptr != NULL) {
            printf("%d  ", ptr->data);
            ptr = ptr->n;
        }
        printf("\n\\==================================--------------\n");
    }
}

void insert_data() {
    int num_data, value;
    printf("/=====================================\\ \n");
    printf("|             Input Data              |\n");
    printf("\\=====================================/\n");
    printf("\tMasukkan Jumlah Data >> ");
    scanf("%d", &num_data);

    for (int i = 0; i < num_data; i++) {
        printf("\tMasukkan Angka >> ");
        scanf("%d", &value);
        create_node(value);
        if (head != NULL) {
            new_node->n = head;
            head = new_node;
        } else {
            head = new_node;
        }
    }

    if (original_head != NULL) {
        while (original_head != NULL) {
            struct node* temp = original_head;
            original_head = original_head->n;
            free(temp);
        }
    }

    copy_list(head, &original_head);
}

void delete_all_nodes() {
    struct node* current = head;
    struct node* next_node = NULL;

    while (current != NULL) {
        next_node = current->n;
        free(current);
        current = next_node;
    }
    
    head = NULL;
    original_head = NULL;
}

void sorting_menu() {
    printf("/====================================\\ \n");
    printf("|            Pilih Sorting           |\n");
    printf("======================================\n");
    printf("| 1. Bubble Sort                     |\n");
    printf("| 2. Selection Sort                  |\n");
    printf("| 3. Insertion Sort                  |\n");
    printf("| 4. All Sort                        |\n");
    printf("| 5. Kembali Ke Menu Utama           |\n");
    printf("\\====================================/\n");
}

void order_menu() {
    printf("/====================================\\ \n");
    printf("|             Pilih Urutan           |\n");
    printf("======================================\n");
    printf("| 1. Ascending                       |\n");
    printf("| 2. Descending                      |\n");
    printf("\\====================================/\n");
}

void menu() {
    printf("/======================================\\ \n");
    printf("|   _____        _____            _    |\n");
    printf("|  / ____|      / ____|          | |   |\n");
    printf("| | (___  _   _| (___   ___  _ __| |_  |\n");
    printf("|  \\___ \\| | | |\\___ \\ / _ \\| '__| __| |\n");
    printf("|  ____) | |_| |____) | (_) | |  | |_  |\n");
    printf("| |_____/ \\__, |_____/ \\___/|_|   \\__| |\n");
    printf("|          __/ |                       |\n");
    printf("|         |___/                        |\n");
    printf("========================================\n");
    printf("| 1. Masukan Data                      |\n");
    printf("| 2. Tambahkan Data                    |\n");
    printf("| 3. Pilihan Sorting                   |\n");
    printf("| 4. Display Data                      |\n");
    printf("| 5. Delete Semua Data                 |\n");
    printf("| 6. Exit                              |\n");
    printf("\\=====================================/\n");
}

void cls() {
    system("cls");
}

int main() {
    int c, sort_choice = 0, order_choice = 0, m;
    do {
        cls();
        menu();
        do {
            printf("\tInput >>  ");
            scanf("%d", &c);
        } while (c > 6 || c < 1);

        switch (c) {
            case 1:
                cls();
                delete_all_nodes();
                insert_data();
                break;
            
            case 2:
                cls();
                insert_data();
                break;
            
            case 3:
                cls();
                
                do {
                    sorting_menu();
                    do {
                        printf("\tInput >>  ");
                        scanf("%d", &sort_choice);
                    } while (sort_choice > 5 || sort_choice < 1);
                    
                    if (sort_choice != 5) {
                        cls();
                        
                        order_menu();
                        do {
                            printf("\tInput >> ");
                            scanf("%d", &order_choice);
                        } while (order_choice > 2 || order_choice < 1);
                            
                        if (order_choice == 1) {
                            is_ascending = 1;
                        } else {
                            is_ascending = 0;
                        }
                        cls();
                        
                        switch (sort_choice) {
                            case 1:
                                swap_count = 0;
                                printf("/=====================================\\ \n");
                                printf("|             Bubble Sort             |\n");
                                bubble_sort();
                                print_sorted_list();
                                sorted_list_menu();
                                cls();
                                break;
                            
                            case 2:
                                swap_count = 0;
                                printf("/=====================================\\ \n");
                                printf("|            Selection Sort           |\n");
                                selection_sort();
                                print_sorted_list();
                                sorted_list_menu();
                                cls();
                                break;
                            
                            case 3:
                                swap_count = 0;
                                printf("/=====================================\\ \n");
                                printf("|            Insertion Sort           |\n");
                                insertion_sort();
                                print_sorted_list();
                                sorted_list_menu();
                                cls();
                                break;
                            
                            case 4:
                                swap_count = 0;
                                printf("/=====================================\\ \n");
                                printf("|             Bubble Sort             |\n");
                                bubble_sort();
                                print_sorted_list();
                                
                                swap_count = 0; head = NULL; copy_list(original_head, &head);
                                printf("/=====================================\\ \n");
                                printf("|            Selection Sort           |\n");
                                selection_sort();
                                print_sorted_list();
                                
                                swap_count = 0; head = NULL; copy_list(original_head, &head);
                                printf("/=====================================\\ \n");
                                printf("|            Insertion Sort           |\n");
                                insertion_sort();
                                print_sorted_list();
                                sorted_list_menu();
                                cls();
                                break;
                        }
                    }
                } while (sort_choice != 5);
                break;
            
            case 4:
                cls();
                display();
                printf("\tInput Any Number To Proceed >> ");
                scanf("%d", &m);
                break;
            
            case 5:
                delete_all_nodes();
                printf("/=====================================\\ \n");
                printf("|    All nodes have been deleted.      |\n");
                printf("\\=====================================/\n");
                printf("\tInput Any Number To Proceed >> ");
                scanf("%d", &m);
                break;
        }
    } while (c != 6);
    cls();
    
    printf("  _______ _                 _     __     __          \n");
    printf(" |__   __| |               | |    \\ \\   / /          \n");
    printf("    | |  | |__   __ _ _ __ | | __  \\ \\_/ /__  _   _  \n");
    printf("    | |  | '_ \\ / _` | '_ \\| |/ /   \\   / _ \\| | | | \n");
    printf("    | |  | | | | (_| | | | |   <     | | (_) | |_| | \n");
    printf("    |_|  |_| |_|\\__,_|_| |_|_|\\_\\    |_|\\___/ \\__,_| \n");
                                                    
                                                
    return 0;
}
