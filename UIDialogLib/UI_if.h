/******************************************************************************
 *
 *    Name: UI_if.h
 *
 *    $Id: //icaclient/unix13.3/client/unix/inc/UI_if.h#1 $
 *
 *    Purpose: Define the plugin UI interface used to display Linux Client UI
 *
 *    Copyright 2011-2015 Citrix Systems, Inc. All rights reserved.
 *
 *****************************************************************************/

#ifndef UI_IF_H
#define UI_IF_H

/* Enum specifying all the different error/info dialogue types. */

typedef enum _EIDialogType {
   EI_DIALOG_ERROR,
   EI_DIALOG_INFO,
   EI_DIALOG_INFO_TEXT,
   EI_DIALOG_QUESTION,
   EI_DIALOG_RECNX,
   MAX_DIALOG_TYPES
} EIDialogType;

/* List of the buttons for use within the UI */

typedef enum _button_type {
    B_NULL, /* No button */
    B_OK,
    B_CANCEL,
    B_QUIT,
    B_ALLOW,
    B_DENY,
    B_LOGOFF,
    B_DISCONNECT,
    B_RECONNECT,
    B_READ,
    B_WRITE,
    B_RESTART,
    B_SHOW_OPTIONS,
    B_YES,
    B_NO,
    B_ACCEPT
} BUTTON_TYPE;

/* List of button text one for each BUTTON_TYPE enum. */

extern char* buttonTextList[];

/* For dialogues with more UI elements than just a message and buttons,
 * an array of structures defines the element type, label and intial value,
 * as well as returning the new value.
 */

/* Enum specifying the element and type of value held in the union in
 * dialogExtra struct (below).
 */

enum dialogExtraTag {
    endTag = 0,         /* End of the array. */
    boolTag,            /* Check box or similar. */
    intTag,             /* Spin box or similar. */
    charTag,            /* Text input field. */
    bodyTextTag,        /* Just some text (passed as label). */
    separatorTag,       /* Draw a separator. */
};

/* Struct used by dialog box functions if extra data needs to be returned. */
struct dialogExtra {
    enum dialogExtraTag  tag;           /* IN param: set by the caller */
    char                *widgetLabel;   /* IN param: set by the caller */
    union {                             /* IN/OUT: set by caller,
                                         * new values returned.
                                         */
        BOOLEAN     b;
        int         i;
        char       *s;  /* Function must allocate, caller must free it. */
    }                    data;
};

/* structs used for forms dialog elements */

enum dialogStyle {
    S_None = 0,
    S_Error,
    S_Warning,
    S_Information,
    S_Security,
    S_YesNo,
    S_Reconnect,
    S_Flash,
    S_Progress
};

enum labelType  {
    L_Plain = 0,
    L_Heading,
    L_Information,
    L_Warning,
    L_Error,
    L_Confirmation,
    L_Secure,
    L_Unsecure
};

enum inputType {
    I_None = 0,      /* No element. */
    I_Text,          /* A text entry box. */
    I_Label,         /* Text label. */
    I_CheckBox,      /* A check box. */
    I_RadioButton,   /* A set of radio buttons. */
    I_ComboBox,      /* A ComboBox. Allowing the selection of a single value from a list. */
    I_MultiComboBox, /* A ComboBox where multiple entries can be selected. */
    I_Button,        /* A button. */
    I_LinkButton,    /* Functions the same as button but looks like a hyperlink. */
    I_Expander,      /* An expandable and collapsible element to contain further elements. */
    I_Scroller,      /* A scrollable window to contain further elements. */
    I_SelectionTable,/* A table of selectable formElements. */
    I_ButtonBox      /* A button box. */
};

struct textBox {
    BOOLEAN secret;             /* This text is secret and should be rendered in a hidden manner. */
    BOOLEAN readOnly;           /* This text should be read only. */
    const char *text;           /* The initial text and return text. */
    const char *constraints;    /* Input validation constraints. */
};

/* This offers a basic text string to be used for selection. */
struct selection {
    const char *id;             /* The id of the selection. */
    const char *text;           /* The text to render against this selection. */
    const char *mnemonic;       /* Pointer within the text string to the mnemonic character. */
    BOOLEAN select;             /* Whether the selection is selected or not. */
};

/* This offers to nest a formsElement for each selection. */
struct selectionElement {
    const char *id;             /* The id of the selection. */
    struct formsElement **elements;
    BOOLEAN select;             /* Whether the selection is selected or not. */
};

struct button {
    const char *id;             /* The id of the button. */
    const char *text;           /* The text to render on the button. */
    const char *mnemonic;       /* Pointer within the text string to the mnemonic character. */
};

/* Specifies a button box which has potentially a set of primary and secondary
   buttons. primary and secondary are NULL terminated lists of buttons or NULL
   if the button group is not requried. */
struct buttonBox {
    const struct button **primary;      /* The primary set of buttons. */
    const struct button **secondary;    /* The secondary set of buttons. */
    const struct button *focus;         /* The button to focus on if the initialFocus is within the buttonBox. */
};

struct formsElement {
    struct label {
        enum labelType type;
        const char *text;
        const char *mnemonic;   /* Pointer within the text string to the mnemonic character. */
    } label;

    struct input {
        enum inputType type;
        const char *assistiveText;
        BOOLEAN initialFocus;           /* The forms element to have input focus initially. */
        union inputUnion {
            struct textBox textBox;
            struct label label;
            struct selection checkBox;
            struct selection **radioButton;
            struct selection **comboBox;
            struct selection **multiComboBox;
            struct button button;
            struct button linkButton;
            struct formsElement **expander;
            struct formsElement **scroller;
            struct selectionElement **selectionTable;
            struct buttonBox buttonBox;
        } inputUnion;
    } input;
};

#endif /* UI_IF_H */
