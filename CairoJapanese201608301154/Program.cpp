#include <gtk-2.0/gtk/gtk.h>
#include <cairo.h>
#include <glib.h>

gboolean expose_event_callback(GtkWidget *widget, GdkEventExpose *event, gpointer data)
{
	cairo_t *cr;
	cr = gdk_cairo_create(widget->window);
	
	cairo_select_font_face (cr, "Serif", CAIRO_FONT_SLANT_NORMAL,
		CAIRO_FONT_WEIGHT_BOLD);
	cairo_set_font_size(cr, 24);
	cairo_move_to(cr, 30, 30);
	cairo_show_text(cr, "Hello Cairo !!");
	cairo_move_to(cr, 30, 100);
	//cairo_show_text(cr, "こんにちはカイロ！");

	GError*  error = NULL;
	gchar* cp932 = "こんにちは　カイロ！";
	gchar* utf8 = g_convert(cp932, -1, "utf-8", "cp932", NULL, NULL, &error);
	if (utf8 == NULL) {
		g_print("%s\n", error->message);
		gint retval = error->code;
		g_error_free(error);
		g_free(utf8);
		return retval;
	}
	cairo_show_text(cr, utf8);
	g_free(utf8);

	cairo_destroy(cr);
	return FALSE;
}
int main(int argc, char* argv[])
{
	gtk_set_locale();
	gtk_init(&argc, &argv);

	GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Hello Cairo !! (GTK+, WindowsXP, VC++2010Express)");
	gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

	GtkWidget *drawing_area = gtk_drawing_area_new();
	gtk_widget_set_size_request (drawing_area, 100, 100);
	gtk_container_add(GTK_CONTAINER(window), drawing_area);
	g_signal_connect(G_OBJECT(drawing_area), "expose_event", G_CALLBACK(expose_event_callback), NULL);
	
	gtk_widget_show_all(window);
	gtk_main();
	return 0;
}