/********* main.c ********
    Student Name 	= Mahdi Bouakline
    Student Number	= 101257788
*/

// Includes go here
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "a2_nodes.h"
#include "a2_functions.h"

int main()
{
    /******** DONT MODIFY THIS PART OF THE CODE ********/
    /* THIS CODE WILL LOAD THE DATABASE OF USERS FROM THE FILE 
       AND GENERATE THE STARTING LINKED LIST.
    */
    FILE *csv_file = fopen("user_details.csv", "r");
    if (csv_file == NULL)
    {
        perror("Error opening the CSV file");
        return 1;
    }
    // Parse CSV data and create users
    user_t *users = read_CSV_and_create_users(csv_file, 50);

    fclose(csv_file);
    /******** DONT MODIFY THIS PART OF THE CODE ********/
    
    /* IMPORTANT: You must use the users linked list created in the code above. 
        Any new users should be added to that linked list.
    */

    // Your solution goes here
    char username[30], password[15], friendName[30];
    int choice;
    bool running = true;

    while (running) {
        print_menu();
        if (scanf("%d", &choice) != 1) {
            // Invalid input, clear input buffer
            while (getchar() != '\n');
            printf("Invalid input. Please enter a number.\n");
            continue; // Restart the loop
        }

        switch (choice) {
            case 1: // Register a new user
                printf("Enter username: ");
                scanf("%s", username);
                printf("Enter an up to 15 characters password: ");
                scanf("%s", password);
                users = add_user(users, username, password);
                break;

            case 2: // Manage a user's profile
                printf("Enter username to change password: ");
                scanf("%s", username);
                user_t *user = find_user(users, username);
                if (user) {
                    printf("Enter new password: ");
                    scanf("%s", password);
                    strcpy(user->password, password);
                    printf("**** Password changed! ****\n");
                } else {
                    printf("-----------------------------------------------\n");
                    printf("User not found.\n");
                    printf("-----------------------------------------------\n");
                }
                break;

            case 3: // Manage a user's posts
                char postUsername[30];
                printf("Enter username to manage their posts: ");
                scanf("%s", postUsername);
                user_t *postUser = find_user(users, postUsername);

                if (postUser) {
                    while (1) {
                        // Print submenu options
                        printf("-----------------------------------------------\n");
                        printf("%s's posts\n", postUser->username);
                        printf("-----------------------------------------------\n");
                        printf("1. Add a new user post\n");
                        printf("2. Remove a user's post\n");
                        printf("3. Return to main menu\n");
                        printf("Your choice: ");

                        int postChoice;
                        scanf("%d", &postChoice);

                        switch (postChoice) {
                            case 1: // Add a new user post
                                // Implement logic to add a post
                                char newPostContent[250];
                                printf("Enter your post content: ");
                                scanf(" %s", newPostContent); // Read the post content with spaces
                                add_post(postUser, newPostContent);
                                printf("Post added to your profile.\n");
                                display_user_posts(postUser); // Display updated posts
                                break;

                            case 2: // Remove a user's post
                                // Implement logic to remove a post
                                int postNumber;
                                printf("Which post do you want to delete? ");
                                scanf("%d", &postNumber);

                                if (delete_post(postUser, postNumber)) {
                                    printf("Post %d was deleted successfully!\n", postNumber);
                                } else {
                                    printf("Invalid post number.\n");
                                }
                                display_user_posts(postUser); // Display updated posts
                                break;

                            case 3: // Return to main menu
                                break; // Exit the submenu loop

                            default:
                                printf("Invalid choice. Please try again.\n");
                        }

                        if (postChoice == 3) {
                            break; // Exit the submenu loop and return to the main menu
                        }
                    }
    } else {
        printf("User not found.\n");
    }
                break;

            case 4: // Manage a user's friends
                printf("Enter username to manage their friends: ");
                scanf("%s", username);
                user = find_user(users, username);
                if (user) {
                    while (1) {
                        print_friend_menu(); // Print the friend management menu
                        int friendChoice;
                        scanf("%d", &friendChoice);

                        switch (friendChoice) {
                            case 1: // Display all user's friends
                                display_user_friends(user);
                                break;

                            case 2: // Add a new friend
                                printf("Enter friend's username: ");
                                scanf("%s", friendName);
                                add_friend(user, friendName);
                                printf("%s added as a friend.\n", friendName);
                                break;

                            case 3: // Delete a friend
                                printf("Enter friend's username to delete: ");
                                scanf("%s", friendName);
                                if (delete_friend(user, friendName)) {
                                    printf("%s removed from friends.\n", friendName);
                                } else {
                                    printf("Invalid friend's username.\n");
                                }
                                break;

                            case 4: // Return to main menu
                                break; // Exit the friend management loop

                            default:
                                printf("Invalid choice. Please try again.\n");
                        }

                        if (friendChoice == 4) {
                            break; // Exit the friend management loop and return to the main menu
                        }
                    }
    } else {
        printf("User not found.\n");
    }
                break;

            case 5: // Display all posts
                display_all_posts(users);
                break;

            case 6: // Exit the application
                printf("*********************************************** \n");
                printf("Thank you for using Text-Based Facebook \n");
                printf("GoodBye! \n");
                printf("*********************************************** \n");
                running = false;
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    teardown(users); // Free all allocated memory
    return 0;


}
