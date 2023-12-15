# Notepad C - Simple Console Notepad Application

Notepad C is a simple console-based notepad application written in C. It provides basic note creation, viewing, and editing functionalities. The program utilizes the Windows API for console color handling and uses a modular structure with separate files for user-related functions, document handling, and GUI elements.

## Features

- **Create a Note:** Easily create a new note with a title, contents (all notes generate a created_at and *updated_at timestamp).  -> *updated_at not yet implemented
- **View a Note:** View and select from existing notes, displaying their titles and contents.
- **Edit a Note:** Future feature to be added.
- **User Authentication:** Users can create an account with a username, and their notes are associated with their account.

## Getting Started
**The program includes a build folder with the executable inside**

1. **Build the Program:**
   **!! PROGRAM USES CMAKE !!**
   - Navigate to the project directory and create a `build` folder.
   - Inside the `build` folder, run `cmake ..` and then `cmake --build .` to compile the executable.

2. **Run the Program:**
   - Execute the generated executable in the `build` folder.

3. **Usage:**
   - Follow the on-screen menu to create, view, and manage your notes.

## To-Do List

0. **Edit Notes:** Implement editing feature where users can edit previously created notes.
1. **Timestamp Update:** Stamp the updated date into the file when editing a note.
2. **Console Color Handling:** Implement console color handling through the Windows API.
3. **Code Refactoring:** Refactor the code for improved readability and maintainability.

## Dependencies

- Windows API: Used for console color handling.

## Notes

- The program assumes the user has unzipped the application for proper functionality.

## Version Information

- Version: v0.0.1-alpha

## Contributors

- Arya Sharifai

Feel free to contribute to the project by addressing the to-do list items or suggesting improvements. Happy note-taking with Notepad C!
