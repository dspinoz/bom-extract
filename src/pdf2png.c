/*
	How to use MuPDF to render a single page and save as a.png

	./pdf2png.exe document.pdf 100 0 1
*/

#include <mupdf/fitz.h>

int main(int argc, char **argv)
{
	char *input;
	float zoom, rotate;
	int page_number, page_count;
	fz_context *ctx;
	fz_document *doc;
	fz_pixmap *pix;
	fz_matrix ctm;
	int x, y;

	if (argc < 3)
	{
		fprintf(stderr, "usage: example input-file page-number [ zoom [ rotate ] ]\n");
		fprintf(stderr, "\tinput-file: path of PDF, XPS, CBZ or EPUB document to open\n");
		fprintf(stderr, "\tPage numbering starts from one.\n");
		fprintf(stderr, "\tZoom level is in percent (100 percent is 72 dpi).\n");
		fprintf(stderr, "\tRotation is in degrees clockwise.\n");
		return EXIT_FAILURE;
	}

	input = argv[1];
	page_number = atoi(argv[2]) - 1;
	zoom = argc > 3 ? atof(argv[3]) : 600; // add more zoom to increase dpi
	rotate = argc > 4 ? atof(argv[4]) : 0;

	/* Create a context to hold the exception stack and various caches. */
	ctx = fz_new_context(NULL, NULL, FZ_STORE_UNLIMITED);
	if (!ctx)
	{
		fprintf(stderr, "cannot create mupdf context\n");
		return EXIT_FAILURE;
	}

	/* Register the default file types to handle. */
	fz_try(ctx)
		fz_register_document_handlers(ctx);
	fz_catch(ctx)
	{
		fprintf(stderr, "cannot register document handlers: %s\n", fz_caught_message(ctx));
		fz_drop_context(ctx);
		return EXIT_FAILURE;
	}

	/* Open the document. */
	fz_try(ctx)
		doc = fz_open_document(ctx, input);
	fz_catch(ctx)
	{
		fprintf(stderr, "cannot open document: %s\n", fz_caught_message(ctx));
		fz_drop_context(ctx);
		return EXIT_FAILURE;
	}

	/* Count the number of pages. */
	fz_try(ctx)
		page_count = fz_count_pages(ctx, doc);
	fz_catch(ctx)
	{
		fprintf(stderr, "cannot count number of pages: %s\n", fz_caught_message(ctx));
		fz_drop_document(ctx, doc);
		fz_drop_context(ctx);
		return EXIT_FAILURE;
	}

	if (page_number < 0 || page_number >= page_count)
	{
		fprintf(stderr, "page number out of range: %d (page count %d)\n", page_number + 1, page_count);
		fz_drop_document(ctx, doc);
		fz_drop_context(ctx);
		return EXIT_FAILURE;
	}

	/* Compute a transformation matrix for the zoom and rotation desired. */
	/* The default resolution without scaling is 72 dpi. */
  // TBD make at least 300dpi, better for OCR
	fz_scale(&ctm, zoom / 100, zoom / 100);
	fz_pre_rotate(&ctm, rotate);

	/* Render page to an RGB pixmap. */
	//pix = fz_new_pixmap_from_page_number(ctx, doc, page_number, &ctm, fz_device_rgb(ctx));
  
	fz_page *page;
	//fz_pixmap *pix;
  fz_colorspace *cs = fz_device_rgb(ctx);

	page = fz_load_page(ctx, doc, page_number);
  
	fz_rect rect;
	fz_irect irect;
	fz_device *dev;

	fz_bound_page(ctx, page, &rect);
	fz_transform_rect(&rect, &ctm);
	fz_round_rect(&irect, &rect);

	pix = fz_new_pixmap_with_bbox(ctx, cs, &irect);
  fz_clear_pixmap_with_value(ctx, pix, 0xFF);
          
	fz_try(ctx)
	{
		dev = fz_new_draw_device(ctx, pix);
		fz_run_page(ctx, page, dev, &ctm, NULL);
	}
	fz_always(ctx)
	{
		fz_drop_device(ctx, dev);
		fz_drop_page(ctx, page);
	}
	fz_catch(ctx)
	{
		fz_drop_pixmap(ctx, pix);
		fprintf(stderr, "cannot render page: %s\n", fz_caught_message(ctx));
		fz_drop_document(ctx, doc);
		fz_drop_context(ctx);
		return EXIT_FAILURE;
	}
  
  /* write as png */
  fz_save_pixmap_as_png(ctx, pix, "a.png", 0);

	/* Clean up. */
	fz_drop_pixmap(ctx, pix);
	fz_drop_document(ctx, doc);
	fz_drop_context(ctx);
	return EXIT_SUCCESS;
}
