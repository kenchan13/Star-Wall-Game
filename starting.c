void starting(void)
{
    int rocket = 1;
    int roc_x = -100;
    int student_ID_x = -200;
    int exchange =0;

    Audio start_music;
    openAudioFile("start.wav", &start_music);
    playAudio(&start_music);

    Image *s105062262 = read_image("s105062262.pixel","s105062262.color");
    Image *s104062361 = read_image("s104062361.pixel","s104062361.color");
    Image *start_animate_0 = read_image("start_animate_0.pixel", "start_animate_0.color");
    Image *start_animate_1 = read_image("start_animate_1.pixel", "start_animate_1.color");

    while(1)
    {
        clearScreen();
        show_image(s105062262, student_ID_x, 13);
        show_image(s104062361, student_ID_x, 32);
        //show_image(start_animate_1, 100, 12);

        if (rocket == 1 && roc_x != 400)
        {
            roc_x += 1;
            exchange = exchange + 1;

            if (exchange <= 50 || exchange > 100 && exchange <= 150 || exchange > 200 && exchange <= 250 || exchange > 300)
                show_image(start_animate_0, roc_x, 12);
            else if (exchange > 50 && exchange <= 100 || exchange > 150 && exchange <= 200 || exchange > 250 && exchange <= 300)
                show_image(start_animate_1, roc_x, 12);

            if (student_ID_x != 82)
            {
                student_ID_x += 1;
            }
        }

        drawCmdWindow();
        Sleep(10);

        if (roc_x == 400) break;

    }
}
