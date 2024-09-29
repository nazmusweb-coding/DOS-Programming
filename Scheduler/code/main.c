#include "headers.h"

char *logged_id;
int logged_priority;
GtkBuilder *builder;
GtkWidget *window;
GtkWidget *status_window;

void show_default_page();
void on_faculty1_activate(GtkWidget *widget, gpointer data);
void on_admin1_activate(GtkWidget *widget, gpointer data);
void on_class_schedules1_activate(GtkWidget *widget, gpointer user_data);
void on_exam_schedules1_activate(GtkWidget *widget, gpointer user_data);
void on_faculty_schedules1_activate(GtkWidget *widget, gpointer user_data);
void on_faq1_activate(GtkWidget *widget, gpointer user_data);
void on_about1_activate(GtkWidget *widget, gpointer user_data); // About

// Admin 
void show_success_status_window();
void on_dashboard1_activate(GtkWidget *widget, gpointer user_data);
void on_scs1_activate(GtkWidget *widget, gpointer user_data);
void on_ses1_activate(GtkWidget *widget, gpointer user_data);
void on_sfc1_activate(GtkWidget *widget, gpointer user_data);
void on_efc1_activate(GtkWidget *widget, gpointer user_data);
void on_sf1_activate(GtkWidget *widget, gpointer user_data);
void on_lq1_activate(GtkWidget *widget, gpointer user_data);
void show_logout_status_window();


// view menu item have to be draw


// Button
void on_button21_clicked(GtkWidget *widget, gpointer data);
void on_button26_clicked(GtkWidget *widget, gpointer user_data);
void on_button27_clicked(GtkWidget *widget, gpointer user_data);
void on_button28_clicked(GtkWidget *widget, gpointer user_data);

// Calender
void set_calendar_to_current_date(GtkCalendar *calendar);

// Routine
void populate_class_routine(GtkListStore *store);


int main(int argc, char *argv[])
{

    gtk_init(&argc, &argv);

    builder = gtk_builder_new_from_file("main.glade");
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window1"));
    status_window = GTK_WIDGET(gtk_builder_get_object(builder, "status_window"));
    if (window == NULL) {
        g_printerr("Error: 'builder' widget not found in .glade file.\n");
    }

    // For User(menu)
    GtkWidget *faculty_menu_item = GTK_WIDGET(gtk_builder_get_object(builder, "faculty1")); // on_faculty1_activate
    GtkWidget *admin_menu_item = GTK_WIDGET(gtk_builder_get_object(builder, "admin1")); // on_admin1_activate
    GtkWidget *class_schedules_menu_item_1 = GTK_WIDGET(gtk_builder_get_object(builder, "class_schedules1")); // on_class_schedules1_activate
    GtkWidget *exam_schedules_menu_item_1 = GTK_WIDGET(gtk_builder_get_object(builder, "exam_schedules1")); // on_exam_schedules1_activate
    GtkWidget *faculty_schedules_menu_item_1 = GTK_WIDGET(gtk_builder_get_object(builder, "faculty_schedules1")); // on_faculty_schedules1_activate
    GtkWidget *faq_menu_item_1 = GTK_WIDGET(gtk_builder_get_object(builder, "faq1")); // on_faq1_activate
    GtkWidget *about_menu_item_1 = GTK_WIDGET(gtk_builder_get_object(builder, "about1")); // on_about1_activate

    // For Admin(menu)
    GtkWidget *dashboard_menu_item = GTK_WIDGET(gtk_builder_get_object(builder, "dashboard1")); // on_dashboard1_activate
    GtkWidget *set_class_schedules_menu_item_1 = GTK_WIDGET(gtk_builder_get_object(builder, "scs1")); // on_scs1_activate
    GtkWidget *set_exam_schedules_menu_item_1 = GTK_WIDGET(gtk_builder_get_object(builder, "ses1")); // on_ses1_activate
    GtkWidget *set_faculty_schedules_menu_item_1 = GTK_WIDGET(gtk_builder_get_object(builder, "sfc1"));// on_sfc1_activate
    GtkWidget *edit_faculty_credentials_menu_item_1 = GTK_WIDGET(gtk_builder_get_object(builder, "efc1")); // on_efc1_activate
    GtkWidget *set_faq_menu_item_1 = GTK_WIDGET(gtk_builder_get_object(builder, "sf1")); // on_sf1_activate
    GtkWidget *log_out_menu_item_1 = GTK_WIDGET(gtk_builder_get_object(builder, "lq1")); // on_lq1_activate
    GtkWidget *class_schedules_menu_item_2 = GTK_WIDGET(gtk_builder_get_object(builder, "class_schedules2")); // on_class_schedules2_activate
    GtkWidget *exam_schedules_menu_item_2 = GTK_WIDGET(gtk_builder_get_object(builder, "exam_schedules2")); // on_exam_schedules2_activate
    GtkWidget *faculty_schedules_menu_item_2 = GTK_WIDGET(gtk_builder_get_object(builder, "faculty_schedules2")); // on_faculty_schedules2_activate
    GtkWidget *faq_menu_item_2 = GTK_WIDGET(gtk_builder_get_object(builder, "faq2")); // on_faq2_activate
    GtkWidget *about_menu_item_2 = GTK_WIDGET(gtk_builder_get_object(builder, "about2")); // on_about2_activate

    // gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview4), -1, "Day and Time", renderer1, "text", 0, NULL);
    // gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview4), -1, "8:00-9:20", renderer1, "text", 1, NULL);
    // gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview4), -1, "9:30-10:50", renderer1, "text", 2, NULL);
    // gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview4), -1, "11:00-12:50", renderer1, "text", 3, NULL);
    // gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview4), -1, "1:00-2:20", renderer1, "text", 4, NULL);
    // gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview4), -1, "2:30-3:50", renderer1, "text", 5, NULL);
    // gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview4), -1, "4:00-5:20", renderer1, "text", 6, NULL);

    // // Set the model for the treeview
    // gtk_tree_view_set_model(GTK_TREE_VIEW(treeview4), GTK_TREE_MODEL(list_store1));

    // Unreference the model if you dont need it elsewhere



    // Admin log in submit button
    GtkWidget *button21 = GTK_WIDGET(gtk_builder_get_object(builder, "button21"));

    // Stacks
    GtkStack *stack1 = GTK_STACK(gtk_builder_get_object(builder, "stack1")); // For Different Menu For Different User
    GtkStack *stack1_1 = GTK_STACK(gtk_builder_get_object(builder, "stack1_1")); // User Stack
    GtkStack *stack1_2 = GTK_STACK(gtk_builder_get_object(builder, "stack1_2")); // Admin Stack

    // Pages
    GtkWidget *stack1_page0 = GTK_WIDGET(gtk_builder_get_object(builder, "page0")); // User Menu
    GtkWidget *stack1_1_page1 = GTK_WIDGET(gtk_builder_get_object(builder, "page1")); // Class Schedules With User Menu
    GtkWidget *stack1_1_page2 = GTK_WIDGET(gtk_builder_get_object(builder, "page2")); // Exam Schedules with User Menu
    GtkWidget *stack1_1_page3 = GTK_WIDGET(gtk_builder_get_object(builder, "page3")); // Faculty Schedules with User Menu
    GtkWidget *stack1_1_page4 = GTK_WIDGET(gtk_builder_get_object(builder, "page4")); // FAQ with User Menu
    GtkWidget *stack1_1_page5 = GTK_WIDGET(gtk_builder_get_object(builder, "page5")); // Admin Login
    GtkWidget *stack1_1_page12 = GTK_WIDGET(gtk_builder_get_object(builder, "page12")); // Default Welcome page
    GtkWidget *stack1_1_page13 = GTK_WIDGET(gtk_builder_get_object(builder, "page13")); // Faculty Login
    

    GtkWidget *stack1_page6 = GTK_WIDGET(gtk_builder_get_object(builder, "page6")); // Admin Menu
    GtkWidget *stack1_2_page7 = GTK_WIDGET(gtk_builder_get_object(builder, "page7")); // Dashboard With Admin Menu
    GtkWidget *stack1_2_page8 = GTK_WIDGET(gtk_builder_get_object(builder, "page8")); // Set Class Schedules With Admin Menu
    GtkWidget *stack1_2_page9 = GTK_WIDGET(gtk_builder_get_object(builder, "page9")); // Set Exam Schedules With Admin Menu
    GtkWidget *stack1_2_page10 = GTK_WIDGET(gtk_builder_get_object(builder, "page10")); // Edit Faculty Credentials With Admin Menu
    GtkWidget *stack1_2_page11 = GTK_WIDGET(gtk_builder_get_object(builder, "page11")); // Set FAQ and About With Admin Menu
    GtkWidget *stack1_2_page14 = GTK_WIDGET(gtk_builder_get_object(builder, "page14")); // View Class Schedules
    GtkWidget *stack1_2_page15 = GTK_WIDGET(gtk_builder_get_object(builder, "page15")); // View Exam Schedules
    GtkWidget *stack1_2_page16 = GTK_WIDGET(gtk_builder_get_object(builder, "page16")); // View Faculty Schedules  


    

    g_signal_connect(G_OBJECT(faculty_menu_item), "activate", G_CALLBACK(on_faculty1_activate), builder);
    g_signal_connect(G_OBJECT(admin_menu_item), "activate", G_CALLBACK(on_admin1_activate), builder);
    g_signal_connect(G_OBJECT(class_schedules_menu_item_1), "activate", G_CALLBACK(on_class_schedules1_activate), builder);
    g_signal_connect(G_OBJECT(exam_schedules_menu_item_1), "activate", G_CALLBACK(on_exam_schedules1_activate), builder);
    g_signal_connect(G_OBJECT(faculty_schedules_menu_item_1), "activate", G_CALLBACK(on_faculty_schedules1_activate), builder);
    g_signal_connect(G_OBJECT(faq_menu_item_1), "activate", G_CALLBACK(on_faq1_activate), builder);
    g_signal_connect(G_OBJECT(about_menu_item_1), "activate", G_CALLBACK(on_about1_activate), builder);

    // Admin menu
    g_signal_connect(G_OBJECT(dashboard_menu_item), "activate", G_CALLBACK(on_dashboard1_activate), builder);
    g_signal_connect(G_OBJECT(set_class_schedules_menu_item_1), "activate", G_CALLBACK(on_scs1_activate), builder);
    g_signal_connect(G_OBJECT(set_exam_schedules_menu_item_1), "activate", G_CALLBACK(on_ses1_activate), builder);
    g_signal_connect(G_OBJECT(edit_faculty_credentials_menu_item_1), "activate", G_CALLBACK(on_efc1_activate), builder);
    g_signal_connect(G_OBJECT(set_faq_menu_item_1), "activate", G_CALLBACK(on_sf1_activate), builder);
    g_signal_connect(G_OBJECT(set_about_menu_item_1), "activate", G_CALLBACK(on_sa1_activate), builder);
    g_signal_connect(G_OBJECT(log_out_menu_item_1), "activate", G_CALLBACK(on_lq1_activate), builder);
    // View menuitem have to be draw again
    g_signal_connect(G_OBJECT(about_menu_item_2), "activate", G_CALLBACK(on_about1_activate), builder); // connected the previous one

    // Login submit button
    g_signal_connect(G_OBJECT(GTK_WIDGET(gtk_builder_get_object(builder, "button21"))), "clicked", G_CALLBACK(on_button21_clicked), builder);

    // Admin login status window buttons
    g_signal_connect(G_OBJECT(GTK_WIDGET(gtk_builder_get_object(builder, "button26"))), "clicked", G_CALLBACK(on_button26_clicked), builder);
    g_signal_connect(G_OBJECT(GTK_WIDGET(gtk_builder_get_object(builder, "button27"))), "clicked", G_CALLBACK(on_button27_clicked), builder);
    g_signal_connect(G_OBJECT(GTK_WIDGET(gtk_builder_get_object(builder, "button28"))), "clicked", G_CALLBACK(on_button28_clicked), builder);

    show_default_page();

    gtk_widget_show_all(window);

    // Connect the main window's delete event to GTK main loop
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);


    gtk_main();

}


void show_default_page()
{ 
    GtkStack *stack_menu = GTK_STACK(gtk_builder_get_object(builder, "stack1"));
    GtkStack *stack_page = GTK_STACK(gtk_builder_get_object(builder, "stack1_1"));
    gtk_stack_set_visible_child_name(stack_menu, "page0"); // Welcome menu
    gtk_stack_set_visible_child_name(stack_page, "page12"); // Welcome page
}

// Callback implementations for switching stack pages
void on_faculty1_activate(GtkWidget *widget, gpointer user_data) 
{
    GtkStack *stack_page = GTK_STACK(gtk_builder_get_object(GTK_BUILDER(user_data), "stack1_1"));
    gtk_stack_set_visible_child_name(stack_page, "page13"); // Faculty Login

    gtk_entry_set_text(GTK_ENTRY(gtk_builder_get_object(builder, "entry14")), "");
    gtk_entry_set_text(GTK_ENTRY(gtk_builder_get_object(builder, "entry15")), "");
}

void on_admin1_activate(GtkWidget *widget, gpointer user_data) 
{
    GtkStack *stack_page = GTK_STACK(gtk_builder_get_object(GTK_BUILDER(user_data), "stack1_1"));
    gtk_stack_set_visible_child_name(stack_page, "page5"); // Faculty Login

    gtk_entry_set_text(GTK_ENTRY(gtk_builder_get_object(builder, "entry12")), "");
    gtk_entry_set_text(GTK_ENTRY(gtk_builder_get_object(builder, "entry13")), "");
}

void on_class_schedules1_activate(GtkWidget *widget, gpointer user_data) 
{
    // Admin Edit Faculty Credentials treeview
    GtkTreeView *treeview1 = GTK_TREE_VIEW(gtk_builder_get_object(GTK_BUILDER(user_data), "treeview1"));
    GtkListStore *list_store1 = gtk_list_store_new(7, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

    if (!treeview1) 
    {
        printf("Failed to get treeview1 from builder\n");
        return;
    }

    gtk_tree_view_set_model(treeview1, GTK_TREE_MODEL(list_store1));
    gtk_widget_queue_draw(GTK_WIDGET(treeview1)); // Force redraw

    // Populate the treeview with data
    populate_class_routine(list_store1);
    GtkStack *stack_page = GTK_STACK(gtk_builder_get_object(GTK_BUILDER(user_data), "stack1_1"));
    gtk_stack_set_visible_child_name(stack_page, "page1"); // Class Schedules
    gtk_widget_show_all(GTK_WIDGET(treeview1));
}

void on_exam_schedules1_activate(GtkWidget *widget, gpointer user_data) 
{
    GtkStack *stack = GTK_STACK(gtk_builder_get_object(GTK_BUILDER(user_data), "stack1_1"));
    gtk_stack_set_visible_child_name(stack, "page2"); // Exam Schedules
}

void on_faculty_schedules1_activate(GtkWidget *widget, gpointer user_data) 
{
    GtkStack *stack = GTK_STACK(gtk_builder_get_object(GTK_BUILDER(user_data), "stack1_1"));
    gtk_stack_set_visible_child_name(stack, "page3"); // Faculty Schedules
}

void on_faq1_activate(GtkWidget *widget, gpointer user_data) 
{
    GtkStack *stack = GTK_STACK(gtk_builder_get_object(GTK_BUILDER(user_data), "stack1_1"));
    gtk_stack_set_visible_child_name(stack, "page4");
}

void on_popup1_activate_link(GtkWidget *widget, gpointer user_data)
{
    GtkWidget *popup_window = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(user_data), "popup1"));

    // Show all widgets in the window
    gtk_widget_show_all(popup_window);

    g_signal_connect(popup_window, "delete-event", G_CALLBACK(gtk_widget_hide_on_delete), NULL);
}

void on_dashboard1_activate(GtkWidget *widget, gpointer user_data) 
{
    GtkStack *stack_menu = GTK_STACK(gtk_builder_get_object(GTK_BUILDER(user_data), "stack1"));
    GtkStack *stack_page = GTK_STACK(gtk_builder_get_object(GTK_BUILDER(user_data), "stack1_2"));
    gtk_stack_set_visible_child_name(stack_menu, "page6");
    gtk_stack_set_visible_child_name(stack_page, "page7");
    GtkCalendar *calendar = GTK_CALENDAR(gtk_builder_get_object(builder, "calendar1"));
    set_calendar_to_current_date(calendar);
}

void on_scs1_activate(GtkWidget *widget, gpointer user_data) 
{
    GtkStack *stack = GTK_STACK(gtk_builder_get_object(GTK_BUILDER(user_data), "stack1_2"));
    gtk_stack_set_visible_child_name(stack, "page8");
}

void on_ses1_activate(GtkWidget *widget, gpointer user_data) 
{
    GtkStack *stack = GTK_STACK(gtk_builder_get_object(GTK_BUILDER(user_data), "stack1_2"));
    gtk_stack_set_visible_child_name(stack, "page9");
}

void on_sfc1_activate(GtkWidget *widget, gpointer user_data) 
{
    GtkStack *stack = GTK_STACK(gtk_builder_get_object(GTK_BUILDER(user_data), "stack1_2"));
    gtk_stack_set_visible_child_name(stack, "page10");
}

void on_efc1_activate(GtkWidget *widget, gpointer user_data) 
{
    if (logged_priority > 1)
    {
        return;
    }
    
    GtkStack *stack = GTK_STACK(gtk_builder_get_object(GTK_BUILDER(user_data), "stack1_2"));
    gtk_stack_set_visible_child_name(stack, "page10");
}

void on_sf1_activate(GtkWidget *widget, gpointer user_data) 
{
    if (logged_priority > 1)
    {
        return;
    }
    GtkStack *stack = GTK_STACK(gtk_builder_get_object(GTK_BUILDER(user_data), "stack1_2"));
    gtk_stack_set_visible_child_name(stack, "page11");
}

void on_lq1_activate(GtkWidget *widget, gpointer user_data) 
{
    logged_priority = 0;
    show_logout_status_window();
}

// We need to create different interface for them to keep up with stacks....

void on_class_schedules2_activate(GtkWidget *widget, gpointer user_data) 
{
    GtkStack *stack = GTK_STACK(gtk_builder_get_object(GTK_BUILDER(user_data), "stack1_2"));
    gtk_stack_set_visible_child_name(stack, "page14");
}

void on_exam_schedules2_activate(GtkWidget *widget, gpointer user_data) 
{
    GtkStack *stack = GTK_STACK(gtk_builder_get_object(GTK_BUILDER(user_data), "stack1_2"));
    gtk_stack_set_visible_child_name(stack, "page15");
}

void on_faculty_schedules2_activate(GtkWidget *widget, gpointer user_data) 
{
    GtkStack *stack = GTK_STACK(gtk_builder_get_object(GTK_BUILDER(user_data), "stack1_2"));
    gtk_stack_set_visible_child_name(stack, "page16");
}

void on_faq2_activate(GtkWidget *widget, gpointer user_data) 
{
    GtkStack *stack = GTK_STACK(gtk_builder_get_object(GTK_BUILDER(user_data), "stack1_2"));
    gtk_stack_set_visible_child_name(stack, "page17");
}

// Log out popup window
void show_logout_status_window()
{
    GtkStack *stack = GTK_STACK(gtk_builder_get_object(builder, "stack2"));
    gtk_stack_set_visible_child_name(stack, "page16");

    gtk_widget_show_all(status_window);

    // g_signal_connect(status_window, "delete-event", G_CALLBACK(gtk_widget_hide_on_delete), NULL);
}

// Admin Login Success popup window
void show_success_status_window()
{
    GtkStack *stack = GTK_STACK(gtk_builder_get_object(builder, "stack2"));
    gtk_stack_set_visible_child_name(stack, "page14");

    gtk_widget_show_all(status_window);

    // g_signal_connect(status_window, "delete-event", G_CALLBACK(gtk_widget_hide_on_delete), NULL);
}

// Admin Login Fail popup window
void show_fail_status_window()
{
    GtkStack *stack = GTK_STACK(gtk_builder_get_object(builder, "stack2"));
    gtk_stack_set_visible_child_name(stack, "page15");

    gtk_widget_show_all(status_window);

    // g_signal_connect(status_window, "delete-event", G_CALLBACK(gtk_widget_hide_on_delete), NULL);
}

// Admin Success popup ok button
void on_button26_clicked(GtkWidget *widget, gpointer user_data)
{
    gtk_widget_hide(status_window);
    on_dashboard1_activate(widget, user_data);  
}

// Admin Fail popup ok button
void on_button27_clicked(GtkWidget *widget, gpointer user_data)
{
    gtk_widget_hide(status_window);
    //on_admin1_activate(widget, user_data);
}

// Admin logout popup ok button
void on_button28_clicked(GtkWidget *widget, gpointer user_data)
{
    gtk_widget_hide(status_window);
    show_default_page();
}

void on_button21_clicked(GtkWidget *widget, gpointer data)
{
    GtkEntry *entry12 = GTK_ENTRY(gtk_builder_get_object(builder, "entry12"));
    GtkEntry *entry13 = GTK_ENTRY(gtk_builder_get_object(builder, "entry13"));

    const char *id_text = gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(builder, "entry12")));
    const char *pc_text = gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(builder, "entry13")));

    // admin login authentication and access priority fetch
    int result = login(admin_db, id_text, pc_text);
    if (result > 0)
    {
        logged_priority = result;
        show_success_status_window();
    }
    else
    {
        logged_priority = 0;
        show_fail_status_window();
    }
}

// faculty starts here
void on_dashboard2_activate(GtkWidget *widget, gpointer user_data) 
{
    GtkStack *stack_menu = GTK_STACK(gtk_builder_get_object(GTK_BUILDER(user_data), "stack1"));
    GtkStack *stack_page = GTK_STACK(gtk_builder_get_object(GTK_BUILDER(user_data), "stack3_1"));
    gtk_stack_set_visible_child_name(stack_menu, "page23");
    gtk_stack_set_visible_child_name(stack_page, "page24");
    GtkCalendar *calendar = GTK_CALENDAR(gtk_builder_get_object(builder, "calendar2"));
    set_calendar_to_current_date(calendar);
}

void on_sf2_activate(GtkWidget *widget, gpointer user_data)
{

}

void on_cmp1_activate(GtkWidget *widget, gpointer user_data)
{

}

void on_lq2_activate(GtkWidget *widget, gpointer user_data)
{
    
}

void on_class_schedules3_activate(GtkWidget *widget, gpointer user_data) 
{
    // Admin Edit Faculty Credentials treeview
    GtkTreeView *treeview12 = GTK_TREE_VIEW(gtk_builder_get_object(GTK_BUILDER(user_data), "treeview12"));
    GtkListStore *list_store1 = gtk_list_store_new(7, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

    if (!treeview12) 
    {
        printf("Failed to get treeview1 from builder\n");
        return;
    }

    gtk_tree_view_set_model(treeview1, GTK_TREE_MODEL(list_store1));
    gtk_widget_queue_draw(GTK_WIDGET(treeview12)); // Force redraw

    // Populate the treeview with data
    populate_class_routine(list_store1);
    GtkStack *stack_page = GTK_STACK(gtk_builder_get_object(GTK_BUILDER(user_data), "stack3_1"));
    gtk_stack_set_visible_child_name(stack_page, "page27"); // Class Schedules
    gtk_widget_show_all(GTK_WIDGET(treeview12));
}

void on_exam_schedules3_activate(GtkWidget *widget, gpointer user_data) 
{
    GtkStack *stack = GTK_STACK(gtk_builder_get_object(GTK_BUILDER(user_data), "stack3_1"));
    gtk_stack_set_visible_child_name(stack, "page28"); // Exam Schedules
}

void on_faculty_schedules3_activate(GtkWidget *widget, gpointer user_data) 
{
    GtkStack *stack = GTK_STACK(gtk_builder_get_object(GTK_BUILDER(user_data), "stack3_1"));
    gtk_stack_set_visible_child_name(stack, "page29"); // Faculty Schedules
}

void on_faq3_activate(GtkWidget *widget, gpointer user_data) 
{
    GtkStack *stack = GTK_STACK(gtk_builder_get_object(GTK_BUILDER(user_data), "stack3_1"));
    gtk_stack_set_visible_child_name(stack, "page30");
}

void on_popup3_activate_link(GtkWidget *widget, gpointer user_data)
{
    GtkWidget *popup_window = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(user_data), "popup1"));

    // Show all widgets in the window
    gtk_widget_show_all(popup_window);

    g_signal_connect(popup_window, "delete-event", G_CALLBACK(gtk_widget_hide_on_delete), NULL);
}

//--------------------------------------------------------------------------

// Log out popup window
void show_logout_status_window()
{
    GtkStack *stack = GTK_STACK(gtk_builder_get_object(builder, "stack2"));
    gtk_stack_set_visible_child_name(stack, "page16");

    gtk_widget_show_all(status_window);

    // g_signal_connect(status_window, "delete-event", G_CALLBACK(gtk_widget_hide_on_delete), NULL);
}

// Admin Login Success popup window
void show_success_status_window()
{
    GtkStack *stack = GTK_STACK(gtk_builder_get_object(builder, "stack2"));
    gtk_stack_set_visible_child_name(stack, "page14");

    gtk_widget_show_all(status_window);

    // g_signal_connect(status_window, "delete-event", G_CALLBACK(gtk_widget_hide_on_delete), NULL);
}

// Admin Login Fail popup window
void show_fail_status_window()
{
    GtkStack *stack = GTK_STACK(gtk_builder_get_object(builder, "stack2"));
    gtk_stack_set_visible_child_name(stack, "page15");

    gtk_widget_show_all(status_window);

    // g_signal_connect(status_window, "delete-event", G_CALLBACK(gtk_widget_hide_on_delete), NULL);
}

// Admin Success popup ok button
void on_button26_clicked(GtkWidget *widget, gpointer user_data)
{
    gtk_widget_hide(status_window);
    on_dashboard1_activate(widget, user_data);  
}

// Admin Fail popup ok button
void on_button27_clicked(GtkWidget *widget, gpointer user_data)
{
    gtk_widget_hide(status_window);
    //on_admin1_activate(widget, user_data);
}

// Admin logout popup ok button
void on_button28_clicked(GtkWidget *widget, gpointer user_data)
{
    gtk_widget_hide(status_window);
    show_default_page();
}

// ----------------------------------------------------------------------------------

void on_button23_clicked(GtkWidget *widget, gpointer data)
{
    // GtkEntry *entry14 = GTK_ENTRY(gtk_builder_get_object(builder, "entry14"));
    // GtkEntry *entry15 = GTK_ENTRY(gtk_builder_get_object(builder, "entry15"));

    const char *id_text = gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(builder, "entry14")));
    const char *pc_text = gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(builder, "entry15")));

    // faculty login authentication and access priority fetch
    char *result = login_faculty(faculty_db, id_text, pc_text);
    if (strcmp(result, NULL) == 0)
    {
        logged_id = NULL;
        show_fail_status_window();
    }
    else
    {
        strcpy(logged_id, result);
        show_success_status_window();
    }
}


// void on_admin_login(GtkWidget *widget, gpointer user_data)
// {
//     // page 14 15
//     GtkWidget *status_window = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(user_data), "status_window"));
//     GtkStack *stack = GTK_STACK(gtk_builder_get_object(GTK_BUILDER(user_data), "stack2"));
//     if (login == success)
//         gtk_stack_set_visible_child_name(stack, "page14"); // Faculty Login
//         GtkWidget *button26 = GTK_BUTTON(gtk_builder_get_object(GTK_BUILDER(user_data), "button26"));
//     else
//         gtk_stack_set_visible_child_name(stack, "page15"); // Faculty Login

//     gtk_widget_show_all(popup_window);

//     g_signal_connect(popup_window, "delete-event", G_CALLBACK(gtk_widget_hide_on_delete), NULL);
// }


void set_calendar_to_current_date(GtkCalendar *calendar)
{
    // Get the current time
    time_t t = time(NULL);
    struct tm *current_time = localtime(&t);

    // Extract the current year, month, and day
    int year = current_time->tm_year + 1900; // tm_year is years since 1900
    int month = current_time->tm_mon;        // tm_mon is 0-based (0 = January)
    int day = current_time->tm_mday;

    // Set the calendar to the current date
    gtk_calendar_select_month(calendar, month, year);
    gtk_calendar_select_day(calendar, day);
}

void populate_class_routine(GtkListStore *store) 
{
    sqlite3 *db;
    sqlite3_stmt *stmt;
    GtkTreeIter iter;
    const char *database_filename = "4f.db"; // Database filename

    int rc = sqlite3_open(database_filename, &db);

    if (rc != SQLITE_OK) 
    {
        printf("Cannot open database: %s\n", sqlite3_errmsg(db));
        return;
    }

    const char *sql = "SELECT \"Day and Time\", \"8:00-9:20\", \"9:30-10:50\", \"11:00-12:50\", \"1:00-2:20\", \"2:30-3:50\", \"4:00-5:20\" FROM ClassRoutine;";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    if (rc != SQLITE_OK) 
    {
        printf("Failed to execute statement: %s\nSQL: %s\n", sqlite3_errmsg(db), sql);
        sqlite3_close(db);
        return;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) 
    {
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
                           0, sqlite3_column_text(stmt, 0) ? (const char*)sqlite3_column_text(stmt, 0) : "",  // Day and Time
                           1, sqlite3_column_text(stmt, 1) ? (const char*)sqlite3_column_text(stmt, 1) : "",  // 8:00-9:20
                           2, sqlite3_column_text(stmt, 2) ? (const char*)sqlite3_column_text(stmt, 2) : "",  // 9:30-10:50
                           3, sqlite3_column_text(stmt, 3) ? (const char*)sqlite3_column_text(stmt, 3) : "",  // 11:00-12:50
                           4, sqlite3_column_text(stmt, 4) ? (const char*)sqlite3_column_text(stmt, 4) : "",  // 1:00-2:20
                           5, sqlite3_column_text(stmt, 5) ? (const char*)sqlite3_column_text(stmt, 5) : "",  // 2:30-3:50
                           6, sqlite3_column_text(stmt, 6) ? (const char*)sqlite3_column_text(stmt, 6) : "",  // 4:00-5:20
                           -1);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}