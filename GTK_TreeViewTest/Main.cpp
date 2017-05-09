//////////////////////////////////////////////////////////////////////////
//TreeView ʹ��MVC�ṹ
//////////////////////////////////////////////////////////////////////////

#include "map.h"
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" ) //����cmd����

vector<string> Ivec;
GtkWidget *gpWinMain=NULL;

enum {INT_COL=0,TEXT_COL};
typedef struct
{
	int ID;
	char Name[5];
}stuUser;
int main( int argc,char *argv[] ){

	InitializeGTK(argc,argv);

	return 0;
} 
int InitializeGTK(int argc,char *argv[] )
{
	gtk_init (&argc, &argv);//��ʼ��

	GtkBuilder *builder;
	GtkWidget *window;  //����һ��widget
	GError     *err=NULL; 

	builder = gtk_builder_new ();  //new widget

	if (gtk_builder_add_from_file (builder,".\\glade\\winTreeViewTest.glade", &err) == 0) //���ļ�����glade
	{
		g_error_free (err);

		return false;
	}
	window = GTK_WIDGET(gtk_builder_get_object(builder, "winMain"));  //��ȡ����
	g_object_set_data(G_OBJECT(window),"winMain",window);


	g_signal_connect(G_OBJECT(window),"destroy",
		G_CALLBACK(destroy),NULL);

	g_signal_connect(G_OBJECT(window),"delete_event",
		G_CALLBACK(delete_event),NULL);

	GtkWidget *pwidget;

	pwidget=GTK_WIDGET(gtk_builder_get_object(builder,"TvUser"));//��ȡ�ؼ�
	g_object_set_data(G_OBJECT(window),"TvUser",pwidget);
	gtk_tree_view_set_grid_lines(GTK_TREE_VIEW(pwidget),GTK_TREE_VIEW_GRID_LINES_BOTH); //�б����������

	init_list(pwidget);
	add_to_list(pwidget,"1","��һ��");
	add_to_list(pwidget,"1","�ڶ���");


	GtkWidget *lblShow=GTK_WIDGET(gtk_builder_get_object(builder,"lblShow"));//��ȡ�ؼ�
	g_object_set_data(G_OBJECT(window),"lblShow",lblShow);

	GtkTreeSelection *selection;
	selection=gtk_tree_view_get_selection(GTK_TREE_VIEW(pwidget));
	g_signal_connect(G_OBJECT(selection),"changed",
		G_CALLBACK(selection_changed),lblShow);

	pwidget=GTK_WIDGET(gtk_builder_get_object(builder,"btnTest"));//��ȡ�ؼ�
	g_signal_connect(G_OBJECT(pwidget),"clicked",
		G_CALLBACK(btnTest_clicked),NULL);

	gpWinMain=window;

	gtk_window_set_title(GTK_WINDOW(window),"TreeView Test");
	//gtk_window_set_icon(GTK_WINDOW(window),create_pixbuf(".\\Pic\\psu.jpg"));
	gtk_window_set_default_size(GTK_WINDOW(window),200,200);
	gtk_widget_show   (window);  //show����
	gtk_main ();  //ִ��gtk main����

	return 0;
}
void btnTest_clicked(GtkButton *button,gpointer data)
{
	GtkWidget *treeView;
	GtkTreeSelection *selection;
	GtkTreeModel *model; 
	GtkTreeIter iter; 
	GtkLabel *label; 
	gchar *active; 

	treeView=(GtkWidget*)(g_object_get_data(G_OBJECT(gpWinMain),"TvUser"));//��ȡ�ؼ�
	model = gtk_tree_view_get_model(GTK_TREE_VIEW(treeView)); 
	selection=gtk_tree_view_get_selection(GTK_TREE_VIEW(treeView));
	gtk_tree_selection_get_selected(selection, &model, &iter); 
	gtk_tree_model_get(model, &iter, 1, &active, -1); 

	label=(GtkLabel*)(g_object_get_data(G_OBJECT(gpWinMain),"lblShow"));//��ȡ�ؼ�
	gtk_label_set_text(label, active);
}
void quick_message(gchar *message,int showTYpe)
{
	GtkWidget *dialog,*label,*content_area;
	switch (showTYpe)
	{
	case 1:
		dialog=gtk_dialog_new_with_buttons("title",
			GTK_WINDOW(gpWinMain),
			GTK_DIALOG_MODAL,  //GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
			GTK_STOCK_OK,
			GTK_RESPONSE_NONE,
			NULL);
		break;
	case 2:
		dialog=gtk_dialog_new_with_buttons("title",
			GTK_WINDOW(gpWinMain),
			GTK_DIALOG_MODAL,  //GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
			GTK_STOCK_OK,
			GTK_RESPONSE_ACCEPT,
			GTK_STOCK_CANCEL,
			GTK_RESPONSE_REJECT,
			NULL);
	}
	content_area=gtk_dialog_get_content_area(GTK_DIALOG(dialog));
	label=gtk_label_new(message);
	g_signal_connect_swapped(dialog,"response",G_CALLBACK(gtk_widget_destroy),dialog);
	gtk_container_add(GTK_CONTAINER (content_area),label);
	gtk_widget_set_size_request(dialog,300,150);
	gtk_widget_show_all(dialog);
}
static void init_list(GtkWidget *pwidget)
{
	//����View
	GtkCellRenderer *render=gtk_cell_renderer_text_new();
	GtkTreeViewColumn *column;
	column=gtk_tree_view_column_new_with_attributes("ID",render,"text",0,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(pwidget),column);

	column=gtk_tree_view_column_new_with_attributes("Name",render,"text",1,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(pwidget),column);
	//View����

	//����Model
	GtkListStore *store;
	store=gtk_list_store_new(2,G_TYPE_STRING,G_TYPE_STRING);
	gtk_tree_view_set_model(GTK_TREE_VIEW(pwidget),GTK_TREE_MODEL(store));
	g_object_unref(store);// model ���Զ������٣����ͷ��ڴ�ռ䡣
	//Model����
}

static void add_to_list(GtkWidget *list,const gchar *num,const gchar *str)
{
	GtkListStore *store;
	GtkTreeIter iter;

	store=GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(list)));

	//�������

	const gchar *s;
	s=g_locale_to_utf8(str,-1,NULL,NULL,NULL);
	gtk_list_store_append(store,&iter);
	gtk_list_store_set(store,&iter,0,num,1,s,-1);
	//������ݽ���
}
gboolean selection_changed(GtkTreeSelection *selection, GtkLabel *label) { 
	GtkTreeView *treeView; 
	GtkTreeModel *model; 
	GtkTreeIter iter; 
	gchar *active; 

	treeView = gtk_tree_selection_get_tree_view(selection); 
	model = gtk_tree_view_get_model(treeView); 
	gtk_tree_selection_get_selected(selection, &model, &iter); 
	gtk_tree_model_get(model, &iter, 
		1, &active, 
		-1); 

	//gtk_label_set_text(label, active); 

	return true;
} 
void destroy(GtkWidget *window,gpointer data)
{
	gtk_main_quit();//�����˳�
}

gboolean delete_event(GtkWidget *window,GdkEvent *event,gpointer data)
{
	return false;
}