#ifndef NameAndScore_h
#define NameAndScore_h

class NameAndScore {
   public:
    char *name;
    short score;

    NameAndScore() {}

    NameAndScore(char *name, short score) {
        this->name = name;
        this->score = score;
    }
};

#endif
