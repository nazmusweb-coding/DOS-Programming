#include "test.h"

// Function declarations for callbacks
void on_submit_button_clicked(GtkWidget *widget, gpointer data);
void D_on_submit_button_clicked(GtkWidget *widget, gpointer data);
void display_result(const char *message);

// Function declarations for callbacks
void show_undergraduate(GtkWidget *widget, gpointer data);
void show_diploma(GtkWidget *widget, gpointer data);

// Function to create and show undergraduate and diploma interface
void create_undergraduate_interface(GtkWidget *container);
void create_diploma_interface(GtkWidget *container);

// Global variables
GtkWidget *content_area;
GtkWidget *ssc_entry, *hsc_entry, *department_combo, *result_view;
GtkTextBuffer *result_buffer;
GtkWidget *diploma_entry;

int main(int argc, char **argv) 
{
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *menu_bar, *menu, *menu_item;

    gtk_init(&argc, &argv);

    // Create the main window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "NUB Admission Costing Calculator");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 500); // 400, 300 default

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

    // Attach the menu bar to the grid
    gtk_grid_attach(GTK_GRID(grid), menu_bar, 0, 0, 1, 1);

    // Create the content area
    content_area = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_grid_attach(GTK_GRID(grid), content_area, 0, 1, 10, 10);

    // Show the undergraduate interface by default
    create_undergraduate_interface(content_area);

    // Show all widgets
    gtk_widget_show_all(window);

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
}

// Callback to show the diploma interface based on selection
void show_diploma(GtkWidget *widget, gpointer data) 
{
    gtk_container_foreach(GTK_CONTAINER(content_area), (GtkCallback)gtk_widget_destroy, NULL); // Clear previous content
    create_diploma_interface(content_area);
    gtk_widget_show_all(content_area); // Refresh the container
}

// Function to create and show undergraduate interface
void create_undergraduate_interface(GtkWidget *container) 
{
    GtkWidget *grid, *ssc_label, *hsc_label, *submit_button, *department_label;
    
    grid = gtk_grid_new();
    gtk_box_pack_start(GTK_BOX(container), grid, TRUE, TRUE, 0);

    ssc_label = gtk_label_new("SSC Result:");
    gtk_grid_attach(GTK_GRID(grid), ssc_label, 0, 0, 1, 1);
    ssc_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), ssc_entry, 1, 0, 1, 1);

    hsc_label = gtk_label_new("HSC Result:");
    gtk_grid_attach(GTK_GRID(grid), hsc_label, 0, 1, 1, 1);
    hsc_entry = gtk_entry_new();
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

    submit_button = gtk_button_new_with_label("Submit");
    g_signal_connect(submit_button, "clicked", G_CALLBACK(on_submit_button_clicked), NULL);
    gtk_grid_attach(GTK_GRID(grid), submit_button, 0, 3, 2, 1);

    result_view = gtk_text_view_new();
    result_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(result_view));
    gtk_text_view_set_editable(GTK_TEXT_VIEW(result_view), FALSE);
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(result_view), FALSE);
    gtk_grid_attach(GTK_GRID(grid), result_view, 0, 4, 2, 1);
    
}

// Callback for the submit button
void on_submit_button_clicked(GtkWidget *widget, gpointer data) 
{
    const char *ssc_text = gtk_entry_get_text(GTK_ENTRY(ssc_entry));
    const char *hsc_text = gtk_entry_get_text(GTK_ENTRY(hsc_entry));
    const char *selected_department = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(department_combo));

    // Check if any of the required fields are empty
    if (strlen(ssc_text) == 0 || strlen(hsc_text) == 0 || selected_department == NULL) 
    {
        display_result("Please fill in all fields.\n");
        // Clear the text view
        gtk_text_buffer_set_text(result_buffer, "", -1);
        if (selected_department != NULL) 
        {
            g_free((gpointer) selected_department); // Free memory allocated by GTK
        }
        return;
    }

    float ssc = atof(ssc_text);
    float hsc = atof(hsc_text);

    // Clear the text view
    gtk_text_buffer_set_text(result_buffer, "", -1);

    if (strcmp(selected_department, "BBA") == 0) 
    {
        UG.BBA(ssc, hsc, display_result);
    } 
    else if (strcmp(selected_department, "LLB") == 0) 
    {
        UG.LLB(display_result);
    } 
    else if (strcmp(selected_department, "EEE") == 0) 
    {
        UG.EEE(ssc, hsc, display_result);
    } 
    else if (strcmp(selected_department, "Textile") == 0) 
    {
        UG.Textile(ssc, hsc, display_result);
    } 
    else if (strcmp(selected_department, "CSE") == 0) 
    {
        UG.CSE(ssc, hsc, display_result);
    } 
    else if (strcmp(selected_department, "Civil") == 0) 
    {
        UG.Civil(ssc, hsc, display_result);
    } else if (strcmp(selected_department, "ME") == 0) 
    {
        UG.ME(ssc, hsc, display_result);
    } 
    else if (strcmp(selected_department, "ECE") == 0) 
    {
        UG.ECE(ssc, hsc, display_result);
    } 
    else if (strcmp(selected_department, "B_Pharm") == 0) 
    {
        UG.B_Pharm(display_result);
    } 
    else if (strcmp(selected_department, "ELL") == 0) 
    {
        UG.ELL(ssc, hsc, display_result);
    } 
    else if (strcmp(selected_department, "Bangla") == 0) 
    {
        UG.Bangla(ssc, hsc, display_result);
    }

    g_free((gpointer)selected_department);
}

// Function to create and show diploma interface
void create_diploma_interface(GtkWidget *container) 
{
    GtkWidget *grid, *diploma_label, *submit_button, *department_label, *scrolled_window;

    grid = gtk_grid_new();
    gtk_box_pack_start(GTK_BOX(container), grid, TRUE, TRUE, 0);

    diploma_label = gtk_label_new("Diploma Result:");
    gtk_grid_attach(GTK_GRID(grid), diploma_label, 0, 0, 1, 1);
    diploma_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), diploma_entry, 1, 0, 1, 1);

    department_label = gtk_label_new("Select Department:");
    gtk_grid_attach(GTK_GRID(grid), department_label, 0, 1, 1, 1);
    department_combo = gtk_combo_box_text_new();
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(department_combo), NULL, "EEE");
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(department_combo), NULL, "Textile");
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(department_combo), NULL, "CSE");
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(department_combo), NULL, "ECE");
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(department_combo), NULL, "Civil");
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(department_combo), NULL, "ME");
    gtk_grid_attach(GTK_GRID(grid), department_combo, 1, 1, 1, 1);

    submit_button = gtk_button_new_with_label("Submit");
    g_signal_connect(submit_button, "clicked", G_CALLBACK(D_on_submit_button_clicked), NULL);
    gtk_grid_attach(GTK_GRID(grid), submit_button, 0, 2, 2, 1);

    result_view = gtk_text_view_new();
    result_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(result_view));
    gtk_text_view_set_editable(GTK_TEXT_VIEW(result_view), FALSE);
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(result_view), FALSE);
    gtk_grid_attach(GTK_GRID(grid), result_view, 0, 4, 2, 1);

}

// Callback for the submit button in diploma interface
void D_on_submit_button_clicked(GtkWidget *widget, gpointer data) 
{
    const char *diploma_text = gtk_entry_get_text(GTK_ENTRY(diploma_entry));
    const char *selected_department = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(department_combo));

    // Check if any of the required fields are empty
    if (strlen(diploma_text) == 0 || selected_department == NULL) 
    {
        display_result("Please fill in all fields.\n");
        // Clear the text view
        gtk_text_buffer_set_text(result_buffer, "", -1);
        if (selected_department != NULL) 
        {
            g_free((gpointer) selected_department); // Free memory allocated by GTK
        }
        return;
    }

    float diploma = atof(diploma_text);

    // Clear the text view
    gtk_text_buffer_set_text(result_buffer, "", -1);

    if (strcmp(selected_department, "EEE") == 0) 
    {
        UGD.EEE(diploma, display_result);
    } 
    else if (strcmp(selected_department, "Textile") == 0) 
    {
        UGD.Textile(diploma, display_result);
    } 
    else if (strcmp(selected_department, "CSE") == 0) 
    {
        UGD.CSE(diploma, display_result);
    } 
    else if (strcmp(selected_department, "ECE") == 0) 
    {
        UGD.ECE(diploma, display_result);
    } 
    else if (strcmp(selected_department, "Civil") == 0) 
    {
        UGD.Civil(diploma, display_result);
    } 
    else if (strcmp(selected_department, "ME") == 0) 
    {
        UGD.ME(diploma, display_result);
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