#include "./MusicPlayer.h"

MusicPlayer::MusicPlayer(Buzzer *buzzer) {
    this->buzzer = buzzer;

    this->tempo = 140;

    this->isDone = false;

    this->repeat = false;
}

void MusicPlayer::setSong(const short *song, short length) {
    this->currentIndex = 0;

    this->song = song;

    this->numberOfNotes = length / 2;

    this->wholeNote = (60000 * 4) / this->tempo;

    this->isDone = false;
}

void MusicPlayer::setTempo(short tempo) {
    this->tempo = tempo;
}

void MusicPlayer::setRepeat(bool repeat) {
    this->repeat = repeat;
}

void MusicPlayer::play() {
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

void MusicPlayer::stop() {
    this->currentIndex = 2 * this->numberOfNotes + 1;
    this->delayer.updateInterval(0);

    this->isDone = true;
}

void MusicPlayer::restart() {
    this->currentIndex = 0;
    this->delayer.updateInterval(0);

    this->isDone = false;
}