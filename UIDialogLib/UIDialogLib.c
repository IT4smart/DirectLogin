#include "UIDialogLib.h"

#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "stdbool.h"

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

// Define sruct used in shared memory
 struct sharedStruct {
		bool terminated;
		bool login_success;
		int n_login;
		char username[128];
		char password[128];
};

// Pointer to sharedStruct in shared memory
struct sharedStruct* shared_memory_struct;

// Shared memory key to find the shared memory
key_t key = 1234;

// ID of the shared memory segment
int shared_memory_ID;


/** @brief Allocate a UIDialog opaque structure. The data will need to be freed
 *  with free() once finished with.
 *
 * @return  Returns a pointer to a UIDAILOG memory block.
 */
extern UIDIALOG* UIDialogAllocate(void) {
	printf("UIDialogAllocate\n");
	return NULL;
}

/** @brief Initialise the UIDialogLib sufficiently to be used with an existing
 * eventloop implementation. UIDialogLoopInit() will need to be subsequently
 * called if the UIDialogLib is required to run its own eventloop.
 *
 * @param icaroot   The icaroot string indicates the main installation
 *                  location for the Linux Receiver. This is used to access
 *                  additional resources such as icons.
 */
extern void UIDialogInit(const char *icaroot) {
	printf("UIDialogInit: %s\n", icaroot);
}

/** @brief Initialise an eventloop for use with the UIDialogLib. This is called
 * after UIDialogInit() if the calling process does not have a its own suitable
 * eventloop to render the UI.
 *
 * @param argc      Is a pointer to the original argc passed in to main.
 * @param argv      Is a pointer to the original argv passed in to main.
 */
extern void UIDialogLoopInit(int *argc, char ***argv) {
	printf("UIDialogLoopInit\n");
}

/** @brief Set overall options for the UIDialog library.
 * This function should be called immediately after initialisation.
 *
 * @param options   Bit mapped options for the library.
 */
extern void UIDialogSetOptions(unsigned int options) {
	printf("UIDialogSetOptions\n");
}

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
extern const char* UIDialogDisplayVarg(UIDIALOG *dialog, struct formsElement **form, const char *window_title, const char *default_response, ...) {
	printf("UIDialogDisplayVarg\n");

	// Locate the segment
	shared_memory_ID = shmget(key, sizeof(struct sharedStruct), 0666);

	// Now we attach the segment to our data space
	shared_memory_struct = (struct sharedStruct*) shmat(shared_memory_ID, NULL, 0);
	
	if (shared_memory_struct->n_login == 0) {
		form[0]->input.inputUnion.textBox.text = shared_memory_struct->username;
		form[1]->input.inputUnion.textBox.text = shared_memory_struct->password;

		shared_memory_struct->n_login++;
		
		return form[3]->input.inputUnion.button.id;
	} else {
		shared_memory_struct->n_login++;
		shared_memory_struct->login_success = false;

		return NULL;
	}
}


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
extern const char* UIDialogDisplay(UIDIALOG *dialog, struct formsElement **form, enum dialogStyle style, UIDIALOG *parent, const char *window_title, const char *default_response, unsigned int timeout, const char *timeout_response) {
	printf("UIDialogDisplay\n");
	return NULL;
}


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
extern const char* UIDialogDisplayWMClass (UIDIALOG *dialog, struct formsElement **form, enum dialogStyle style, UIDIALOG *parent, const char *window_title, const char *default_response, unsigned int timeout, const char *timeout_response,
                                           const char *wmclass_name, const char *wmclass_class) {
	printf("UIDialogDisplayWMClass\n");
	return NULL;
}


/** @brief Any UI initialisation required to be called prior to 
 *  UIDialogDisplay() should be run in here.
 *
 *  When a process utilising the UI Dialog library already has UI initialised
 *  this function may not need to be called.
 *
 * @param dialog        Is a pointer to a visible UIDialog displayed by calling
 *                      UIDialogDisplay with the given UIDIALOG memory block.
 */
extern void UIDialogClose(UIDIALOG *dialog) {
	printf("UIDialogClose\n");
	if (shared_memory_struct->n_login == 1) {
			shared_memory_struct->login_success = true;
			shared_memory_struct->n_login = 0;
	}

	shared_memory_struct->terminated = true;
}

/** @brief Any UI Deinitialisation required to tidy up after using the
 *  UIDialogLib.
 */
extern void UIDialogDeInit(void) {
	printf("UIDialogDeInit\n");
}
