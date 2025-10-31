#include <assert.h>
#include <cairo-pdf.h>
#include <cairo.h>
#include <pango/pangocairo.h>

#define _(X) assert(CAIRO_STATUS_SUCCESS==X);

cairo_surface_t *surface = NULL;
cairo_t *cr = NULL;

void new() {

	// create pdf surface
	surface = cairo_pdf_surface_create("/home/darren/Desktop/ugpc.pdf", 595, 842);
	_(cairo_surface_status(surface));
	assert(CAIRO_SURFACE_TYPE_PDF == cairo_surface_get_type(surface));

	// create drawing context
	cr = cairo_create(surface);

}

void draw() {

	// background
	cairo_set_source_rgb(cr, 1, 1, 1);
	cairo_paint(cr);

	// rectangle
	cairo_set_source_rgb(cr, 0, 0, 0);
	cairo_rectangle(cr, 100, 100, 10, 10);
	cairo_fill(cr);
	//cairo_paint(cr);

}

void delete() {
	cairo_destroy(cr);
	cr = NULL;
	cairo_surface_destroy(surface);
	surface = NULL;
}

int main() {

	new();

	draw();

	delete();

}

