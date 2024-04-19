#ifndef MACROS_H
#define MACROS_H

#define WINDOW_WIDTH                                   (500)
#define WINDOW_HEIGHT                                  (500)

#define F1GP_PLAYER_CAR_IMAGE_SIZE_X                 (47)
#define F1GP_PLAYER_CAR_IMAGE_SIZE_Y                 (81)
#define F1GP_PLAYER_CAR_CARSH_IMAGE_SIZE_X           (50)
#define F1GP_PLAYER_CAR_CARSH_IMAGE_SIZE_Y           (108)
#define F1GP_PLAYER_CAR_FLY_IMAGE_SIZE_X             (133)
#define F1GP_PLAYER_CAR_FLY_IMAGE_SIZE_Y             (120)
#define F1GP_OPPOSITE_CAR_TYPE_COUNT                 (7)
#define F1GP_PLAYER_CAR_FLY_FRAME_COUNT              (15)
#define F1GP_OPPOSITE_CAR_0_IMAGE_SIZE_X             (78)
#define F1GP_OPPOSITE_CAR_0_IMAGE_SIZE_Y             (162)
#define F1GP_OPPOSITE_CAR_1_IMAGE_SIZE_X             (51)
#define F1GP_OPPOSITE_CAR_1_IMAGE_SIZE_Y             (81)
#define F1GP_OPPOSITE_CAR_2_IMAGE_SIZE_X             (55)
#define F1GP_OPPOSITE_CAR_2_IMAGE_SIZE_Y             (86)
#define F1GP_OPPOSITE_CAR_3_IMAGE_SIZE_X             (57)
#define F1GP_OPPOSITE_CAR_3_IMAGE_SIZE_Y             (86)
#define F1GP_OPPOSITE_CAR_4_IMAGE_SIZE_X             (73)
#define F1GP_OPPOSITE_CAR_4_IMAGE_SIZE_Y             (122)
#define F1GP_OPPOSITE_CAR_5_IMAGE_SIZE_X             (61)
#define F1GP_OPPOSITE_CAR_5_IMAGE_SIZE_Y             (85)
#define F1GP_OPPOSITE_CAR_6_IMAGE_SIZE_X             (51)
#define F1GP_OPPOSITE_CAR_6_IMAGE_SIZE_Y             (89)
#define F1GP_SPECIAL_BOX_SIZE                        (35)
#define F1GP_PLAYER_CAR_RUN_FRAME                    (12)
#define F1GP_PLAYER_CAR_TRANSFORM_FRAME              (19)
#define F1GP_OPPOSITE_CAR_COUNT                      (7)
#define F1GP_OPPOSITE_CAR_DEFAULT_APPEAR_RATE        (3)
#define F1GP_MAX_FLY_COUNT                           (9)
#define F1GP_TIMER_ELAPSE                            (100)
#define F1GP_PLAYER_CAR_SHIFT                        (20)
#define F1GP_PLAYER_CAR_FLY_SHIFT                    (2)
#define F1GP_DISPLAY_START_X                         (9)
#define F1GP_DISPLAY_START_Y                         (1)
#define F1GP_DISPLAY_END_X                           (500)
#define F1GP_DISPLAY_END_Y                           (500)
#define F1GP_ROAD_WIDTH                              (102)
#define F1GP_SEPARATOR_WIDTH                         (F1GP_ROAD_WIDTH / 12)
#define F1GP_SEPARATOR_HEIGHT_SPACE                  (F1GP_SEPARATOR_WIDTH * 2)
#define F1GP_SEPARATOR_RATIO                         (4)
#define F1GP_SEPARATOR_HEIGHT                        (F1GP_SEPARATOR_HEIGHT_SPACE * F1GP_SEPARATOR_RATIO)
#define F1GP_STATUS_NUMBER_WIDTH                     (21)
#define F1GP_STATUS_NUMBER_HEIGHT                    (50)
#define F1GP_ROAD_0_START_X                          (30)
#define F1GP_ROAD_0_END_X                            (F1GP_ROAD_0_START_X + F1GP_ROAD_WIDTH)
#define F1GP_SEPARATOR_0_START_X                     (F1GP_ROAD_0_END_X) - (F1GP_SEPARATOR_WIDTH / 2)
#define F1GP_SEPARATOR_0_END_X                       (F1GP_SEPARATOR_0_START_X + F1GP_SEPARATOR_WIDTH)
#define F1GP_ROAD_1_START_X                          (F1GP_ROAD_0_END_X)
#define F1GP_ROAD_1_END_X                            (F1GP_ROAD_1_START_X + F1GP_ROAD_WIDTH)
#define F1GP_SEPARATOR_1_START_X                     (F1GP_ROAD_1_END_X - (F1GP_SEPARATOR_WIDTH / 2))
#define F1GP_SEPARATOR_1_END_X                       (F1GP_SEPARATOR_1_START_X + F1GP_SEPARATOR_WIDTH)
#define F1GP_ROAD_2_START_X                          (F1GP_ROAD_1_END_X)
#define F1GP_ROAD_2_END_X                            (F1GP_ROAD_2_START_X + F1GP_ROAD_WIDTH)
#define F1GP_STATUS_START_X                          (380)
#define F1GP_STATUS_END_X                            (480)
#define F1GP_STATUS_WIDTH                            (F1GP_STATUS_END_X - F1GP_STATUS_START_X)
#define F1GP_STATUS_HEIGHT                           (27)

// 14/03
#define F1GP_EXPLOSIVE_EFFECT_FRAME                  (10)
#define F1GP_EXPLOSIVE_EFFECT_FRAME_WIDTH            (128)
#define F1GP_EXPLOSIVE_EFFECT_FRAME_HEIGHT           (80)
#define F1GP_EXPLOSIVE_EFFECT_INCREMENT              (15)
#define F1GP_TRANSFORM_FRAME                         (80)

#define F1GP_BUTTON_BACK_WIDTH                       (103)
#define F1GP_BUTTON_BACK_HEIGHT                      (27)
#define F1GP_BUTTON_LEADERBOARD_WIDTH                (221)
#define F1GP_BUTTON_LEADERBOARD_HEIGHT               (48)
#define F1GP_BUTTON_PLAY_WIDTH                       (142)
#define F1GP_BUTTON_PLAY_HEIGHT                      (46)
#define F1GP_BUTTON_QUIT_WIDTH                       (191)
#define F1GP_BUTTON_QUIT_HEIGHT                      (47)

#define F1GP_BUTTON_LEADERBOARD_X                    (( WINDOW_WIDTH - F1GP_BUTTON_LEADERBOARD_WIDTH ) / 2)
#define F1GP_BUTTON_LEADERBOARD_Y                    (( WINDOW_HEIGHT - F1GP_BUTTON_LEADERBOARD_HEIGHT ) / 2)
#define F1GP_BUTTON_PLAY_X                           (( WINDOW_WIDTH - F1GP_BUTTON_PLAY_WIDTH ) / 2)
#define F1GP_BUTTON_PLAY_Y                           (( WINDOW_HEIGHT * 4 / 5 - F1GP_BUTTON_PLAY_HEIGHT ) / 2)
#define F1GP_BUTTON_QUIT_X                           (( WINDOW_WIDTH - F1GP_BUTTON_QUIT_WIDTH ) / 2)
#define F1GP_BUTTON_QUIT_Y                           (( WINDOW_HEIGHT * 6 / 5 - F1GP_BUTTON_QUIT_HEIGHT ) / 2)

#define F1GP_RELEASE_ALL_KEY {                   \
    F1GP_key_up_pressed      = false;            \
    F1GP_key_down_pressed    = false;            \
    F1GP_key_left_pressed    = false;            \
    F1GP_key_right_pressed   = false;            \
    if (F1GP_is_crashing == true)                \
        return;                                  \
}                                                     



#endif
