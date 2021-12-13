#pragma once

class MusicPlayer {
   public:
    short tempo, currentIndex, numberOfNotes;

    const short *song = 0;

    int wholeNote;

    bool isDone;

    bool repeat;

    // TODO: should have 0 by default, in the class
    Delayer delayer = Delayer(0);
    Buzzer *buzzer;

    MusicPlayer(Buzzer *buzzer) {
        this->buzzer = buzzer;

        this->tempo = 140;

        this->isDone = false;

        this->repeat = false;
    }

    void setSong(const short *song, short length) {
        this->currentIndex = 0;

        this->song = song;

        this->numberOfNotes = length / 2;

        this->wholeNote = (60000 * 4) / this->tempo;

        this->isDone = false;
    }

    void setTempo(short tempo) {
        this->tempo = tempo;
    }

    void setRepeat(bool repeat) {
        this->repeat = repeat;
    }

    void play() {
        if (this->currentIndex > 2 * this->numberOfNotes) {
            return;
        }

        if (!this->delayer.canRun()) return;

        this->buzzer->stop();

        short divider = this->song[this->currentIndex + 1];

        short noteDuration = 0;

        if (divider > 0) {
            noteDuration = this->wholeNote / divider;
        }

        else if (divider < 0) {
            noteDuration = this->wholeNote / -divider;

            noteDuration *= 1.5;
        }

        this->buzzer->buzz(this->song[this->currentIndex], noteDuration * 0.9);

        this->delayer.updateInterval(noteDuration);

        this->currentIndex += 2;

        if (this->currentIndex > 2 * this->numberOfNotes) {
            this->buzzer->stop();

            if (this->repeat) {
                this->restart();
            }

            else {
                this->isDone = true;
            }
        }
    }

    void stop() {
        this->currentIndex = 2 * this->numberOfNotes + 1;
        this->delayer.updateInterval(0);

        this->isDone = true;
    }

    void restart() {
        this->currentIndex = 0;
        this->delayer.updateInterval(0);

        this->isDone = false;
    }
};
