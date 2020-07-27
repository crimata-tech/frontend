/* Scatter dots and move relative to sound effects and
** the transcription of the user's voice dynamically renders
** on screen.
**
**
**                           ▼
**                      *    ▼     *
**                      ▲    *     ▲
**                                 ▲
**
**
**                  "Hey Andrew, how's..."
**
*/
void * recording_anim ()
{
    struct Strobes circle_1;
    circle_1.positionY=0;
    circle_1.positionX=0;

    circle_1.velocityY=0;
    circle_1.velocityX=0;

    struct Strobes circle_2;
    circle_2.positionY=0;
    circle_2.positionX=0;

    circle_2.velocityY=0;
    circle_2.velocityX=0;

    struct Strobes circle_3;
    circle_3.positionY=0;
    circle_3.positionX=0;

    circle_3.velocityY=0;
    circle_3.velocityX=0;

    struct Strobes circle_4;
    circle_4.positionY=0;
    circle_4.positionX=0;

    circle_4.velocityY=0;
    circle_4.velocityX=0;

    struct Strobes circle_5;
    circle_5.positionY=0;
    circle_5.positionX=0;

    circle_5.velocityY=0;
    circle_5.velocityX=0;

    struct Strobes circle_6;
    circle_6.positionY=0;
    circle_6.positionX=0;

    circle_6.velocityY=0;
    circle_6.velocityX=0;

    cairo_t *cr = init_context ();

    cairo_set_source_rgba (cr, 0.2, 0.2, 0.2, 1);

    cairo_arc (cr, 0, -10, 7.25, 0, 6.28);
    cairo_fill (cr);
    cairo_arc (cr, -9.34, 6, 7.25, 0, 6.28);
    cairo_fill (cr);
    cairo_arc (cr, 9.34, 6, 7.25, 0, 6.28);
    cairo_fill (cr);

    destroy_context (cr);

    sleep(1);

    // first damped oscillator animation
    static float k = 30;
    for (float c=0; c<1; c+=0.02)
    {
        cairo_t *cr = init_context ();

        float c_elastic = exponential_ease_out (c); 





        cairo_set_source_rgba (cr, 0.2, 0.2, 0.2, 1);
        float x1 = -1*c_elastic*30;
        float y1 = x1/4;
        cairo_arc (cr, x1-7+2, (y1)-8, 7, 0, 6.28);
        cairo_fill (cr);

        cairo_set_source_rgba (cr, 0.2, 0.2, 0.2, 0.75);
        damped_oscillator( x1, y1, k, &circle_1 );
        cairo_arc (cr, circle_1.positionX-7+2, (circle_1.positionY)-8, 7, 0, 6.28);
        cairo_fill (cr);

        cairo_set_source_rgba (cr, 0.2, 0.2, 0.2, 0.5);
        damped_oscillator( circle_1.positionX, circle_1.positionY, k, &circle_2 );
        cairo_arc (cr, circle_2.positionX-7+2, (circle_2.positionY)-8, 7, 0, 6.28);
        cairo_fill (cr);





        cairo_set_source_rgba (cr, 0.2, 0.2, 0.2, 1);
        float x2 = c_elastic*30/2;
        float y2 = -1*x2;
        cairo_arc (cr, x2-7+2, y2+8, 7, 0, 6.28);
        cairo_fill (cr);

        cairo_set_source_rgba (cr, 0.2, 0.2, 0.2, 0.75);
        damped_oscillator( x2, y2, k, &circle_3 );
        cairo_arc (cr, circle_3.positionX-7+2, (circle_3.positionY)+8, 7, 0, 6.28);
        cairo_fill (cr);

        cairo_set_source_rgba (cr, 0.2, 0.2, 0.2, 0.5);
        damped_oscillator( circle_3.positionX, circle_3.positionY, k, &circle_4 );
        cairo_arc (cr, circle_4.positionX-7+2, (circle_4.positionY)+8, 7, 0, 6.28);
        cairo_fill (cr);





        cairo_set_source_rgba (cr, 0.2, 0.2, 0.2, 1);
        float x3 = c_elastic*30+10;
        float y3 = -1*x3/4;
        cairo_arc (cr, x3+7+2, y3, 7, 0, 6.28);
        cairo_fill (cr);

        cairo_set_source_rgba (cr, 0.2, 0.2, 0.2, 0.75);
        damped_oscillator( x3, y3, k, &circle_5 );
        cairo_arc (cr, circle_5.positionX+7+2, (circle_5.positionY), 7, 0, 6.28);
        cairo_fill (cr);

        cairo_set_source_rgba (cr, 0.2, 0.2, 0.2, 0.5);
        damped_oscillator( circle_5.positionX, circle_5.positionY, k, &circle_6 );
        cairo_arc (cr, circle_6.positionX+7+2, (circle_6.positionY), 7, 0, 6.28);
        cairo_fill (cr);




        destroy_context (cr);
    }

    for (float c=0; c<10; c+=0.01)
    {
        cairo_t *cr = init_context ();





        //! where we will input sound values
        float wav_y = sin_wave_scaled (c, 1.2, 20);
        float wav_y_2 = sin_wave_scaled (c, 1, 10); 
        float wav_y_3 = sin_wave_scaled (c, 1, 25); 





        cairo_set_source_rgba (cr, 0.2, 0.2, 0.2, 1);
        float x1 = -30;
        float y1 = wav_y-7.5;
        cairo_arc (cr, x1-7+2, (y1)-8, 7, 0, 6.28);
        cairo_fill (cr);

        cairo_set_source_rgba (cr, 0.2, 0.2, 0.2, 0.75);
        damped_oscillator( x1, y1, k, &circle_1 );
        cairo_arc (cr, circle_1.positionX-7+2, (circle_1.positionY)-8, 7, 0, 6.28);
        cairo_fill (cr);

        cairo_set_source_rgba (cr, 0.2, 0.2, 0.2, 0.5);
        damped_oscillator( circle_1.positionX, circle_1.positionY, k, &circle_2 );
        cairo_arc (cr, circle_2.positionX-7+2, (circle_2.positionY)-8, 7, 0, 6.28);
        cairo_fill (cr);





        cairo_set_source_rgba (cr, 0.2, 0.2, 0.2, 1);
        float x2 = 15;
        float y2 = wav_y_2-15;
        cairo_arc (cr, x2-7+2, y2+8, 7, 0, 6.28);
        cairo_fill (cr);

        cairo_set_source_rgba (cr, 0.2, 0.2, 0.2, 0.75);
        damped_oscillator( x2, y2, k, &circle_3 );
        cairo_arc (cr, circle_3.positionX-7+2, (circle_3.positionY)+8, 7, 0, 6.28);
        cairo_fill (cr);

        cairo_set_source_rgba (cr, 0.2, 0.2, 0.2, 0.5);
        damped_oscillator( circle_3.positionX, circle_3.positionY, k, &circle_4 );
        cairo_arc (cr, circle_4.positionX-7+2, (circle_4.positionY)+8, 7, 0, 6.28);
        cairo_fill (cr);





        cairo_set_source_rgba (cr, 0.2, 0.2, 0.2, 1);
        float x3 = 40;
        float y3 = wav_y_3-10;
        cairo_arc (cr, x3+7+2, y3, 7, 0, 6.28);
        cairo_fill (cr);

        cairo_set_source_rgba (cr, 0.2, 0.2, 0.2, 0.75);
        damped_oscillator( x3, y3, k, &circle_5 );
        cairo_arc (cr, circle_5.positionX+7+2, (circle_5.positionY), 7, 0, 6.28);
        cairo_fill (cr);

        cairo_set_source_rgba (cr, 0.2, 0.2, 0.2, 0.5);
        damped_oscillator( circle_5.positionX, circle_5.positionY, k, &circle_6 );
        cairo_arc (cr, circle_6.positionX+7+2, (circle_6.positionY), 7, 0, 6.28);
        cairo_fill (cr);





        destroy_context (cr);
    }
    return 0;
}