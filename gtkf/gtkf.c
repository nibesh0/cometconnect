#include <gtk/gtk.h>

void on_quit_button_clicked(GtkWidget *widget, gpointer data) {
    gtk_main_quit();
}

GtkWidget *chat_window;
GtkWidget *text_view;

void on_send_button_clicked(GtkWidget *widget, gpointer data) {
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    GtkTextIter end;
    gtk_text_buffer_get_end_iter(buffer, &end);

    const gchar *text = gtk_entry_get_text(GTK_ENTRY(data));
    gtk_text_buffer_insert(buffer, &end, text, -1);
    gtk_text_buffer_insert(buffer, &end, "\n", -1);

    // Clear the input field
    gtk_entry_set_text(GTK_ENTRY(data), "");
}

void on_button1_clicked(GtkWidget *widget, gpointer data) {
    chat_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(chat_window), "Chat_Window");
    gtk_widget_set_size_request(chat_window, 400, 300);

    GdkRGBA color;
    gdk_rgba_parse(&color, "red");
    gtk_widget_override_background_color(chat_window, GTK_STATE_FLAG_NORMAL, &color);

    text_view = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), FALSE);

    GtkWidget *scroll = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(scroll), text_view);

    GtkWidget *entry = gtk_entry_new();
    GtkWidget *send_button = gtk_button_new_with_label("Send");
    g_signal_connect(send_button, "clicked", G_CALLBACK(on_send_button_clicked), entry);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_box_pack_start(GTK_BOX(vbox), scroll, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), entry, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), send_button, FALSE, FALSE, 0);

    gtk_container_add(GTK_CONTAINER(chat_window), vbox);
    gtk_widget_show_all(chat_window);
}

void on_file_button_clicked(GtkWidget *widget, gpointer data) {
    // Open file manager code here
    g_print("Open file manager\n");
}

void on_button3_clicked(GtkWidget *widget, gpointer data) {
    GtkWidget *new_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(new_window), "voicecall window");
    gtk_widget_set_size_request(new_window, 400, 300);
    gtk_widget_show_all(new_window);
}

void on_button4_clicked(GtkWidget *widget, gpointer data) {
    GtkWidget *new_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(new_window), "videocall window");
    gtk_widget_set_size_request(new_window, 400, 300);
    gtk_widget_show_all(new_window);
}

void on_button5_clicked(GtkWidget *widget, gpointer data) {
    GtkWidget *new_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(new_window), "scan for ip window");
    gtk_widget_set_size_request(new_window, 400, 300);
    gtk_widget_show_all(new_window);
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *window;
    GtkWidget *box;
    GtkWidget *button1, *button2, *button3, *button4, *button5, *button6;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Buttons Example");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_widget_set_size_request(window, 400, 300);

    GdkRGBA color;
    gdk_rgba_parse(&color, "blue");
    gtk_widget_override_background_color(window, GTK_STATE_FLAG_NORMAL, &color);

    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), box);

    button1 = gtk_button_new_with_label("Chat");
    button2 = gtk_button_new_with_label("File Transfer(nudes not allowed)");
    button3 = gtk_button_new_with_label("Voice Call");
    button4 = gtk_button_new_with_label("Video Call(nudidity is not allowed)");
    button5 = gtk_button_new_with_label("Scan for IP address");
    button6 = gtk_button_new_with_label("Quit");

    g_signal_connect(button6, "clicked", G_CALLBACK(on_quit_button_clicked), NULL);
    g_signal_connect(button1, "clicked", G_CALLBACK(on_button1_clicked), NULL);
    g_signal_connect(button2, "clicked", G_CALLBACK(on_file_button_clicked), NULL);
    g_signal_connect(button3, "clicked", G_CALLBACK(on_button3_clicked), NULL);
    g_signal_connect(button4, "clicked", G_CALLBACK(on_button4_clicked), NULL);
    g_signal_connect(button5, "clicked", G_CALLBACK(on_button5_clicked), NULL);

    gtk_box_pack_start(GTK_BOX(box), button1, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(box), button2, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(box), button3, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(box), button4, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(box), button5, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(box), button6, TRUE, TRUE, 0);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
