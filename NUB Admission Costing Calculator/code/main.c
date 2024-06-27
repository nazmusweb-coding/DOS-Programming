#include "test.h"

// Function declarations for callbacks
void on_submit_button_clicked(GtkWidget *widget, gpointer data);
void D_on_submit_button_clicked(GtkWidget *widget, gpointer data);



// Function pointer type fillers
void display_result(const char *message);
int get_credit(sqlite3_stmt *stmt);
int D_get_credit(sqlite3_stmt *stmt, double DiplomaResult);



// Togglebutton functions for callbacks
void on_credit_transfer_no_toggled(GtkToggleButton *togglebutton, gpointer data);
void on_credit_transfer_yes_toggled(GtkToggleButton *togglebutton, gpointer data);


// Function declarations for callbacks
void show_undergraduate(GtkWidget *widget, gpointer data);
void show_diploma(GtkWidget *widget, gpointer data);



// Function to create and show undergraduate and diploma interface
void create_undergraduate_interface(GtkWidget *container);
void create_diploma_interface(GtkWidget *container);



// Function declaration for callbacks for About option
void on_about_activate(GtkWidget *widget);
void on_give_star_clicked();



// Global variables
GtkWidget *content_area;
GtkWidget *ssc_entry, *hsc_entry, *department_combo, *result_view;
GtkTextBuffer *result_buffer;
GtkWidget *diploma_entry;
GtkWidget *credit_transfer_check_no, *credit_transfer_check_yes, *credit_entry;





int main(int argc, char **argv) 
{
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *menu_bar, *menu, *menu_item, *about_item;;

    gtk_init(&argc, &argv);

    // Create the main window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "NUB Admission Costing Calculator");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 680); // 400, 300 (w, h) default

    // sets the window position when starting, NONE,CENTER,MOUSE,CENTER_ALWAYS,CENTER_ON_PARENT	
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

	// sets if the user can resize the window or not, TRUE means yes, FALSE means no
	gtk_window_set_resizable(GTK_WINDOW(window), FALSE); // True Default

    // Create a grid and attach it to the window
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Create the menu bar
    menu_bar = gtk_menu_bar_new();

    // Create the main "Menu" item
    menu = gtk_menu_new();
    menu_item = gtk_menu_item_new_with_label("Menu");
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_item), menu);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), menu_item);

    // Create the "Undergraduate" menu item
    menu_item = gtk_menu_item_new_with_label("Undergraduate");
    g_signal_connect(menu_item, "activate", G_CALLBACK(show_undergraduate), NULL);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), menu_item);

    // Create the "Undergraduate (for Diploma Holders)" menu item
    menu_item = gtk_menu_item_new_with_label("Undergraduate (for Diploma Holders)");
    g_signal_connect(menu_item, "activate", G_CALLBACK(show_diploma), NULL);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), menu_item);

    // Create the "About" menu item
    about_item = gtk_menu_item_new_with_label("About");
    g_signal_connect(about_item, "activate", G_CALLBACK(on_about_activate), NULL);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), about_item);

    // Attach the menu bar to the grid
    gtk_grid_attach(GTK_GRID(grid), menu_bar, 0, 0, 1, 1);

    // Create the content area
    content_area = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_grid_attach(GTK_GRID(grid), content_area, 0, 1, 10, 10);

    // Show the undergraduate interface by default
    create_undergraduate_interface(content_area);

    // Show all widgets
    gtk_widget_show_all(window);
    gtk_widget_hide(credit_entry); // Since its default, so we have to handle default things from here

    // Connect the main window's delete event to GTK main loop
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_main();

    return 0;
}





// Callback to show the undergraduate interface based on selection
void show_undergraduate(GtkWidget *widget, gpointer data) 
{
    gtk_container_foreach(GTK_CONTAINER(content_area), (GtkCallback)gtk_widget_destroy, NULL); // Clear previous content
    create_undergraduate_interface(content_area);
    gtk_widget_show_all(content_area); // Refresh the container
    gtk_widget_set_visible(credit_entry, FALSE); // Hiding because no is toggled by default
}





// Callback to show the diploma interface based on selection
void show_diploma(GtkWidget *widget, gpointer data) 
{
    gtk_container_foreach(GTK_CONTAINER(content_area), (GtkCallback)gtk_widget_destroy, NULL); // Clear previous content
    create_diploma_interface(content_area);
    gtk_widget_show_all(content_area); // Refresh the container
    gtk_widget_set_visible(credit_entry, FALSE); // Hiding because no is toggled by default
}





// Function to create and show undergraduate interface
void create_undergraduate_interface(GtkWidget *container) 
{
    GtkWidget *grid, *ssc_label, *hsc_label, *submit_button, *department_label, *credit_transfer_label, *credit_transfer_box;
    
    grid = gtk_grid_new();
    gtk_box_pack_start(GTK_BOX(container), grid, TRUE, TRUE, 0);

    ssc_label = gtk_label_new("SSC Result:");
    gtk_grid_attach(GTK_GRID(grid), ssc_label, 0, 0, 1, 1);
    ssc_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(ssc_entry), "Enter your SSC result");
    gtk_grid_attach(GTK_GRID(grid), ssc_entry, 1, 0, 1, 1);

    hsc_label = gtk_label_new("HSC Result:");
    gtk_grid_attach(GTK_GRID(grid), hsc_label, 0, 1, 1, 1);
    hsc_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(hsc_entry), "Enter your HSC result");
    gtk_grid_attach(GTK_GRID(grid), hsc_entry, 1, 1, 1, 1);

    department_label = gtk_label_new("Select Department:");
    gtk_grid_attach(GTK_GRID(grid), department_label, 0, 2, 1, 1);
    department_combo = gtk_combo_box_text_new();
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(department_combo), NULL, "BBA");
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(department_combo), NULL, "LLB");
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(department_combo), NULL, "EEE");
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(department_combo), NULL, "Textile");
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(department_combo), NULL, "CSE");
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(department_combo), NULL, "Civil");
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(department_combo), NULL, "ME");
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(department_combo), NULL, "ECE");
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(department_combo), NULL, "B_Pharm");
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(department_combo), NULL, "ELL");
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(department_combo), NULL, "Bangla");
    gtk_grid_attach(GTK_GRID(grid), department_combo, 1, 2, 1, 1);

    // Add Credit Transfer check buttons
    credit_transfer_label = gtk_label_new("Credit transferring here?");
    gtk_grid_attach(GTK_GRID(grid), credit_transfer_label, 0, 3, 1, 1);

    credit_transfer_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_grid_attach(GTK_GRID(grid), credit_transfer_box, 1, 3, 1, 1);

    credit_transfer_check_no = gtk_check_button_new_with_label("No");
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(credit_transfer_check_no), TRUE);
    g_signal_connect(credit_transfer_check_no, "toggled", G_CALLBACK(on_credit_transfer_no_toggled), NULL);
    gtk_box_pack_start(GTK_BOX(credit_transfer_box), credit_transfer_check_no, FALSE, FALSE, 0);

    credit_transfer_check_yes = gtk_check_button_new_with_label("Yes");
    g_signal_connect(credit_transfer_check_yes, "toggled", G_CALLBACK(on_credit_transfer_yes_toggled), NULL);
    gtk_box_pack_start(GTK_BOX(credit_transfer_box), credit_transfer_check_yes, FALSE, FALSE, 0);

    credit_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(credit_entry), "Amount of credit");
    gtk_grid_attach(GTK_GRID(grid), credit_entry, 1, 4, 1, 1);

    submit_button = gtk_button_new_with_label("Submit");
    g_signal_connect(submit_button, "clicked", G_CALLBACK(on_submit_button_clicked), NULL);
    gtk_grid_attach(GTK_GRID(grid), submit_button, 0, 5, 2, 1);

    result_view = gtk_text_view_new();
    result_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(result_view));
    gtk_text_view_set_editable(GTK_TEXT_VIEW(result_view), FALSE);
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(result_view), FALSE);
    gtk_grid_attach(GTK_GRID(grid), result_view, 0, 6, 2, 1);
    
}





// Callback for the submit button
void on_submit_button_clicked(GtkWidget *widget, gpointer data) 
{
    const char *ssc_text = gtk_entry_get_text(GTK_ENTRY(ssc_entry));
    const char *hsc_text = gtk_entry_get_text(GTK_ENTRY(hsc_entry));
    const char *selected_department = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(department_combo));
    const char *credit_text = gtk_entry_get_text(GTK_ENTRY(credit_entry));

    // Check if any of the required fields are empty
    gboolean is_credit_transfer = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(credit_transfer_check_yes));
    if (strlen(ssc_text) == 0 || strlen(hsc_text) == 0 || selected_department == NULL ||
        (is_credit_transfer && strlen(credit_text) == 0)) 
    {
        display_result("Please fill in all fields.\n");
        gtk_text_buffer_set_text(result_buffer, "", -1); // Clear the text view
        if (selected_department != NULL) 
        {
            g_free((gpointer) selected_department); // Free memory allocated by GTK
        }
        return;
    }

    double ssc = atof(ssc_text);
    double hsc = atof(hsc_text);

    // Clear the text view
    gtk_text_buffer_set_text(result_buffer, "", -1);

    if (strcmp(selected_department, "BBA") == 0) 
    {
        getCalculated(selected_department, ssc, hsc, get_credit, display_result);
    } 
    else if (strcmp(selected_department, "LLB") == 0) 
    {
        getCalculated(selected_department, ssc, hsc, get_credit, display_result);
    } 
    else if (strcmp(selected_department, "EEE") == 0) 
    {
        getCalculated(selected_department, ssc, hsc, get_credit, display_result);
    } 
    else if (strcmp(selected_department, "Textile") == 0) 
    {
        getCalculated(selected_department, ssc, hsc, get_credit, display_result);
    } 
    else if (strcmp(selected_department, "CSE") == 0) 
    {
        getCalculated(selected_department, ssc, hsc, get_credit, display_result);
    } 
    else if (strcmp(selected_department, "Civil") == 0) 
    {
        getCalculated(selected_department, ssc, hsc, get_credit, display_result);
    } 
    else if (strcmp(selected_department, "ME") == 0) 
    {
        getCalculated(selected_department, ssc, hsc, get_credit, display_result);
    } 
    else if (strcmp(selected_department, "ECE") == 0) 
    {
        getCalculated(selected_department, ssc, hsc, get_credit, display_result);
    } 
    else if (strcmp(selected_department, "B_Pharm") == 0) 
    {
        getCalculated(selected_department, ssc, hsc, get_credit, display_result);
    } 
    else if (strcmp(selected_department, "ELL") == 0) 
    {
        getCalculated(selected_department, ssc, hsc, get_credit, display_result);
    } 
    else if (strcmp(selected_department, "Bangla") == 0) 
    {
        getCalculated(selected_department, ssc, hsc, get_credit, display_result);
    }

    g_free((gpointer)selected_department);
}





// Function to create and show diploma interface
void create_diploma_interface(GtkWidget *container) 
{
    GtkWidget *grid, *diploma_label, *submit_button, *department_label, *credit_transfer_label, *credit_transfer_box;

    grid = gtk_grid_new();
    gtk_box_pack_start(GTK_BOX(container), grid, TRUE, TRUE, 0);

    diploma_label = gtk_label_new("Diploma Result:");
    gtk_grid_attach(GTK_GRID(grid), diploma_label, 0, 0, 1, 1);
    diploma_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(diploma_entry), "Enter Diploma result");
    gtk_grid_attach(GTK_GRID(grid), diploma_entry, 1, 0, 1, 1);

    department_label = gtk_label_new("Select Department:");
    gtk_grid_attach(GTK_GRID(grid), department_label, 0, 1, 1, 1);
    department_combo = gtk_combo_box_text_new();
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(department_combo), NULL, "EEE");
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(department_combo), NULL, "Textile");
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(department_combo), NULL, "CSE");
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(department_combo), NULL, "ECE");
    gtk_grid_attach(GTK_GRID(grid), department_combo, 1, 1, 1, 1);

    // Add Credit Transfer check buttons
    credit_transfer_label = gtk_label_new("Credit transferring here?");
    gtk_grid_attach(GTK_GRID(grid), credit_transfer_label, 0, 2, 1, 1);

    credit_transfer_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_grid_attach(GTK_GRID(grid), credit_transfer_box, 1, 2, 1, 1);

    credit_transfer_check_no = gtk_check_button_new_with_label("No");
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(credit_transfer_check_no), TRUE);
    g_signal_connect(credit_transfer_check_no, "toggled", G_CALLBACK(on_credit_transfer_no_toggled), NULL);
    gtk_box_pack_start(GTK_BOX(credit_transfer_box), credit_transfer_check_no, FALSE, FALSE, 0);

    credit_transfer_check_yes = gtk_check_button_new_with_label("Yes");
    g_signal_connect(credit_transfer_check_yes, "toggled", G_CALLBACK(on_credit_transfer_yes_toggled), NULL);
    gtk_box_pack_start(GTK_BOX(credit_transfer_box), credit_transfer_check_yes, FALSE, FALSE, 0);

    credit_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(credit_entry), "Amount of credit");
    gtk_grid_attach(GTK_GRID(grid), credit_entry, 1, 3, 1, 1);

    submit_button = gtk_button_new_with_label("Submit");
    g_signal_connect(submit_button, "clicked", G_CALLBACK(D_on_submit_button_clicked), NULL);
    gtk_grid_attach(GTK_GRID(grid), submit_button, 0, 4, 2, 1);

    result_view = gtk_text_view_new();
    result_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(result_view));
    gtk_text_view_set_editable(GTK_TEXT_VIEW(result_view), FALSE);
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(result_view), FALSE);
    gtk_grid_attach(GTK_GRID(grid), result_view, 0, 5, 2, 1);

}





// Callback for the submit button in diploma interface
void D_on_submit_button_clicked(GtkWidget *widget, gpointer data) 
{
    const char *diploma_text = gtk_entry_get_text(GTK_ENTRY(diploma_entry));
    const char *selected_department = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(department_combo));
    const char *credit_text = gtk_entry_get_text(GTK_ENTRY(credit_entry));

    // Check if any of the required fields are empty
    gboolean is_credit_transfer = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(credit_transfer_check_yes));
    if (strlen(diploma_text) == 0 || selected_department == NULL ||
        (is_credit_transfer && strlen(credit_text) == 0)) 
    {
        display_result("Please fill in all fields.\n");
        gtk_text_buffer_set_text(result_buffer, "", -1); // Clear the text view
        if (selected_department != NULL) 
        {
            g_free((gpointer) selected_department); // Free memory allocated by GTK
        }
        return;
    }

    double diploma = atof(diploma_text);

    // Clear the text view
    gtk_text_buffer_set_text(result_buffer, "", -1);

    if (strcmp(selected_department, "EEE") == 0) 
    {
        D_getCalculated(selected_department, diploma, D_get_credit, display_result);
    } 
    else if (strcmp(selected_department, "Textile") == 0) 
    {
        D_getCalculated(selected_department, diploma, D_get_credit, display_result);
    } 
    else if (strcmp(selected_department, "CSE") == 0) 
    {
        D_getCalculated(selected_department, diploma, D_get_credit, display_result);
    } 
    else if (strcmp(selected_department, "ECE") == 0) 
    {
        D_getCalculated(selected_department, diploma, D_get_credit, display_result);
    }

    g_free((gpointer)selected_department);
}





// Function to display results
void display_result(const char *message) 
{
    GtkTextIter end;
    gtk_text_buffer_get_end_iter(result_buffer, &end);
    gtk_text_buffer_insert(result_buffer, &end, message, -1);

    // Debug print
    printf("Displaying result: %s\n", message);
}





// Fucntion to handle all credit affairs for undergraduate
int get_credit(sqlite3_stmt *stmt)
{
    // Fetching original data at first (from database)
    credit = sqlite3_column_int(stmt, 4);
    semester = sqlite3_column_int(stmt, 6);
    year = sqlite3_column_int(stmt, 5);

    gboolean is_credit_transfer = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(credit_transfer_check_yes));

    // Approximate Calculation for credit transefer candidates
    if (is_credit_transfer)
    {
        char err_msg[256];                                              // error message array
        const double min_credit = (double)credit / (double)semester;    // idea of average credit per semester
        const double max_credit = credit;                               // original maximum credit is the limit
        const double semesters_per_year = semester / 4;                 // idea of semesters per year
        credit = atoi(gtk_entry_get_text(GTK_ENTRY(credit_entry)));     // now get the user entered credit reloaded

        // Credit limit handling and approximate calculation
        if (credit < (int)min_credit)
        {
            snprintf(err_msg, sizeof(err_msg), "At least %0.0f credits needed for credit transfer.\n", min_credit);
            display_result(err_msg);
            return -1;
        }
        else if (credit > (int)max_credit)
        {
            snprintf(err_msg, sizeof(err_msg), "At most %0.0f credits allowed for credit transfer.\n", max_credit);
            display_result(err_msg);
            return -1;
        }

        semester = (double)credit / min_credit;
        year = semester / semesters_per_year;
        return 0;
    }
    return 0;
}





// Fucntion to handle all credit affairs for Diploma holders
int D_get_credit(sqlite3_stmt *stmt, double DiplomaResult)
{
    // Fetching original data at first (from database, based on diploma result)
    if (D_getwaiver(DiplomaResult))
    {
        credit = sqlite3_column_int(stmt, 4);
        semester = sqlite3_column_int(stmt, 7);
    }
    else
    {
        credit = sqlite3_column_int(stmt, 5);
        semester = sqlite3_column_int(stmt, 8);
    }

    gboolean is_credit_transfer = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(credit_transfer_check_yes));
    
    // Approximate Calculation for credit transefer candidates
    if (is_credit_transfer)
    {
        char err_msg[256];                                              // error message array
        const double min_credit = (double)credit / (double)semester;    // idea of average credit per semester
        const double max_credit = credit;                               // original maximum credit is the limit
        const double semesters_per_year = semester / 3;                 // idea of semesters per year
        credit = atoi(gtk_entry_get_text(GTK_ENTRY(credit_entry)));     // now get the user entered credit reloaded

        // Credit limit handling and approximate calculation
        if (credit < (int)min_credit)
        {
            snprintf(err_msg, sizeof(err_msg), "At least %0.0f credits needed for credit transfer.\n", min_credit);
            display_result(err_msg);
            return -1;
        }
        else if (credit > (int)max_credit)
        {
            snprintf(err_msg, sizeof(err_msg), "At most %0.0f credits allowed for credit transfer.\n", max_credit);
            display_result(err_msg);
            return -1;
        }

        semester = ceil((double)credit / min_credit);                   // special case to use ceil
        year = ceil((double)semester / semesters_per_year);             // special case to use ceil
        return 0;
    }
    return 0;
}





// Callback for "NO" check button toggled
void on_credit_transfer_no_toggled(GtkToggleButton *togglebutton, gpointer data)
{
    if (gtk_toggle_button_get_active(togglebutton))
    {
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(credit_transfer_check_yes), FALSE);
        gtk_widget_set_visible(credit_entry, FALSE);
    }
}





// Callback for "Yes" check button toggled
void on_credit_transfer_yes_toggled(GtkToggleButton *togglebutton, gpointer data)
{
    if (gtk_toggle_button_get_active(togglebutton))
    {
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(credit_transfer_check_no), FALSE);
        gtk_widget_set_visible(credit_entry, TRUE);
    }
}





// Function to handle "About" dialog activation
void on_about_activate(GtkWidget *widget) 
{
    GtkWidget *dialog, *label, *button;
    read_about_description(); // Read the description from file

dialog = gtk_dialog_new_with_buttons("About", GTK_WINDOW(gtk_widget_get_toplevel(widget)),
                                     GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                     NULL, GTK_RESPONSE_OK,
                                     NULL);

    // Create a vertical box to hold contents
    GtkWidget *content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10); // Vertical box with spacing

    // Create a label widget for the description
    label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(label), "About Us");
    gtk_label_set_text(GTK_LABEL(label), about_description); // Set the text of the label

    // Pack the label into the vertical box
    gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 0);

    // Create a horizontal box to hold the additional text and button
    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10); // Horizontal box with spacing

    // Create a label widget for the additional text
    GtkWidget *additional_label = gtk_label_new("  Help us by giving a star to the GitHub repo");

    // Pack the additional text label into the horizontal box
    gtk_box_pack_start(GTK_BOX(hbox), additional_label, FALSE, FALSE, 0);

    // Create a button widget for giving a star
    button = gtk_button_new_with_label("Give a Star");
    g_signal_connect(button, "clicked", G_CALLBACK(on_give_star_clicked), NULL); // Connect button click signal
    gtk_box_pack_start(GTK_BOX(hbox), button, FALSE, FALSE, 0); // Pack button into the horizontal box

    // Pack the horizontal box into the vertical box
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

    // Pack the vertical box into the content area of the dialog
    gtk_container_add(GTK_CONTAINER(content_area), vbox);

    gtk_widget_show_all(dialog);
    g_signal_connect(dialog, "response", G_CALLBACK(gtk_widget_destroy), dialog);
}





// Function to handle "Give a Star" button click
void on_give_star_clicked()
{
    const gchar *github_repo_url = "https://github.com/nazmusweb-coding/DOS-Programming";
    gtk_show_uri_on_window(NULL, github_repo_url, GDK_CURRENT_TIME, NULL);
}