/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/* atom list for CSS pseudo-classes */

#ifndef nsCSSPseudoClasses_h___
#define nsCSSPseudoClasses_h___

#include "nsStringFwd.h"

// The following two flags along with the pref defines where this pseudo
// class can be used:
// * If none of the two flags is presented, the pref completely controls
//   the availability of this pseudo class. And in that case, if it has
//   no pref, this property is usable everywhere.
// * If any of the flags is set, this pseudo class is always enabled in
//   the specific contexts regardless of the value of the pref. If there
//   is no pref for this pseudo class at all in this case, it is an
//   internal-only pseudo class, which cannot be used anywhere else.
#define CSS_PSEUDO_CLASS_ENABLED_MASK                  (3<<0)
#define CSS_PSEUDO_CLASS_ENABLED_IN_UA_SHEETS          (1<<0)
#define CSS_PSEUDO_CLASS_ENABLED_IN_CHROME             (1<<1)
#define CSS_PSEUDO_CLASS_ENABLED_IN_UA_SHEETS_AND_CHROME \
  (CSS_PSEUDO_CLASS_ENABLED_IN_UA_SHEETS | CSS_PSEUDO_CLASS_ENABLED_IN_CHROME)

class nsIAtom;

class nsCSSPseudoClasses {
public:

  static void AddRefAtoms();

  enum Type {
#define CSS_PSEUDO_CLASS(_name, _value, _flags, _pref) \
    ePseudoClass_##_name,
#include "nsCSSPseudoClassList.h"
#undef CSS_PSEUDO_CLASS
    ePseudoClass_Count,
    ePseudoClass_NotPseudoClass /* This value MUST be last!  SelectorMatches
                                   depends on it. */
  };

  static Type GetPseudoType(nsIAtom* aAtom,
                            bool aAgentEnabled, bool aChromeEnabled);
  static bool HasStringArg(Type aType);
  static bool HasNthPairArg(Type aType);
  static bool HasSelectorListArg(Type aType) {
    return aType == ePseudoClass_any;
  }
  static bool IsUserActionPseudoClass(Type aType);

  // Should only be used on types other than Count and NotPseudoClass
  static void PseudoTypeToString(Type aType, nsAString& aString);

private:
  static uint32_t FlagsForPseudoClass(const Type aType);
};

#endif /* nsCSSPseudoClasses_h___ */
