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
