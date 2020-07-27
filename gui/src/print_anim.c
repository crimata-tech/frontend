void * print_anim ()
{
	while (1)
	{
		cairo_t *cr = init_context ();

		//! Render text based on global text variable.
        cairo_set_source_rgba (cr, 0.2, 0.2, 0.2, counter/200);
        cairo_text_extents_t te;
        cairo_select_font_face (cr, "Montserrat", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
        cairo_set_font_size (cr, 20);
        cairo_text_extents (cr, "Crimata", &te);
        cairo_move_to (cr, te.width/-2+25, te.height/2-4);
        cairo_show_text (cr, "Crimata");

		destroy_context (cr);
	}
}