#include <iostream>

#include <gtk/gtk.h>
#include <boost/filesystem.hpp>
#include "domain/ExploadingAtoms.h"
#include "domain/models/Coordinate.h"
#include "domain/ai/Minimax.h"

using namespace exploading_atoms;
using namespace exploading_atoms::ai;

GtkWidget *box;
GtkWidget *label;
GtkWidget *menu;
GtkWidget *window;
GtkWidget *grid;
GtkWidget *gridContainer;
GtkWidget ***images;
GtkWidget *progess;

ExploadingAtoms *exploadingAtoms = new ExploadingAtoms(8, 10);
Minimax *minimax = nullptr;

void onClick(GtkWidget *widget, Coordinate *data);

void destroy(GtkWidget *widget, gpointer data);

void newPlayerGame(GtkWidget *widget, gpointer data);

void newComputerGame(GtkWidget *widget, gpointer data);

void initImages();

void reloadGridImages();

void createGrid();

void createBox();

void createMenu();

std::string getImagePath(Field field);

std::string getPath();

std::string player_to_string(Player player);

int main(int argc, char **argv) {
    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    gtk_window_set_default_size(GTK_WINDOW(window), 640, 480);
    gtk_window_set_title(GTK_WINDOW(window), "Exploading Atoms");

    initImages();
    createGrid();
    createBox();

    GtkCssProvider *cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(cssProvider, (getPath() + "/res/style/style.css").c_str(), NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                                              GTK_STYLE_PROVIDER(cssProvider),
                                              GTK_STYLE_PROVIDER_PRIORITY_USER);

    gtk_container_add(GTK_CONTAINER(window), box);

    g_signal_connect(window, "destroy", G_CALLBACK(destroy), NULL);

    gtk_container_set_border_width(GTK_CONTAINER(window), 20);

    gtk_widget_show_all(window);

    gtk_main();

    delete exploadingAtoms;

    return 0;
}


void onClick(GtkWidget *widget, Coordinate *data) {
    exploadingAtoms->move(data->getX(), data->getY());
    reloadGridImages();

    if(exploadingAtoms->getWinner() == none)
        gtk_label_set_text(GTK_LABEL(label), ("Player on move: " + player_to_string(exploadingAtoms->getPlayerOnMove())).c_str());
    else
        gtk_label_set_text(GTK_LABEL(label), (player_to_string(exploadingAtoms->getWinner()) + " player wins!").c_str());

    int reds = exploadingAtoms->count(red);
    int blues = exploadingAtoms->count(blue);

    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(progess), (double)reds / (double)(reds + blues));

    if(minimax != nullptr) {
        Coordinate *coords = minimax->getNextMove(exploadingAtoms);
        exploadingAtoms->move(coords->getX(), coords->getY());
        reloadGridImages();

        if(exploadingAtoms->getWinner() == none)
            gtk_label_set_text(GTK_LABEL(label), ("Player on move: " + player_to_string(exploadingAtoms->getPlayerOnMove())).c_str());
        else
            gtk_label_set_text(GTK_LABEL(label), (player_to_string(exploadingAtoms->getWinner()) + " player wins!").c_str());

        reds = exploadingAtoms->count(red);
        blues = exploadingAtoms->count(blue);

        gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(progess), (double)reds / (double)(reds + blues));
    }
}

void destroy(GtkWidget *widget, gpointer data) {
    gtk_main_quit ();
}

void newPlayerGame(GtkWidget *widget, gpointer data) {
    minimax = nullptr;
    exploadingAtoms = new ExploadingAtoms(8, 10);
    reloadGridImages();
    gtk_label_set_text(GTK_LABEL(label), ("Player on move: " + player_to_string(exploadingAtoms->getPlayerOnMove())).c_str());
}

void newComputerGameF(GtkWidget *widget, gpointer data) {
    minimax = new Minimax();
    exploadingAtoms = new ExploadingAtoms(8, 10);
    reloadGridImages();
    gtk_label_set_text(GTK_LABEL(label), ("Player on move: " + player_to_string(exploadingAtoms->getPlayerOnMove())).c_str());
}

void initImages() {

    //TODO: cleanup the old images...

    images = new GtkWidget**[exploadingAtoms->getRows()];
    for (int i = 0; i < exploadingAtoms->getRows(); i++) {
        images[i] = new GtkWidget*[exploadingAtoms->getColumns()];
        for (int j = 0; j < exploadingAtoms->getColumns(); j++) {
            images[i][j] = gtk_image_new_from_file(
                    getImagePath(exploadingAtoms->getField(j, i)).c_str()
            );
        }
    }
}

void reloadGridImages() {
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(progess), 0.5);
    initImages();

    for (int i = 0; i < exploadingAtoms->getColumns(); i++) {
        for (int j = 0; j < exploadingAtoms->getRows(); j++) {
            GtkWidget *button = gtk_grid_get_child_at(GTK_GRID(grid), i, j);
            gtk_button_set_image(GTK_BUTTON(button), images[j][i]);
        }
    }
}

void createGrid() {
    gridContainer = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    grid = gtk_grid_new();

    for (int i = 0; i < exploadingAtoms->getColumns(); i++) {
        for (int j = 0; j < exploadingAtoms->getRows(); j++) {
            GtkWidget *button = gtk_button_new();

            gtk_button_set_always_show_image (GTK_BUTTON (button), TRUE);
            gtk_button_set_image(GTK_BUTTON(button), images[j][i]);
            gtk_widget_set_name(button, "grid");

            g_signal_connect(button, "clicked", G_CALLBACK(onClick), new Coordinate(i, j));
            gtk_grid_attach(GTK_GRID(grid), button, i, j, 1, 1);
        }
    }
    gtk_box_set_center_widget(GTK_BOX(gridContainer), grid);
}

std::string player_to_string(Player player) {
    return player == red ? "Red" : "Blue";
}

void createBox() {
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    label = gtk_label_new(("Player on move: " + player_to_string(exploadingAtoms->getPlayerOnMove())).c_str());
    createMenu();
    gtk_container_add(GTK_CONTAINER(box), label);
    gtk_container_add(GTK_CONTAINER(box), gridContainer);
}

void createMenu() {
    menu = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    GtkWidget *buttons = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);

    gtk_widget_set_name(buttons, "menu-container");
    gtk_widget_set_name(menu, "menu");

    GtkWidget *newPvpGame = gtk_button_new_with_label("Player vs Player");
    GtkWidget *newComputerGame = gtk_button_new_with_label("Player vs Computer");

    g_signal_connect(newPvpGame, "clicked", G_CALLBACK(newPlayerGame), NULL);
    g_signal_connect(newComputerGame, "clicked", G_CALLBACK(newComputerGameF), NULL);

    gtk_container_add(GTK_CONTAINER(buttons), newPvpGame);
    gtk_container_add(GTK_CONTAINER(buttons), newComputerGame);

    gtk_box_set_center_widget(GTK_BOX(menu), buttons);

    gtk_container_add(GTK_CONTAINER(box), menu);

    progess = gtk_progress_bar_new();
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(progess), 0.5);
    gtk_container_add(GTK_CONTAINER(box), progess);
}

std::string getPath() {
    boost::filesystem::path full_path(boost::filesystem::current_path());
    return full_path.string();
}

std::string getImagePath(Field field) {
    std::string PATH = getPath();

    if(field.getPlayer() == red) {
        if(field.getAmount() == 1)
            return PATH + "/res/red_1.png";
        else if(field.getAmount() == 2)
            return PATH + "/res/red_2.png";
        else if(field.getAmount() == 3)
            return PATH + "/res/red_3.png";
    } else if(field.getPlayer() == blue) {
        if(field.getAmount() == 1)
            return PATH + "/res/blue_1.png";
        else if(field.getAmount() == 2)
            return PATH + "/res/blue_2.png";
        else if(field.getAmount() == 3)
            return PATH + "/res/blue_3.png";
    }

    return PATH + "/res/empty.png";
}