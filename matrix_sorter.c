#include<stdio.h>
#include<gtk/gtk.h>
#include<string.h>

static int a[4][4];
static GtkWidget* wid[4][4],*window;

void solve();
void solve2();

static void get_element(GtkWidget* widget,gpointer data)
{
	for(int i=0;i<4;i++)
        {
                for(int j=0;j<4;j++)
                {
                        a[i][j]=atoi(gtk_entry_get_text(GTK_ENTRY(wid[i][j])));
                }
	
	}
	
	solve();
}

static void get_element2(GtkWidget* widget,gpointer data)
{
	for(int i=0;i<4;i++)
        {
                for(int j=0;j<4;j++)
                {
                        a[i][j]=atoi(gtk_entry_get_text(GTK_ENTRY(wid[i][j])));
                }
	
	}
	
	solve2();
}

static void menu_response(GtkWidget* menu_item,gpointer data)
{
        if(strcmp(gtk_menu_item_get_label(GTK_MENU_ITEM(menu_item)),"New")==0)
        {
                for(int i=0;i<4;i++)
                        for(int j=0;j<4;j++)
                        {
                                a[i][j]=0;
                                gtk_entry_set_text(GTK_ENTRY(wid[i][j]),"0");
                        }
        }

	
	else if(strcmp(gtk_menu_item_get_label(GTK_MENU_ITEM(menu_item)),"Exit")==0)
        {
                gtk_main_quit();
        }

}

void solve()
{
	int i, j, k, l, tmp;	
	for (i = 0; i < 4; i++) 
	{
                for (j = 0; j < 4; j++) 
		{
                        tmp = a[i][j];
                        l = j + 1;
                        for (k = i; k < 4; k++) 
			{
                                while (l < 4) 
				{
                                        /* swapping the data */
                                        if (tmp < a[k][l]) 
					{
                                                tmp = a[k][l];
                                                a[k][l] = a[i][j];
                                                a[i][j] = tmp;
                                        }
                                        l++;
                                }
                                l = 0;
                        }
                }
        }

	for(int i=0;i<4;i++)
                {
                        for(int j=0;j<4;j++)
                        {
                                char c[2];
                                sprintf(c,"%d",a[i][j]);
                                gtk_entry_set_text(GTK_ENTRY(wid[i][j]),c);
                        }
                }

	

}

void solve2()
{
	int i, j, k, l, n, tmp;	
	for (i = 0; i < 4; i++) 
	{
                for (j = 0; j < 4; j++) 
		{
                        tmp = a[i][j];
                        l = j + 1;
                        for (k = i; k < 4; k++) 
			{
                                while (l < 4) 
				{
                                        /* swapping the data */
                                        if (tmp > a[k][l]) 
					{
                                                tmp = a[k][l];
                                                a[k][l] = a[i][j];
                                                a[i][j] = tmp;
                                        }
                                        l++;
                                }
                                l = 0;
                        }
                }
        }

	for(int i=0;i<4;i++)
                {
                        for(int j=0;j<4;j++)
                        {
                                char d[2];
                                sprintf(d,"%d",a[i][j]);
                                gtk_entry_set_text(GTK_ENTRY(wid[i][j]),d);
                        }
                }

	

}

int main(int argc,char* argv[])
{
	for(int i=0;i<4;i++)
                for(int j=0;j<4;j++)
                        a[i][j]=0; 	

	const char* file[] = {"New","Exit"};
        gtk_init(&argc,&argv);
        GtkWidget *vbox,*hbox,*separator,*button,*button2,*menu_item,*file_menu,*help_menu,*menu_bar;
	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);        
	vbox=gtk_vbox_new(0,0);
        
        file_menu=gtk_menu_new();
        menu_bar=gtk_menu_bar_new();
        menu_item=gtk_menu_item_new_with_label("File");
     	gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_item),file_menu);
        gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar),menu_item);
	
        for(int i=0;i<2;i++)
        {
                menu_item=gtk_menu_item_new_with_label(file[i]);
                gtk_menu_shell_append(GTK_MENU_SHELL(file_menu),menu_item);
                g_signal_connect(menu_item,"activate",G_CALLBACK(menu_response),NULL);
        }
        
	gtk_box_pack_start(GTK_BOX(vbox),menu_bar,0,0,0);

	
	for(int i=0;i<4;i++)
	{
		hbox=gtk_hbox_new(0,0);
		for(int j=0;j<4;j++)
		{
			wid[i][j]=gtk_entry_new();
			gtk_entry_set_max_length(GTK_ENTRY(wid[i][j]),2);
			gtk_widget_set_size_request(wid[i][j],70,70);
			gtk_box_pack_start((GTK_BOX(hbox)),wid[i][j],0,0,0);
			if(j%j==0)
			{
				separator=gtk_vseparator_new();
				gtk_box_pack_start(GTK_BOX(hbox),separator,0,0,0);
			}
			
		}

		
			gtk_box_pack_start(GTK_BOX(vbox),hbox,0,0,0);
			if(i%i==0)
			{
				separator=gtk_hseparator_new();
				gtk_box_pack_start(GTK_BOX(vbox),separator,0,0,0);
			}
	}
	
	button=gtk_button_new_with_label("Sort the matrix in descending order");
	g_signal_connect(button,"clicked",G_CALLBACK(get_element),NULL);
	gtk_box_pack_start(GTK_BOX(vbox),button,0,0,0);	
	button2=gtk_button_new_with_label("Sort the matrix in ascending order");
	g_signal_connect(button2,"clicked",G_CALLBACK(get_element2),NULL);
	gtk_box_pack_start(GTK_BOX(vbox),button2,0,0,0);	
	g_signal_connect(window,"delete_event",G_CALLBACK(gtk_main_quit),NULL);
	gtk_container_add(GTK_CONTAINER(window),vbox);
	gtk_widget_set_size_request(window,290,400);
	gtk_window_set_title(GTK_WINDOW(window),"~=~=~=~=~=~ _MATRIX SORTER_ ~=~=~=~=~=~ ");	
	gtk_widget_show_all(window);
	gtk_main();
	
return 0;
}	
