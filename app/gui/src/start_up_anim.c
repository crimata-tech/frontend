void * start_up_anim ()
{
    sleep (1);
    static const char *render_text = "Good Morning";

    for (float counter=0; counter<100; counter+=2)
    {
        int x_dist = 100;

        cairo_t *cr = init_context ();

        cairo_scale(cr, 0.9, 0.9);

        /* X-Axis Ease */
        float ease_x = quadratic_ease_in_out(counter, x_dist);

        /* Logo */
        cairo_set_source_rgba (cr, 0.2, 0.2, 0.2, counter/x_dist);
        cairo_arc (cr, ease_x,        -10,  7.25, 0, 6.28);
        cairo_fill (cr);
        cairo_arc (cr, ease_x-9.34,   6,    7.25, 0, 6.28);
        cairo_fill (cr);
        cairo_arc (cr, ease_x+9.34,   6,    7.25, 0, 6.28);
        cairo_fill (cr);

        destroy_context (cr);
    }

    for (float counter=0; counter<200; counter+=10)
    {
        int last_pos_x = 100;
        int x_dist = 185; 

        cairo_t *cr = init_context ();

        cairo_scale(cr, 0.9, 0.9);

        double ease_x = quadratic_ease_in_out(counter, x_dist);

        cairo_set_source_rgba (cr, 0.2, 0.2, 0.2, 1);
        cairo_arc (cr, (ease_x*-1)+last_pos_x,        -10,  7.25, 0, 6.28);
        cairo_fill (cr);
        cairo_arc (cr, (ease_x*-1)+last_pos_x-9.34,   6,    7.25, 0, 6.28);
        cairo_fill (cr);
        cairo_arc (cr, (ease_x*-1)+last_pos_x+9.34,   6,    7.25, 0, 6.28);
        cairo_fill (cr);

        cairo_set_source_rgba (cr, 0.2, 0.2, 0.2, counter/200);
        cairo_text_extents_t te;
        cairo_select_font_face (cr, "Montserrat", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
        cairo_set_font_size (cr, 40);
        cairo_text_extents (cr, "Crimata", &te);
        cairo_move_to (cr, te.width/-2+25, te.height/2-4);
        cairo_show_text (cr, "Crimata");

        destroy_context (cr);
    }

    for (float counter=0; counter<10; counter+=1)
    {
        int last_pos_x = -85;
        int y_dist = 10; 

        cairo_t *cr = init_context ();

        cairo_scale(cr, 0.9, 0.9);

        double ease_y = quadratic_ease_in_out(counter, y_dist);

        cairo_set_source_rgba (cr, 0.2, 0.2, 0.2, 1);
        cairo_arc (cr, last_pos_x,        ease_y-10,  7.25, 0, 6.28);
        cairo_fill (cr);
        cairo_arc (cr, last_pos_x-9.34,   ease_y+6,    7.25, 0, 6.28);
        cairo_fill (cr);
        cairo_arc (cr, last_pos_x+9.34,   ease_y+6,    7.25, 0, 6.28);
        cairo_fill (cr);

        cairo_set_source_rgba (cr, 0.2, 0.2, 0.2, 1);
        cairo_text_extents_t te;
        cairo_select_font_face (cr, "Montserrat", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
        cairo_set_font_size (cr, 40);
        cairo_text_extents (cr, "Crimata", &te);
        cairo_move_to (cr, te.width/-2+25, te.height/2-4);
        cairo_show_text (cr, "Crimata");

        destroy_context (cr);
    }

    for (float counter=0; counter<15; counter+=1)
    {
        int last_pos_x = -85;
        int last_pos_y = 10;
        int y_dist = 15; 

        cairo_t *cr = init_context ();

        cairo_scale(cr, 0.9, 0.9);

        double ease_y = quadratic_ease_in_out(counter, y_dist);

        cairo_set_source_rgba (cr, 0.2, 0.2, 0.2, 1);
        cairo_arc (cr, last_pos_x,        (ease_y*-1)+last_pos_y-10,  7.25, 0, 6.28);
        cairo_fill (cr);
        cairo_arc (cr, last_pos_x-9.34,   (ease_y*-1)+last_pos_y+6,    7.25, 0, 6.28);
        cairo_fill (cr);
        cairo_arc (cr, last_pos_x+9.34,   (ease_y*-1)+last_pos_y+6,    7.25, 0, 6.28);
        cairo_fill (cr);

        cairo_set_source_rgba (cr, 0.2, 0.2, 0.2, 1);
        cairo_text_extents_t te;
        cairo_select_font_face (cr, "Montserrat", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
        cairo_set_font_size (cr, 40);
        cairo_text_extents (cr, "Crimata", &te);
        cairo_move_to (cr, te.width/-2+25, te.height/2-4);
        cairo_show_text (cr, "Crimata");

        destroy_context (cr);
    }

    for (float counter=0; counter<5; counter+=0.25)
    {
        int last_pos_x = -85;
        int last_pos_y = -5;
        int y_dist = 5; 

        cairo_t *cr = init_context ();

        cairo_scale(cr, 0.9, 0.9);

        double ease_y = quadratic_ease_in_out(counter, y_dist);

        cairo_set_source_rgba (cr, 0.2, 0.2, 0.2, 1);
        cairo_arc (cr, last_pos_x,        ease_y+last_pos_y-10,  7.25, 0, 6.28);
        cairo_fill (cr);
        cairo_arc (cr, last_pos_x-9.34,   ease_y+last_pos_y+6,    7.25, 0, 6.28);
        cairo_fill (cr);
        cairo_arc (cr, last_pos_x+9.34,   ease_y+last_pos_y+6,    7.25, 0, 6.28);
        cairo_fill (cr);

        cairo_set_source_rgba (cr, 0.2, 0.2, 0.2, 1);
        cairo_text_extents_t te;
        cairo_select_font_face (cr, "Montserrat", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
        cairo_set_font_size (cr, 40);
        cairo_text_extents (cr, "Crimata", &te);
        cairo_move_to (cr, te.width/-2+25, te.height/2-4);
        cairo_show_text (cr, "Crimata");

        // Render text beta.
        cairo_set_source_rgba (cr, 0.2, 0.2, 0.2, 1);
        cairo_select_font_face (cr, "Montserrat", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
        cairo_set_font_size (cr, 12);
        cairo_text_extents (cr, render_text, &te);
        cairo_move_to (cr, te.width/-2, te.height/2+60);
        cairo_show_text (cr, render_text);

        destroy_context (cr);
    }

    while ( 1 )
    {
        int last_pos_x = -85;
        int last_pos_y = 0;

        cairo_t *cr = init_context ();

        cairo_scale(cr, 0.9, 0.9);

        cairo_set_source_rgba (cr, 0.2, 0.2, 0.2, 1);
        cairo_arc (cr, last_pos_x,        last_pos_y-10,  7.25, 0, 6.28);
        cairo_fill (cr);
        cairo_arc (cr, last_pos_x-9.34,   last_pos_y+6,    7.25, 0, 6.28);
        cairo_fill (cr);
        cairo_arc (cr, last_pos_x+9.34,   last_pos_y+6,    7.25, 0, 6.28);
        cairo_fill (cr);

        cairo_set_source_rgba (cr, 0.2, 0.2, 0.2, 1);
        cairo_text_extents_t te;
        cairo_select_font_face (cr, "Montserrat", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
        cairo_set_font_size (cr, 40);
        cairo_text_extents (cr, "Crimata", &te);
        cairo_move_to (cr, te.width/-2+25, te.height/2-4);
        cairo_show_text (cr, "Crimata");

        // Render text beta.
        cairo_set_source_rgba (cr, 0.2, 0.2, 0.2, 1);
        cairo_select_font_face (cr, "Montserrat", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
        cairo_set_font_size (cr, 12);
        cairo_text_extents (cr, render_text, &te);
        cairo_move_to (cr, te.width/-2, te.height/2+60);
        cairo_show_text (cr, render_text);

        destroy_context (cr);
    }
    return 0;
}
