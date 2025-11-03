/*
export A=fourline L=cairo; B() { gcc -Wall -Wextra -O0 -Og -std=gnu23 $(pkg-config --cflags $L) -DPDF="\"$A.pdf\"" $A.c $(pkg-config --libs $L) -o $A.out; }; R() { env O=$A.pdf ./$A.out; };
*/

#include <assert.h>
#include <cairo-pdf.h>
#include <cairo.h>
#include <stdio.h>

//#define W 842
//#define H 1191

#define W 1191
#define H 842

#define _(X) assert(CAIRO_STATUS_SUCCESS==X);

cairo_surface_t *surface = NULL;
cairo_t *cr = NULL;

void new() {
	surface = cairo_pdf_surface_create(PDF, W, H);
	_(cairo_surface_status(surface));
	assert(CAIRO_SURFACE_TYPE_PDF == cairo_surface_get_type(surface));
	cr = cairo_create(surface);
}

void delete() {
	cairo_destroy(cr);
	cr = NULL;
	cairo_surface_destroy(surface);
	surface = NULL;
}

void bg() {
	cairo_set_source_rgb(cr, 1, 1, 1);
	cairo_paint(cr);
}

void size() {
	// top baseline
	double y = 200;
	cairo_set_line_width(cr, .05);
	cairo_move_to(cr, 0, y);
	cairo_rel_line_to(cr, W, 0);
	cairo_stroke(cr);
	// lines
	for (int h=50; h<=200; h+=5) {
		y += (double)h/10;
		cairo_move_to(cr, 0, y);
		cairo_rel_line_to(cr, W, 0);
		if (0==h%25)
			cairo_set_source_rgb(cr, 0, 0, 0);
		else
			cairo_set_source_rgb(cr, .7, .7, .7);
		cairo_stroke(cr);
	}
	//cairo_fill(cr);
	//cairo_get_current_point(cr, NULL, &y);
	//cairo_stroke(cr);
}

int main() {
	new();
	bg();
	size();
	delete();
	return 0;
}

