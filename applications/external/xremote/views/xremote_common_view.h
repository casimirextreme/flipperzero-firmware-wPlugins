/*!
 *  @file flipper-xremote/views/xremote_common_view.h
    @license This project is released under the GNU GPLv3 License
 *  @copyright (c) 2023 Sandro Kalatozishvili (s.kalatoz@gmail.com)
 *
 * @brief Common view and canvas functionality shared between the pages.
 */

#pragma once

#include <furi.h>
#include <gui/view.h>
#include <gui/elements.h>

#include <notification/notification.h>
#include <notification/notification_messages.h>

#include <infrared_transmit.h>
#include <xc_icons.h>

#define XREMOTE_COMMAND_POWER "Power"
#define XREMOTE_COMMAND_SETUP "Setup"
#define XREMOTE_COMMAND_INPUT "Input"
#define XREMOTE_COMMAND_MENU "Menu"
#define XREMOTE_COMMAND_LIST "List"
#define XREMOTE_COMMAND_INFO "Info"
#define XREMOTE_COMMAND_BACK "Back"
#define XREMOTE_COMMAND_OK "Ok"
#define XREMOTE_COMMAND_UP "Up"
#define XREMOTE_COMMAND_DOWN "Down"
#define XREMOTE_COMMAND_LEFT "Left"
#define XREMOTE_COMMAND_RIGHT "Right"
#define XREMOTE_COMMAND_JUMP_FORWARD "Next"
#define XREMOTE_COMMAND_JUMP_BACKWARD "Prev"
#define XREMOTE_COMMAND_FAST_FORWARD "Fast_fo"
#define XREMOTE_COMMAND_FAST_BACKWARD "Fast_ba"
#define XREMOTE_COMMAND_PLAY_PAUSE "Play_pa"
#define XREMOTE_COMMAND_PAUSE "Pause"
#define XREMOTE_COMMAND_PLAY "Play"
#define XREMOTE_COMMAND_STOP "Stop"
#define XREMOTE_COMMAND_MUTE "Mute"
#define XREMOTE_COMMAND_MODE "Mode"
#define XREMOTE_COMMAND_VOL_UP "Vol_up"
#define XREMOTE_COMMAND_VOL_DOWN "Vol_dn"
#define XREMOTE_COMMAND_NEXT_CHAN "Ch_next"
#define XREMOTE_COMMAND_PREV_CHAN "Ch_prev"

typedef enum {
    /* Navigation */
    XRemoteIconOk,
    XRemoteIconEnter,
    XRemoteIconBack,
    XRemoteIconArrowUp,
    XRemoteIconArrowDown,
    XRemoteIconArrowLeft,
    XRemoteIconArrowRight,

    /* Playback */
    XRemoteIconPlay,
    XRemoteIconPause,
    XRemoteIconStop,
    XRemoteIconPlayPause,
    XRemoteIconFastForward,
    XRemoteIconFastBackward,
    XRemoteIconJumpForward,
    XRemoteIconJumpBackward
} XRemoteIcon;

typedef struct {
    bool ok_pressed;
    bool back_pressed;
    bool up_pressed;
    bool down_pressed;
    bool left_pressed;
    bool right_pressed;
    uint32_t reserverd;
} XRemoteViewModel;

typedef enum {
    XRemoteViewNone,

    /* Main page */
    XRemoteViewSubmenu,
    XRemoteViewLearn,
    XRemoteViewSaved,
    XRemoteViewSettings,
    XRemoteViewAbout,

    /* Remote app */
    XRemoteViewIRSubmenu,
    XRemoteViewIRGeneral,
    XRemoteViewIRControl,
    XRemoteViewIRNavigation,
    XRemoteViewIRPlayer,
    XRemoteViewIRCustom
} XRemoteViewID;

typedef struct XRemoteView XRemoteView;
typedef void (*XRemoteViewClearCallback)(void* context);

void xremote_canvas_draw_header(Canvas* canvas, const char* section);
void xremote_canvas_draw_exit_footer(Canvas* canvas, char* text);

void xremote_canvas_draw_icon(Canvas* canvas, uint8_t x, uint8_t y, XRemoteIcon icon);
void xremote_canvas_draw_button(
    Canvas* canvas,
    bool pressed,
    uint8_t x,
    uint8_t y,
    XRemoteIcon icon);
void xremote_canvas_draw_button_wide(
    Canvas* canvas,
    bool pressed,
    uint8_t x,
    uint8_t y,
    char* text,
    XRemoteIcon icon);
void xremote_canvas_draw_frame(
    Canvas* canvas,
    bool pressed,
    uint8_t x,
    uint8_t y,
    uint8_t xl,
    const char* text);

XRemoteView* xremote_view_alloc(
    NotificationApp* notifications,
    ViewInputCallback input_cb,
    ViewDrawCallback draw_cb);
void xremote_view_free(XRemoteView* rview);

View* xremote_view_get_view(XRemoteView* rview);
void xremote_view_send_ir(XRemoteView* rview, const char* name);

void xremote_view_set_context(XRemoteView* rview, void* context, XRemoteViewClearCallback on_clear);
void* xremote_view_get_context(XRemoteView* rview);
void xremote_view_clear_context(XRemoteView* rview);