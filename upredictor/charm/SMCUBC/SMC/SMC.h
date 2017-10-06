/*
SMC.h
Thierry Moszkowicz May 2012
*/

//Description: 
//
// This is the base class for the SMC modules: Client and Server.
// 
//


#ifndef SMC_LIB_H
#define SMC_LIB_H

#include "DirectLink/DirectLink.h"

namespace SMC {
   class CSMC : public DirectLink::CDirectLink
   {
   public:
      inline CSMC() {}
      inline ~CSMC() {}
   };
} // End namespace SMC

#endif //SMC_LIB_H