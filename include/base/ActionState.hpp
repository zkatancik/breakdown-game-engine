#ifndef ACTION_STATE
#define ACTION_STATE

/**
 * @brief Defines the possible states one of our humanoid GameObjects could be in.
 * Mostly used for animating based on current action.
 */
enum ActionState
{
    IDLE,
    WALK,
    JUMP,
    SLIDE,
    DEAD
};

#endif // ACTION_STATE
