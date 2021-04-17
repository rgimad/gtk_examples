#include <gtk/gtk.h>

enum state_e {
    S_START,
    S_WAIT_NUM2
};

enum binop_e {
    OP_NONE,
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV
};

struct calc_ctx_s {
    double number1;
    double number2;
    int binop;
    int state;
};

void init_calc_ctx(struct calc_ctx_s *ctx) {
    ctx->number1 = 0.0;
    ctx->number2 = 0.0;
    ctx->binop = OP_NONE;
    ctx->state = S_START;
}

static void add_button(GtkWidget *grid, GtkWidget *btn, int x, int y, int w, int h) {
    gtk_widget_set_hexpand(btn, TRUE);
    gtk_widget_set_vexpand(btn, TRUE);
    gtk_grid_attach(GTK_GRID(grid), btn, x, y, w, h);
}

static void click_digit(GtkWidget *widget, gpointer data) {
    printf("Clicked button %u\n", GPOINTER_TO_UINT(data));
}

static void click_dot(GtkWidget *widget, gpointer data) {
    //
}

static void click_sgn(GtkWidget *widget, gpointer data) {
    //
}

static void click_add(GtkWidget *widget, gpointer data) {
    //
}

static void click_sub(GtkWidget *widget, gpointer data) {
    //
}

static void click_mul(GtkWidget *widget, gpointer data) {
    //
}

static void click_div(GtkWidget *widget, gpointer data) {
    //
}

static void click_c(GtkWidget *widget, gpointer data) {
    //
}

static void click_ce(GtkWidget *widget, gpointer data) {
    //
}

static void click_sqrt(GtkWidget *widget, gpointer data) {
    //
}

static void click_sqr(GtkWidget *widget, gpointer data) {
    //
}

static void click_equal(GtkWidget *widget, gpointer data) {
    //
}

static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *display;
    GtkWidget *btn_digit[10];
    GtkWidget *btn_dot;
    GtkWidget *btn_sgn;
    GtkWidget *btn_add;
    GtkWidget *btn_sub;
    GtkWidget *btn_mul;
    GtkWidget *btn_div;
    GtkWidget *btn_c;
    GtkWidget *btn_ce;
    GtkWidget *btn_sqrt;
    GtkWidget *btn_sqr;
    GtkWidget *btn_equal;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW (window), "Calculator");
    gtk_window_set_default_size(GTK_WINDOW(window), 350, 400);
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);

    grid = gtk_grid_new(); // grid for packing components
    gtk_container_add (GTK_CONTAINER (window), grid);

    display = gtk_label_new (NULL); // NULL means create without text 
    char *markup = g_markup_printf_escaped ("<span size=\"28000\">\%s</span>", "0"); // pango markup (https://developer.gnome.org/pygtk/stable/pango-markup-language.html)
    gtk_label_set_markup (GTK_LABEL (display), markup);
    g_free (markup);
    gtk_label_set_xalign(GTK_LABEL(display), 0.9);
    gtk_grid_attach (GTK_GRID (grid), display, 0, 0, 6, 1);

    for (int i = 1; i <= 9; i++) {
        btn_digit[i] = gtk_button_new_with_label((char[]){'0' + i, '\0'});
        add_button(grid, btn_digit[i], (i - 1) % 3, 1 + (i - 1) / 3, 1, 1);
        g_signal_connect(btn_digit[i], "clicked", G_CALLBACK(click_digit), GUINT_TO_POINTER((unsigned)i));
    }
    btn_digit[0] = gtk_button_new_with_label("0");
    add_button(grid, btn_digit[0], 1, 4, 1, 1);
    g_signal_connect(btn_digit[0], "clicked", G_CALLBACK(click_digit), GUINT_TO_POINTER((unsigned)0));

    btn_dot = gtk_button_new_with_label(".");
    add_button(grid, btn_dot, 2, 4, 1, 1);
    g_signal_connect(btn_dot, "clicked", G_CALLBACK(click_dot), NULL);
    
    btn_sgn = gtk_button_new_with_label("±");
    add_button(grid, btn_sgn, 0, 4, 1, 1);
    g_signal_connect(btn_sgn, "clicked", G_CALLBACK(click_sgn), NULL);

    btn_div = gtk_button_new_with_label("/");
    add_button(grid, btn_div, 3, 1, 1, 1);
    g_signal_connect(btn_div, "clicked", G_CALLBACK(click_div), NULL);

    btn_mul = gtk_button_new_with_label("*");
    add_button(grid, btn_mul, 3, 2, 1, 1);
    g_signal_connect(btn_mul, "clicked", G_CALLBACK(click_mul), NULL);

    btn_sub = gtk_button_new_with_label("-");
    add_button(grid, btn_sub, 3, 3, 1, 1);
    g_signal_connect(btn_sub, "clicked", G_CALLBACK(click_sub), NULL);

    btn_add = gtk_button_new_with_label("+");
    add_button(grid, btn_add, 3, 4, 1, 1);
    g_signal_connect(btn_add, "clicked", G_CALLBACK(click_add), NULL);

    btn_c = gtk_button_new_with_label("C");
    add_button(grid, btn_c, 4, 1, 1, 1);
    g_signal_connect(btn_c, "clicked", G_CALLBACK(click_c), NULL);

    btn_ce = gtk_button_new_with_label("CE");
    add_button(grid, btn_ce, 4, 2, 1, 1);
    g_signal_connect(btn_ce, "clicked", G_CALLBACK(click_ce), NULL);

    btn_sqrt = gtk_button_new_with_label("√");
    add_button(grid, btn_sqrt, 4, 3, 1, 1);
    g_signal_connect(btn_sqrt, "clicked", G_CALLBACK(click_sqrt), NULL);

    btn_sqr = gtk_button_new_with_label("x²");
    add_button(grid, btn_sqr, 4, 4, 1, 1);
    g_signal_connect(btn_sqr, "clicked", G_CALLBACK(click_sqr), NULL);

    btn_equal = gtk_button_new_with_label("=");
    add_button(grid, btn_equal, 5, 1, 1, 4);
    g_signal_connect(btn_equal, "clicked", G_CALLBACK(click_equal), NULL);
       
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