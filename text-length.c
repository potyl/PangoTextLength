#include <pango/pango.h>
#include <glib/glib.h>
#include <pango/pangocairo.h>
#include <cairo/cairo.h>

static void compute_text_length (char *font, char *text, int *width, int *height);

int main (int argc, char **argv) {
	
	if (argc != 3) {
		g_print("Usage: font text\n");
		g_print("Usage: font text [filename]\n");
		return 1;
	}
	char *font = argv[1];
	char *text = argv[2];

	
	g_type_init();

	int width, height;
	compute_text_length(font, text, &width, &height);
	g_print("Converting %s using font %s %dx%d\n", text, font, width, height);

	return 0;
}


static void compute_text_length (char *font, char *text, int *width, int *height) {

	cairo_surface_t* surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 0, 0);
	cairo_t *cr = cairo_create(surface);


	PangoLayout *layout = pango_cairo_create_layout(cr);
	pango_layout_set_text(layout, text, -1);

	PangoFontDescription *desc = pango_font_description_from_string(font);
	pango_layout_set_font_description(layout, desc);
	pango_font_description_free(desc);
	
	pango_layout_get_pixel_size(layout, width, height);

	if (FALSE) {
		pango_cairo_show_layout(cr, layout);
		cairo_surface_write_to_png(surface, "a.png");
	}

	g_object_unref(layout);
	cairo_destroy(cr);
	cairo_surface_destroy(surface);
}
