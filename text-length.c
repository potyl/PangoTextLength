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

	cairo_surface_t* surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 1024, 300);
	cairo_t *cr = cairo_create(surface);


	PangoLayout *layout = pango_cairo_create_layout(cr);
	pango_layout_set_text(layout, text, -1);

	PangoFontDescription *desc = pango_font_description_from_string(font_name);
	pango_layout_set_font_description(layout, desc);
	pango_font_description_free(desc);
	
	int width, height;
	pango_layout_get_pixel_size(layout, &width, &height);

	//int width = pango_layout_get_width(layout);
	g_print("Converting %s using font %s %dx%d\n", text, font_name, width, height);

	if (TRUE) {
		pango_cairo_show_layout(cr, layout);
		cairo_surface_write_to_png(surface, "a.png");
	}

	g_object_unref(layout);
	cairo_destroy(cr);
	cairo_surface_destroy(surface);
}
