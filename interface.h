#ifndef __INTERFACE_H__
#define __INTERFACE_H__

#include <gtk/gtk.h>

#define UI_FILE "interface.glade"

GtkBuilder *builder;
GtkWidget *startWindow, *gameWindow, *msgWindow;
GtkEntry *textBox;
GtkButton *startButton, *exitButton, *checkButton;
GtkLabel *hiddenWordLabel, *gameMsg, *gameLabel2, *gameLabel3; 
GtkImage *hangmanImage;

int start_interface(/*int argc, char *argv[]*/);

#endif