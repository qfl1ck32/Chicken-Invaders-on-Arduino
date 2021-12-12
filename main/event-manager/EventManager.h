#define MAX_EVENTS 20

// TODO: TBD?

class Event {
};

class EventManager {
   public:
    EventManager *instance == nullptr;

    EventManager() {
        if (this->instance == nullptr) {
            this->instance = new EventManager();
        }

        return this->instance;
    }

    void addListener(HandlerFunction *);

    void emit(Event &);
};
