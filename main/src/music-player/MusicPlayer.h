#ifndef MusicPlayer_h
#define MusicPlayer_h

#include "../app/globals.h"
#include "../delayer/Delayer.h"

class MusicPlayer {
   public:
    short tempo, currentIndex, numberOfNotes;

    const short *song = 0;

    int wholeNote;

    bool isDone;

    bool repeat;

    Delayer delayer;
    Buzzer *buzzer;

    MusicPlayer(Buzzer *);

    void setSong(const short *, short);
    void setTempo(short);
    void setRepeat(bool);

    void play();
    void stop();
    void restart();
};

#endif
