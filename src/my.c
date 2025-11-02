/*
export L=pango,cairo,pangocairo; b() { gcc -Wall -Wextra -O0 -Og -std=gnu23 $(pkg-config --cflags $L) my.c $(pkg-config --libs $L) -o my.out; }; r() { ./my.out; };
*/

#include <assert.h>
#include <cairo-pdf.h>
#include <cairo.h>
#include <pango/pangocairo.h>
#include <pango/pango-font.h>

#define W 595
#define H 842

#define _(X) assert(CAIRO_STATUS_SUCCESS==X);

cairo_surface_t *surface = NULL;
cairo_t *cr = NULL;

PangoFontDescription *desc = NULL;

void new() {
	surface = cairo_pdf_surface_create("/home/darren/Desktop/ugpc.pdf", W, H);
	_(cairo_surface_status(surface));
	assert(CAIRO_SURFACE_TYPE_PDF == cairo_surface_get_type(surface));
	cr = cairo_create(surface);
	desc = pango_font_description_from_string("Noto Serif Old Uyghur Regular 27");
}

void delete() {
	pango_font_description_free(desc);
	desc = NULL;
	cairo_destroy(cr);
	cr = NULL;
	cairo_surface_destroy(surface);
	surface = NULL;
}

void bg() {
	cairo_set_source_rgb(cr, 1, 1, 1);
	cairo_paint(cr);
}

void grid() {
	// horizontal
	cairo_move_to(cr, W, 100); cairo_rel_line_to(cr, -500, 0);
	cairo_move_to(cr, W, 200); cairo_rel_line_to(cr, -500, 0);
	cairo_move_to(cr, W, 300); cairo_rel_line_to(cr, -500, 0);
	cairo_move_to(cr, W, 400); cairo_rel_line_to(cr, -500, 0);
	cairo_move_to(cr, W, 500); cairo_rel_line_to(cr, -500, 0);
	cairo_move_to(cr, W, 600); cairo_rel_line_to(cr, -500, 0);
	cairo_move_to(cr, W, 700); cairo_rel_line_to(cr, -500, 0);
	cairo_move_to(cr, W, 800); cairo_line_to(cr, W-500, 800);
	// verticle
	cairo_move_to(cr, W-100, 0); cairo_rel_line_to(cr, 0, 800);
	cairo_move_to(cr, W-200, 0); cairo_rel_line_to(cr, 0, 800);
	cairo_move_to(cr, W-300, 0); cairo_rel_line_to(cr, 0, 800);
	cairo_move_to(cr, W-400, 0); cairo_rel_line_to(cr, 0, 800);
	cairo_move_to(cr, W-500, 0); cairo_rel_line_to(cr, 0, 800);
	// draw
	cairo_set_source_rgb(cr, 1, 0, 0);
	cairo_fill(cr);
}

void rect() {
	cairo_set_source_rgb(cr, 0, 0, 0);
	cairo_rectangle(cr, 100, 100, 10, 10);
	cairo_fill(cr);
}

void text() {

	int w = -1;

	PangoLayout *layout = pango_cairo_create_layout(cr);
	pango_layout_set_font_description(layout, desc);
	cairo_set_source_rgb(cr, 0, 0, 0);

	cairo_move_to(cr, W-200, 400);
	pango_layout_set_text(layout, "\u0626 \u06c7 \u064a \u063a \u06c7 \u0631", -1);
	pango_layout_get_size(layout, &w, NULL);
	printf("%d = %d\n", __LINE__, w);
	pango_cairo_show_layout(cr, layout);
	//pango_cairo_update_layout(cr, layout);

	cairo_move_to(cr, W-200, 300);
	pango_layout_set_text(layout, "twinkle twinkle little star", -1);
	pango_layout_get_size(layout, &w, NULL);
	printf("%d = %d\n", __LINE__, w);
	pango_cairo_show_layout(cr, layout);

	cairo_move_to(cr, W-200, 200);
	pango_layout_set_text(layout, "\u0626\u06c7\u064a\u063a\u06c7\u0631", -1);
	pango_layout_get_size(layout, &w, NULL);
	printf("%d = %d\n", __LINE__, w);
	pango_cairo_show_layout(cr, layout);

}

int main() {
	new();
	bg();
	grid();
	text();
	delete();
	return 0;
}
