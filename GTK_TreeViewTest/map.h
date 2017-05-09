#include <gtk/gtk.h>
#include <string>
#include <vector>

using namespace std;

int InitializeGTK(int argc,char *argv[] );
void destroy(GtkWidget *window,gpointer data);
gboolean delete_event(GtkWidget *window,GdkEvent *event,gpointer data);
gboolean selection_changed(GtkTreeSelection *selection, GtkLabel *label);

static void init_list(GtkWidget *pwidget);
static void add_to_list(GtkWidget *list,const gchar *num,const gchar *str);
void btnTest_clicked(GtkButton *button,gpointer data);
void quick_message(gchar *message,int showTYpe);