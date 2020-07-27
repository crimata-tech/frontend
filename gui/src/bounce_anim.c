void * bounce_anim ()
{
    cairo_t *cr = init_context ();
    cairo_set_source_rgba (cr, 0.2, 0.2, 0.2, 1.0);

    logo (cr, 0, 0, 0, 0, 0, 0);

    destroy_context (cr);

    sleep(1);

    int counter = 0;
    while (1)
    {
        cairo_t *cr = init_context ();
        cairo_set_source_rgba (cr, 0.2, 0.2, 0.2, 1.0);

        float e = sine_wave (counter, 1.5, 30);
        e = fabsf(e);
        logo (cr, 0, // circle top
                  -e, 
                  0, // circle bottom left
                  -e, 
                  0, // circle bottom right
                  -e
        );

        destroy_context (cr);
        counter++;
    }

    return 0;
}