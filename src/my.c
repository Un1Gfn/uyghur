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


void background() {
	cairo_set_source_rgb(cr, 1, 1, 1); // white
	cairo_paint(cr);
}

void grid() {

	// black
	cairo_set_source_rgb(cr, 0, 0, 0);

	// horizontal
	cairo_move_to(cr, 595, 100); cairo_rel_line_to(cr, -500, 0);
	cairo_move_to(cr, 595, 200); cairo_rel_line_to(cr, -500, 0);
	cairo_move_to(cr, 595, 300); cairo_rel_line_to(cr, -500, 0);
	cairo_move_to(cr, 595, 400); cairo_rel_line_to(cr, -500, 0);
	cairo_move_to(cr, 595, 500); cairo_rel_line_to(cr, -500, 0);
	cairo_move_to(cr, 595, 600); cairo_rel_line_to(cr, -500, 0);
	cairo_move_to(cr, 595, 700); cairo_rel_line_to(cr, -500, 0);
	cairo_move_to(cr, 595, 800); cairo_line_to(cr, 95, 800);
	cairo_fill(cr);

	// verticle
	cairo_move_to(cr, 495, 0); cairo_rel_line_to(cr, 0, 800);
	cairo_move_to(cr, 395, 0); cairo_rel_line_to(cr, 0, 800);
	cairo_move_to(cr, 295, 0); cairo_rel_line_to(cr, 0, 800);
	cairo_move_to(cr, 195, 0); cairo_rel_line_to(cr, 0, 800);
	cairo_move_to(cr,  95, 0); cairo_rel_line_to(cr, 0, 800);
	cairo_fill(cr);

}

void rect() {
	cairo_set_source_rgb(cr, 0, 0, 0);
	cairo_rectangle(cr, 100, 100, 10, 10);
	cairo_fill(cr);
}

void text() {

}

void delete() {
	cairo_destroy(cr);
	cr = NULL;
	cairo_surface_destroy(surface);
	surface = NULL;
}

int main() {

	new();

	background();

	grid();

	delete();

}

