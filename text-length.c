#include <pango/pango.h>
#include <glib/glib.h>
#include <pango/pangocairo.h>
#include <cairo/cairo.h>

static void compute_text_length (gchar *font_name, gchar *text);

int main (int argc, char **argv) {
	
	if (argc != 3) {
		g_print("Usage: font text\n");
		return 1;
	}
	char *font_name = argv[1];
	char *text = argv[2];

	
	g_type_init();
	compute_text_length(font_name, text);

	return 0;
}


static void compute_text_length (char *font_name, char *text) {

	PangoFontMap *fontmap = pango_cairo_font_map_get_default();
	PangoContext *context = pango_font_map_create_context(fontmap);

//	PangoContext *context = pango_context_new();
	PangoFontDescription *desc = pango_font_description_from_string(font_name);
	pango_context_set_font_description(context, desc);
	PangoLayout *layout = pango_layout_new(context);
	pango_layout_set_text(layout, text, -1);
	pango_layout_set_font_description(layout, desc);
	
	int width, height;
	pango_layout_get_pixel_size(layout, &width, &height);

	//int width = pango_layout_get_width(layout);
	g_print("Converting %s: %s length: %d\n", font_name, text, width);

	pango_font_description_free(desc);
	g_object_unref(context);
}
