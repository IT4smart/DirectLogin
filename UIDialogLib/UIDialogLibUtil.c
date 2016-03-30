/******************************************************************************
 *
 *    Name: UIDialogLibUtil.c
 *
 *    $Id: //icaclient/unix13.3/client/unix/UIDialogLib/UIDialogLibUtil.c#1 $
 *
 *    Purpose: A generic implementation of UI Dialog Library utility functions.
 *
 *    Copyright 2013-2014 Citrix Systems, Inc. All rights reserved.
 *
 *****************************************************************************/

#include <string.h>

#include "UIDialogLib.h"
#include "UIDialogLibUtil.h"

/*****************************************************************************/
/*         Implementations on the UIDialogLibUtil external functions.        */
/*****************************************************************************/

/** @brief UIDialogVersion() returns the UIDialogLib major & minor version
 *         numbers. 
 * @param [out] major   The major version number.
 * @param [out] minor   The minor version number.
 */
void UIDialogVersion(unsigned int *major, unsigned int *minor)
{
    *major = UIDIALOG_MAJOR;
    *minor = UIDIALOG_MINOR;
}

/** @brief UIDialogMnemonicAtChar() takes a mnemonicString with marker 
 *  characters indicating the mnemonic and what the mnemonic marker is. 
 *  Both GTK+ and Qt do this, using an '_' and '&' respectively.
 *  The UIDialogMnemonicAtChar() uses this information to strip the mnemonic
 *  markers from the passed in string and return a pointer to the first
 *  mnemonic character.
 * @param mnemonicString    The mnemonicString to process.
 * @param marker            The mnemonic marker character.
 * @return  Returns a pointer to the mnemonic character within the updated
 *          mnemonicString. If no mnemonic is found NULL is returned.
 */
/* UIDialogMnemonicAtChar() searches a given mnemonicString for the mnemonic
   marker character. Both GTK+ and Qt do this, using an '_' and '&'
   respectively. Treat a double marker character as a single marker character.
   This is certainly the case in GTK+ not 100% sure in Qt. */
char* UIDialogMnemonicAtChar(char *mnemonicString, const char marker)
{
    char *mnemonic = NULL;
    char *iter = mnemonicString;
    int length = strlen(mnemonicString) + 1; /* Plus 1 for NULL terminator. */

    /* Keep searching until there is no more string. */
    while (iter && (iter = strchr(iter, marker)) != NULL)
    {
        /* Remove the marker character. */
        memmove(iter, iter + 1, length - (iter - mnemonicString) - 1);

        /* Check if the next character is not another marker. */
        if (mnemonic == NULL && iter[0] != marker)
            mnemonic = iter;

        iter++; /* Skip the next character after a marker. */           
    }

    return mnemonic;
}

