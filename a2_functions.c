/********* definitions.c ********
    Student Name 	= Mahdi Bouakline
    Student Number	= 101257788 
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "a2_nodes.h"
#include "a2_functions.h"

// Your solution goes here

/*
   Function that creates a new user and adds it to a sorted (ascending order) linked list at
   the proper sorted location. Return the head of the list.
*/
user_t *add_user(user_t *users, const char *username, const char *password)
{
    user_t *primary_user = malloc(sizeof(user_t));
    user_t *current = users;    
    
    assert(primary_user != NULL);
    
    strcpy(primary_user->username, username);
    strcpy(primary_user->password, password);
    
    primary_user->friends = NULL;
    primary_user->posts = NULL;

    if (users == NULL )
    {
        primary_user->next = users;
        return primary_user;
    }
    
    if(strcmp(primary_user->username, users->username) < 0)
    {
        primary_user->next = users;
        return primary_user;        
    }
    
    while (current->next != NULL && strcmp(primary_user->username, current->next->username) > 0)
    {
        current = current->next;
    }
    
    primary_user->next = current->next;
    current->next = primary_user;
    
    return users;
}
/*
   Function that searches if the user is available in the database
   Return a pointer to the user if found and NULL if not found.
*/
user_t *find_user(user_t *users, const char *username)
{

    user_t *current = users;
    while (current != NULL) {
        if (strcmp(current->username, username) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

/*
   Function that creates a new friend's node.
   Return the newly created node.
*/
friend_t *create_friend(const char *username)
{
    friend_t *new_friend = (friend_t *)malloc(sizeof(friend_t));
    if (new_friend == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    strcpy(new_friend->username, username);
    new_friend->next = NULL;

    return new_friend;
}

/*
   Function that links a friend to a user. The friend's name should be added into
   a sorted (ascending order) linked list.
*/
void add_friend(user_t *user, const char *friend)
{
    if (user == NULL) {
        return;
    }

    friend_t *new_friend = create_friend(friend);
    if (new_friend == NULL) {
        return;
    }

    if (user->friends == NULL || strcmp(user->friends->username, friend) > 0) {
        new_friend->next = user->friends;
        user->friends = new_friend;
        return;
    }

    friend_t *current = user->friends;
    while (current->next != NULL && strcmp(current->next->username, friend) < 0) {
        current = current->next;
    }

    new_friend->next = current->next;
    current->next = new_friend;
}

/*
   Function that removes a friend from a user's friend list.
   Return true of the friend was deleted and false otherwise.
*/
_Bool delete_friend(user_t *user, char *friend_name)
{
    if (user == NULL || user->friends == NULL) {
        return false;
    }

    friend_t *current = user->friends, *prev = NULL;
    while (current != NULL) {
        if (strcmp(current->username, friend_name) == 0) {
            if (prev == NULL) { // First node
                user->friends = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            return true;
      }
      prev = current;
      current = current->next;
   }
   return false;
}

/*
   Function that creates a new user's post.
   Return the newly created post.
*/
post_t *create_post(const char *text)
{
    post_t *post = malloc(sizeof(post_t));
    assert(post != NULL);

    strcpy(post->content, text);
    post->next = NULL;
    return post;
}

/*
   Function that adds a post to a user's timeline. New posts should be added following
   the stack convention (LIFO) (i.e., to the beginning of the Posts linked list).
*/
void add_post(user_t *user, const char *text)
{
    post_t *new_post = create_post(text);
    new_post->next = user->posts;
    user->posts = new_post;
}

/*
   Function that removes a post from a user's list of posts.
   Return true if the post was deleted and false otherwise.
*/
_Bool delete_post(user_t *user, int number)
{
    if (user == NULL || user->posts == NULL || number < 1) {
        return false;
    }

    post_t *current = user->posts, *prev = NULL;
    int count = 1;
    while (current != NULL && count < number) {
        prev = current;
        current = current->next;
        count++;
    }

    if (current != NULL && count == number) {
        if (prev == NULL) { // First node
            user->posts = current->next;
        } else {
            prev->next = current->next;
        }
        free(current);
        return true;
   }
   return false;
}

/*
   Function that  displays a specific user's posts
*/
void display_user_posts(user_t *user)
{
    int counter = 1;
    post_t *post = user->posts;
    if (post == NULL)
    {
        printf("No posts available for %s.\n\n", user->username);
    }
    while (post != NULL)
    {
        printf("%d- %s: %s\n\n", counter, user->username, post->content);
        post = post->next;
        counter++;
    }
}

/*
   Function that displays a specific user's friends
*/
void display_user_friends(user_t *user)
{
    printf("\nList of %s's friends:\n", user->username);
    int counter = 1;
    friend_t *friend = user->friends;
    if (friend == NULL)
    {
        printf("No friends available for %s.\n\n", user->username);
    }
    while (friend != NULL)
    {
        printf("%d- %s\n", counter, friend->username);
        friend = friend->next;
        counter++;
    }
}
/*
   Function that displays all the posts of 2 users at a time from the database.
   After displaying 2 users' posts, it prompts if you want to display
   posts of the next 2 users.
   If there are no more post or the user types “n” or “N”, the function returns.
*/
void display_all_posts(user_t *users)
{
    if (users == NULL) {
      printf("No users in the database.\n");
      return;
    }

    user_t *current = users;
    char choice;
    int count = 0;

    while (current != NULL) {
        display_user_posts(current);
        current = current->next;
        count++;

        if (count % 2 == 0 && current != NULL) {
            printf("Do you want to continue to the next users? (Y/N): ");
            scanf(" %c", &choice);
            if (choice == 'n' || choice == 'N') {
                break;
        }
      }
   }
}

/*
   Fucntion that free all users from the database before quitting the application.
*/
void teardown(user_t *users)
{
    user_t *current = users;
    while (current != NULL) {
        user_t *temp = current;
        current = current->next;

        // Free friend list
        friend_t *friend = temp->friends;
        while (friend != NULL) {
            friend_t *friend_temp = friend;
            friend = friend->next;
            free(friend_temp);
        }

        // Free post list
        post_t *post = temp->posts;
        while (post != NULL) {
            post_t *post_temp = post;
            post = post->next;
            free(post_temp);
        }

        free(temp); // Free the user
   }
}

/*
   Function that prints the main menu with a list of options for the user to choose from
*/
void print_menu()
{
    printf("***********************************************\n");
    printf("MAIN MENU\n");
    printf("***********************************************\n");
    printf("1. Register a new user\n");
    printf("2. Manage a user's profile\n");
    printf("3. Manage a user's posts\n");
    printf("4. Manage a user's friends\n");
    printf("5. Display all posts\n");
    printf("6. Exit the application\n");
    printf("Enter Choice: \n");
}

// Function definition for print_submenu
void print_submenu(const char *username)
{
    printf("\n-----------------------------------------------\n");
    printf("%s's posts\n", username);
    printf("-----------------------------------------------\n");
    printf("1. Add a new user post\n");
    printf("2. Remove a user's post\n");
    printf("3. Return to main menu\n");
    printf("Your choice: ");
}

void print_friend_menu() {
    printf("\n-----------------------------------------------\n");
    printf("Friend Management Menu\n");
    printf("-----------------------------------------------\n");
    printf("1. Display all user's friends\n");
    printf("2. Add a new friend\n");
    printf("3. Delete a friend\n");
    printf("4. Return to main menu\n");
    printf("Your choice: ");
}

/*
   ******** DONT MODIFY THIS FUNCTION ********
   Function that reads users from the text file.
   IMPORTANT: This function shouldn't be modified and used as is
   ******** DONT MODIFY THIS FUNCTION ********   
*/
user_t *read_CSV_and_create_users(FILE *file, int num_users)
{
    user_t *users = NULL;
    char buffer[500];
    fgets(buffer, sizeof(buffer), file); // Read and discard the header line
    int count = 0;
    for (int i = 0; i < num_users; i++)
    {
        fgets(buffer, sizeof(buffer), file);
        buffer[strcspn(buffer, "\r\n")] = 0; // Remove newline characters

        char *token = strtok(buffer, ",");
        char *token2 = strtok(NULL, ",");
        users = add_user(users, token, token2);
        char *username = token;

        token = strtok(NULL, ",");

        user_t *current_user = users;
        for (; current_user != NULL && strcmp(current_user->username, username) != 0; current_user = current_user->next)
            ;

        while (token != NULL && strcmp(token, ",") != 0 && count < 3)
        {
            if (strcmp(token, " ") != 0)
            {
                add_friend(current_user, token);
            }
            token = strtok(NULL, ",");
            count++;
        }
        count = 0;

        // token = strtok(NULL, ",");
        while (token != NULL && strcmp(token, ",") != 0)
        {
            add_post(current_user, token);
            token = strtok(NULL, ",");
        }
    }
    return users;
}
