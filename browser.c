#include <gtk/gtk.h>
#include <webkit2/webkit2.h>

static void destroyWinCb(GtkWidget* widget, GtkWidget* window)
{
    gtk_main_quit();
}

static gboolean closeWebCb(WebKitWebView* webView, GtkWidget* window)
{
    gtk_widget_destroy(window);
    return TRUE;
}

int main(int argc, char* argv[])
{
    GtkWidget *win;
    WebKitWebView *web;
    gchar * url = "http://www.google.fr/";
 
    gtk_init(&argc, &argv);

    if (argc == 2)
        url = argv[1];

    win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(win), 1280, 720);

    web = WEBKIT_WEB_VIEW(webkit_web_view_new());

    gtk_container_add(GTK_CONTAINER(win), GTK_WIDGET(web));

    g_signal_connect(win, "destroy", G_CALLBACK(destroyWinCb), NULL);
    g_signal_connect(web, "close", G_CALLBACK(closeWebCb), win);

    webkit_web_view_load_uri(web, url);

    gtk_widget_grab_focus(GTK_WIDGET(web));

    gtk_widget_show_all(win);

    gtk_main();

    return 0;
}
