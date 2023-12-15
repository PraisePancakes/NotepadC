#ifndef USER_H
#define USER_H

typedef struct User
{
    char *username;
    char **note_titles;
    int note_length;

} User;

User *get_user();
void save_user(const char *filepath, User *user);
User *load_user(const char *filepath);
void free_user(User *user);

#endif