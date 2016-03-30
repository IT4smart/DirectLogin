/******************************************************************************
 *
 *
 *    $Id: //icaclient/unix13.3/client/unix/test/UIDialogLibGTK/main.c#1 $
 *
 *    Purpose: Example file for calling the UI Dialog Library.
 *
 *    Copyright 2013 Citrix Systems, Inc. All rights reserved.
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "UIDialogLibCall.h"


/*
The Dialog to be displayed:

########################################
#                                      #
#     Please log on to CtxSrv          #
#                                      #
#               ___________________    #
#     Username |___________________|   #
#               ___________________    #
#     Password |___________________|   #
#      _                               #
#     |_| Remember my password         #
#______________________________________#
#               ________    ________   #
#              |_Cancel_|  |_Log_On_|  #
#                                      #
########################################
*/


int main(int argc, char *argv[])
{
    const char *result;
    char *icaroot;
    UIDIALOG *dialog;

    struct formsElement heading =   {
                                        {L_Heading, "Please log on to CtxSrv", NULL},
                                        {
                                            I_None,
                                            NULL,
                                            FALSE,
                                            {{ 0 }}}
                                    };

    struct formsElement username =  {
                                        {L_Plain, "Username", NULL},
                                        {
                                            I_Text, 
                                            "Enter your Windows domain username.",
                                            TRUE,
                                            {{
                                                FALSE,
                                                FALSE,
                                                "",
                                                ""
                                            }}
                                        }
                                    };

    struct formsElement password =  {
                                        {L_Plain, "Password", NULL},
                                        {
                                            I_Text,
                                            "This needs to be a secure string with a minimum of 8 character string contaning nomral characters, digits and symbols.",
                                            FALSE,
                                            {{
                                                TRUE,
                                                FALSE,
                                                "",
                                                ""
                                            }}
                                        }
                                    };

    struct formsElement check =     {
                                        {L_Plain, NULL, NULL},
                                        {
                                            I_CheckBox,
                                            "Store the password securely so that it does not require entry each time.",
                                            FALSE,
                                            {
                                                .checkBox = { 
                                                    NULL,                                                
                                                    "Remember my password",
                                                    NULL,
                                                    FALSE
                                                }
                                            }
                                        }                            
                                    };

    struct formsElement cancel =    {
                                        {L_Plain, NULL, NULL},
                                        {
                                            I_Button,
                                            NULL,
                                            FALSE,
                                            {
                                                .button = {"CancelId", "Cancel", NULL}
                                            }
                                        }
                                    };

    struct formsElement logon =     {
                                        {L_Plain, NULL, NULL},
                                        {
                                            I_Button,
                                            NULL,
                                            FALSE,
                                            {
                                                .button = {"logonId", "Log On", NULL}
                                            }
                                        }
                                    };

    struct formsElement padlock =   {
                                        {L_Secure, "Connection is secure", NULL},
                                        {
                                            I_None,
                                            NULL,
                                            FALSE,
                                            {{ 0 }}
                                        }
                                    };

    struct formsElement *form[] =   {
                                        &heading,
                                        &username,
                                        &password,
                                        &check,
                                        &cancel,
                                        &logon,
                                        &padlock,
                                        NULL
                                    };

    /* Add the mnemonics. */
    username.label.mnemonic = username.label.text;
    password.label.mnemonic = password.label.text;
    check.input.inputUnion.checkBox.mnemonic = check.input.inputUnion.checkBox.text;
    logon.input.inputUnion.button.mnemonic = logon.input.inputUnion.button.text;
    cancel.input.inputUnion.button.mnemonic = cancel.input.inputUnion.button.text;

    icaroot = "./UIDialogLib.so";

    /* Load the UI Dialog Library. */ 
    UIDialogLibLoad(icaroot);  

    /* Initialise the UI Dialog Library */
    UI_DIALOG_INIT(icaroot);
    UI_DIALOG_LOOP_INIT(&argc, &argv);

    dialog = UI_DIALOG_ALLOCATE();

    /* Display UI */
    result = UI_DIALOG_DISPLAY(dialog, form, S_None, NULL, "Citrix Receiver", "logonId", 10, "CancelId");

    /* Close the dialog. */
    UI_DIALOG_CLOSE(dialog);

    free(dialog);

    printf("Username=%s\n", username.input.inputUnion.textBox.text);
    printf("Password=%s\n", password.input.inputUnion.textBox.text);
    
    free((void *) username.input.inputUnion.textBox.text);
    free((void *) password.input.inputUnion.textBox.text);

    printf("Received the following id=%s\n", result);
    return 0;
}
