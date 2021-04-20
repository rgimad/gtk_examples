#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>

enum state_e {
    S_ENTER_1, // state before entering number1
    S_EDIT_1, // number1 editing state
    S_ENTER_2, // state before entering number2
    S_EDIT_2 // number2 editing state
};

enum binop_e {
    OP_NONE,
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV
};

struct calc_ctx_s {
    char display_text[32];
    double number1;
    double number2;
    int binop;
    int state;
};

struct calc_ctx_s calc_ctx;
GtkWidget *window;
GtkWidget *display;
GtkWidget *grid;
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
GtkWidget *btn_bksp;
GtkWidget *btn_equal;

void init_calc_ctx(struct calc_ctx_s *ctx) {
    strcpy(ctx->display_text, "0");
    ctx->number1 = 0.0;
    ctx->number2 = 0.0;
    ctx->binop = OP_NONE;
    ctx->state = S_ENTER_1;
}

static void add_button(GtkWidget *grid, GtkWidget *btn, int x, int y, int w, int h) {
    gtk_widget_set_hexpand(btn, TRUE); // enable horizontal auto-expand
    gtk_widget_set_vexpand(btn, TRUE); // enable vertical auto-expand
    gtk_grid_attach(GTK_GRID(grid), btn, x, y, w, h);
}

static void display_set_style(GtkWidget *disp, char *init_text) {
    char *markup = g_markup_printf_escaped("<span size=\"28000\">\%s</span>", init_text); // pango markup (https://developer.gnome.org/pygtk/stable/pango-markup-language.html)
    gtk_label_set_markup(GTK_LABEL (disp), markup);
    g_free(markup);
    gtk_label_set_xalign(GTK_LABEL(disp), 0.9);
}

static void update_display() {
    display_set_style(display, calc_ctx.display_text);
}

static void click_digit(GtkWidget *widget, gpointer data) {
    int st = calc_ctx.state;
    if (st == S_ENTER_1 || st == S_ENTER_2) {
        calc_ctx.state = (st == S_ENTER_1 ? S_EDIT_1 : S_EDIT_2);
    }
    if (strcmp(calc_ctx.display_text, "0") == 0) {
        strcpy(calc_ctx.display_text, "");
    }
    strcat(calc_ctx.display_text, (char[]){'0' + GPOINTER_TO_UINT(data), '\0'});
    update_display();
}

static void click_dot(GtkWidget *widget, gpointer data) {
    //
}

static void click_bksp(GtkWidget *widget, gpointer data) {
    int st = calc_ctx.state;
    if (st == S_EDIT_1 || st == S_EDIT_2) {
        if (strlen(calc_ctx.display_text) == 1) {
            strcpy(calc_ctx.display_text, "0");
        } else {
            calc_ctx.display_text[strlen(calc_ctx.display_text) - 1] = '\0';
        }
        update_display();
    }
}

static void click_sgn(GtkWidget *widget, gpointer data) {
    if (strcmp(calc_ctx.display_text, "0") != 0) { // if text is not just 0
        char tmp[36];
        if (calc_ctx.display_text[0] == '-') { // if already minus, delete it
            memmove(calc_ctx.display_text, calc_ctx.display_text + 1, strlen(calc_ctx.display_text));
        } else { // if not, add minus
            if (strlen(calc_ctx.display_text) < 32) { // check length
                sprintf(tmp, "%c%s", '-', calc_ctx.display_text);
                strcpy(calc_ctx.display_text, tmp);
            }
        }
        update_display();
    }
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
    init_calc_ctx(&calc_ctx);

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW (window), "Calculator");
    gtk_window_set_default_size(GTK_WINDOW(window), 350, 300);
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);

    grid = gtk_grid_new(); // grid for packing components
    gtk_container_add (GTK_CONTAINER (window), grid);

    display = gtk_label_new (NULL); // NULL means create without text 
    display_set_style(display, calc_ctx.display_text);
    gtk_grid_attach (GTK_GRID (grid), display, 0, 0, 5, 1); // 0/0 - x/y coord (in cells), 5/1 - w/h (in cells)

    btn_bksp = gtk_button_new_with_label("Bksp");
    add_button(grid, btn_bksp, 5, 0, 1, 1);
    g_signal_connect(btn_bksp, "clicked", G_CALLBACK(click_bksp), NULL);

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