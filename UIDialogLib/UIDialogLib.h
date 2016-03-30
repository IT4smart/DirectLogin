/******************************************************************************
 *
 *    Name: UIDialogLib.h
 *
 *    $Id: //icaclient/unix13.3/client/unix/UIDialogLib/UIDialogLib.h#1 $
 *
 *    Purpose: UI Dialog Library API header.
 *
 *    Copyright 2013-2014 Citrix Systems, Inc. All rights reserved.
 *
 *****************************************************************************/

#ifndef UI_DIALOG_LIB_H
#define UI_DIALOG_LIB_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef BOOLEAN_DEFINED
typedef unsigned char BOOLEAN;
#endif

// Defined in /usr/include/glib-2.0/glib/gmacros.h
#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE !FALSE
#endif

#include "UI_if.h"

/* Version */
#define UIDIALOG_MAJOR 2
#define UIDIALOG_MINOR 0

/* Possible variable arguments that can be taken by UIDialogDisplayVarg(). */
enum argType {
    A_LAST_ARG = 0,         /* The argument used to delimit the vargs list. */
    A_STYLE,                /* The style in enum styleType format. */
    A_PARENT,               /* A pointer to the parent's UIDIALOG structure. */
    A_TIMEOUT,              /* The timeout in seconds as an unsigned int. */
    A_TIMEOUT_RESPONSE,     /* The char* response string to return on a timeout. */
    A_WMCLASS_NAME,         /* The wmclass name in char* format. */
    A_WMCLASS_CLASS,        /* The wmclass class in char* format. */
    A_IDLE_TIMEOUT,         /* The idle timeout in seconds as an unsigned int. */
    A_IDLE_TIMEOUT_RESPONSE /* The char* response string to return on a idle timeout. */
};

/* Forward Declarations for opaque UIDIALOG structure. */
typedef struct UIDialog  UIDIALOG;


/** @brief Allocate a UIDialog opaque structure. The data will need to be freed
 *  with free() once finished with.
 *
 * @return  Returns a pointer to a UIDAILOG memory block.
 */
extern UIDIALOG *UIDialogAllocate(void);


/** @brief Initialise the UIDialogLib sufficiently to be used with an existing
 * eventloop implementation. UIDialogLoopInit() will need to be subsequently
 * called if the UIDialogLib is required to run its own eventloop.
 *
 * @param icaroot   The icaroot string indicates the main installation
 *                  location for the Linux Receiver. This is used to access
 *                  additional resources such as icons.
 */
extern void UIDialogInit(const char *icaroot);


/** @brief Initialise an eventloop for use with the UIDialogLib. This is called
 * after UIDialogInit() if the calling process does not have a its own suitable
 * eventloop to render the UI.
 *
 * @param argc      Is a pointer to the original argc passed in to main.
 * @param argv      Is a pointer to the original argv passed in to main.
 */
extern void UIDialogLoopInit(int *argc, char ***argv);


/** @brief Set overall options for the UIDialog library.
 * This function should be called immediately after initialisation.
 *
 * @param options   Bit mapped options for the library.
 */
extern void UIDialogSetOptions(unsigned int options);

/* Definitions of option bits. */

#define UI_DIALOGS_ABOVE        1   /* Keep dialogues above other windows. */


/** @brief UIDialogDisplayVarg is responsible for rendering the structure format
 *  that it is given into a dialogue for the user to interact with.
 *
 *  Before returning UIDialogDisplayVarg() updates the contents of form to
 *  represent the state of the UI dialogue when it was dismissed such that all
 *  information is returned to the caller for further processing.
 *
 *  Implicit layout hint:
 *      * Any buttons adjacent to each other at the bottom of the forms
 *        formsElement list should be grouped together horizontally.
 *
 *  Security Requirements:
 *      * Before deallocating UI widgets it is imperative that their contents is
 *        wiped prior to being deallocated, especially if it is a text box
 *        containing hidden contents such as a password.
 *
 * @param dialog            Is a opaque block of memory previously allocated
 *                          with UIDialogAllocate().
 * @param form              Is a set of formsElement structures containing all
 *                          the information required to render the UI.
 * @param window_title      The window title string.
 * @param default_response  The default_response is the response to be returned
 *                          should enter be pressed while focused on a
 *                          non-button element within the dialog.
 * @param ...               A list of pairs of enum argType with the
 *                          corresponding data terminated with a single
 *                          enum argType A_LAST_ARG.
 * @return  Returns the identifier string relating to the button that was
 *          pressed. If no button was pressed and the dialogue was dismissed
 *          via another means then NULL is returned .e.g the cross in the top
 *          corner has been pressed.
 */
extern const char* UIDialogDisplayVarg(UIDIALOG *dialog,
                             struct formsElement **form,
                             const char *window_title,
                             const char *default_response,
                             ...);


/** @brief UIDialogDisplay is responsible for rendering the structure format
 *  that it is given into a dialogue for the user to interact with.
 *
 *  Before returning UIDialogDisplay() updates the contents of form to
 *  represent the state of the UI dialogue when it was dismissed such that all
 *  information is returned to the caller for further processing.
 *
 *  Implicit layout hint:
 *      * Any buttons adjacent to each other at the bottom of the forms
 *        formsElement list should be grouped together horizontally.
 *
 *  Security Requirements:
 *      * Before deallocating UI widgets it is imperative that their contents is
 *        wiped prior to being deallocated, especially if it is a text box
 *        containing hidden contents such as a password.
 *
 * @param dialog            Is a opaque block of memory previously allocated
 *                          with UIDialogAllocate().
 * @param form              Is a set of formsElement structures containing all
 *                          the information required to render the UI.
 * @param style             The style is used to hint at the icon to use and
 *                          the overall layout and formatting of the dialog.
 * @param parent            Tells UIDialogDisplay() to treat the dialog parent
 *                          as a parent to the new dialog window.
 * @param window_title      The window title string.
 * @param default_response  The default_response is the response to be returned
 *                          should enter be pressed while focused on a
 *                          non-button element within the dialog.
 * @param timeout           Is how soon to automatically close the dialogue if
 *                          no user decision is made, in seconds.
 * @param timeout_response  The timeout_response is the response to be returned
 *                          should the timeout on the dialog expire.
 * @return  Returns the identifier string relating to the button that was
 *          pressed. If no button was pressed and the dialogue was dismissed
 *          via another means then NULL is returned .e.g the cross in the top
 *          corner has been pressed.
 */
extern const char* UIDialogDisplay(UIDIALOG *dialog,
                             struct formsElement **form,
                             enum dialogStyle style,
                             UIDIALOG *parent,
                             const char *window_title,
                             const char *default_response,
                             unsigned int timeout,
                             const char *timeout_response);


/** @brief UIDialogDisplayWMClass is responsible for rendering the structure
 *  format that it is given into a dialogue for the user to interact with.
 *  This is exactly the same as UIDialogDisplay() except it takes a couple of
 *  X specific wmclass arguments. If this is not supportable on your platform
 *  then please implement this function ignoring the wmclass arguments.
 *
 *  Before returning UIDialogDisplay() updates the contents of form to
 *  represent the state of the UI Dialog when it was dismissed such that all
 *  information is returned to the caller for further processing.
 *
 *  Implicit layout hint:
 *      * Any buttons adjacent to each other at the bottom of the forms
 *        formsElement list should be grouped together horizontally.
 *
 *  Security Requirements:
 *      * Before deallocating UI widgets it is imperative that their contents is
 *        wiped prior to being deallocated, especially if it is a text box
 *        containing hidden contents such as a password.
 *
 * @param dialog            Is a opaque block of memory previously allocated
 *                          with UIDialogAllocate().
 * @param form              Is a set of formsElement structures containing all
 *                          the information required to render the UI.
 * @param style             The style is used to hint at the icon to use and
 *                          the overall layout and formatting of the dialog.
 * @param parent            Tells UIDialogDisplay() to treat the dialog parent
 *                          as a parent to the new dialog window.
 * @param window_title      The window title string.
 * @param default_response  The default_response is the response to be returned
 *                          should enter be pressed while focused on a
 *                          non-button element within the dialog.
 * @param timeout           Is how soon to automatically close the dialogue if
 *                          no user decision is made, in seconds.
 * @param timeout_response  The timeout_response is the response to be returned
 *                          should the timeout on the dialog expire.
 * @param wmclass_name      The X Window name hint. This is ignored if NULL or
 *                          if wmclass_class is NULL.
 * @param wmclass_class     The X Window class hint. This is ignored if NULL or
 *                          if wmclass_name is NULL.
 * @return  Returns the identifier string relating to the button that was
 *          pressed. If no button was pressed and the dialogue was dismissed
 *          via another means then NULL is returned .e.g the cross in the top
 *          corner has been pressed.
 */
extern const char* UIDialogDisplayWMClass( UIDIALOG *dialog,
                                           struct formsElement **form,
                                           enum dialogStyle style,
                                           UIDIALOG *parent,
                                           const char *window_title,
                                           const char *default_response,
                                           unsigned int timeout,
                                           const char *timeout_response,
                                           const char *wmclass_name,
                                           const char *wmclass_class);


/** @brief Any UI initialisation required to be called prior to 
 *  UIDialogDisplay() should be run in here.
 *
 *  When a process utilising the UI Dialog library already has UI initialised
 *  this function may not need to be called.
 *
 * @param dialog        Is a pointer to a visible UIDialog displayed by calling
 *                      UIDialogDisplay with the given UIDIALOG memory block.
 */
extern void UIDialogClose(UIDIALOG *dialog);


/** @brief Any UI Deinitialisation required to tidy up after using the
 *  UIDialogLib.
 */
extern void UIDialogDeInit(void);

#ifdef __cplusplus
} /* End extern "C". */
#endif

#endif /* ! UI_DIALOG_LIB_H */


