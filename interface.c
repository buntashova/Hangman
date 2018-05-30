#include "interface.h"

int start_interface(int argc, char *argv[])
{
    GError *error = NULL;

    gtk_init(&argc, &argv);
    builder = gtk_builder_new();
    if (!gtk_builder_add_from_file(builder, UI_FILE, &error))
    {
        printf("Interface file \"%s\" not found.", UI_FILE);
        GtkWidget *errMsg = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE, "Error");
        gtk_message_dialog_format_secondary_text(GTK_MESSAGE_DIALOG (errMsg), "Interface file \"%s\" not found.", UI_FILE);
        gtk_dialog_run(GTK_DIALOG(errMsg));
        return 1;
    }

    startWindow = GTK_WIDGET(gtk_builder_get_object(builder, "startWindow"));
    gameWindow = GTK_WIDGET(gtk_builder_get_object(builder, "gameWindow"));
    msgWindow = GTK_WIDGET(gtk_builder_get_object(builder, "msgWindow"));

    startButton = GTK_BUTTON(gtk_builder_get_object(builder, "startButton"));
    exitButton = GTK_BUTTON(gtk_builder_get_object(builder, "exitButton"));

    hiddenWordLabel = GTK_LABEL(gtk_builder_get_object(builder, "hiddenWordLabel"));
    gameMsg = GTK_LABEL(gtk_builder_get_object(builder, "gameMsg"));
    hangmanImage = GTK_IMAGE(gtk_builder_get_object(builder, "hangmanImage"));

    gtk_builder_connect_signals(builder, NULL);
    g_object_unref(G_OBJECT(builder));
    gtk_widget_show(startWindow);
    gtk_main();

    return 0;
}
