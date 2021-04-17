#include <gtk/gtk.h>

static void click_digit(GtkWidget *widget, gpointer data) {
    printf("Clicked button %u\n", GPOINTER_TO_UINT(data));
}

static void add_button(GtkWidget *grid, GtkWidget *btn, int x, int y, int w, int h) {
    gtk_widget_set_hexpand(btn, TRUE);
    gtk_widget_set_vexpand(btn, TRUE);
    gtk_grid_attach(GTK_GRID(grid), btn, x, y, w, h);
}

static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *display;
    GtkWidget *btn_digit[10];

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW (window), "Calculator");
    gtk_window_set_default_size(GTK_WINDOW(window), 350, 400);
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);

    grid = gtk_grid_new(); // grid for packing components
    gtk_container_add (GTK_CONTAINER (window), grid);

    display = gtk_label_new (NULL); // NULL means create without text 
    char *markup = g_markup_printf_escaped ("<span size=\"30000\">\%s</span>", "0"); // pango markup (https://developer.gnome.org/pygtk/stable/pango-markup-language.html)
    gtk_label_set_markup (GTK_LABEL (display), markup);
    g_free (markup);
    gtk_label_set_xalign(GTK_LABEL(display), 0.9);
    gtk_grid_attach (GTK_GRID (grid), display, 0, 0, 4, 1);

    for (int i = 1; i <= 9; i++) {
        btn_digit[i] = gtk_button_new_with_label((char[]){'0' + i, '\0'});
        add_button(grid, btn_digit[i], (i - 1) % 3, 1 + (i - 1) / 3, 1, 1);
        g_signal_connect(btn_digit[i], "clicked", G_CALLBACK(click_digit), GUINT_TO_POINTER((unsigned)i));
    }
    btn_digit[0] = gtk_button_new_with_label("0");
    add_button(grid, btn_digit[0], 1, 4, 1, 1);
    g_signal_connect(btn_digit[0], "clicked", G_CALLBACK(click_digit), GUINT_TO_POINTER((unsigned)0));
       
    gtk_widget_show_all (window); // show windows with and all its child components
}

int main (int argc, char *argv[]) {
    GtkApplication *app;
    int status;

    app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
    status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);

    return status;
}