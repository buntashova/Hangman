#ifndef __INTERFACE_H__
#define __INTERFACE_H__

#include <gtk/gtk.h>

#define UI_FILE "interface.glade"

GtkBuilder *builder;
GtkWidget *startWindow, *gameWindow, *msgWindow;
GtkButton *startButton, *exitButton;
GtkLabel *hiddenWordLabel, *gameMsg;
GtkImage *hangmanImage;
int start_interface(/*int argc, char *argv[]*/);

#endif