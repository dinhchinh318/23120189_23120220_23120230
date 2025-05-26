#ifndef _APP_SCREEN_H_
#define _APP_SCREEN_H_

// AppScreen.h
// This file defines the different screens in the application.
enum class AppScreen 
{
    INIT_SCREEN,        // Initial screen with welcome message
    ADD_PHONE,          // Screen for adding a new phone
    DISPLAY_LIST,       // Screen for displaying the list of phones
    SEARCH_PHONE,       // Screen for searching a phone
    FIND_LIST,          // Screen for finding a phone in the list by search
    DELETE_PHONE,       // Screen for deleting a phone
    EDIT_PHONE,         // Screen for find phone for editing
    EDIT_LIST,          // Screen for editing a list of phones
    EDIT                // Screen for editing a phone
};

#endif