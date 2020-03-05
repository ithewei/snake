#ifndef SNAKE_SETTING_H_
#define SNAKE_SETTING_H_

/**************************************************
Game UI

###################################
# score: 99    time: 88s          #
###################################
#         $            $          #
#    $                            #
#                                 #
#            @@@                  #
#                                 #
#        $                   $    #
#                                 #
###################################

**************************************************/

#define WALL_WIDTH  (60+2)

#define BBS_HEIGHT  (1+1)
#define WALL_HEIGHT (20+2)

#define OUTLINE_WIDTH  WALL_WIDTH
#define OUTLINE_HEIGHT (BBS_HEIGHT + WALL_HEIGHT)

#define INIT_SNAKE_LEN  3
#define FOOD_NUM        10

#define WALL_CHAR   ACS_CKBOARD
#define SNAKE_CHAR  '@'
#define FOOD_CHAR   '$'

// speed: 1 ~ 10
#define DEFAULT_SPEED  5
#define MIN_SPEED      1
#define MAX_SPEED      10

#define KEY_CTL_LEFT      KEY_LEFT
#define KEY_CTL_UP        KEY_UP
#define KEY_CTL_RIGHT     KEY_RIGHT
#define KEY_CTL_DOWN      KEY_DOWN

#define KEY_CTL_QUIT      'q'
#define KEY_CTL_PAUSE     'p'
#define KEY_CTL_SLOW      's'
#define KEY_CTL_FAST      'f'

#endif  // SNAKE_SETTING_H_

