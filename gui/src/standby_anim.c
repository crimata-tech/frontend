/* On start-up animation; poster-child Crimata animation.
**
**
** 
**
*/
void * standby_anim ()
{
    /* Hold starting point for 1s. */
    cairo_t *cr = init_context ();
    cairo_set_source_rgba (cr, 0.2, 0.2, 0.2, 1.0);

    logo (cr, 0, 0, 0, 0, 0, 0);

    destroy_context (cr);

    sleep(1);

    while (1)
    {
        /* Pulse-out 12 points slow. */
        for (float counter=0; counter<12; counter+=0.5)
        {
            cairo_t *cr = init_context ();

            cairo_set_source_rgba (cr, 0.2, 0.2, 0.2, 1.0);

            int e = quadratic_ease_in_out (counter, 12);
            logo (cr, 0, // circle top
                      -e, 
                      -e, // circle bottom left
                      e, 
                      e, // circle bottom right
                      e
            );

            destroy_context (cr);
        }

        sleep (1);

        /* Pulse-in 12 points fast */
        for (float counter=0; counter<12; counter+=2)
        {
            cairo_t *cr = init_context ();
            cairo_set_source_rgba (cr, 0.2, 0.2, 0.2, 1.0);

            /* Begin @ position where the last anim left off */
            //! might be good thing to automate
            int offset = 11;
            int e = quadratic_ease_in_out (counter, 12);
            logo (cr, 0, // circle top
                      e-offset, 
                      e-offset, // circle bottom left
                      -e+offset, 
                      -e+offset, // circle bottom right
                      -e+offset
            );

            destroy_context (cr);
        }

        /* Accellerate rotation. */ 
        for (float speed=0; speed<1; speed+=0.1)
        {
            cairo_t *cr = init_context ();
            cairo_set_source_rgba (cr, 0.2, 0.2, 0.2, 1.0);

            float v = quadratic_ease_in (speed);
            cairo_rotate(cr, 10*v);

            logo (cr, 0, 0, 0, 0, 0, 0);

            destroy_context (cr);
        }

        /* Decellerate rotation. */ 
        for (float speed=0; speed<1; speed+=0.01)
        {
            cairo_t *cr = init_context ();
            cairo_set_source_rgba (cr, 0.2, 0.2, 0.2, 1.0);

            float v = sine_ease_out (speed);
            cairo_rotate(cr, 80*v-2.5);

            logo (cr, 0, 0, 0, 0, 0, 0);

            destroy_context (cr);
        }

        sleep (1);

        /* Pulse-out-in 8 points twice. */ 
        for (float c=0; c<2; c++)
        {
            for (float counter=0; counter<8; counter+=1)
            {
                cairo_t *cr = init_context ();
                cairo_set_source_rgba (cr, 0.2, 0.2, 0.2, 1.0);

                int e = quadratic_ease_in_out (counter, 8);
                logo (cr, 0, // circle top
                          -e, 
                          -e, // circle bottom left
                          e, 
                          e, // circle bottom right
                          e
                );

                destroy_context (cr);
            }

            for (float counter=0; counter<8; counter+=1)
            {
                cairo_t *cr = init_context ();
                cairo_set_source_rgba (cr, 0.2, 0.2, 0.2, 1.0);

                int offset = 7;
                int e = quadratic_ease_in_out (counter, 8);
                logo (cr, 0, // circle top
                          e-offset, 
                          e-offset, // circle bottom left
                          -e+offset, 
                          -e+offset, // circle bottom right
                          -e+offset
                );

                destroy_context (cr);
            }
        }
        sleep(8);
    }
    return 0;
}