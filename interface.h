#ifndef __INTERFACE_H__
#define __INTERFACE_H__

#include <gtk/gtk.h>

#define UI_FILE "interface.glade"

GtkBuilder *builder;
GtkWidget *startWindow, *gameWindow, *msgWindow;
GtkEntry *textBox;
GtkButton *startButton, *exitButton, *checkButton, *againButton, *exitButton;
GtkLabel *gameMsg, *Label_category, *Label_hidden, *Label_word;
GtkImage *hangmanImage, *msgImage;

int start_interface();

#endif