

typedef struct {
    const char *name;
    
    // Function pointers matching the game lifecycle
    void (*init)(void **state);
    void (*update)(void *state);
    void (*render)(void *state);
    void (*cleanup)(void *state);
} GameMode;

typedef enum {
    STATE_MENU,
    STATE_IN_GAME
} AppState;

extern AppState app_state;
extern GameMode *current_game;
extern void *game_memory;


int startMode(int mode);
int gameLoop(void);