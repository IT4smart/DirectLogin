/******************************************************************************
 *
 *    Name: UIDialogLibUtil.h
 *
 *    $Id: //icaclient/unix13.3/client/unix/UIDialogLib/UIDialogLibUtil.h#1 $
 *
 *    Purpose: UI Dialog Library Util API header.
 *
 *    Copyright 2013-2014 Citrix Systems, Inc. All rights reserved.
 *
 *****************************************************************************/

#ifndef UI_DIALOG_LIB_UTIL_H
#define UI_DIALOG_LIB_UTIL_H

#ifdef __cplusplus
extern "C" {
#endif
/** @brief UIDialogVersion() returns the UIDialogLib major & minor version
 *         numbers. 
 * @param [out] major   The major version number.
 * @param [out] minor   The minor version number.
 */
extern void UIDialogVersion(unsigned int *major, unsigned int *minor);

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
extern char* UIDialogMnemonicAtChar(char *mnemonicString, const char marker);

#ifdef __cplusplus
} /* End extern "C". */
#endif

#endif /* ! UI_DIALOG_LIB_UTIL_H */


