#include "list.h"
void options();
void edittask();
void mark_as_done();
nodeptr list = NULL;
int length = 0;

int main(int argc, char const *argv[])
{

    options();
    return 0;
}

void options()
{
    int option;
    while (1)
    {
        system("clear");
        printf("Choose Option\n");
        printf("1|-Show Tasks\n2|-Create a new task\n3|-Edit Task\n4|-Delete Task\n5|-Mark AS Done\n");
        scanf(" %d", &option);
        switch (option)
        {
        case 1:
            showtaks();
            break;
        case 2:
            createtask();
            break;
        case 3:
            edittask();
            break;
        case 4:
            deletetask();
            break;
        case 5:
            mark_as_done();
            break;

        default:
            break;
        }
        getchar();
    }
}
void createtask()
{
    int i = 0;
    system("clear");
    printf("\n-------------------------Create Task-------------------------\n");
    printf("enter new task (type exit to leave)\n");
    char new_task[100];
    scanf(" %99[a-zA-Z0-9 ]", new_task);

    if (strncmp(new_task, "exit", 5) == 0)
    {
        printf("leaving program\n");
    }
    else
    {

        nodeptr new_node = (nodeptr)malloc(sizeof(node));
        if (new_node == NULL)
        {
            printf("Memory allocation failure\n");
            exit(1);
        }
        new_node->next = NULL;
        strncpy(new_node->data.buffer, new_task, sizeof(new_task));
        new_node->data.state = 0;
        time_t rawtime;
        struct tm *timeinfo;
        time(&rawtime);
        timeinfo = localtime(&rawtime);
        strncpy(new_node->data.time, asctime(timeinfo), 50);
        if (list == NULL)
        {
            new_node->data.position = i;
            list = (nodeptr)malloc(sizeof(node));
            if (list == NULL)
            {
                printf("Memory allocation failure\n");
                exit(1);
            }
            *list = *new_node;
        }
        else
        {
            nodeptr pos = list;
            while (pos->next != NULL)
            {
                pos->data.position = i++;
                pos = pos->next;
            }
            pos->next = malloc(sizeof(node));
            if (pos->next == NULL)
            {
                printf("Memory allocation failure\n");
                exit(1);
            }
            new_node->data.position = i;
            *pos->next = *new_node;
        }

        free(new_node);
        length++;
    }
    sleep(2);
}
// edit task and time
void edittask()
{
    int task;
    char new_task[100];

    system("clear");
    printf("\n-------------------------Edit Tasks-------------------------\n");

    if (list == NULL)
    {
        printf("no tasks available\n");
        sleep(3);
    }
    else
    {
        nodeptr pos = list;
        int i = 0;

        while (pos)
        {
            pos->data.position = i++;
            printf("\n Task %d Time|- %s\t", pos->data.position + 1, pos->data.time);
            printf("|- %s\t", pos->data.buffer);
            switch (pos->data.state)
            {
            case 0:
                printf("\t not done\n");
                break;
            case 1:
                printf("\t done\n");
                break;
            default:
                break;
            }
            pos = pos->next;
        }
        printf("\n Enter task to change (press 0 to leave)\n");
        scanf("%d", &task);
        if (task == 0)
        {
            printf("leaving program\n");
        }
        else
        {
            if (task <= length)
            {
                printf("\n Enter new task \n");
                scanf(" %99[a-zA-Z0-9 ]", new_task);

                pos = list;
                i = 0;
                while (pos && i < task - 1)
                {
                    pos = pos->next;
                    i++;
                }
                strncpy(pos->data.buffer, new_task, 100);
                pos->data.state = 0;
                time_t rawtime;
                struct tm *timeinfo;
                time(&rawtime);
                timeinfo = localtime(&rawtime);
                strncpy(pos->data.time, asctime(timeinfo), 50);
                sleep(2);
            }
        }
    }
}
// delete task list
void deletetask()
{
    int i;

    int task;
    system("clear");
    printf("\n-------------------------Delete Tasks-------------------------\n");
    if (list == NULL)
    {
        printf("no tasks available\n");
        sleep(3);
    }
    else
    {
        nodeptr pos = list;
        i = 0;

        while (pos)
        {
            pos->data.position = i++;
            printf("\n Task %d Time|- %s\t", pos->data.position + 1, pos->data.time);
            printf("|- %s\t", pos->data.buffer);
            switch (pos->data.state)
            {
            case 0:
                printf("\t not done\n");
                break;
            case 1:
                printf("\t done\n");
                break;
            default:
                break;
            }
            pos = pos->next;
        }
        pos = list;
        i = 0;
        printf("\n Enter task to delete (press 0 to leave)\n");
        scanf("%d", &task);
        if (task == 0)
        {
            printf("leaving program\n");
        }
        else
        {
            if (task <= length)
            {
                nodeptr temp = list;
                if (task - 1 == 0)
                {

                    list = list->next;
                    temp->next = NULL;
                    free(temp);
                }
                else
                {
                    for (i = 0; i < task - 2; i++)
                    {
                        temp = temp->next;
                    }
                    nodeptr del = temp->next;
                    temp->next = temp->next->next;
                    del->next = NULL;
                    free(del);
                }
                length--;
                sleep(2);
            }
        }
    }
}
// show all tasks
void showtaks()
{
    system("clear");
    printf("\n-------------------------Show Tasks-------------------------\n");
    if (list == NULL)
    {
        printf("no tasks available\n");
        sleep(3);
    }
    else
    {
        nodeptr pos = list;
        int i = 0;

        while (pos)
        {
            pos->data.position = i++;
            printf("\n Task %d Time|- %s\t", pos->data.position + 1, pos->data.time);
            printf("|- %s\t", pos->data.buffer);
            switch (pos->data.state)
            {
            case 0:
                printf("\t not done\n");
                break;
            case 1:
                printf("\t done\n");
                break;
            default:
                break;
            }
            pos = pos->next;
        }

        printf("\n press enter to key continue...\n");
        getchar();
    }
}

// mark task as done
void mark_as_done()
{
    int task;
    system("clear");
    printf("\n-------------------------Mark AS DONE-------------------------\n");
    if (list == NULL)
    {
        printf("no tasks available\n");
        sleep(3);
    }
    else
    {
        nodeptr pos = list;
        int i = 0;

        while (pos)
        {
            pos->data.position = i++;
            printf("\n Task %d Time|- %s\t", pos->data.position + 1, pos->data.time);
            printf("|- %s\t", pos->data.buffer);
            switch (pos->data.state)
            {
            case 0:
                printf("\t not done\n");
                break;
            case 1:
                printf("\t done\n");
                break;
            default:
                break;
            }
            pos = pos->next;
        }
        printf("\n Enter task to mark (press 0 to leave)\n");
        scanf("%d", &task);
        if (task == 0)
        {
            printf("leaving program\n");
        }
        else
        {
            pos = list;
            i = 0;
            while (i < task - 1)
            {
                pos = pos->next;
                i++;
            }
            if (pos->data.state == 0)
                pos->data.state = 1;
            sleep(2);
        }
    }
}